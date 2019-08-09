[toc]
# 1. 背景
* wine 主要目的是在Linux（Uninx）上运行windows程序
* wine不是模拟器。利用API转换技术，使得Windows调用Windows内核接口转化成调用Linux内核接口。
* wine 并不能运行所有Windows程序。会遇到很多适配问题，也会出现较多的bug。


# 2. Wine系统结构

* 本质上，wine就是Windows应用软件和Linux内核之间的适配层。
* Wine 本省作为一个进程和一组动态链接库在系统中存在。

* Wine GUI界面依赖X11（X11drv和X11服务组成）
    * x11drv 作为wine和X11之间界面。
    * X11 本身存在，因为Unix和Unix衍生系统都是依赖X11服务的。Wine本身和X11服务存在无关。

* Wine 启动程序至少有三个进程在运行
    * 应用进程本身。
        * 所有DDL调用都在该经常上下文中调用
        * 该进程需要Wine或者Wine间接提供的其它服务(特别是内核)，该进程往往通过Wine提供的各种静态链接库逐层下调。
        * wine 内部，该进程需要通过socket或者pipe和wine进程通信，已接受服务进程的管理和协调。
        * 另一方面，通过x11drv通过别的socket与X11服务进行通信，向其发送图形界面和鼠标键盘请求
    
    * Wine进程
        * Windows进程间通信和同步手段
        * Windows进程和线程、注册表、文件、Win32各种对象管理
    
    * X11服务
        *图形显示和鼠标键盘输入
    

Note:总的来说，Windows程序需要通过Wine和X11进程通信。Wine主要负责进程管理和交互（Windows内核作用），X11主要负责图形。结构图如下（本质上Windows程序直接交互的都是Wine提供的各种动态链接库）

![2019-08-08-09-04-12.png](./images/2019-08-08-09-04-12.png)


Note：其实在运行Windows程序时，一开始运行的不是Windows程序本身，而是先用Wine启动一个进程，然后使用wine启动Windows程序。


## 2.1 wine 进程

### 2.1.1 wine为Windows进程提供的函数指针
* windows 程序和wine需要通过socket和pipe进行交互。可以理解wine为Windows程序提供RPC（跨进程系统调用）。有下面Wine提供的函数指针接口可以看出，基本上包含各种系统调用函数。

```
static const req_handler req_handlers[REQ_NB_REQUESTS] =
{
(req_handler)req_new_process,
(req_handler)req_new_thread,
(req_handler)req_terminate_process,
(req_handler)req_terminate_thread,
......
(req_handler)req_load_dll,
(req_handler)req_unload_dll,
......
(req_handler)req_create_event,
(req_handler)req_create_mutex,
(req_handler)req_create_semaphore,
......
(req_handler)req_create_file,
(req_handler)req_alloc_file_handle,
(req_handler)req_get_handle_fd,
(req_handler)req_flush_file,
(req_handler)req_lock_file,
(req_handler)req_unlock_file,
......
(req_handler)req_create_socket,
(req_handler)req_accept_socket,
(req_handler)req_set_socket_event,
(req_handler)req_get_socket_event,
(req_handler)req_enable_socket_event,
(req_handler)req_set_socket_deferred,
......
(req_handler)req_open_console,(req_handler)req_read_console_input,
(req_handler)req_write_console_output,
......
(req_handler)req_output_debug_string,

(req_handler)req_continue_debug_event,
(req_handler)req_debug_process,
(req_handler)req_debug_break,
......
(req_handler)req_set_key_value,
(req_handler)req_get_key_value,
(req_handler)req_load_registry,
......
(req_handler)req_create_timer,
(req_handler)req_open_timer,
(req_handler)req_set_timer,
(req_handler)req_cancel_timer,
......
(req_handler)req_get_msg_queue,
(req_handler)req_send_message,
(req_handler)req_get_message,
......
(req_handler)req_create_window,
(req_handler)req_link_window,
(req_handler)req_destroy_window,
(req_handler)req_set_foreground_window,
(req_handler)req_set_focus_window,
(req_handler)req_set_global_windows,
...... 共有将近 200 个函数
}
```


