<!-- TOC -->

- [1 本地仓库绑定远程仓库](#1-本地仓库绑定远程仓库)
- [2 添加](#2-添加)
- [3 提交](#3-提交)
- [4 分支创建](#4-分支创建)
- [5 **合并分支**](#5-合并分支)

<!-- /TOC -->


# 1 本地仓库绑定远程仓库

        git remote rm origin
        如果本地已经绑定过叫origin的远程厂库，删除远程origin
        
        git remote add origin https://github.com/xiaoluwwwxiaolu/MyMybatisGeneratos.git
        关联新的远程仓库 名字叫origin
        
        git remote
        查看关联的远程分支
        
        git push origin master
        将本地仓库Head区推送到远程厂库的master分支
        
        git clone https://github.com/jinhucheung/milog.git


# 2 添加

        git add file_path
        添加指定的单个文件到缓冲区
        
        git add .
        将当前目录的所有文件到缓冲区

# 3 提交

        git commit -m "提交注释"
        将缓存区所有内容提交到本地仓库
        
         git push origin master
         本地仓库推送到远程仓库
         
# 4 分支创建

        git branch register
        创建本地分支 register
        
        git checkout register
        切换到本地分支 register
        
        git push origin register
        将本地分支推送到远程仓库
        
        git push origin :register
        将远程分支register删除
        
        git branch
        查看分支，带*表示当前所处分支
        
        git branch -d register
        删除指定分支
        
        git log --oneline --graph --decorate --all
        从commit角度来看分支树
        
        git fetch origin
        从远程仓库更新代码
        完成新的分支获取
       
# 5 **合并分支**
      
      5.1 merge合并(当主分支和分支不存在冲突使用)：
      首先切换到主分支
      git merge 分支名称
      
      5.2 rebase合并(当主分支和分支存在冲突使用):
      首先切换到主分支
      git rebase 分支名称
      
      5.3当主干和分支之间内容不一致出现冲突时,并且使用了merge合并，发现报错，然后又rebase一次
      
      5.3.1出现以下类似内容
      <<<<<<< HEAD
      sdfaf
      =======
      fafaf
      afa
      :
      >>>>>>> merge
      
      5.3.2新建了一分支，同时发现不能切换到master，register分支
      
            git log --oneline --graph --decorate --all
            查看commit情况，也可看目前的分支情况
            
            git reflog [show master]
            查看历史分支情况
            
            git reset --hard HEAD@{6}
            回退到历史指定版本
            
            解决提示符 master|REBASE 1/5
            这是由于rebase造成的，表示master还有4个提交等待处理
            git rebase --continue继续进行rebase过程
            git rebase --abort则会推出rebase过程
            git rebase --skip跳过你指定分支的提交
            
            
      
      
    
       
        
    