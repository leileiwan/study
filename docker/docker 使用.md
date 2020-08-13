# 镜像

# 容器

1、查看容器
docker ps

2、删除容器

docker rm 容器id（强制 -f）

3、删除所有容器

docker rm $(docker ps -aq)

4、停止所有容器

docker stop $(docker ps -aq)