### 2.1.2 wine程序主函数逻辑结构
* 函数进程主题是server/fd.c中无限循环main_loop()
* 这和循环通过poll（）函数监听已经建立的所有socket和pipe。当从某个端口监听到消息时间时，就通过fd_poll_event处理消息事件。



```
[main() > main_loop()]
void main_loop(void)
{
    ......
    while (active_users)
    {
        timeout = get_next_timeout();
        if (!active_users) break; /* last user removed by a timeout */
        ret = poll( pollfd, nb_users, timeout );
        if (ret > 0)
        {
            for (i = 0; i < nb_users; i++)
            {
                if (pollfd[i].revents)
                {
                    fd_poll_event( poll_users[i], pollfd[i].revents );
                    if (!--ret) break;
                }
            }
        }
    }
}
```


* 服务进程启动之初只有一个socket（master socket），所有Windows程序运行时开始都是同master socket 通信。当wine收到通信时，就为Windows程序创建一个进程管理块，并为之创建一个Pipe，作为进程和进程之间通信手段（pipe和socket之间的区别在这里就能体现，socket 多对多，效率低。pipe一对一，效率高）.上面代码是通过master_socket_poll_event()中，master_socket的fd_ops数据结构在master_socket_df_ops保证服务进程对此函数调用（server/request.c）


* 之后Windows程序和服务进程通过pip保持通信。对Windows程序发出的请求，服务进程通过fd_poll_event（）函数响应请求。fd_poll_event执行由管道的 fd_ops 数据结构
thread_fd_ops 中给定的函数 thread_poll_event()，这个函数使用请求中使用的调用号（REQ_load_dll）为下标，在上述数组中req_handlers[]内找出相应函数并执行。最后给予请求答复。

* windows在发出请求后就sleep，在收到回复后就恢复执行。

* thread_poll_event 代码如下
    * thread_poll_event
    ```
    [main() > main_loop() > fd_poll_event() > thread_poll_event()]
    /* handle a client event */
    static void thread_poll_event( struct fd *fd, int event ){
        struct thread *thread = get_fd_user( fd );
        assert( thread->obj.ops == &thread_ops );
        if (event & (POLLERR | POLLHUP)) kill_thread( thread, 0 );
        else if (event & POLLIN) read_request( thread );
        else if (event & POLLOUT) write_reply( thread );
    }
    ```
    数据结构 struct fd 中含有具体管道属于(通往)哪一个进程/线程的信息,因此可
以知道是谁发来的请求。在正常的情况下,这个函数会调用 read_request(),我们
只看其主体部分.
    
    * read_request
    ```
    [main() > main_loop() > fd_poll_event() > thread_poll_event() > read_request()]
    /* read a request from a thread */
    void read_request( struct thread *thread )
    {
        ......
        if (!thread->req_toread) /* no pending request */
        {
            if ((ret = read( get_unix_fd( thread->request_fd ), &thread->req,
            sizeof(thread->req) )) != sizeof(thread->req)) goto error;
            if (!(thread->req_toread = thread->req.request_header.request_size))
            {
                        /* no data, handle request at once */
                call_req_handler( thread );
                return;
            }
            if (!(thread->req_data = malloc( thread->req_toread )))
            fatal_protocol_error( thread,
            "no memory for %d bytes request\n", thread->req_toread );
        }
        ......
    }
    ```
    所谓 read_request(),实际上是“读取并执行”请求。具体的执行由
call_req_handler()启动.


    * call_req_handler
    ```
    /* call a request handler */
    static void call_req_handler( struct thread *thread )
    {
        union generic_reply reply;
        enum request req = thread->req.request_header.req;
        current = thread;
        current->reply_size = 0;
        clear_error();
        memset( &reply, 0, sizeof(reply) );
        if (debug_level) trace_request();
        if (req < REQ_NB_REQUESTS)
        {
            req_handlers[req]( &current->req, &reply );
            if (current)
            {
                if (current->reply_fd)
                {
                    reply.reply_header.error = current->error;
                    reply.reply_header.reply_size = current->reply_size;
                    if (debug_level) trace_reply( req, &reply );
                    send_reply( &reply );
                }
                else fatal_protocol_error( current, "no reply fd for request %d\n", req );
            }
            current = NULL;
            return;
        }
        fatal_protocol_error( current, "bad request %d\n", req );
    }
    ```

