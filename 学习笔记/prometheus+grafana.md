[toc]

# 概念

​	Prometheus是一个完整的监控和趋势系统，包括基于时间序列数据的内置和主动抓取、存储、查询、图形和警报。

​	在与Grafana集成中，Prometheus更类似于一个**时间序列数据库**。事实上在[Prometheus与其他代替品的比较](https://prometheus.io/docs/introduction/comparison/)中，其也将自身与其他时间序列数据库进行比较。



![普罗米修斯架构](https://gitee.com/lin_haoran/Picgo/raw/master/img/architecture.png)

<center>架构图</center>

​	所以我认为，Prometheus是一个支持数据拉取（包括通过服务发现），警报推送的时间序列数据库。而Grafana更像是一个前端，使用PromQL在Prometheus中查询数据并展示，同时还拓展了其他功能。

# Prometheus

## 安装

### 包管理安装

```shell
#arch系
pacman -S prometheus
```

### 部分启动参数

```shell
#通过添加启动参数选择配置文件位置
--config.file=配置文件地址
```

#### 持久化

- Prometheus 的本地时间序列数据库以自定义、高效的格式将数据存储在本地存储上

- Prometheus的存储数据库默认只保留15天的数据，可以通过启动参数来配置存储的规则

```shell
#配置本地存储的路径
--storage.tsdb.path=data/
#配置删除旧数据的时间，默认15d代表删除15天以前的数据
--storage.tsdb.retention.time=15d
```

​	Prometheus还支持[使用远程数据库存储](https://prometheus.io/docs/operating/integrations/#remote-endpoints-and-storage)，这里不展开

## 配置

### 配置Target

#### 简介

可以通过配置文件来定义要抓取的job和instance，所有抓取到的服务可以在Target页面查看到。

通常，一个instance代表单个进程，而相同instance组成一个job。

![image-20210719141256560](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719141256560.png)

<center>本次demo的例子</center>

同样的，Prometheus也有自己的metrics页面，所以可以开启多个Prometheus来**交叉监控**，提高可用性

#### eureka

##### Prometheus配置

```yml
#可以直接在配置文件底部添加 
- job_name: 'Spring Cloud'
    #配置metrics路径
    metrics_path: '/actuator/prometheus'
    eureka_sd_configs:
      #可以支持设置多个注册中心
      - server: 'http://127.0.0.1:7001/eureka'
      - server: 'http://127.0.0.1:7002/eureka'
```

##### maven项目开启

**要导入的maven依赖**

```xml
<dependency>
    <groupId>io.micrometer</groupId>
    <artifactId>micrometer-registry-prometheus</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```

**项目配置文件**

```properties
management.endpoints.web.exposure.include:*
management.endpoints.enabled-by-default=true
management.endpoint.metrics.enabled=true
management.endpoint.prometheus.enabled=true
management.metrics.export.prometheus.enabled=true
```

#### mysql

##### Prometheus配置

```yaml
  - job_name: 'mysql'
    static_configs:
    #mysqld_exporter的ip及端口，多个exporter可以用","隔开
    - targets: ['127.0.0.1:9104']
```

##### 部署exporter

想要配置一个数据源，一般都是要配置一个外置的*导出器（exporter）*。`exporter`会在目标服务上监控对应中间件等其他服务的指标并暴露一个用来展示`metrics`的接口，而Prometheus会从这个接口拉取数据。

以mysql为例，想要配置一个mysql的数据源，要在目标机器上启动一个`mysqld_exporter`来导出`mysql`的`metrics`。

> mysqld_exporter项目地址：[mysqld_exporter](https://github.com/prometheus/mysqld_exporter)

**配置**

通过以下方法可以快速配置并启动`mysqld_exporter`

1. 编辑配置文件：`.my.cnf`

   ```cnf
   [client]
   user=root
   password=haoran8060
   ```

2. 通过参数启动`mysqld_exporter`

   ```shell
   mysqld_exporter \
   --config.my-cnf:配置文件地址
   ```

更多详细启动参数可以从[mysqld_exporter](https://github.com/prometheus/mysqld_exporter)中查看

**更多exporter**

prometheus还提供很多其他中间件的`exporter`，可以在GitHub上找到

> 更多exporter：[prometheus](https://github.com/prometheus)

### 配置自定义Label

> 默认情况下，当Prometheus加载Target实例完成后，这些Target时候都会包含一些默认的标签：
>
>  上面这些标签将会告诉Prometheus如何从该Target实例中获取监控数据。一般来说，Target以`__`作为前置的标签是在系统内部使用的，因此这些标签不会被写入到样本数据中。不过这里有一些例外，例如，我们会发现所有通过Prometheus采集的样本数据中都会包含一个名为instance的标签，该标签的内容对应到Target实例的`__`address`__`。 这里实际上是发生了一次标签的**重写处理**。
>
> 这种发生在采集样本数据之前，对Target实例的标签进行重写的机制在Prometheus被称为Relabeling。

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/when-relabel-work.png)



```yaml
# The source labels select values from existing labels. Their content is concatenated
# using the configured separator and matched against the configured regular expression
# for the replace, keep, and drop actions.
[ source_labels: '[' <labelname> [, ...] ']' ]

# Separator placed between concatenated source label values.
[ separator: <string> | default = ; ]

# Label to which the resulting value is written in a replace action.
# It is mandatory for replace actions. Regex capture groups are available.
[ target_label: <labelname> ]

# Regular expression against which the extracted value is matched.
[ regex: <regex> | default = (.*) ]

# Modulus to take of the hash of the source label values.
[ modulus: <int> ]

# Replacement value against which a regex replace is performed if the
# regular expression matches. Regex capture groups are available.
[ replacement: <string> | default = $1 ]

# Action to perform based on regex matching.
[ action: <relabel_action> | default = replace ]
```

#### 实例

在本次demo中，添加了一个`app_name`的标签

![image-20210722144002632](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210722144002632.png)

可以看出以eureka作为Target，有很多独有的变量

![image-20210722144218359](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210722144218359.png)

```yaml
  - job_name: 'Spring Cloud'
    scheme: http
    metrics_path: '/actuator/prometheus'
    eureka_sd_configs:
      - server: 'http://127.0.0.1:7001/eureka'
      - server: 'http://127.0.0.1:7002/eureka'
    relabel_configs:
    #数据来源，这里使用了eureka中的application.name
    - source_labels: [__meta_eureka_app_name]
    #映射的Label名
      target_label: app_name
```

<center>demo中的部分配置文件</center>

更多详细内容查看[relabel_config](https://prometheus.io/docs/prometheus/latest/configuration/configuration/#relabel_config)

#### 更多配置

官方文档地址：[CONFIGURATION](https://prometheus.io/docs/prometheus/latest/configuration/configuration/)

## PromQL

Prometheus提供了一种名为（PromQL）的查询语句，可以用户实时选择和聚合时间序列数据。

官方文档：[QUERYING PROMETHEUS](https://prometheus.io/docs/prometheus/latest/querying/basics/)

### 简介

#### 数据类型

PromQL数据类型分为四类

- **Instant vector（瞬时向量）**：一组时间序列，有多个时序序列，但是每一个时序序列只有一个时刻的值

  ![image-20210722150101266](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210722150101266.png)

- **Range vector（区间向量）**：一组时间序列，每一个时序有个一个时间区间的数据

  ![image-20210722150120166](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210722150120166.png)

- **Scalar（标量数据）**：一个简单的数字浮点值

- **String（字符串）**：一个字符串，目前尚未使用

#### 时间序列选择器

##### 瞬时向量选择器

对于向量来说，瞬时向量选择器支持通过在花括号`{}`内的**标签匹配器**来过滤时间序列如：

```PromQL
http_requests_total{job="prometheus",group="canary"}
```

可以过滤出`job`为`prometheus`且`group`为`canary`的时间序列

匹配标签支持始终匹配运算符

- `=`：匹配完全相同的标签
- `!=`：匹配相同的标签
- `=~`：通过正则表达式匹配标签
- `!~`：与正则表达式不匹配的标签

##### 范围向量选择器

通过在末尾添加`[]`来指定时间区间

```PromQL
http_requests_total{job="prometheus"}[5m]
```

##### 时间区间

时间区间为一个数字加上一个单位

- `ms`：毫秒
- `s`：秒
- `m`：分钟
- `h`：小时
- `d`：天
- `w`：周
- `y`：年

时间可以通过串联来组合，如：

```
5h30m
```

#### 运算符

PromQL支持算数二元运算符（`+`，`-`，`*`，`/`，`%`，`^ 幂`）、比较二元运算符（`==`，`!=`，`>`，`<`，`>=`，`<=`）、逻辑二维运算符（`and`，`or`，`unless 补充`）等运算符。

因为Prometheus拥有**向量**和**标量**，所以运算符的运算要区分出**向量**与**标量**的运算

##### 算数二元运算符

- 标量与标量：结果为一个标量
- 向量与标量：运算符作用于向量中的每个数字，结果为向量。例如，如果对向量乘2，那么结果为一个向量，且其中的每个值都乘二。
- 向量与向量：运算符作用于左侧向量中的每个条目以及右侧向量中的[匹配](#向量匹配)的元素。

##### 比较二元运算符

- 标量与标量：必须使用`bool`修饰，结果产生一个标量，值为0（false）或1（true）如

```PromQL
1< bool 2
```

- 向量与标量：运算符运用于向量中的每个值。如果不使用`bool`修饰，结果为`false`的向量会直接被删除，如果使用`bool`修饰，每个向量都会被保存，而向量的值被修改为0（false）或1（true）

```PromQL
#不匹配的向量被去除，结果保留向量原有的值
http_requests_total< 100
#所有向量会被保留，每个向量的值为0或1
http_requests_total< bool 100
```

- 向量与向量：运算符默认充当过滤器，应用于匹配向量。表达式不为真或在表达式的另一侧找不到匹配项的向量元素则被删除，如果用`bool`则会被保留，而向量的值被修改为0（false）或1（true）

```PromQL
#对照查询
process_cpu_usage
#结果和上面的对照组相同
process_cpu_usage== process_cpu_usage
#结果为空
process_cpu_usage< process_cpu_usage
#数量与对照组相同，但是值都为0
process_cpu_usage< bool process_cpu_usage
```

#### <a id="向量匹配">向量匹配</a>

**一对一向量匹配**

在默认情况下，如果两个向量的标签和对应的值相同，则认为他们匹配，可以使用关键字来修改匹配的规则

- `on(<label list>)`：表示只需要列出的标签匹配就认为匹配
- `ignoring(<label list>)`：表示在原有的基础上，即使列出的标签不匹配，也可以认为向量匹配

```PromQL
<vector expr> <bin-op> ignoring(<label list>) <vector expr>
<vector expr> <bin-op> on(<label list>) <vector expr>
```

使用示例查看[官方文档](https://prometheus.io/docs/prometheus/latest/querying/operators/#one-to-one-vector-matches)

**多对一与一对多向量匹配**

**多对一**和**一对多**匹配是指左端或右端的**一个向量元素**可以与另一端的**多个元素**匹配的情况。这必须使用`group_left`或`group_right`修饰符明确请求，其中左/右确定哪个向量的匹配。

```PromQL
<vector expr> <bin-op> ignoring(<label list>) group_left(<label list>) <vector expr>
<vector expr> <bin-op> ignoring(<label list>) group_right(<label list>) <vector expr>
<vector expr> <bin-op> on(<label list>) group_left(<label list>) <vector expr>
<vector expr> <bin-op> on(<label list>) group_right(<label list>) <vector expr>
```



使用示例查看[官方文档](https://prometheus.io/docs/prometheus/latest/querying/operators/#many-to-one-and-one-to-many-vector-matches)

### 使用的语句

下面列出本次demo中各个面板使用的语句

其中展示结果是使用Grafana的图表

#### QPS（1分钟平均）

- 作用：
  1. 展示一分钟内平均Ops/s
- PromQL语句：
  1. `sum by(instance)(rate(http_server_requests_seconds_count{ job="Spring Cloud"}[1m]))`
- 结果展示

![image-20210720100020061](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720100020061.png)

#### 响应时间

- 作用：
  1. 展示各个实例的响应时间
- PromQL语句：
  1. `sum by(instance)(rate(http_server_requests_seconds_sum{job="Spring Cloud", status!~"5.."}[1m]))/sum by(instance)(rate(http_server_requests_seconds_count{job="Spring Cloud", status!~"5.."}[1m]))`
- 结果展示：

![image-20210719103847005](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719103847005.png)

#### 堆内存使用率

- 作用：
  1. 展示jvm堆内存使用率
- PromQL语句：
  1. `sum by(instance)(jvm_memory_used_bytes{job="Spring Cloud", area="heap"})*100/sum by(instance)(jvm_memory_max_bytes{job="Spring Cloud", area="heap"})`
- 结果展示：
- ![image-20210719103907236](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719103907236.png)

#### GC暂停时间

- 作用：
  1. 展示jvm GC暂停时间
- PromQL语句：
  1. `rate(jvm_gc_pause_seconds_sum{job="Spring Cloud"}[1m])/rate(jvm_gc_pause_seconds_count{job="Spring Cloud"}[1m])`
- 结果展示：

![image-20210719144211010](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719144211010.png)

#### 非堆内存使用率

- 作用：
  1. 展示非堆内存使用率
- PromQL语句：
  1. `sum by(instance)(jvm_memory_used_bytes{job="Spring Cloud", area="nonheap"})*100/sum by(instance)(jvm_memory_max_bytes{job="Spring Cloud", area="nonheap"})`
- 结果展示：

![image-20210719103941825](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719103941825.png)

#### CPU使用率

- 作用：
  1. 展示实例的CPU使用率
- PromQL语句：
  1. `process_cpu_usage{job="Spring Cloud"}`
- 结果展示：

![image-20210719104000467](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719104000467.png)

#### 网关请求量

- 作用：
  1. 记录从Zuul网关总的请求量
  2. 记录每个`client`被分摊到的请求量
- PromQL语句：
  1. `sum(increase(http_server_requests_seconds_count{instance=~".*zuul.*"}[30s]))`
  2. `sum by(instance)(increase(http_server_requests_seconds_count{instance=~".*client.*"}[30s]))`

- 结果展示：

![image-20210720100201577](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720100201577.png)

#### 请求错误率

- 作用：

  1. 展示每台实例接收到的请求数

  2. 展示每台实例接收到的请求后出现的错误数
  3. 展示每台实例的错误率

- PromQL语句：

  1. `sum by(instance)(increase(http_request_total[30s]))`
  2. `increase(http_request_error_total[30s])`
  3. `sum by(instance)(increase(http_server_requests_seconds_count[30s]))/(increase(http_request_total[30s])+(increase(http_request_total[30s])  == bool 0 ))*(increase(http_request_total[30s])!=bool 0)*100`

- 备注：

  1. `http_request_total`与`http_request_error_total`为自定义的指标，具体查看[Spring Boot自定义指标](#Spring Boot自定义指标)
  2. 第三条语句是为了避免除零，所以才这么复杂。因为错误率是$\frac{请求错误数}{请求数}$，如果没有请求，就会出现除零，导致图表连线不连续，具体查看[除零问题](#除零问题)

- 结果展示：

![image-20210719145135247](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719145135247.png)

#### 在线微服务

- 作用：
  1. 展示微服务的在线情况
- PromQL语句：
  1. `up{job="Spring Cloud"}`
- 结果展示：

![image-20210719104729254](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719104729254.png)

#### 在线服务器数量

- Spring Boot自定义指标作用：

  1.展示微服务在线数

- PromQL语句：

  1. `sum(up{job="Spring Cloud"})`

- 结果展示：

![image-20210719104750145](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210719104750145.png)

## <a id="Spring Boot自定义指标">Spring Boot自定义Metrics</a>

### 概述

https://www.cnblogs.com/yunlongn/p/11343848.html

https://www.cnblogs.com/cjsblog/p/11556029.html

Micrometer

### 几个类

```java
    public Counter counter(String name, String... tags) {
        return counter(name, Tags.of(tags));
    }
    public static Tags of(@Nullable String... keyValues) {
        ...
        if (keyValues.length % 2 == 1) {
            throw new IllegalArgumentException("size must be even, it is a set of key=value pairs");
        }
        ...
    }

```

#### Meter

> `Micrometer`提供一系列原生的`Meter`，包括`Timer `, `Counter` , `Gauge `, `DistributionSummary `, `LongTaskTimer` , `FunctionCounter` , `FunctionTimer `, `TimeGauge`。不同的meter类型导致有不同的时间序列指标值。例如，单个指标值用Gauge表示，计时事件的次数和总时间用Timer表示

`Meter`由`MeterRegistry`生成

#### Tag

> `Tag`(标签)是`Micrometer`的一个重要的功能，严格来说，一个度量框架只有实现了标签的功能，才能真正地多维度进行度量数据收集。Tag的命名一般需要是有意义的，所谓有意义就是可以根据Tag的命名可以推断出它指向的数据到底代表什么维度或者什么类型的度量指标。

如这样声明一个`Counter`

```java
registry.counter("test", "test_tag", "tag_info");
```

最后显示出的指标就是

```
test_tag_total{tag_name="tag_info"}
```

#### MeterRegistry

- `MeterRegistry`
  - 是一个抽象类，定义了获取一系列预制的`Meter`的方法

- `PrometheusMeterRegistry`
  - 实现了`MeterRegistry`抽象类

- `CompositeMeterRegistry` 
  - 使用了组合模式，实现了`MeterRegistry`抽象类
  - 内置了一个`Set<MeterRegistry> registries`，可以向里头添加删除`MeterRegistry`

#### Metrics

是全局的`MeterRegistry`，使用方式更加简单便捷，因为一切只需要操作工厂类Metrics的静态方法，如

```java
Metrics.addRegistry(new SimpleMeterRegistry());
Counter counter = Metrics.counter("counter", "tag-1", "tag-2");
counter.increment();
```

上面就是一个最简单的使用例，代码创建了一个`Counter`，如果使用了`Prometheus`的包，那么就会自动显示到`metrics`页面，并且在`Prometheus`可以直接查看到

内部有一个静态的`CompositeMeterRegistry`，如果导入的是`Prometheus`的包，那么Spring会自动注入一个`PrometheusRegistry`的实例

![image-20210720150921272](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720150921272.png)

<center>Spring会自动注入的实例</center>

### 实例

通过自定义指标来展示每个模块的最大实例数（Eureka为注册中心）

```java
package com.example.server2.service;
import ...

@Service
public class CountService {

    //定时查询最大微服务数
    @Scheduled(cron = "*/10 * * * * *")
    public void getAllService(){
        //获取已经注册过的所有微服务信息
        PeerAwareInstanceRegistry registry = EurekaServerContextHolder.getInstance().getServerContext().getRegistry();
        List<Pair<Long, String>> instancesList = registry.getLastNRegisteredInstances();
        
        //将微服务通过名称来分别计数
        HashMap<String, Integer> map = new HashMap<>();
        for (Pair<Long, String> longStringPair : instancesList) {
            System.out.println(longStringPair.first()+": "+longStringPair.second());
            //从默认传回的字符串中切割出模块名
            String name = getServerName(longStringPair.second());
            map.put(name, map.getOrDefault(name, 0)+1);
        }
        
        //将结果展示为指标，其中指标名为"server_total"，给指标添加了"server_name"的tag来区分不同的模块。
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            Metrics.gauge("server_total", Collections.singleton(Tag.of("server_name", entry.getKey())),entry.getValue());
        }
    }
    
    //获取字符串中的模块名
    private String getServerName(String name){
        int index = name.indexOf('(');
        String s = new String(name.substring(0,index));
        System.out.println(s);
        return s;
    }
}
```

## PushGateway

Prometheus实际上只支持`pull`的方式获取指标数据，如果想要采用`push`的方法推送数据，则要先将数据`push`到PushGateway，之后Prometheus再从PushGateway中拉取数据

[官方文档](https://prometheus.io/docs/practices/pushing/#when-to-use-the-pushgateway)的建议是尽量少使用这种方式来推送数据，因为有以下缺点

- 当通过单个 Pushgateway 监控多个实例时，Pushgateway可能会发生故障并且潜在瓶颈。
- PushGateway中的 `up`状态是在作业推送数据时自动生成，无法监控作业的状态
- PushGateway 可以持久化推送给它的所有监控数据，即使你的监控已经下线，Prometheus 还会拉取到旧的监控数据，除非通过api删除

官方推荐仅在运行批处理作业（不会连续运行，抓取困难的作业）的情况下使用。而如果是运行时间**超过几分钟**的批处理作业，官方还是推荐使用基于**拉取**的方式来监控

批处理作业的关键指标有最后一次成功的时间、作业的每个主要阶段所花费的时间、整体运行时间和上次完成作业的时间（成功或失败）

如果是因为防火墙或者NAT导致无法直接获取Target的指标，官方推荐将Prometheus部署在防火墙后，或者使用[PushProx](https://github.com/RobustPerception/PushProx)进行内网穿透

### PushGateway部署

从[GitHub](https://github.com/prometheus/pushgateway)下载Release后直接运行，也支持从docker部署

运行后可以访问到PushGateway的页面（默认地址为[127.0.0.1:9091](127.0.0.1:9091)）：

![image-20210726155211893](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210726155211893.png)

之后在Prometheus中添加PushGateway为Target

```yaml
...
  - job_name: 'pushgateway'
    static_configs:
    - targets: ['localhost:9091']
...
```

在Prometheus中可以查看到PushGateway：

![image-20210726155504787](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210726155504787.png)

### Java使用PushGateway类

这里实现了一个模拟耗时的操作。一个线程累加一个数到100，每次都延迟1s。而另一个线程则定时push数的当前值，时间间隔为1s

```java
import ...

public class Pushgateway {
    public static void main(String[] args) throws IOException {
        //一个计数器，模拟一个耗时操作，当数字到达100就停止
        Count count = new Count();
        //用来定时获取count中的数字，并push到PushGateway上
        Push push = new Push(count);
        
        //启动线程
        Thread t1 = new Thread(count);
        Thread t2 = new Thread(push);
        t1.start();
        t2.start();
    }
    
    static class Count implements Runnable{
        //初始为0
        Integer value=0;

        //获取当前的值
        public Integer getValue() {
            return value;
        }

        //将当前的值加一
        public synchronized void addValue() {
            value = value+1;
        }

        @Override
        public void run() {
           //延迟1秒来模拟耗时操作，当数值达到100时停止
           while(getValue()<100){
               try {
                   Thread.sleep(1000);
               } catch (InterruptedException e) {
                   e.printStackTrace();
               }
               addValue();
           }
        }
    }
    
    static class Push implements Runnable{
        //一个内置Gauge类型的指标，与Counter不同，他的值可以上下浮动
        Gauge duration;
        //上文的Count类
        Count count;
        //PushGateway类，通过ip端口来构造
        PushGateway pg = new PushGateway("127.0.0.1:9091");
        //创建一个注册器
        CollectorRegistry registry = new CollectorRegistry();
        //构造函数，传入一个Count类
        public Push(Count count) throws IOException {
            this.count=count;
            //创建指标，并指定指标的名字和说明信息，并注册到registery上
            duration = Gauge.build()
                    .name("count_now_number").help("一个说明信息，会展示在Prometheus上").register(registry);
        }
        @Override
        public void run() {
            //每秒push一次数据，当数值达到100时停止
            while(count.getValue()<100){
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                //更新数据并将新数据push到PushGateway上
                Integer value = count.getValue();
                duration.set(value);
                try {
                    pg.pushAdd(registry, "test");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
```

#### 结果

![image-20210726155025578](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210726155025578.png)

# Grafana

## 安装

### 包管理安装

```shell
#arch系
pacman -S grafana
```

### 配置文件

可以零配置启动

## 连接数据源

![image-20210720154542225](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720154542225.png)

![image-20210720154602795](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720154602795.png)

直接在页面中填入服务器URL即可

## 图表设置

### Variables

在设置页面中可以设置变量

![image-20210720154802325](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720154802325.png)

设置完成后会在图表界面最上端出现你设置的变量，并且可以修改变量的值

![image-20210720154735265](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720154735265.png)

之后在Grafana的查询语句中可以用`${变量名}`来插入变量的值，如

![image-20210720155127799](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720155127799.png)

但注意，这是Grafana的功能，不是Prometheus的功能，而且目前版本（Grafana 8）中，Alert rules中并**不能使用**变量模板

### 设置Legend

![image-20210720155657219](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720155657219.png)

可以通过Legend来修结果改图表展示的名字

使用`{{tag名}}`可以动态插入tag名

### 导入面板

grafana支持通过url或id导入别人分享的面板

grafana官方仓库有很多别人设置好的面板，可以直接导入使用

![image-20210720155856759](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720155856759.png)

## 警报

在`Grafana 8`之前的版本，`Alert Rule`（警报规则）是与`Panel`（即图表）强依赖的，即`Rules`必须对应一个`Panel`，而一个`Panel`可以有多个`Alert Rule`

在`Grafana 8`开始修改警报模块，但是还是开发版本，要在配置文件（grafana.ini）中添加

```ini
[feature_toggles]
enable=ngalert
```

<hr/>

新版的警报分为`Alert rules`、`Silences`、`Contact points`和`Notification policies`四个部分

- `Alert rules`：警报规则，定义在什么情况下会触发警报。可以添加tag来方便选择对应的警报规则
- `Silences`：屏蔽警报，即在设定的时间内可以屏蔽指定tag（在规则中设定的）的警报
- `Contact points`：接入点，设置接入的警报渠道，支持邮箱、钉钉等
- `Notification policies`：配置警报策略，可以配置默认的接入点，所有的警报都会通知默认的接入点，也可以通过tag、value来分组设置警报策略。‘’

### Alert rules

1. 设置服警报信息

![image-20210720163621238](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720163621238.png)

2. 创建警报规则

注意不能使用模板变量

![image-20210720163632387](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720163632387.png)

其中Grafana 8支持了基于标签的**多维警报**，可以使用**reduce**来创建多维条件，如

![image-20210723134748024](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723134748024.png)

之后再使用条件语句去进行处理

![image-20210723134833853](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723134833853.png)

3. 选择触发的表达式

同样的，使用多维警报也会为每个实例创建一个警报信息

![image-20210723135025090](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723135025090.png)

4. 警报提示的信息

![image-20210720163700771](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720163700771.png)

5. 设置tag，类似于分组

![image-20210720163712221](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720163712221.png)

6. 结果，其中结果格式使用了[消息模板](#消息模板)来自定义格式

![image-20210723135255587](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723135255587.png)



[在此](https://grafana.com/docs/grafana/latest/alerting/unified-alerting/alerting-rules/create-grafana-managed-rule/)查看更多细节

### Silences

设置在什么时段忽略警报，同时可以通过Alert rules中的tag来设置忽略警报的条件

![image-20210720170143060](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720170143060.png)

### Contact points

#### <a id="消息模板">消息模板|Message Template</a>

Grafana 8支持消息模板，基于[Go Template](https://golang.org/pkg/text/template)，可以吧包括触发警告的查询结果等信息进行自定义处理并输出。

更详细信息查看[文档](https://grafana.com/docs/grafana/latest/alerting/unified-alerting/message-templating/)，查看[模板数据](https://grafana.com/docs/grafana/latest/alerting/unified-alerting/message-templating/template-data/)来了解模板中的可用变量

##### 实例

**配置的模板**

![image-20210723135359523](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723135359523.png)

**在连接点中使用模板**

![image-20210723135428100](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723135428100.png)

其中`{{template "Alerts" .}}`中的`test`为`{{define "Alerts"}}`中定义的名称，即为`Alerts`

`Alerting`的值可以在设置Rule的界面中预览

![image-20210723135548819](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210723135548819.png)

#### 连接点|Contact points

可以设置警报的渠道，这里以钉钉为例

##### DingDing

![image-20210720170654126](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720170654126.png)

- Contact point type：警报通知的方式，这里选择钉钉
- Url：钉钉机器人创建给出的url
- MessageType：支持ActionCard 和 link两种
- Message：警报的提示消息

同时记得修改配置文件，不然提示的url打不开`http_port、domain、root_url`

### Notification policies

可以将Alert rules和Contact point通过tag联系在一起

![image-20210720171405748](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210720171405748.png)

## 杂项

### <a id="除零问题">除零问题</a>

因为错误率是$\frac{请求错误数}{请求数}$，如果没有请求，就会出现除零，结果变成`NaN`，导致图表连线不连续

解决方法就是使用一些表达式来规避这些问题，如在上文中的错误率的表达式：

```
sum by(instance)(increase(http_server_requests_seconds_count[30s]))/(increase(http_request_total[30s])+(increase(http_request_total[30s])  == bool 0 ))*(increase(http_request_total[30s])!=bool 0)*100
```

重点在于`(increase(http_request_total[30s])+(increase(http_request_total[30s])  == bool 0 )`，当`(increase(http_request_total[30s])`为0时，`increase(http_request_total[30s])  == bool 0 `的值就为1，相加结果为1，去除了除零的情况