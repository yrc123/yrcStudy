## Spring Cloud Stream

### 概述

Spring Cloud Stream 是消息中间件组件，可以方便将RabbitMQ、RocketMQ等消息中间件集成到Spring Cloud中。

### 主要概念

#### 应用模型

![带粘合剂的 SCSt](https://gitee.com/lin_haoran/Picgo/raw/master/img/SCSt-with-binder.png)

<center>模型图</center>

- Application Core：包含应用程序提供的消息*生产者*和*消费者*
- inputs、outputs：应用程序通过创建inputs、outputs与Binder的绑定来与外部中间件联系
- Binder：[Destination Binders](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_destination_binders)负责提供与外部中间件集成的组件。Spring Cloud Stream为[Kafka](https://github.com/spring-cloud/spring-cloud-stream-binder-kafka)和[RabbitMQ](https://github.com/spring-cloud/spring-cloud-stream-binder-rabbit)提供了 Binder 实现
- Middleware：外部中间件，如RabbitMQ等

#### 发布-订阅支持

#### 消费者组

### 使用

### Spring Cloud Function支持

从Spring Cloud Stream v2.1开始支持使用`java.util.function`包下的`[Supplier/Function/Consumer]`注入bean的方式来定义*stream handlers*与*sources*。

注意，如果要将符合上述类型的bean用于处理消息，必须提供`spring.cloud.function.definition`[属性](#配置)。因为要避免将非目标的bean用于处理消息。

#### 生产者

`Function`与`Supplier`都可以作为生产者来产生信息。而`Supplier`比较特殊，因为他只有一个`get()`方法，不能从别的信息源来触发，所以框架提供了一种轮询触发的机制。

默认情况下，如果`Supplier`作为output，会每秒触发一次，这个触发间隔可以通过配置文件来调整。

但是在某些情况下，如果`get()`方法产生的两学的消息流而不是单个消息，框架会自动识别并只会被触发一次。

[官方示例](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_suppliers_sources)

#### 消费者

`Function`与`Consumer`都可以作为消费者来消费信息。

[官方示例](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_consumer_reactive)

Destination Binders

Bindings

#### 

### 配置

```properties
spring.cloud.function.definition=var1;var2
```



### 使用实例

### 遇到的问题

#### 依赖重复冲突

解决方法，更改maven以及spring-cloud依赖版本

```xml
	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>2.4.4</version>
		<relativePath/> <!-- lookup parent from repository -->
	</parent>
	<properties>
		<java.version>11</java.version>
		<spring-cloud.version>2020.0.2</spring-cloud.version>
	</properties>

```