* 这种RPC调用和动态链接库调用有本质区别。
    * 动态链接库是在进程内调用，性能高，扩张性差。
    * RPC是进程之间调用。性能差，扩展性好，隔离性强。


### 2.1.3 wine和Windows程序之间文件操作

* wine 中使用了大量的宏定义，理解这些宏定义都理解wine代码至关重要。

下面是一段关于文件冲刷代码
```
NTSTATUS
WINAPI NtFlushBuffersFile(HANDLE hFile, IO_STATUS_BLOCK* IoStatusBlock )
{
    NTSTATUS ret;
    HANDLE hEvent = NULL;
    SERVER_START_REQ( flush_file )
    {
        req->handle = hFile;
        ret = wine_server_call( req );
        hEvent = reply->event;
    }
    SERVER_END_REQ;
    ......
    return ret;
}
```

* 这段代码主要内容是，Windows程序向wine请求冲刷文件，wine处理后返回结果
* req、reply分别代码请求和返回，wine_server_call代表wine处理函数。
* SERVER_START_REQ、SERVER_END_REQ是两个宏定义

```
#define SERVER_START_REQ(type) \
do { \
struct __server_request_info __req; \
struct type##_request * const req = &__req.u.req.type##_request; \
const struct type##_reply * const reply = &__req.u.reply.type##_reply; \
memset( &__req.u.req, 0, sizeof(__req.u.req) ); \
__req.u.req.request_header.req = REQ_##type; \
__req.data_count = 0; \
(void)reply ; \
do
```

```
#define SERVER_END_REQ \
while(0); \
} while(0)
```
* 此时首先把发送给服务进程的数据结构视为 struct flush_file_request,而把服务进程的答复则视为 struct flush_file_reply。
* REQ_flush_file,这个常数定义于 server_protocol.h 中的 enum request{}
* 两个宏操作以及夹在其中的代码构成嵌套的 do{ }while(0)语句。总的来说就是完成对flush_file_request 的设置,将其发送给服务进程,等待其答复,并从答复中抽取所需的信息。

宏展开代码如下
```
do {
    struct __server_request_info __req;
    struct type##_request * const req = &__req.u.req. flush_file_request;
    const struct type##_reply * const reply = &__req.u.reply. flush_file_reply;
    memset( &__req.u.req, 0, sizeof(__req.u.req) );
    __req.u.req.request_header.req = REQ_flush_file;
    __req.data_count = 0;
    (void)reply ;do
    {
        req->handle = hFile;
        ret = wine_server_call( req );
        hEvent = reply->event;
    }
    while(0);
} while(0)
```

这里的函数 wine_server_call()就是把调用请求发送给服务进程,并等待服务进
程的回答,其代码在 server.c 中。
```
unsigned int wine_server_call( void *req_ptr )
{
    struct __server_request_info * const req = req_ptr;
    sigset_t old_set;
    sigprocmask( SIG_BLOCK, &block_set, &old_set );
    send_request( req );
    wait_reply( req );
    sigprocmask( SIG_SETMASK, &old_set, NULL );
    return req->u.reply.reply_header.error;
}
```
* 这里的 send_request()将调用请求写入通向服务进程的管道,当服务进程接受到调用请求时会根据调用号从函数指针数组
req_handlers[ ]中找到相应的指针并加以调用。对于 flush_file,这个指针是
req_flush_file

