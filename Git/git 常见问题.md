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

