## Spring Cloud Stream

### 概述

Spring Cloud Stream 是消息中间件组件，可以方便将RabbitMQ、RocketMQ等消息中间件集成到Spring Cloud中。

### 主要概念

#### RabbitMQ的Exchange

![通过交换和队列从发布者到消费者的发布路径](https://www.rabbitmq.com/img/tutorials/intro/hello-world-example-routing.png)

在RabbitMQ中，Exchange是通过指定的规则，将消息路由到对应的Queue

**Exchange模式**

- direct
  - 他是根据`routing_key`来路由消息，只有当路由键（routing_key）完全匹配时，才会将消息加入队列
  - 适用于将消息一对一传输到队列中的情况

![交换根据路由键将消息传递到队列](https://gitee.com/lin_haoran/Picgo/raw/master/img/exchange-direct.png)

- fanout
  - 他将消息路由到所有绑定到他的队列，并忽略路由键
  - 每个绑定的队列都会得到一个消息的副本，适用于广播消息

![交换将消息传递到三个队列](https://gitee.com/lin_haoran/Picgo/raw/master/img/exchange-fanout.png)

- topic
  - 根据路由键将消息路由到匹配的一个或多个队列
  - 适用于应用程序有想要有选择的接收消息的情况
- header
  - 忽略路由键，而是通过headers的属性来匹配队列
  - 只有当headers的值**等于**绑定时匹配的值时，则认为消息匹配
  - 如果可以使用多个headers进行匹配，则可以通过`x-match`参数来指定匹配的规则，如将值设为`any`时，只要有一个匹配的header即认为匹配

一般来说，这几种模式中，fanout的效率最高，因为他不会对路由键进行处理，其次是direct，最差是topic

除此之外还有一个默认交换（Default Exchange）

默认交换是一个没有名称的（名称为空字符串）direct交换。每个创建的队列都会通过一个**与队列名称相同的路由键**自动绑定到默认交换

如声明一个名为`search-indexing-online`的队列时，AMQP 0-9-1 将使用`"search-indexing-online"`作为路由键绑定到`Default Exchange`。因此，使用路由键`"search-indexing-online"`发布到*默认交换*的消息将被路由到`search-indexing-online`队列。换句话说，默认交换使得*消息***看起来**可以直接传递到*队列*，虽然实际上是通过默认交换来实现的。

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

注意，如果要将符合上述类型的bean用于处理消息，必须提供`spring.cloud.function.definition`属性。因为要避免将非目标的bean用于处理消息。

#### 函数绑定名称

如下定义一个函数式的Spring Cloud Function应用

```java
@SpringBootApplication
public class SampleApplication {

	@Bean
	public Function<String, String> uppercase() {
	    return value -> value.toUpperCase();
	}
}
```

> 注意，如果有多个注入的bean，必须要如下配置要识别为绑定到队列的函数bean
>
> ```properties
> spring.cloud.function.definition=var1;var2
> ```
>
> 其中var1、var2都为函数名，多个函数使用`;`来分割
>
> 还可以使用`|`管道来串联函数，如
>
> ```properties
> spring.cloud.function.definition=var1|var2
> ```
>
> 其中var1的输出会作为var2的输入，最后`var1|var2`会被识别为一个函数被绑定到名为类似于`var1Var2`的队列中去

作为一个`Function`类型的函数，它有一个输入和输出。用于命名输入和输出绑定的命名约定如下：

- 输入：`<functionName> + -in- + <index>`
- 输出：`<functionName> + -out- + <index>`

而这个例子中的名称对应如下：

- 输入：`uppercase-in-0`
- 输出：`uppercase-out-0`

其中`fucntionName`为注入bean的函数名，`in`和`out`对应输入输出的队列名，而`index`则是输入输出的索引。因为上文代码是单输入输出的，所以`index`始终为0

可以通过配置文件来自定义绑定名

```properties
spring.cloud.stream.bindings.<bindingName>.destination=myQueue
```

其中`<bindingName>`为上文默认的绑定名，而如果想将上文函数的输入绑定名改为`myQueue`的配置是

```properties
spring.cloud.stream.bindings.uppercase-in-0.destination=myQueue
```

#### 生产者

`Function`与`Supplier`都可以作为生产者来产生信息。而`Supplier`比较特殊，因为他只有一个`get()`方法，不能从别的信息源来触发，所以框架提供了一种轮询触发的机制。

默认情况下，如果`Supplier`作为output，会每秒触发一次，这个触发间隔可以通过配置文件来调整。

但是在某些情况下，如果`get()`方法产生的两学的消息流而不是单个消息，框架会自动识别并只会被触发一次。

在**一个**应用程序中，不同的**生产者**绑定时不能同时拥有相同的`spring.cloud.stream.bindings.<bindingName>.destination`和`spring.cloud.stream.bindings.<bindingName>.group`

[官方示例](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_suppliers_sources)

#### 消费者

`Function`与`Consumer`都可以作为消费者来消费信息。

在**一个**应用程序中，不同的**消费者**绑定时不能同时拥有相同的`spring.cloud.stream.bindings.<bindingName>.destination`和`spring.cloud.stream.bindings.<bindingName>.group`

[官方示例](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_consumer_reactive)

**消费者组**

可以通过配置文件来设置每个消费者所在的消费者组，如果不指定，则会使用随机字符串来作为组名

```properties
spring.cloud.stream.bindings.<bindingName>.group
```

![SCSt组](https://gitee.com/lin_haoran/Picgo/raw/master/img/SCSt-groups.png)

> 每个消费者组都会收到一份消息的副本，但是每个组中的每一条消息只会被一个消费者消费
>
> 默认情况下，当未指定组时，Spring Cloud Stream 会将应用程序分配给一个匿名且独立的单成员消费者组，并且该队列是auto-delete的，该消费者组与所有其他消费者组处于发布订阅关系。

#### 将任意数据发送到output

因为在上文的函数式编程中，我们很难通过如http请求的方式来触发消息，所以可以通过`StreamBridge`来主动的发送消息

```java
@SpringBootApplication
@Controller
public class WebSourceApplication {

	public static void main(String[] args) {
		SpringApplication.run(WebSourceApplication.class);
	}

	@Autowired
	private StreamBridge streamBridge;

	@RequestMapping
	@ResponseStatus(HttpStatus.ACCEPTED)
	public void delegateToSupplier(@RequestBody String body) {
		System.out.println("Sending " + body);
		streamBridge.send("toStream-out-0", body);
	}
}
```

Spring Cloud Stream会生成一个`StreamBridge`的Bean，我们可以直接装配并使用。

但是使用`StreamBridge`有一个问题与函数式绑定不同，使用`StreamBridge`没有对应的函数名，所以也不会生成对应的绑定名称。

解决的方法是在`send(String bindingName)`中指定绑定名称，这个绑定名称的规范和上文的一致。之后要在配置文件中的`spring.cloud.stream.source`指定识别为绑定到队列的名称，在这个例子中为`spring.cloud.stream.source=toStream`。其分割方式与上文的`spring.cloud.function.definition`类似，在此不在赘述。

### 事件路由

[官方文档](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_event_routing)

[StreamBridge 和动态目的地](https://docs.spring.io/spring-cloud-stream/docs/3.1.3/reference/html/spring-cloud-stream.html#_streambridge_and_dynamic_destinations)

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

