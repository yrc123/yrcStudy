# java学习

## Java基础

### 枚举类

```java
public enum Test{Test1, Test2};
```

​	上面的声明定义的是一个类，其枚举的每一个值都是该枚举类

的一个实例，不会再构造新的实例。

- 枚举类继承了Enum类，所以不能再继承其他类。而且枚举类是final的，所以不能再被其他类继承。

- 枚举类在经过编译器编译之后产生的还是一个class文件，因此枚举类虽然语法和普遍类差别很大，但是他还是一个类。
- 如果要在枚举类内声明其他成员，要在最后枚举常量结尾加一个分号。
- 枚举没有构造方法，但是可以自定义自己的方法，同样可以定义一个私有的构造方法。

### I/O流

### 多线程与锁

### 注解与反射

## javaWeb

### Cookie与Session

### 重定向与转发

### MVC三层架构

#### 什么是MVC

| Model                                    | view                       | Cntroller                                        |
| ---------------------------------------- | -------------------------- | ------------------------------------------------ |
| 模型                                     | 视图                       | 控制器                                           |
| 业务处理（业务逻辑）、数据持久层（CRUD） | 展示数据、提供链接发起请求 | 接受用户请求、交给业务层对应代码、控制视图层跳转 |

#### 三者之间的关系图

![image-20200607203007137](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200607202733624.png)

## MyBatis



## Spring

### Spring是什么

​	Spring是一个轻量级、非入侵的控制反转(IOC)和面向切面编程(AOP)的框架。

### Spring组成

![这里写图片描述](https://gitee.com/lin_haoran/Picgo/raw/master/img/20170713150400373.bmp)

### 什么是IOC

#### 为什么要IOC

​	在没有IOC的程序中，各个对象相互合作，最终实现业务。但是这样导致的各个对象相互耦合在一起，如果其中的一个对象出了问题，其他的对象也不能正常工作。

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/30130748-488045b61d354b019a088b9cb7fc2d73.png)

<center>耦合的对象</center>

​	在引入IOC容器之后，各个对象没有了耦合关系，对象的控制权交给了第三方。

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/30131727-a8268fe6370049028078e6b8a1cbc88f.png)

<center>IOC解耦过程</center>

​	在取出IOC容器后，发现各个对象没有了耦合关系，这样我们可以在编写一个对象的时候不需要考虑其他的对象，各个对象之间的依赖降到最低。

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/30132051-58562511cc6541fdb2636081e455d808.png)

<center>对理想的系统</center>

​	而在放到实际的开发之中，在没有引入IOC之前，对象A依赖对象B，那么在对象A创建运行或运行到某一时刻，必须要主动创建对象B。在这种状态下，创建、控制对象的权力都在程序之中，如果有新的需求，那么就必须要修改程序。

​	而引入IOC之后，我们把创建、控制对象的权力交给第三方，第三方可以自己通过IOC容器来控制对象，也就实现了**控制反转**。

#### IOC本质

​	控制反转IOC(Inversion of Control)是一种设计思想，依赖查找（DL）和依赖注入（DI）是实现IOC的方式。而的控制反转就是：**获得依赖对象的方式反转了**。

### Spring与IOC

​	**IOC是Spring框架的核心内容**。使用多种方式完美实现了IOC，可以使用XML配置，也可以使用注解。

​	Spring容器在初始化时先读取配置文件，根据配置文件或元数据创建与组织对象存入容器中，程序使用时再从IOC容器中取出需要的对象，这种实现是**依赖注入**。



### 第一个Spring程序

```java
package com.demo.Hello;
    
public class Hello{
    private String str;
    public String getStr(){
		return str;
    }
    public String setStr(String str){
        this.str = str;
    }
    public String toString(){
        return str;
    }
}
```

```xml
<!--xml配置文件:beans.xml(随意命名)-->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd" >
    <!--
		Spring 与 new 一个对象的对比
		id = 变量名
		class = new 的对象
		property = 给对象中属性设置一个值 value:一个具体的值 ref:引用Spring创建好的对象
	-->
    <beab id="hello" class="com.demo.Hello">
    	<property name="str" value="Spring"/>
    </beab>
    
    <!--import 导入配置-->
    <import resource="配置文件"/>
```

