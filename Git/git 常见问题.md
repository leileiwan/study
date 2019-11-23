# 1. process 
* gernarate ssh key
```
ssh-keygen
```

* add ssh pub key to github 

* test ssh key add result
```
ssh -T git@github.com

if return You've successfully authenticated,But GitHUb does not provice shell access  --means your process success
```

# 2. some Probles

* problem: when you finsh last step,you can git clone the responsity.But when you use git push,you must input github usename and password,which is much unconvenint.

* reason: git clone default use https protocol,not ssh.

* solution:
    * use ssh protocal:git remote set-url origin git@github.com:username/repo.git
    * add local cache to store identify:
    ```
    git config credential.helper store
    git push https://github.com/owner/repo.git
    git config --global credential.helper 'cache --timeout 7200'(the cache timeout is 7200 seconds)
    ```

# 3. 怎样算contribution
提交将出现在您的贡献图上，如果它们满足所有以下条件：
    * 用于提交的电子邮件地址是与您 GitHub 帐户相关联
    * 提交是在一个独立的库，不是 fork 来的库
    * 提交是在库的默认分支master。
    * 一定要注意邮箱和账号(字符串不要引号)
        * git config user.name XXX //绑定用户名
        * git config user.email XXX //绑定邮箱
    * git log 查看提交的名字和邮箱
    ![](./images/2019-11-23-22-04-33.png)