```
/* flush a file buffers */
DECL_HANDLER(flush_file)
{
    struct fd *fd = get_handle_fd_obj( current->process, req->handle, 0 );
    struct event * event = NULL;
    if (fd)
    {
        fd->fd_ops->flush( fd, &event );
        if ( event )
        {
            reply->event = alloc_handle( current->process, event, SYNCHRONIZE, 0 );
        }
        release_object( fd );
    }
}
```
显然,DECL_HANDLER 是个宏定义,其定义如下:
```
#define DECL_HANDLER(name) \
void req_##name( const struct name##_request *req, struct name##_reply *reply )
```
这样,这个函数经过预处理以后就成为了:
```
void req_flush_file ( const struct flush_file_request *req, struct flush_file_reply
*reply )
{
. . . . . .
}
```
注意 req_flush_file()中的 fd->fd_ops->flush( fd, &event ),这里的函数指针 flush
实际上指向函数 file_flush(),这是由数据结构 file_fd_ops 给定的:
```
static const struct fd_ops file_fd_ops =
{
    file_get_poll_events, /* get_poll_events */
    file_poll_event,/* poll_event */
    file_flush,/* flush */
    file_get_info,/* get_file_info */
    
    file_queue_async, /* queue_async */
    file_cancel_async /* cancel_async */
};

```
我们接着看 file_flush()的代码:
```
[main_loop() > fd_poll_event() > thread_poll_event() > read_request()
> call_req_handler() > req_flush_file() > file_flush()]
static int file_flush( struct fd *fd, struct event **event )
{
    int ret = (fsync( get_unix_fd(fd) ) != -1);
    if (!ret) file_set_error();
    return ret;
}
```
* 这里的 fsync()是 Linux 系统调用,而 get_unix_fd()将代表着 Windows 已打开文件的数据结构 fd 转换成代表着 Linux 已打开文件的“打开文件号”。

完成了所要求的服务以后,程序依次返回到 call_req_handler()中,并在那里调
用 send_reply():
* call_req_handler 是wine服务程序一部分，需要见上一小姐
```
[main_loop() > fd_poll_event() > thread_poll_event() > read_request()
> call_req_handler() > send_reply()]
/* send a reply to the current thread */
static void send_reply( union generic_reply *reply )
{
    int ret;
    if (!current->reply_size)
    {
        if ((ret = write( get_unix_fd( current->reply_fd ),
         reply, sizeof(*reply) )) != sizeof(*reply)) goto error;
    }
    ......
}
```
* 于是,Linux 内核将睡眠中的 Windows 应用进程唤醒,并调度其运行,控制又回到了 Windows 应用进程的手里。
* 显然,凡代码中出现 SERVER_START_REQ 的代码一定是在客户端,而出现DECL_HANDLER 的代码一定是在服务端。


可以看到，文件从刷操作是在Wine服务段执行的，为什么不直接使用动态链接库将Windows文件句柄转换成Linux文件号显得简单明了。这里有作者无可奈何地方，后面有讲解。


# 3. Windows和Linux文件操作

* windows 和linux内核之间并不似简单映射关系。如果真是简单映射，就不可能存在两套内核，兼容内核也不存在意义。

* 两种内核间多功能差异有大有小，比如内存这一块就非常小，但是文件操作这一块非常大。因此，我们应该主要着手从差异很大的文件操作去分析兼容行内核实现。

## 3.1 文件系统在Windows和Linux之间差异
从表面上看,文件操作不外乎打开文件/关闭文件、读、写、移动指针、冲涮
缓冲区,还有就是对文件加锁/解锁这些操作,变也变不到哪儿去。这里面似乎不
会有什么根本的、结构性的差异。但是在实现上，两者之间有着巨大差异。


### 3.1.1 打开文件号
* Linux文件操作标识叫做文件号，是一种文件指针数组的下标。
* Windows 文件标识叫举兵，也是一种对象指针数组下标。

上面两者都是指针数组下边。关键是数组类型不同。
* Linux是文件数组下标（Unix遗传），包括文件和设备。每个进程都有一个文件打开列表。
* Windows标识对象数组下标，除了文件和设备，还包括各种对象（比如PCB进程控制块）。每个进程都有一个打开对象列表。

Linux把设备看成文件。Windows直接包文件看成对象。

### 3.1.2 文件遗传
当一个进程创建一个子进程时,可以将它的一些已打开文件“遗传”给所创建
的子进程。这样,子进程从一开始就取得了对这些文件的访问权和上下文。这一点
上 Windows 和 Linux 都是如此。

* windows
    * 在打开文件是就能设置是否可以讲文件遗传给子进程。
    * 在创建子进程时，可以设定是否将可以遗传的文件遗传给子进程。如果设置为遗传，Windows会扫描父进程对象列表，将可以遗传的表项复制到子进程已打开表项中。