```java
//test类
public class Test{
    public static void main(String[] args){
        ApplcationContext context = new ClassPathXmlApplicationContext("beans.xml");
        Hello hello = (Hello) context.getBean("hello");
        //至此获取到了hello对象
    }
}
```

### 对于程序的思考

- Hello对象是谁创建的？

  是由Spring创建的

- Hello对象的属性是怎么设置的？

  是由Spring容器设置的

**这个过程就叫控制反转**

- 控制：谁来控制对象的创建，传统应用程序的对象是由程序本身控制创建的，使用Spring后，对象是由Spring来创建的。
- 反转：程序本身不创建对象，而变成被动的接收对象。
- 依赖注入：就是用set方法来注入的。
- IOC是一种编程实现，由主动的编程变成被动的接收。
- 所有bean在配置文件加载后就被Spring实例化了，默认在内存中每个bean只存在一个实例，是单例模式。

​	使用Spring之后，我们**无需去程序中改动**，要实现不同的操作，只需要在配置文件中进行修改，即**对象由Spring来创建，管理，装配**。

### 依赖注入

```java
package com.demo.Test;
    
public class Test{
    private String name;
    private int age;
    public Test(String name,int age){
        this.name=name;
        this.age=age;
    }
}
```

#### 构造器注入

```xml
<bean id="test" class="com.demo.Test">
	<constructor-arg index="0" value="张三"/>
    <constructor-arg index="1" value="22"/>
</bean>
```

#### Set方式注入

```xml
<bean id="test1"class="com.demo.Test">
</bean>
<bean id="test" class="com.demo.Test">
    <!--例子中的name不是固定类型-->
    <!--普通值注入-->
    <property name="name" value="str"/>
    <!--bean注入-->
    <property name="name" ref="test1"/>
    <!--数组-->
    <property name="name">
    	<array>
        	<value>test1</value>
            <value>test2</value>
            ...
        </array>
    </property>
    <!--List-->
    <property name="name">
    	<list>
        	<value>test1</value>
            <value>test2</value>
            ...
        </list>
    </property>
    <!--Map-->
    <property name="name">
    	<map>
        	<entry key="test1"value="test1"/>
            <entry key="test1"value="test1"/>
            ...
        </map>
    </property>
    <!--Set-->
    <property name="name">
    	<set>
        	<value>test1</value>
            <value>test2</value>
            ...
        </set>
    </property>
    <!--null-->
    <property name="name">
        <null/>
    </property>
    <!--Properties-->
    <property name="name">
    	<props>
        	<prop key="test1">test1</prop>
            <prop key="test2">test2</prop>
            ...
        </props>
    </property>
</bean>
```

#### 拓展方式注入

```xml
<!--p命名空间注入，可以直接注入属性的值:property-->
<bean id="test" class="com.demo.Test" p:name="name" p:age="18"/>
<!--c命名空间注入，通过构造器注入:construct-args-->
<bean id="test" class="com.demo.Test" c:name="name" c:age="18"/>
```

### 自动装配

​	关键字：autowire

```xml
<bean id="test" class="com.demo.Test" autowire="..."/>
```

#### ByName

​	会自动在上下文查找和自己对象set方法后面的值对应的beanid。	

#### ByType

​	会自动在上下文查找和自己对象类型相同的bean。

### 注解实现自动装配

​	jdk1.4支持注解，Spring2.5支持注解。

```xml
<!--
	要使用注解：
	1.导入约束:context
	2.配置注解的支持
-->
	<context:annotation-config/>
```

#### @Autowired

​	表示被修饰的类需要注入对象，可以直接在属性上使用，也可在set上使用。

```java
@Autowired
pirvate Test test;
//优先根据类型进行标注装配，可以忽略set方法。
```

#### @Nullable

​	字段标记这个注解，说明这个字段可以为null。

```java
public void setTest(@Nullable Test test){
    this.test=test;
}
//如果显示定义了Autowired的required为false，说明这个对象为null。否则不许为空。
@Autowired(required = false)
private Test test;
```

