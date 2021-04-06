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