* Linux
    Linux 创建子进程主要分前后两步
    * 首先通过系统调用fork创建一个线程，共享父进程空间和资源。然后通过execve（）将线程变成进程，开始独立拥有空间和资源。如果不做其他设置，这时子进程和父进程资源是完全一致的。
    * 这步实现支持有选择遗传和继承。Linux内核有个struct file_struct有个位图和close_on_exec_init位图中的遗传标志位决定着以打开文件在执行execve（）时遗传与否。应用程序可以通过调用ioctl（）设置一打开文件的遗传位。

于是,Windows 的打开文件系统调用可以这样实现:
```
NtOpenFile()
{
    ......
    fd = open();
    if (允许遗传)
    ioctl(fd, FIONCLEX);
    // exec 时不关闭
    else
    ioctl(fd, FIOCLEX);
    //// exec 时关闭
}
```
Windows 允许在创建子进程时再作一次选择。如果选择不遗传,那
么所有的已打开文件都不遗传。而 Linux 却不提供这一次选择,这就是一项比较显
著的“核内差异”了。

核外补补方案：
```
NtCreateProcess()
{
    ......
    if (不遗传)
    {
        //根据副本 close_on_exec 位图
        for(每个允许遗传的已打开文件)
        ioctl(fd, FIOCLEX);
        //暂时设置成不遗传
    }
    fork()
    if (在父进程中)
    {
        if (不遗传)
        {
            //还是根据副本 close_on_exec 位图
            for(每个允许遗传的已打开文件)
            ioctl(fd, FIONCLEX);
            //恢复原状
        }
    }
    ......
}
```
如果选择不遗传,就在 fork()之前先把有关的已打开文件暂时改成不让遗传,
然后在 fork()以后由父进程把这些已打开文件的遗传控制位复原。这里的问题是允
许遗传的已打开文件可能很多,所以可能要调用 ioctl()很多次。

用 Linux 的系统调用来模拟实现 Windows 的系统调用,就好像是用一种高级语言实现另一种高级语言,这就是一个实例。

相对核外补补，在核内修改相对而言就简单很多。但是修改修改发现越来越像Windows，这就失去了兼容内核意义。

### 3.1.3 文件访问的跨进程复制
Windows文件系统不仅支持遗传，还支持非血缘关系的进程之间的文件复制。Windows 为此提供了一个系统调用 NtDuplicateObject()

```
NTSTATUS
NTAPI
NtDuplicateObject(
IN HANDLE SourceProcessHandle,
IN HANDLE SourceHandle,
IN HANDLE TargetProcessHandle,
OUT PHANDLE TargetHandle OPTIONAL,
IN ACCESS_MASK DesiredAccess,
IN ULONG Attributes,
IN ULONG Options);
```
* windows 调用该函数可以是source 和target进程，也可是第三方进程。
* Linux 管道限制于父进程和子进程之间。而Windows可以调用NtDuplicateObject在任何两进程之间建立管道。
* 如果使用核外补补方式，只能通过文件服务器形式进行复制，wine是这么做的。但是这样也存在很多问题。
    * 本来都在本地，却要走文件服务器，效率低。但是文件操作往往有又是基本操作，对效率要求比较大。
    * wine以牺牲效率为代价死守核外补补策略，导致用户不愿意使用wine。


# 4. Wine 的文件读写

* wine中通过文件服务来实现不同进程之间文件复制。如果不适用任何措施，会有两次缓冲区拷贝，一次是将请求和缓冲区拷贝到内核，一次是将内核数据拷贝到用户区。Linux通过copy_from_user()和copy_to_user()两种方式实现。

* 但是Wine采用了一种比较巧妙方法。通过socket实现文件授权方式。通过sendmsg（）和recvmes（）传递报文同时。将文件操作权限给予接收段，这样客户端就可以直接操作文件。