#### @Qualifier

​	与@Autowired组合可以按照名字进行装配。

```java
@Autowired()
@Qualifier("test1")
privated Test test;
```

#### @Resource

- 是J2EE的注解。
- 匹配顺序

  1. 如果同时指定了name和type，则从Spring上下文中找到唯一匹配的bean进行装配，找不到则抛出异常.
  2. 如果指定了name，则从上下文中查找名称（id）匹配的bean进行装配，找不到则抛出异常
  3. 如果指定了type，则从上下文中找到类型匹配的唯一bean进行装配，找不到或者找到多个，都会抛出异常
  4. 如果既没有指定name，又没有指定type，则自动按照byName方式进行装配；如果没有匹配，则回退为一个原始类

```java
@Resouce(name = "...")
//加name属性指定名字进行装配。
```

### Spring注解开发

```xml
<!--指定要扫描的包，这个包下的注解就会生效-->
<context:component-scan base-package="要被扫描的包"/>
```

#### @Component

​	把类注册到spring容器中，Bean实例的名称默认是Bean类的首字母小写，还可以在使用时指定Bean实例的名称。

```java
package com.demo;

//等价于<bean id="test" class="com.demo.Test"/>
@Component
public class Test{
    public String name;
}
```

​	@Component还有3个衍生注解，他们功能上一样，但是对应不同的mvc分层。

- dao:@Repository。
- service:@Service。
- controller:@Controller。

#### @Value

​	用来注入基本类型和String，可以直接在属性上使用，也可在set上使用。

#### @Scope

​	用来设置bean的作用域。

#### xml与注解对比

- xml更加灵活，适用于任何场合，维护简单。

- 注解不是自己的类使用不了，维护相对复杂。

- 最佳实践

  - xml用来管理bean。

  - 注解负责属性注入。

#### @Configuration&@ComponentScan&@Bean

​	用纯java来代替xml配置，也会被注册到容器中。

```java
@Configuration
@ComponentScan("com.demo")
//相当于<context:component-scan base-package="要被扫描的包"/>
public class Config{
    
    /**
      * 注册一个bean，相当于写一个bean标签
      * 这个方法的名字相当于bean标签中的id属性
      * 这个方法的返回值，就相当于bean标签中的class属性
    **/
    @Bean
    public Test getTest(){
        return new Test();
        //要注入bean中的对象。
    }
    
    //使用方法
    public static void main(String[] args){
        ApplicationContext context = new AnnotaationConfigAplicationContext(Config.class);
        Test getTest=(Test) context.getBean("getTest");
    }
}
```

#### @Import

​	用来引入其他的java配置。

### Spring AOP

#### AOP介绍

​	AOP 即 Aspect Oriented Program 面向切面编程。通过预编译和运行期动态代理实现程序功能的统一维护的一种技术。

​	利用AOP横向添加的进去的功能一般与主体业务无关，且复用性高。例如日志记录，性能统计，安全控制，事务处理，异常处理等。

​	将这些比较公用的逻辑从业务主逻辑代码中划分出来，通过分离，我们可以将它们独立到非主导业务逻辑的单独方法中。

- **横切关注点**: 跨越应用程序多个模块的方法或功能。
- **切面(ASPECT)**: 横切关注点被模块化的特殊对象。即,它是一个类。
- **通知(Advice)**: 切面必须要完成的工作。即,它是类中的一个方法
- **目标(Target)**: 被通知对象。
- **代理(Proxy)**: 向目标对象应用通知之后创建的对象。
- **切入点(PointCut)**: 切面通知执行的"地点"的定义。
- **连接点(JoinPoint)**: 与切入点匹配的执行点。

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/uIjQbm.jpg)

#### 使用Spring实现AOP

##### 使用原生Spring API接口实现AOP

| 通知类型     | 连接点               | 实现接口                |
| ------------ | -------------------- | ----------------------- |
| 前置通知     | 方法前               | MethodBeforeAdvice      |
| 后置通知     | 方法后               | AfterReturningAdivce    |
| 环绕通知     | 方法前后             | MethodInterceptor       |
| 异常抛出通知 | 方法抛出异常         | ThrowsAdvice            |
| 引介通知     | 类中增加新的方法属性 | IntroductionInterceptor |

