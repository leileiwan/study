# 监控快速迭代过程问题梳理

## 首次部署监控环境

1、部署prometheus、AlertManager、Grafana

（1）提前准备好编译后的二进制文件，系统版本最好一致

（2）prometheus 配置文件可以体检添加ALertManager，所有的报警规则（报警规则的分组设计：需要花时间，主要是将不同类型报警发送给不同的人）

（3）AlertManager 发送报警的对象可以提前固定死

（4）Grafana 配置文件 （json文件）

2、以上可以通过脚本集中部署完成，但是部署之后一定要进行测试


## 新exporter迭代

1、代码开发
	业务过程不可避免，但是我们可以做一个Exporter开发模板

2、部署


3、修改配置文件，prometheus


## Grafana 展示
对于自定义开发的Exporter展示，需要设计（耗时）

## 网络环境
OpenStack 端口策略

Linux 系统防火墙


## 重点解决问题

1、报警规则规范化分组，一是去重，二是分发不同人

2、开发Exporter工作量，开发模板最好能固定好

3、Grafana展示，自定义Exporter展示

4、新Exporter配置文件添加（prometheus.yaml,rules.yml,alertmanager.yml,grafana展示）

对于Exporter的迭代，建议先做一份需求调研，先将竟可能将Exporter的功能提前开发好。













	
		