且看 NtWriteFile()的代
```
[WriteFile() > NtWriteFile()]
NTSTATUS WINAPI NtWriteFile(HANDLE hFile, HANDLE hEvent,
PIO_APC_ROUTINE apc, void* apc_user,
PIO_STATUS_BLOCK io_status,
const void* buffer, ULONG length,
PLARGE_INTEGER offset, PULONG key)
{
    int unix_handle, flags;
    ......
    io_status->Information = 0;
    io_status->u.Status = wine_server_handle_to_fd( hFile, GENERIC_WRITE,
    &unix_handle, &flags );
    if (io_status->u.Status) return io_status->u.Status;
    ......
    if (flags & (FD_FLAG_OVERLAPPED|FD_FLAG_TIMEOUT))
    {
    ......
    }
    if (offset)
    {
        FILE_POSITION_INFORMATION fpi;
        fpi.CurrentByteOffset = *offset;
        io_status->u.Status = NtSetInformationFile(hFile, io_status, &fpi, sizeof(fpi),
        FilePositionInformation);
        ......
    }
    /* synchronous file write */
    while ((io_status->Information = write( unix_handle, buffer, length )) == -1)
    {
        if ((errno == EAGAIN) || (errno == EINTR)) continue;
        if (errno == EFAULT)
        {
            io_status->Information = 0;
             io_status->u.Status = STATUS_INVALID_USER_BUFFER;
        }
        else if (errno == ENOSPC) io_status->u.Status = STATUS_DISK_FULL;
        else io_status->u.Status = FILE_GetNtStatus();
        break;
    }
    wine_server_release_fd( hFile, unix_handle );
    return io_status->u.Status;
}
```
* wine_server_handle_to_fd()与服务进程交互,从服务进程取得对已打开目标文件的访问授权。
* 然后根据几个标志位决定所要求的是异步写还是同步写。实际应用中多数都是同步写,所以我们跳过针对异步写操作的代码。
* 如果是指定了位置的写,那就先要通过 NtSetInformationFile()实现类似于lseek()的操作,我们也把它跳过去。接下来就是 write()
* 注意这就是 Linux 的系统调用 write(),而且这是在客户进程一边直接进行、而不是通过服务进程代理的。最后,还有个对 wine_server_release_fd()的调用,其作用是释放对目标文件的访问权


wine_server_handle_to_fd()代码如下
```
int wine_server_handle_to_fd( obj_handle_t handle, unsigned int access,
int *unix_fd, int *flags )
{
    obj_handle_t fd_handle;
    int ret, fd = -1;
    *unix_fd = -1;
    for (;;)
    {
        SERVER_START_REQ( get_handle_fd )
        {
            req->handle = handle;
            req->access = access;
            if (!(ret = wine_server_call( req ))) fd = reply->fd;
            if (flags) *flags = reply->flags;
        }
        SERVER_END_REQ;
        if (ret) return ret;
        if (fd != -1) break;
```
* 客户进程向wine服务进程发送get_handle_fd请求，wine服务进程接收后调用DECLHADNLER（get_handle_fd）(调用的是Wine提供的函数列表，前面理解一致)，经过预编译处理后就变成req_get_handle_fd(),源码如下。（这里通过宏好像实现类似接口机制，但是针对有必要使用宏吗？）

```
/* get a Unix fd to access a file */
void req_get_handle_fd ( const struct get_handle_fd_request *req,struct get_handle_fd_reply *reply )
{
    struct fd *fd;
    reply->fd = -1;
    if ((fd = get_handle_fd_obj( current->process, req->handle, req->access )))
    {
        int unix_fd = get_handle_unix_fd( current->process, req->handle, req->access );
        if (unix_fd != -1) reply->fd = unix_fd;
        else if (!get_error())
        {
            assert( fd->unix_fd != -1 );
            send_client_fd( current->process, fd->unix_fd, req->handle );
        }
        reply->flags = fd->fd_ops->get_file_info( fd );
        release_object( fd );
    }
}
```
* get_handle_fd_obj() 获取当前进程（客户）所具有的读写权限handler是否有效，来判断是否第一次来访问文件（ req->access 访问文件权限）
* 如果handle有效
    * struct fd: 服务进程已经创建客户进程handler和wine服务器中Unix文件号映射。所以返回指向这个映射关系的结构体指针fd。
    * struct unix_fd: 进一步通过get_handle_unix_fd（）函数取得客户进程到linux中已打开文件号映射。
    * 如果客户进程对此文件的读/写已经不是第一次,那么映射已经建立,unix_fd 就不是-1,于是就把 reply->fd 设置成 unix_fd,作为对客户进程的回答。
    * 如果unix_fd=-1,说明进程和第一次打开文件之间映射并没有创建。但是,只要服务进程已经打开目标文件,则 fd->unix_fd、即目标文件在服务进程中的已打开文件号就不会是-1(意思是绕过了wine服务端，客户端直接和文件交互)。在这种情况下,就通过 send_client_fd()把对这个已打开文件的访问权授予客户进程