​	目标对象

```java
package com.demo;

public class Test{
    public void sayHello(){}
}
```

​	切面要实现增强接口

```java
package com.demo;

public class AopTest implements MechodBeforeAdvice{
    /** method: 要执行的目标对象的方法
      * args: 参数
      *	target: 目标对象
    **/
    public void before(Method method, Object[] args, Object target) throws Throwable{}
} 
```

​	xml配置

```xml
<!--注册bean-->
<bean id="test" class="com.demo.Test"/>
<bean id="AopTest" class="com.demo.AopTest"/>
<!--配置aop-->
<aop:config>
	<!--配置切入点-->
    <aop:pointcut id="pointcut" expression="execution(* com.demo.Test.*(..))"/>
    <!--执行环绕增加-->
    <aop:advisor advice-ref="AopTest" pointcut-ref="pointcut"/>
</aop:config>
```

​	**execution表达式**

```java
execution(<修饰符模式>？<返回类型模式><方法名模式>(<参数模式>)<异常模式>?);
//除了返回类型模式、方法名模式和参数模式外，其它项都是可选的。
```

​	**示例**

```java
execution(* com.sample.service.impl..*.*(..));
```

- 第一个*代表任意返回类型。
- `com.sample.service.impl..`代表``com.sample.service.impl`下的当前包和子包。
- 第二个*代表任意类。
- 第三个*代表任意方法。
- `(..)`代表任意参数类型。

##### 使用自定义类实现AOP

​	自定义类

```java
package com.demo;

public class AnotherAopTest{
    public void before(..){...}
    public void after(..){...}
} 
```

​	xml配置

```xml
<!--注册bean-->
<bean id="test" class="com.demo.Test"/>
<bean id="anotherAopTest" class="com.demo.AopTest"/>
<!--配置aop-->
<aop:config>
    <!--自定义切面-->
    <aop:aspect ref="anotherAopTest">
    	<!--配置切入点-->
    	<aop:pointcut id="pointcut" expression="execution(* com.demo.Test.*(..))"/>
   		<!--通知-->
    	<aop:before mothod="before" pointcut-ref="pointcut"/>
        <aop:after mothod="after" pointcut-ref="pointcut"/>
    </aop:aspect>
