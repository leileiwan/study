# 1. 背景
默认ctrl+r 只是提示一行，我们系统能有提示多行工具。
zsh 能满足我们的基本要求。

# 2. 安装zsh
参考:
* https://github.com/robbyrussell/oh-my-zsh
* https://github.com/zsh-users/zsh-autosuggestions/blob/master/INSTALL.md

## 2.1 安装zsh并设置主题
* sudo apt-get install fonts-powerline 安装字体
* sh -c "$(wget -O- https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
* vim ~/.zshrc 
  设置ZSH_THEME="agnoster" (设置主题)
* 新打开终端

这部分只是安装zsh，并没有什么很好的提示工具，但是zsh支持很多插件，我们可以安装提示插件
# 3. 安装zsh-autosuggestions
这部分安装了自动提示工具，输入部分字段就能提示history命令。
* git clone https://github.com/zsh-users/zsh-autosuggestions ~/.zsh/zsh-autosuggestions
* source ~/.zsh/zsh-autosuggestions/zsh-autosuggestions.zsh
* new terminal