Wine 对文件读/写的优化,关键就在这里。
```
[req_get_handle_fd() > send_client_fd()]
/* send an fd to a client */
int send_client_fd( struct process *process, int fd, obj_handle_t handle )
{
    int ret;
    ......
    #ifdef HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS
    msghdr.msg_accrightslen = sizeof(fd);
    msghdr.msg_accrights = (void *)&fd;
    #else /* HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS */
    msghdr.msg_control
    = &cmsg;
    msghdr.msg_controllen = sizeof(cmsg);
    cmsg.fd = fd;
    #endif /* HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS */
    myiovec.iov_base = (void *)&handle;
    myiovec.iov_len = sizeof(handle);
    ret = sendmsg( get_unix_fd( process->msg_fd ), &msghdr, 0 );
    if (ret == sizeof(handle)) return 0;
    ......
}
```
* fd 不是数据结构指针,而是服务进程的一个已打开文件号
* 发送端必须调用sendmsg()（是发送给Windows程序客户端，因为这里wine服务段已经有文件操作权限）,而接收端必须调用 rcvmsg()。才能使用Socket 通信的一个特殊功能把对这个已打开文件的访问权授予对方。

回到 req_get_handle_fd()、即 DECL_HANDLER(get_handle_fd)的代码,下面就没有什么操作了,所以服务进程把 get_handle_fd_reply 数据结构作为响应报文发回给客户进程。注意这个发送与 sendmsg()的区别。前者是通过管道发送,并且此时客户进程也正在这个管道的另一端等待接收。而后者,如果调用了的话,是通过一个 Unix 域的 Socket 发送,但是客户进程此刻还没有企图从 Socket 的另一端接收,发送过去的报文将进入其接收队列。

客户进程受内核调度继续运行之后,首先取得响应报文发回来的打开文件号 fd。
如果 fd 不是-1,那么这就是目标文件在客户进程这一头的 Unix 打开文件号,这就
行了。可是,如果 fd 是-1,那就说明这是本进程第一次企图读/写这个文件,此时
应该从上述的 Socket 获取对此已打开文件的授权。