</aop:config>
```

##### 使用注解实现AOP

​	开启注解支持。

```xml
<aop:aspectj-autoproxy/>
```

###### @Aspect

​	标注一个类为切面。

###### @Before

​	标注一个方法为通知目标。

```java
@Before("execution(* * * * *)")
//参数为execution表达式，用来标注配置切入点。
```

###### @After

 	同@Before。

###### @Around

 	同@Before。不同的啊我们可以给定一个参数，代表我们要获取的切入点。

```java
@Around("execution表达式")
public void around(ProceedingJoinPoint jp)throws Throwable{
    ...
    //执行方法
    Object proceed = jp.proceed();
    ...
} 
```

### 声明式事务

#### 事务是什么

​	事务是应用程序中一系列严密的操作，所有操作必须成功完成，否则在每个操作中所作的所有更改都会被撤消。也就是事务具有原子性，一个事务中的一系列的操作要么全部成功，要么一个都不做。

**事务的ACID原则**

- 原子性
- 一致性
- 隔离性
- 持久性

## Spring Boot

## JVM

### 概述

**Java虚拟机**

![image-20200607205751748](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200607205751748.png)

### Java内存区域与内存溢出异常

#### 运行时数据区域

![image-20200608000044625](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200607224519737.png)

​	其中方法区、堆、执行引擎和本地库接口是由所有线程共享的数据区，而虚拟机栈、本地方法栈、程序计数器是线程隔离的数据区。

#### 程序计数器

- 线程私有。随线程而生，随线程而灭。

- 用来记录当前线程字节码的行号，字节码解释器通过改变他来选取下一条需要执行的字节码指令。
- 由于Java虚拟机的多线程是通过线程轮流切换、分配处理器执行时间的方式来实现的，所以每条线程都有一个单独的程序计数器。
- 如果执行的是Java方法，它记录的是正在执行的虚拟机字节码指令的地址。
- 如果执行的是本地(Native)方法，它为空(Undefined)。

#### Java虚拟机栈

- 线程私有。随线程而生，随线程而灭。
- 当每个方法执行时，Java虚拟机都会为它创建一个**栈帧**(Stack Frame)用来存储方法的信息，当方法执行完毕后出栈。
- 存储了包括存储局部变量表、操作数栈、动态连接、方法出口等信息。
- 局部变量表存储了编译器可知的**Java基本类型**。以局部**变量槽(**Slot)为单位。64位长的类型会占用2个变量槽。
- 当进入一个方法时，这个方法需要在栈帧中分配多大的局部变量空间是完全确定的，在方法运行期间不会改变局部变量表的大小。
- 一个变量槽实际的占用空间的大小由虚拟机实现。

####  本地方法栈

- 线程私有。随线程而生，随线程而灭。
- 同虚拟机栈类似，区别是保存的不是字节码而是本地方法。

####  Java堆

- 被所有线程共享。
- 在虚拟机启动时创建。
- 唯一目的是存放对象实例。
- 被垃圾收集器管理。
- 可被实现为固定大小，也可为可拓展大小，主流为可拓展大小。

#### 方法区

- 被所有线程共享。
- 用于存储被虚拟机加载的类型信息、常量、静态变量等数据。
- 用堆实现。
- 该区域内存回收主要是针对常量池的回收和类型的卸载。

#### 运行时常量池

- 为方法区的一部分。
- 常量池表用来存储编译期生成的字面量和符号引用，在类加载后存放到常量池中。
- 具有动态性，可以在常量可以在非编译期产生。

#### 对象的创建

1. **Java虚拟机遇到new指令**。
2. **检查类是否存在**。检查指令的参数是否在常量池内定位到一个类的符号引用，检查这个符号引用的类是否被加载、解析、初始化过。若没有则执行类的加载过程。
3. **虚拟机为新生对象分配内存**。分配内存的方法有两种：**指针碰撞**和**空闲列表**，使用那种方法主要看Java堆**是否规整**并且垃圾收集器是否有**空间压缩整理**的能力。同时还要考虑线程安全。
4. 对象进行初始化为零值。
5. 对对象进行设置。如对象是哪个类的实例、对象的GC分带年龄信息等将被存放到对象头中。
6. 执行构造函数。

#### 对象的内存布局

- 分为3部分：对象头、实例数据、对齐填充。
- 对象头包含两类信息：第一类是存储对象自身运行时数据，第二类是类型指针
  - 运行时数据包含如GC分布带、锁状态标志位、线程持有的锁等信息，这些信息被存储在32位或64位的Mark Word中。
  - Java虚拟机通过类型指针来确定对象是哪个类的实例。
- 实例数据是对象存储的有效信息，即文默在代码中定义的各种类型字段。
- 对齐填充是为了满足Java虚拟机要求的对象起始位置必须是8字节的整数倍。

#### 对象的访问定位

- 主流的访问粉丝有使用句柄访问和直接指针两种
- 使用句柄访问，好处是当对象被移动，只会改变句柄中的实例数据指针，而reference不需要修改。

![image-20200608113045602](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200608113045602.png)



- 使用直接指针访问，好处是节省一次指针定位的时间。

![image-20200608113135243](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200608113135243.png)

#### 内存溢出实例

- Java堆溢出：

  > Java堆内存的OutOfMemoryError异常是实际应用中最常见的内存溢出异常情况。出现Java堆内存 溢出时，异常堆栈信息“java.lang.OutOfMemoryError”会跟随进一步提示“Java heap space”。

- 虚拟机栈和本地方法栈溢出：

  >1）如果线程请求的栈深度大于虚拟机所允许的最大深度，将抛出StackOverflowError异常。
  >2）如果虚拟机的栈内存允许动态扩展，当扩展栈容量无法申请到足够的内存时，将抛出 OutOfMemoryError异常。

- 方法区和运行时常量池溢出：

  > 运行时常量池溢出时，在OutOfMemoryError异常后面跟随的提示信息是“PermGen space”。

- 本机直接内存溢出：

  >由直接内存导致的内存溢出，一个明显的特征是在Heap Dump文件中不会看见有什么明显的异常 情况，如果读者发现内存溢出之后产生的Dump文件很小，而程序中又直接或间接使用了 DirectMemory（典型的间接使用就是NIO），那就可以考虑重点检查一下直接内存方面的原因了。

### 垃圾收集器与内存分配策略

#### 引用计数器算法

​	该方法的原理是在对象中添加一个引用计数器，当被引用时计数器加一，当引用失效时计数器减一，当计数器为零时，说明对象不可再被引用。

​	该方法的优点是原理简单，判定高效，但是当对象相互引用，形成一个环时，就无法正确的释放空间。

​	主流的Java虚拟机不使用这个方法。

#### 可达性分析算法

​	通过"GC Roots"的根对象为起始节点集，开始向下搜索，走过的路程称为"引用链"。

![image-20200608204207423](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200608204207423.png)

​	可被作为GC Roots的对象包括：

- 在虚拟机栈（栈帧中的本地变量表）中引用的对象。
- 在方法区中类静态属性引用的对象。
- 在方法区中常量引用的对象。
- 在本地方法栈中JNI（即通常所说的Native方法）引用的对象。
- Java虚拟机内部的引用，如基本数据类型对应的Class对象，一些常驻的异常对象（比如 NullPointExcepiton、OutOfMemoryError）等，还有系统类加载器。
- 所有被同步锁（synchronized关键字）持有的对象。
- 反映Java虚拟机内部情况的JMXBean、JVMTI中注册的回调、本地代码缓存等。
- 不可达对象要经历两次标记才会被宣告死亡。
  1. 如果对象在进行可达性分析后发现没有与 GC Roots 相连接的引用链，那它将会被第一次标记并且进行一次筛选，筛选的条件是此对象是否有必要执行 finalize() 方法。
  2. 当对象没有覆盖 finalize() 方法，或者 finalize() 方法已经被虚拟机调用过，虚拟机将这两种情况都视为“没有必要执行”，直接进行第二次标记。
  3. 如果这个对象被判定为有必要执行 finalize() 方法，那么这个对象将会放置在一个叫做 F-Queue 的队列之中，并在稍后由一个由虚拟机自动建立的、低优先级的 Finalizer 线程去执行它。


#### 引用

##### 强引用|Strongly Reference

- 是指在程序代码之中普遍存在的引用赋值，即类似“Object obj=new Object()”这种引用关系。
- 被强引用所引用的对象永远不会被垃圾收集器回收。
- Vector类的clear方法是通过把引用赋值为null来实现清理工作。

##### 软引用|Soft Reference

- 如果一个对象具有软引用，内存空间足够，垃圾回收器就不会回收它。
- 在系统将要发生内存溢出异常前，会把被软引用的对象列进回收范围之中进行第二次回收。
- 软引用可用来实现内存敏感的高速缓存,比如网页缓存、图片缓存等。

##### 弱引用|Weak Reference

- 弱引用也是用来描述非必需对象的。
- 当JVM进行垃圾回收时，无论内存是否充足，都会回收被弱引用关联的对象。

##### 虚引用|Phantom Reference

- 虚引用并不影响对象的生命周期。
- 虚引用只是为了能在这个对象被收集器回收时收到一个系统通知。
- 无法通过虚引用来取得一个对象实例 。

#### 回收方法区

- 方法区的垃圾收集主要分为两部分：废弃的常量和不再使用的类型。

- 判定一个常量是否废弃：

  1. 该类所有的实例都已经被回收，也就是Java堆中不存在该类及其任何派生子类的实例。

  2. 加载该类的类加载器已经被回收。

  3. 该类对应的java.lang.Class对象没有在任何地方被引用，无法在任何地方通过反射访问该类的方
     法。

- 常量池中其他类(接口)、方法、字段的符号引用也与此类似。

#### 垃圾收集算法

##### 标记清除算法

1. 首先标记出所有需要回收的对象。

2. 在标记完成后，统一回收掉所有被标记的对象。

- 缺点
  - 执行效率不稳定。
  - 内存空间碎片化。

##### 标记复制算法

- 内存被分成大小相等的两块，每次只使用一块。
- 当一块用完，就将存活的对象复制到另一块内存上，然后把已使用的内存空间一次清理掉。
- 实现简单，运行高效。
- 缺点
  - 如果大部分对象存活，复制对象的消耗过大。
  - 可使用的内存缩小一半。

##### 标记整理算法

1. 首先标记出所有需要回收的对象。

2. 在标记完成后，让存活的对象向内存一端移动。

3. 直接清理掉边界以外的内存。

- 缺点
  - 如果回收时有大量对象存活，移动存活对象开销大。
  - 移动对象的操作要求全程暂停用户应用。

##### 分带收集算法

- 根据内存中对象的存活周期不同，在JVM中一般把内存划分为**新生代**和**老年代**。
- 老年代的特点是每次垃圾收集时只有少量对象需要被回收。
- 新生代的特点是每次垃圾回收时都有大量的对象需要被回收。

- 在新生代一般使用标记复制算法，并且不是按1:1的比例来划分内存。
- 在年老代一般使用的是标记整理算法。

- 创建对象时一般在新生代中分配内存空间，当新生代垃圾收集器回收几次之后仍然存活的对象会被移动到年老代内存中。
- 当大对象在新生代中无法找到足够的连续内存时也直接在年老代中创建。
- **永久代**用来存放class类、常量、方法描述等。对永久代的回收主要回收两部分内容：废弃常量和无用的类。

#### HotSpot的算法细节实现

#### 经典垃圾收集器

##### Seria收集器

![image-20201117114457175](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201117114457175.png)

- 使用一个线程去完成垃圾收集
- 优点
  - 简单高效
  - 适合运行在客户端下的虚拟机
  - 内存占用小
- 缺点
  - 要暂停用户线程

##### ParNew收集器

![image-20201117114508651](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201117114508651.png)

- ParNew收集器除了支持多线程**并行**收集之外，其他与Serial收集器相比并没有太多创新之处
- 并行与并发
  - **并行**描述的是多条垃圾收集器线程之间的关系，说明同一时间有多条这样的线程在协同工作，通常默认此时用户线程是处于**等待状态**
  - **并发**描述的是垃圾收集器线程与用户线程之间的关系，说明同一时间垃圾收集器线程与用户线程**都在运行**

##### Parallel Scavenge收集器

- 基于标记-复制算法
- 目标是达到一个可控制的**吞吐量**

$$
吞吐量=\frac{运行用户代码时间}{运行用户代码时间+运行垃圾搜集时间}
$$

##### Serial Old收集器

![image-20201120084853671](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120084853671.png)

- Serial的老年代版本

- 使用标记整理算法

##### Parallel Old收集器

![image-20201120090101325](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120090101325.png)

- Parallel Old是Parallel Scavenge收集器的老年代版本
- 支持多线程并发收集
- 基于标记-整理算法实

##### CMS收集器

![image-20201120090230703](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120090230703.png)

- CMS（Concurrent Mark Sweep）收集器是一种以获取最短回收停顿时间为目标的收集器。
- 基于标记-清除算法
- 收集分为四个部分
  - 初始标记(要暂停用户线程)
  - 并发标记
  - 重新标记(要暂停用户线程)
  - 并发清除
- 四个部分的作用
  - 初始标记用来标记GC Roots能直接关联到的对象
  - 并发标记是从GC Roots直接关联对象遍历整个对象图
  - 重新标记是为了修正并发期间的数据不一致
  - 并发清除是清除掉标记阶段被判断成死亡的对象
- 缺点
  - 无法处理"浮动垃圾"，即在并发标记和并发清理生成的垃圾
  - 因为在并发的时候用户线程还在运行，所以CMS不能等到老年代几乎满了才进行搜集。
  - 要预留空间，不然会出现"并发失败"，要暂停用户线程，并临时使用Serial Old来收集
  - 因为是标记清除算法，会产生很多碎片，触发一次Full GC

##### Garbage First(G1) 收集器

