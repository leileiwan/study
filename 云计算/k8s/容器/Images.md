# 一、简介

将image关联到pod之前，需要创建image并且push到Registry。

所有容器支持镜像的属性是一致的，包括是由registers和tags（可以docker为模板）


# 二、更新镜像

当我们pull镜像时，如果本地存在该镜像，k8s会停止pull镜像。

如果想强制pull镜像，有如下防范
- 设置 container 的imagePullPolicy标签为 Always
- 删掉imagePullPolicy，使用：latest作为image的 tag。(尽量避免使用latest标签)
- 删掉镜像的imagePullPolicy 和 tag
- enable the AlwaysPullImages admission controller






