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