```
我们继续往下看 wine_server_handle_to_fd()的代码:
[WriteFile() > NtWriteFile() > wine_server_handle_to_fd()]
        /* it wasn't in the cache, get it from the server */
        fd = receive_fd( &fd_handle );
        /* and store it back into the cache */
        ret = store_cached_fd( &fd, fd_handle );
        if (ret) return ret;
        if (fd_handle == handle) break;
        /* if we received a different handle this means there was
        * a race with another thread; we restart everything from
        * scratch in this case.
        */
    }
    /* end for */
    if ((fd != -1) && ((fd = dup(fd)) == -1)) return
    STATUS_TOO_MANY_OPENED_FILES;
    *unix_fd = fd;
    return STATUS_SUCCESS;
}
```
显然,这段代码中 receive_fd()的目的就是从 Socket 获取授权。
```
[WriteFile() > NtWriteFile() > wine_server_handle_to_fd() > receive_fd()]
static int receive_fd( obj_handle_t *handle )
{
    struct iovec vec;
    int ret, fd;
    #ifdef HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS
    struct msghdr msghdr;
    fd = -1;
    msghdr.msg_accrights= (void *)&fd;
    msghdr.msg_accrightslen = sizeof(fd);
    #else /* HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS */
    struct msghdr msghdr;
    struct cmsg_fd cmsg;
    cmsg.len = sizeof(cmsg);
    cmsg.level = SOL_SOCKET;
    cmsg.type = SCM_RIGHTS;
    cmsg.fd= -1;
    msghdr.msg_control= &cmsg;
    msghdr.msg_controllen = sizeof(cmsg);
    msghdr.msg_flags= 0;
    #endif /* HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS */
    msghdr.msg_name= NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov= &vec;
    msghdr.msg_iovlen = 1;
    vec.iov_base = (void *)handle;
    vec.iov_len = sizeof(*handle);
    for (;;)
    {
        if ((ret = recvmsg( fd_socket, &msghdr, 0 )) > 0)
        {
            #ifndef HAVE_STRUCT_MSGHDR_MSG_ACCRIGHTS
            fd = cmsg.fd;
            #endif
            if (fd == -1) server_protocol_error( "no fd received for handle %d\n", *handle );
            fcntl( fd, F_SETFD, 1 ); /* set close on exec flag */
            return fd;
        }
        if (!ret) break;
        if (errno == EINTR) continue;
        if (errno == EPIPE) break;
        server_protocol_perror("recvmsg");
    }
    /* the server closed the connection; time to die... */
    server_abort_thread(0);
}
```
* 每个进程的“打开文件表”的主体是个指针数组,每个表项的下标就是“打开文件号”。如果一个表项代表着一个已打开文件、即一个读/写文件的上下文,这个指针就指向一个 struct file 数据结构。
* 所谓 sendmsg()把对某个已打开文件的访问授权发送过来,实际上就是把这个指针(放在报文的头部作为控制信息)发送了过来。
* 而 rcvmsg(),在接收报文中别的信息(如果有的话)的同时,负责在本进程的“打开文件表”中找到一个空闲的表项,然后把传过来的指针“安装”在这个位置上,并将其下标通过 msghdr、更确切地说是 msghdr.msg_control、传给用户空间。

这样,当客户进程以后使用这个打开文件号来访问目标文件时,内核根据这个指针找到的就是服务进程使用的那个struct file 数据结构(一进入内核,就不存在进程间的边界了)。这也解释了为什么要通过 Unix 域的 Socket 传送这种授权,因为Unix 域 Socket 是用于本机的。而若是网络 Socket,则两个进程不在同一机器上,当然就不能通过指针指到对方的机器上去。

下面的事情很有意思。接着调用的是 store_cached_fd()。顾名思义,这是要建
立一个从 Handle 到打开文件号的便查表,所以说是“缓存的(cached)”。那么这个
便查表在那里呢?初一想应该是在客户进程这一边、即客户进程的用户空间,要不
怎么说是“缓存”呢?我们看看这个函数的代码。

[WriteFile() > NtWriteFile() > wine_server_handle_to_fd() > store_cached_fd()]
inline static int store_cached_fd( int *fd, obj_handle_t handle )
{
    int ret;
    SERVER_START_REQ( set_handle_info )
    {
        req->handle = handle;
        req->flags = 0;
        req->mask = 0;
        req->fd
        = *fd;
        if (!(ret = wine_server_call( req )))
        {
            if (reply->cur_fd != *fd)
            {
                /* someone was here before us */
                close( *fd );
                *fd = reply->cur_fd;
            }
            }else{
                close( *fd );
                *fd = -1;
            }
    }
    SERVER_END_REQ;
    return ret;
}
* 毫无疑问,这是“缓存”在服务进程那一边。为什么不存储在客户端，问题就出在遗传。作为客户进程的一个已打开文件,是有可能需要遗传的。

* 事实上,这个“缓存的”对照表就是前面服务进程那一头通过 get_handle_unix_fd()查找过程中用到的一些数据结构。这也是为什么如果不是第一次访问,服务进程就能找到从<进程,Handle>到目标文件在客户进程中的已打开文件号的映射的原因。
* 在客户进程调用 store_cached_fd()之前,服务进程虽然通过 Socket 向客户进程授权,却无从知道其到达客户进程一边以后被安装在哪一个打开文件号上。现在,通过向服务进程登记,服务进程一边就建立起了这种映射。以后每当客户进程要访问这个文件时,就再通过wine_server_handle_to_fd()查询,就像上面看到的那样;只是那时已经不是第一次,因此就不用那么费事了(不过仍是跨进程的查询)。



