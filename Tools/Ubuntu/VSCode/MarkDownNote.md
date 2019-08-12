[toc]
# default
* ctrl+shift+p run: pugin command

# 1. Install markdown pugin
* install Markdown Preview Enhanced

# 2. Use AutoGit automatic synchronize github  respositories

* install Auto-git(by:auto-git doc in vscode)
```
git init
git remote add origin <url>
git fetch origin
git pull origin master(must success)
git branch --set-upstream-to=origin/master
git config --global credential.helper cache
git config --global user.name "Your Full Name"
git config --global user.email "your@email.com"

Auto-Git: Version // Shows current installed version in a notification box
Auto-Git: Start // Starts the interval and routine
Auto-Git: Stop // Stops the interval and routine
Auto-Git: Restart // Reloads configuration + Stop + Start
```

# 2. Paste image
* apt-get install xclip
* install Paste image
* "ctrl+alt+v" paste image(tip:ctrl+shift+p->paste image)

## 2.1 设置Markdown存储images路径
```
    "pasteImage.path": "${currentFileDir}/images/",
    "pasteImage.forceUnixStyleSeparator": true,
    "pasteImage.prefix": "./",
    "pasteImage.insertPattern": "![${imageFileName}](${imageFilePath}${imageSyntaxSuffix}",
```
但是在Ubuntu中，没有发现setting json入口，因此本人只通过修改窗口中赋值对应的值。

file->preferences->settings->extensions->Paste Image
![2019-08-06-15-53-41.png](./images/2019-08-06-15-53-41.png)


# 3. 自动保存
之前没有设置自动保存，笔记写多了之后就很容易忘记保存，因此还是添加上自动保存功能。

点击左下角设置->点击 settings->点击user的application->点击update做如下设置
![2019-08-12-11-15-02.png](./images/2019-08-12-11-15-02.png)