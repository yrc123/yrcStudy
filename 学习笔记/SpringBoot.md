# SpringBoot

## 关于Spring

### Spring是什么

​	Spring是一个轻量级、非入侵的控制反转(IOC)和面向切面编程(AOP)的框架。

### Spring组成

![这里写图片描述](https://gitee.com/lin_haoran/Picgo/raw/master/img/20170713150400373.bmp)

### 为什么要IoC

#### 从理论来说

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

##### IOC本质

​	控制反转IOC(Inversion of Control)是一种设计思想，依赖查找（DL）和依赖注入（DI）是实现IOC的方式。而的控制反转就是：**获得依赖对象的方式反转了**。

#### 从现实问题来解释|[知乎回答：Spring IoC有什么好处呢？](https://www.zhihu.com/question/23277575/answer/169698662)

##### 遇到的问题

​	在我们正在开发过程中，对于类的依赖，我们常常是用在上层类中new了底层的类来实现的：

![alt 图片来源：Mingqi的回答](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-8ec294de7d0f9013788e3fb5c76069ef_720w.jpg)

<center>一个汽车类的依赖</center>

​	而这样有时会遇到一个问题，就是开发到一半，发现一个底层的依赖想要多传入一个或多个参数，那就得从最上层一层一层的把新加的参数传入到底层，会有很多的代码量：

![alt 图片来源：Mingqi的回答](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-82e0c12a1b26f7979ed9241e169affda_720w.jpg)

<center>想给轮胎添加一个设置大小的功能</center>

​	从上面可以看出，在这种模式下，我要给底层的类添加参数，修改会波及依赖上所有的类，这样是非常麻烦而且很容易出错的。

​	而控制反转的就是为了解决这一问题，它通过将依赖**注入**到需要的类中，就解决了上面的问题

![alt 图片来源：Mingqi的回答](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-c920a0540ce0651003a5326f6ef9891d_720w.jpg)

<center>依赖注入的方法来实现Car类</center>

​	现在我再想给轮胎添加一个参数时，只要修改轮胎的构造，而不需要对其他被注入的类进行修改

![alt 图片来源：Mingqi的回答](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-99ad2cd809fcb86dd791ff7f65fb1779_720w.jpg)

<center>给轮胎添加参数</center>

​	Spring就是将*初始化车*的过程给封装起来，简化我们的开发过程

### Spring与IOC

​	**IOC是Spring框架的核心内容**。使用多种方式完美实现了IOC，可以使用XML配置，也可以使用注解。

​	Spring容器在初始化时先读取配置文件，根据配置文件或元数据创建与组织对象存入容器中，程序使用时再从IOC容器中取出需要的对象，这种实现是**依赖注入**。

## 全注解下的Spring IoC

### @Bean

### @Valuealt 

### @AutoWired

### @Compent

### @ComponentScan

### @Configuration

### @PropertySource

### @ConfigurationProperties

### @Condition

### @Qualifier

### @Primary

### @Scope

### @Profile

### @ImportResource

### @ControllerAdvice

- @ExceptionHandler：用于捕获Controller中抛出的不同类型的异常，从而达到异常全局处理的目的
- @InitBinder：用于请求中注册自定义参数的解析，从而达到自定义请求参数格式的目的
- @ModelAttribute：表示此方法会在执行目标Controller方法之前执行 

```java
@ControllerAdvice
public class MyControllerAdvice{
    @ExceptionHandler(Exception.class)
    public Object catchException(Exception e){
        //对异常的处理
        System.out.println("从Controller捕捉到异常")
    }
    //待补充
    @InitBinder("b")
	public void b(WebDataBinder binder) {
    	binder.setFieldDefaultPrefix("b.");
	}
    @ModelAttribute(name = "model")
    public Object getSomeThing{
        /**
         * 可以设定一些公共的数据，如UserDetails
         * 之后在任何一个Controller的接口可以中加一个Model参数，就可获得
        **/
    }
}
```

### Spring EL

#### ${...}

```java
//读取属性文件的值
@Value("${database.driverName}")
String driver
```

#### #{...}

```java
//T(...)引入类
//System是java.lang.*包的类，不必写全称，其他的要写全称
//这个就是调用System.currentTimeMillis()为这个方法赋值
@Value("#{T(System).currentTimeMillis()}") 
private Long initTime = null;

//赋值字符串
@Value("#{'Text'}")
private String str=null;

//科学计数法赋值
@Value("#{9.3E3}") 
private double d;

//赋值浮点数 
@Value("#{3.14}") 
private float pi;

//用名为beanName的Bean的str属性填充
@Value("#{beanName.str}")
private STring otherBeanProp = null;

//用名为beanName的Bean的str属性转为大写后填充
//?是用来判断是否为空，为空就不执行toUpperCase
@Value("#{beanName.str?.toUpperCase()}")
private STring otherBeanProp = null;

//可以进行计算
@Value("#{1+2}")
@Value("{beanName.str+'Text'}")
@Value("#{beanName.str eq 'Spring Boot'}")
...
```

## Spring AOP

| 术语     | 解释                                                         |
| -------- | ------------------------------------------------------------ |
| 连接点   | 被代理对象的特定方法就是连接点，AOP 将通过动态代理技术把它织入对应的流程中 |
| 切点     | 我们的切面可以对应多个连接点，这时候多个连接点可以抽象成切点 |
| 通知     | 分为前置通知、后置通知、环绕通知 、 事后返回通知和异常通知，它会根据约定织入流程中， |
| 目标对象 | 被代理对象                                                   |
| 引入     | 引入新的类和方法，增强Bean的功能                             |
| 织入     | 通过动态代理，为原有服务对象生成代理对象                     |
| 切面     | 在切面可以为被代理对象添加功能                               |

### 注解开发AOP

| 注解            | 作用                               |
| --------------- | ---------------------------------- |
| @Aspect         | 被注解的类会被Spring识别成一个切面 |
| @Before         | 前置通知                           |
| @After          | 后置通知                           |
| @AfterReturning | 事后返回通知                       |
| @AfterThrowing  | 异常通知                           |

### 定义切点

#### execution表达式

- 例：`execution(* com.springboot.chapter4.aspect.service.impl.UserServiceImpl.printUser(..))`
- `execution` 表示在执行的时候，拦截里面的正则匹配的方法
- `*` 表示任意返回类型的方法
- `com.springboot.chapter4.aspect.service.impl.UserServiceImpl`指定目标对象的全限定名称
- `printUser`指定目标对象的方法
- `(..)`表示任意参数进行匹配

### 引入

#### @DeclareParents

- 例：`@DeclareParents(value="com.springboot.study+",defaultImpl=UserValidatorImpl.class)`
- `value`：指向你要增强功能的目标对象
  - "study+"表示study的所有子类
- `defaultImpl`：引入增强功能的类

引入增强的实现，是通过调用增强方法时通过反射，直接调用引入增强的实现类，从而达到目的。

[源码解读](https://my.oschina.net/u/2377110/blog/1532127)

#### 通知获取参数

```java
@Before("pointCut()&&args(user)")
public void beforeParam(JoinPoint point, User user){
    Object[] args = point.getArgs();
}
```

- 即使不加`args(user)`，JoinPoint也会自动包含所有被代理方法的参数
- 加入`args(user)`后，把被代理方法的对应参数放到代理中

### 多个切面

​	Spring AOP支持多个切面，但是默认执行顺序是混乱的，Spring提供了`@Order`和一个`Ordered`接口，可以指定顺序

#### @Order

```java
...
    
@Aspect
@Order(1)
public class MayAspect1{
    ...
}
```

这样对于前置通知都是从小到大运行，后置通知是从大到小运行

#### Ordered接口

```java
...
    
@Aspect
public class MayAspect1 implements Ordered{
    @Overide
    public int getOrder(){
        return 1;
    }
    ...
}
```

### 实例

- User

```java
package com.studyspringboot.ch4.AOP;

public class User {
	private Long id;
	private String username;
	private String password;
	/**Getter and Setter**/
}

```

- 切入点

```java
package com.studyspringboot.service;

import ...
    
public interface UserServer {
	public void printUser(User user);
}
```

```java
package com.studyspringboot.service;

import ...

@Service
public class UserServerImpl implements UserServer {
	@Override
	public void printUser(User user) {
		if(user.getId()==null)
			throw new RuntimeException("用户参数为空");
		System.out.println("id = "+user.getId());
		System.out.println("username = "+user.getUsername());
		System.out.println("password = "+user.getPassword());
	}
}
```

- 切面

```java
package com.studyspringboot.aspect;

import ...
    
@Component
@Aspect
public class MyAspect {
	//引入增强类
	@DeclareParents(value="com.studyspringboot.ch4.AOP.service.UserServerImpl",
			defaultImpl= UserValidatorImpl.class)
	public UserValidator userValidator;

	//匹配表达式
	@Pointcut("execution( * com.studyspringboot.ch4.AOP.service.UserServerImpl.*(..))")
	public void pointCut(){}

	//JoinPoint包含了被代理方法的所有参数
	@Before("pointCut()")
	public void before(JoinPoint jp){
		Object[] args = jp.getArgs();
		System.out.println("before ...");
	}

	//user为被代理方法传入的的user参数
	@After("pointCut() && args(user)")
	public void after(User user){
		System.out.println("after ...");
	}
	@AfterReturning("pointCut()")
	public void afterReturning(){
		System.out.println("afterReturning ...");
	}

	@AfterThrowing("pointCut()")
	public void afterThrowing(){
		System.out.println("afterThrowing ...");
	}
	@Around("pointCut()")
	public void around(ProceedingJoinPoint pj) throws Throwable {
		System.out.println("around before ...");
		pj.proceed();
		System.out.println("around after ...");
	}
}
```

- 引入的增强类

```java
package com.studyspringboot.service;

import ...

public interface UserValidator {
	public boolean validate(User user);
}
```

```java
package com.studyspringboot.service;

import ...

public class UserValidatorImpl implements UserValidator{
	//判断是否有userId
	@Override
	public boolean validate(User user) {
		System.out.println("新接口");
		return user.getId()!=null;
	}
}
```

- Controller

```java
package com.studyspringboot.controller;

import ...

@Controller
@RequestMapping("/user")
public class UserController {
	@Autowired
	private UserServer userServer = null;

	@RequestMapping("/print")
	@ResponseBody
	public User printUser(Long id, String userName, String password){
		System.out.println(userServer.getClass());
		User user = new User();
		user.setId(id);
		user.setUsername(userName);
		user.setPassword(password);
		//使用引入的验证器
		UserValidator uv = (UserValidator) this.userServer;
		if(uv.validate(user)){
			this.userServer.printUser(user);
		}else{
			System.out.println("空id");
		}
		return user;
	}
}
```

## 访问数据库

### 数据库配置文件

```properties
#数据库驱动程序，不写自动匹配
spring.datasource.driver-class-name=com.mysql.jdbc.Driver
#数据库url
spring.datasource.url=jdbc:mysql://ip/DataBaseName
#数据库用户名
spring.datasource.username=...
#密码
spring.datasource.password=...
#是否开启自动下划线转驼峰
mybatis.configuration.map-underscore-to-camel-case=...
```

### 整合MyBatis框架|[MyBatis3中文文档](https://mybatis.org/mybatis-3/zh)

#### 前置代码

##### pojo类

```java
package com.studyspringboot.ch5.pojo;

import ...

@Component
@Alias(value = "user")//别名
public class User {
	private Long id = null;
	private String userName = null;
	private SexEnum sex = null;
	private String note = null;

	/**Getter and Setter**/
}
```

```java
package com.studyspringboot.ch5.enumeration;

public enum SexEnum {
	MALE(1,"男"),
	FEMALE(2,"女");
    
	private int id;
	private String name;
    
    //构造函数
	SexEnum(int id, String name){
		this.id=id;
		this.name=name;
	}
    //通过id来获取性别的枚举类型
	public static SexEnum getEnumById(int id){
		for(SexEnum sex : SexEnum.values()){
			if(sex.getId()==id){
				return sex;
			}
		}
		return null;
	}

	/**Getter and Setter**/
}
```

#### TypeHandler

- TypeHandler是将java类型和数据库类型转换的接口，MyBatis有许多默认实现

- 自定义类型需要用typeHandler进行转换

```java
package com.studyspringboot.ch5.typeHandler;

import ...

//为自定义的SexEnum写的TypeHandler
@MappedJdbcTypes(JdbcType.INTEGER)	//java类对应的数据库的类型
@MappedTypes(value=SexEnum.class)	//数据库类型对应的java类
public class SexTypeHandler extends BaseTypeHandler<SexEnum> {

	//存储性别
	@Override
	public void setNonNullParameter(PreparedStatement preparedStatement, int i, SexEnum sexEnum, JdbcType jdbcType) throws SQLException {
		preparedStatement.setInt(i, sexEnum.getId());
	}

	//通过列名读取性别
	@Override
	public SexEnum getNullableResult(ResultSet resultSet, String s) throws SQLException {
		int sex = resultSet.getInt(s);
		if(sex!=1&&sex!=2)return null;
		return SexEnum.getEnumById(sex);
	}

	//通过下标读取性别
	@Override
	public SexEnum getNullableResult(ResultSet resultSet, int i) throws SQLException {
		int sex = resultSet.getInt(i);
		if(sex!=1&&sex!=2)return null;
		return SexEnum.getEnumById(sex);
	}

	//通过存储过程读取性别
	@Override
	public SexEnum getNullableResult(CallableStatement callableStatement, int i) throws SQLException {
		int sex = callableStatement.getInt(i);
		if(sex!=1&&sex!=2)return null;
		return SexEnum.getEnumById(sex);
	}
}
```

#### 注解

#### @Alias

- `value`给被注释的类一个别名
  - 如`@Alias(value = "user")`

#### @MappedJdbcType

- 定义JdbcType类型
  - 如`@MappedJdbcTypes(JdbcType.INTEGER)`

#### @Mappedtypes

- `value`定义JavaType类型
  - 如`@MappedTypes(value=SexEnum.class)`

#### MyBatis映射文件

```xml
<?xml version="1.0" encoding="utf-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<!--namespace：指定一个接口，后面就使用这个接口来调用sql语句-->
<mapper namespace="com.studyspringboot.ch5.dao.MyBatisUserDao">
    <!--
		id：对应接口的方法，调用这个方法会执行这个语句
		parameterType：这个例子中代表一个长整型参数，多参数不能使用这个属性，
		resultType：调拨返回为user类型，这个是通过@Alias指定的别名，也可以直接用全限定名去指定
	-->
    <select id="getUser" parameterType="long" resultType="user">
        <!--
			如果是多参数可以用#{索引值}来传入，下标从0开始
			或者可以使用 @Param("参数名")参数 在对应接口来注解
		-->
        select id, user_name as userName, sex, note from user where id = #{id}
    </select>
</mapper>
```

#### 实现接口

- 实现映射文件的接口

```java
package com.studyspringboot.ch5.dao;

import ...

//@Repostiory注解在扫描加载MyBatis接口时有用
@Repository
//getUser对应映射文件中的id
public interface MyBatisUserDao {
	public User getUser(Long id);
}
```

#### 配置文件

```properties
#定义映射xml文件路径
mybatis.mapper-locations=...
#定义别名扫描的包，与@Alias一起使用
mybatis.type-aliases-package=...
#自定义类型对应的TypeHandler类的包
mybatis.type-handlers-package=...
```

#### 装配MyBatis

##### 使用MapperFactoryBean装配MyBatis

```java
//MyBatis会自动帮我们生成SqlSessionFactory工厂
@Autowired
SqlSessionFactory sqlSessionFactory =null;
//使用工厂装配实现了我们自定义的接口(这里为MybatisUserDao)的Bean
@Bean
public MapperFactoryBean<MyBatisUserDao> initMyBatisUserDao(){
	MapperFactoryBean<MyBatisUserDao> bean = new MapperFactoryBean<>();
	bean.setMapperInterface(MyBatisUserDao.class);
	bean.setSqlSessionFactory(sqlSessionFactory);
	return bean;
}
```

##### ~~使用@MapperScan装配MyBatis~~

```java
package com.studyspringboot.ch5.main;

//没被注释的为必须的
//定义Spring Boot扫描路径
@SpringBootApplication(scanBasePackages = {"com.studyspringboot.ch5.*"})
//定义JPA接口扫描路径
//@EnableJpaRepositories(basePackages = "com.studyspringboot.ch5.dao")
//定义实体类扫描路径
//@EntityScan(basePackages = "com.studyspringboot.ch5.pojo")
@MapperScan(
		//指定扫描的包
		basePackages = "com.studyspringboot.ch5.*",
		//指定SqlSessionFactory
		//sqlSessionFactoryRef = "sqlSessionFactory",
		//指定sqlSessionTemplate
		//sqlSessionTemplateRef = "sqlSessionTemplate",
		//限定名扫描接口，不常用
		//markerInterface = Class.class
		//扫描的注解
		annotationClass = Repository.class
)
public class Application {
	...
}
```

##### 使用@Mapper装配MyBatis

直接在Dao接口上使用`@Mapper`注解，而不是用别的，就可以了

#### 其他代码

##### Service

```java
package com.studyspringboot.ch5.service;

import ...

public interface MyBatisUserService {
	public User getUser(Long id);
}
```

```java
package com.studyspringboot.ch5.service;

import ...

@Service
public class MyBatisUserServiceImpl implements MyBatisUserService{

	@Autowired
	private MyBatisUserDao myBatisUserDao = null;

	@Override
	public User getUser(Long id) {
		return myBatisUserDao.getUser(id);
	}
}
```

##### Controller

```java
package com.studyspringboot.ch5.controller;

import ...

@Controller
@RequestMapping("/mybatis")
public class MyBatisController {
	@Autowired
	MyBatisUserService myBatisUserService = null;

	@RequestMapping("/getUser")
	@ResponseBody
	public User getUser(Long id){
		return myBatisUserService.getUser(id);
	}
}
```

#### MyBatis整合总结

1. 编写实体类
2. 如果实体类有自定义类型，要实现对应的TypeHandler
3. 编写MyBatis映射文件
4. 编写映射文件的接口
5. 编写配置文件
6. 装配MyBatis

## 数据库事务

### Spring声明式事务

#### @Transactional

- 一般在service的实现类上注释

- `isolation`：设置隔离级别
  - Isolation.READ_UNCOMMITTED
  - Isolation.READ_COMMITTED
  - Isolation.REPEATABLE_READ
  - Isolation.SERIALIZABLE
- `timeout`：设置超时时间，单位为秒
- `propagation`：设置传播行为
  - Propagation.传播行为

#### 配置文件设置隔离级别

```properties
#隔离级别数字配置的含义
#-1 数据库默认隔离级别 
#1 未提交读 
#2 读写提交
#4 可重复读 
#8 串行化 
#tomcat 数据源默认隔离级别 
spring.datasource.tomcat.default-transaction-isolation=2 
#dbcp2 数据库连接池默认隔离级别 
#spring.datasource.dbcp2.default-transaction-isolation=2
```

### 隔离级别

#### 数据库事务

- 原子性
- 一致性
- 隔离性
- 持久性

#### 数据库隔离级别

##### 未提交读|read uncommitted

- 允许一个事务读取另外一个事务没 有提交的数据
- 会发生**脏读**
- 性能高但危险，应用不广

| 时刻 | 事务1       | 事务2    | 备注                                                         |
| ---- | ----------- | -------- | ------------------------------------------------------------ |
| T0   | ...         | ...      | 商品库存为2                                                  |
| T1   | 读取库存为2 |          |                                                              |
| T2   | 库存-1      |          | 库存为1                                                      |
| T3   |             | 库存-1   | 库存为0                                                      |
| T4   |             | 提交事务 | 提交，库存为0                                                |
| T5   | 回滚事务    |          | 因为第一类丢失更新已经克服，所以不会因滚为2 ，库存为 0，结果错误 |

##### 读写提交|read committed

- 一个事务只能读取另外一个事务已经提交的数据
- 克服脏读
- 会发生不可重复读
- 常用的级别

| 时刻 | 事务1       | 事务2       | 备注                              |
| ---- | ----------- | ----------- | --------------------------------- |
| T0   | ...         | ...         | 商品库存为1                       |
| T1   | 读取库存为1 |             |                                   |
| T2   | 库存-1      |             | 库存为1                           |
| T3   |             | 读取库存为1 | 确认可减                          |
| T4   | 提交事务    |             | 提交，库存为0                     |
| T5   |             | 库存-1      | 失败， 因为此时库存为 0，无法扣减 |

##### 可重复读|repeatable read

- 如果事务读取时，另一个事务未提交，那么要拥塞到另一个事务提交
- 会发生幻读

| 时刻 | 事务1        | 事务2            | 备注                                |
| ---- | ------------ | ---------------- | ----------------------------------- |
| T0   | ...          | ...              | 商品总库存为100，已经销售50，库存50 |
| T1   | 读取库存为50 |                  |                                     |
| T2   |              | 查询交易为50     | 库存为1                             |
| T3   | 库存-1       |                  |                                     |
| T4   | 交易+1       |                  |                                     |
| T5   | 提交事务     |                  | 已经销售51，库存49                  |
| T6   |              | 打印交易记录为51 | 查询不一致，出现幻读                |

##### 串行化|Serializable

- 完全串行化
- 效率低

##### 总结

| 隔离级别 | 脏读 | 不可重复读 | 幻读 |
| -------- | ---- | ---------- | ---- |
| 未提交读 | ✔    | ✔          | ✔    |
| 读写提交 | ✘    | ✔          | ✔    |
| 可重复读 | ✘    | ✘          | ✔    |
| 串行化   | ✘    | ✘          | ✘    |

### 传播行为

​	当一个方法调用另外一个方法时，可以让事务采取不同的策略工作，如新建事务 或者挂起当前事务等，这便是事务的传播行为。

#### 传播行为的种类

​	一共有7种传播行为，加星为常用

##### \*REQUIRED

	- 需要事务
	- 它是默认传播行为，如果当前存在事务，就**沿用当前事务**
	- 否则新建一个事务运行子方法

##### SUPPORTS

- 支持事务
- 如果当前存在事务，就沿用当前事务
- 如果不存在，则继续采用无事务的方式运行子方法

##### MANDATORY

	- 必须使用事务
 - 如果存在当前事务， 就沿用当前事务
	- 如果当前没有事务，则会抛出异常

##### \*REQUIERS_NEW

- 无论当前事务是否存在，都会创建新事务运行方法
- 这样新事务就可以拥有新的锁和隔离级别等特性，与当前事务**相互独立**
- 每一个事务都可以拥有自己独立的隔离级别和锁

##### NOT_SUPPORTED

- 不支持事务
- 当前存在事务时，将挂起事务，运行方法

##### NEVER

- 不支持事务
- 如果当前方法存在事务，则抛出异常
- 否则继续使用无事务机制运行

##### \*NESTED

- 子方法发生异常， 只回滚子方法执行过的 SQL，而不回滚当前方法的事务
- 实现是通过设置保存点实现
- 如果数据库不支持保存点，那么就创建新事务，这种情况下就与`REQUIERS_NEW`一致
- `NESTED`传播行为会沿用当前事务的隔离级别和锁等特性，而`REQUIRES_NEW`则可以拥有自己独立的隔离级别和锁等特性

#### @Transactional 自调用失效问题

​	如果是通过接口调用方法，那不会失效

```java
@Service
public class UserServiceImpl implements UserService{
    @Autowired
    private UserService userService = null;
    
    @Transactional(...)
    public int insertUsers(List<User> userList){
        for(User user:userList){
            //调用的是userService的代理接口
            userService.insertUser(user);
        }
    }
}
```

​	而如果是直接调用类内部的函数，就会失效

```java
@Service
public class UserServiceImpl implements UserService{
    @Autowired
    private UserService userService = null;
    
    @Transactional(...)
    public int insertUsers(List<User> userList){
        for(User user:userList){
            //调用的是自身的方法，不会被代理
            insertUser(user);
        }
    }
    public int insertUser(User user){
        ...
    }
}
```

​	因为Spring的声明式事务是通过AOP织入的，而直接调用自身方法就不是通过代理对象来调用方法

## Redis

### spring-data-redis

- 是对redis提供的客户端（Jedis）的封装
- 连接池自动管理，提供了RedisTemplate类
- 将jedis的api封装，将同一类型的操作封装为operation接口

#### RedisTemplate

##### 数据封装接口

| 操作接口        | 功能                 | 获取接口      |
| --------------- | -------------------- | ------------- |
| HashOperations  | 散列操作接口         | opsForHash()  |
| ListOperations  | 列表（链表）操作接口 | opsForList()  |
| SetOperations   | 集合操作接口         | opsForSet()   |
| ValueOperations | 字符串操作接口       | opsForValue() |
| ZSetOperations  | 有序集合操作接口     | opsForZSet()  |

##### 对一个键值对连续操作接口

| 接口                 | 说明                                 | 获取接口             |
| -------------------- | ------------------------------------ | -------------------- |
| BoundHashOperations  | 绑定一个散列数据类型的键操作         | boundHashOps([key])  |
| BoundListOperations  | 绑定一个列表（链表）数据类型的键操作 | boundListOps([key])  |
| BoundSetOperations   | 绑定一个集合数据类型的键操作         | boundSetOps([key])   |
| BoundValueOperations | 绑定一个字符串集合数据类型的键操作   | boundValueOps([key]) |
| BoundZSetOperations  | 绑定一个有序集合数据类型的键操作     | boundZSetOps([key])  |

##### 序列化器

- JdkSerializationRedisSerializer
  - RedisTemplate中默认的序列化器
  - 将pojo类通过ObjectInputStream/ObjectOutputStream进行序列化操作
- StringRedisSerializer
  - 根据指定的charset对数据的字节序列编码成string
  - RedisTemplate中帮我们实现的，可以从RedisTemplate中获取
  - 也可从`RedisSerizlizer.string()`获取，但是这个相当于使用了 UTF_8 编码的 StringRedisSerializer，需要注意字符集问题。
- Jackson2JsonRedisSerializer
  - 可以将pojo实例序列化成json格式存储在redis中
  - 在构造的时候要给出class或JavaType
  - 不够通用
- GenericJackson2JsonRedisSerializer
  - 同上，但是这种序列化方式**不用自己手动指定对象的Class**。
  - 所以其实我们就可以使用一个**全局通用的序列化方式了**。
  - 可以从`RedisSerizlizer.json()`中获取
  - ![image-20210207200121001](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210207200121001.png)

#### StringRedisTemplate

- 继承自`RedisTemplate<String, String>`
- 只能使用传入String类型

#### RedisCallback和SessionCallback接口

- 两个接口都可以在一个连接下执行多条指令
- RedisCallback比较底层，要对类型进行转换
- SessionCallback进行了封装

##### RedisCallback

```java
public void useRedisCallback(RedisTemplate redisTemplate){
    redisTemplate.excute(new RedisCallback(){
        @Override
        public Object doInRedis(RedisConnection rc){
            rc.set("key1".getBytes(),"value1".getBytes());
            return null;
        }
    })
}
```

##### SessionCallback

```java
public void useSessionCallback(RedisTemplate redisTemplate){
    redisTemplate.excute(new SessionCallback(){
        @Override
        public Object execute(RedisOpserations ro){
            ro.opsForValue().set("key1","value1");
            return null;
        }
    })
}
```

### 在Spring Boot中使用Redis

#### 配置文件

```properties
#配置连接池属性
# 连接池中的最小空闲连接
spring.redis.jedis.pool.min-idle=5
# 连接池最大连接数（使用负值表示没有限制）
spring.redis.jedis.pool.max-active=10
# 连接池中的最大空闲连接
spring.redis.jedis.pool.max-idle=10
# 连接池最大阻塞等待时间（使用负值表示没有限制）
spring.redis.jedis.pool.max-wait=2000
# 连接超时时间（毫秒）
spring.redis.timeout=0
#配置Redis服务器属性
spring.redis.port=6379
spring.redis.host=ip
spring.redis.password=password
```

#### 注解

##### @PostConstruct

- Java自带的注解，可以注释一个非静态的void方法
- @PostConstruct修饰的方法会在服务器加载Servlet的时候运行，并且只会被服务器执行一次
- Constructor(构造方法) -> @Autowired(依赖注入) -> @PostConstruct(注释的方法)

### Redis特殊用法

#### Redis事务

- 事务通常组合是watch...multi...exec
  - `watch([key])`：用来设置监视的key
  - `multi()`：用来开启事务
  - `exec()`：执行事务
- 如果被监视的值的值在`watch`后、`exec`之前改变，事务会被取消
- 因为事务的watch...multi...exec要在**一次连接中执行**，使用SessionCallback
- 因为开启事务后，命令**不会马上被执行**，而是放在一个队列中，所以**返回值null**
- `exec()`的返回值为`List`类，是事务中所有语句的返回值列表

```java
//返回值为一个List，一种返回实例为：[true,"1"]
public Object getMultiUser(String key){
	return redisTemplate.execute(new SessionCallback() {
		@Override
		public Object execute(RedisOperations operations) throws DataAccessException {
            //监视key
			operations.watch(key);
            //开启事务
			operations.multi();				
            operations.opsForValue().set(key,"1");
			operations.opsForValue().get(key);
            //执行并返回结果
			return operations.exec();
		}
	});
}
```

#### 使用Redis流水线

- 即`redisTemplate.executePiplined`方法
- 和`execute`相似，不在赘述
- 使用流水线技术，减缓在网络传输中的瓶颈

#### 使用Redis发表订阅

![image-20210208111649686](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210208111649686.png)

- 实现`MessageListener`接口，其中
  - `Message message`参数代表Redis发送来的信息
  - `byte[] pattern`是渠道名称
- `RedisMessageListenerContainer`是监听容器，要将连接工厂、任务池(可选)、消息监听器放入，就实现了消息监听

```java
//自定义监听器
@Component
public class RedisMessageListener implements MessageListener{
    @Override
    public void onMessage(Message message, byte[] pattern){
        //消息体
        String body = new String(message.getBody());
        //消息渠道
        String topic = new String(pattern);
        System.out.println(body);
        System.out.println(topic);
    }
}
```

```java
//定义Redis的监听容器
public class Application{
    //Redis连接工厂
    @Autowired
    private RedisConnectionFactory connectionFactory = null;
    //Redis消息监听器
    @Autowired
    private MessageListener redisMsgListener = null;
    
    //连接池
    private ThreadPoolTaskScheduler taskScheduler = null;
    
    @Bean
    public ThreadPoolTaskScheduler initTaskScheduler(){
        if(TaskScheduler != null){
            return taskScheduler;
        }
        taskScheduler = new ThreadPoolTaskScheduler();
        //设置任务池大小为20，可以运行线程，并进行阻塞
        taskScheduler.setPoolSize(20);
        return taskScheduler;
    }
    
    @Bean
	public RedisMessageListenerContainer initRedisContainer(){
        //新建连接器
		RedisMessageListenerContainer container = new RedisMessageListenerContainer();
		//设置连接工厂
		container.setConnectionFactory(connectionFactory);
        //设置任务池[可选]
        container.setTaskExecutor(initTaskScheduler());
		//新建消息渠道
		Topic topic = new ChannelTopic(("topic1"));
		//添加监听器
		container.addMessageListener(redisMessageListener,topic);
		//自动装配
		return container;
	}

}
```

#### 缓存管理器配置

```properties
#如果由底层的缓存管理器支持创建，以逗号分隔的列表来缓存名称，便于注解的引用
spring.cache.cache-names=redisCache
#是否允许Redis缓存空值
spring.cache.redis.cache-null-values=true
#Redis的键前缀
spring.cache.redis.key-prefix=
#缓存超时时间戳，配置为 0 则不设置超时时间
spring.cache.redis.time-to-live=0ms
#是否启用Redis的键前缀
spring.cache.redis.use-key-prefix=true
#缓存类型，在默认的情况下，Spring会自动根据上下文探测
spring.cache.type=redis
```

#### 注解

##### @EnableCaching

- 在配置类中加上这个注解，就可以启用Spring缓存

##### @CachePut

- 用来将被注释方法返回的结果存放到缓存中
- 在更新数据库的操作中，**不要从缓存中读取数据**，因为缓存是不可信的！
- `value`：缓存名，即配置文件中的`spring.cache.cache-names`的值
- `key`：是一个Spring EL表达式，用来设置键名
  - 如`'redis_user_'+#id`中，`#id`是通过参数名匹配
  - 还可以通过`#a[0], #p[0], #a[1], #p[1] ...`来匹配第零个参数、第一个参数...
  - `#result`代表方法的返回结果对象，是在MyBatis回填之后的值，`#result.id`代表返回结果中的id属性
- `condition`：是一个Spring EL表达式，要求返回Boolean值，如果为true，就使用缓存操作，否则执行方法
  - 如`#result != 'null'`，如果返回`null`，就不再操作缓存

##### @Cacheable

- 用来从缓存中读取结果，如果结果存在，则返回，否则执行被注释的方法，并将结果**保存到缓存中**
- `value`：同上
- `key`：同上
- `condition`：同上

##### @CacheEvict

- 通过定义的键移除缓存
- `value`：同上
- `key`：同上
- `condition`：同上
- `beforeInvocation`：表示在方法前还是在方法后删除缓存，默认是`false`，即在方法后移除缓存

#### 缓存注解实例

**用户实体类**

```java
package com.studyspringboot.ch7.pojo;

import ...

@Alias("user")
public class User implements Serializable {
	private static final long serialVersionUID = 776061456107358247L;
	private Long id;
	private String userName;
	private String note;

	/**Getter and Setter*/
}
```

**数据库接口**

```java
package com.studyspringboot.ch7.dao;

import ...

@Repository
public interface MyDao {
	//获取单个用户
	User getUser(Long id);
	//插入用户
	int insertUser(User user);
	//更新用户
	int updateUser(User user);
	//查询用户
	List<User> findUsers(@Param("userName") String userName, @Param("note") String note);
	//删除用户
	int deleteUser(Long id);
}

```

**MyBatis映射文件**

```xml
<?xml version="1.0" encoding="utf-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.studyspringboot.ch7.mycache.dao.MyDao">
    <!--通过id查找用户-->
    <select id="getUser" parameterType="long" resultType="user">
        select id, user_name as userName, note from user where id=#{id}
    </select>
    <!--插入用户-->
    <insert id="insertUser" useGeneratedKeys="true" keyProperty="id" parameterType="user">
        insert into user(user_name, note) values(#{userName}, #{note})
    </insert>
    <!--更新用户信息-->
    <update id="updateUser">
        update user
        <set>
            <if test="userName != null">
                user_name =#{userName},
            </if>
            <if test="note != null">
                note =#{note}
            </if>
        </set>
        where id = #{id}
    </update>
    <!--通过用户名和简介查找用户-->
    <select id="findUsers" resultType="user">
        select id, user_name as userName, note from user
        <where>
            <if test="userName != null">
                and user_name=#{userName}
            </if>
            <if test="note != null">
                and note = #{note}
            </if>
        </where>
    </select>
    <!--删除用户-->
    <delete id="deleteUser" parameterType="long">
        delete from user where id = #{id}
    </delete>
</mapper>
```

**配置文件**

```properties
#ch7
#MyBatis
mybatis.mapper-locations=sql/userMapperch7.xml
mybatis.type-aliases-package=com.studyspringboot.ch7
#redis
spring.redis.host=ip
spring.redis.port=port
spring.redis.password=password
#缓存管理器
spring.cache.cache-names=redisCache
spring.cache.type=redis

```

**控制器**

```java
package com.studyspringboot.ch7.controller;

import ...

@Controller
public class MyController {
	@Autowired
	private MyService myService = null;
	
    //通过id查找用户
	@RequestMapping("/getUser")
	@ResponseBody
	public User getUser(Long id){
		return myService.getUser(id);
	}
    //插入用户
	@RequestMapping("/insertUser")
	@ResponseBody
	public User insertUser(String userName, String note){
		User user = new User();
		user.setUserName(userName);
		user.setNote(note);
		myService.insertUser(user);
		return user;
	}
	//通过用户名和简介查找用户
	@RequestMapping("/findUsers")
	@ResponseBody
	public List<User> findUsers(String userName, String note){
		return myService.findUsers(userName,note);
	}
	//更新用户信息
	@RequestMapping("/updateUserName")
	@ResponseBody
	public Map<String,Object> updateUserName(Long id, String userName){
		User user = myService.updateUserName(id,userName);
		boolean flag = user != null;
		String message = flag?"update success":"update fail";
		return resultMap(flag,message);
	}
	//删除用户
	@RequestMapping("/deleteUser")
	@ResponseBody
	public Map<String, Object> deleteUser(Long id){
		int result = myService.deleteUser(id);
		boolean flag = result==1;
		String message = flag? "del success":"del fail";
		return resultMap(flag,message);
	}

	private Map<String,Object> resultMap(boolean success, String message){
		Map<String, Object> map = new HashMap<>();
		map.put("flag",success);
		map.put("message",message);
		return map;
	}
}
```

**服务**

```java
package com.studyspringboot.ch7..service;

import ...

public interface MyService {
	public User insertUser(User user);
	public User getUser(Long id);
	public User updateUserName(Long id, String userName);
	public List<User> findUsers(String userName, String note);
	public int deleteUser(Long id);
}
```

```java
package com.studyspringboot.ch7.service;

import ...

@Service
public class MyServiceImpl implements MyService {
	@Autowired
	private MyDao myDao= null;

    //插入用户
	@Override
	@Transactional
	@CachePut(value="redisCache",key = "'redis_user_'+#result.id")
	public User insertUser(User user) {
		myDao.insertUser(user);
		return user;
	}
	//通过id查找用户
	@Override
	@Transactional
	@Cacheable(value = "redisCache" ,key = "'redis_user_'+#id")
	public User getUser(Long id) {
		return myDao.getUser(id);
	}
	//更新用户信息
	@Override
	@Transactional
	@CachePut(value = "redisCache" ,key = "'redis_user_'+#id", condition = "#result != 'null'")
	public User updateUserName(Long id, String userName) {
		User user = this.getUser(id);
		if(user == null){
			return null;
		}
		user.setUserName(userName);
		myDao.updateUser(user);
		return user;
	}
	//通过用户名和简介查找用户
	@Override
	public List<User> findUsers(String userName, String note) {
		return myDao.findUsers(userName,note);
	}
	//删除用户
	@Override
	@Transactional
	@CacheEvict(value = "redisCache" ,key = "'redis_user_'+#id",beforeInvocation = false)
	public int deleteUser(Long id) {
		return myDao.deleteUser(id);
	}
}
```

主函数

```java
package com.studyspringboot.ch7.main;

import ...

@SpringBootApplication(scanBasePackages = {"com.studyspringboot.ch7.mycache"})
@MapperScan(basePackages = "com.studyspringboot.ch7.mycache", annotationClass = Repository.class)
//启用缓存
@EnableCaching
public class Application {
	@Autowired
	private RedisConnectionFactory connectionFactory = null;
	@Autowired
	private RedisTemplate redisTemplate = null;
    
	@PostConstruct
	public void init(){
		initRedisTemplate();
	}
    //配置序列化器
	private void initRedisTemplate(){
		RedisSerializer stringSerializer = redisTemplate.getStringSerializer();
		redisTemplate.setKeySerializer(stringSerializer);
		redisTemplate.setValueSerializer(RedisSerializer.json());
		redisTemplate.setStringSerializer(stringSerializer);
		redisTemplate.setHashKeySerializer(stringSerializer);
		System.out.println("Serializer");
	}
	public static void main(String[] args) {
		SpringApplication.run(Application.class,args);
	}
}
```

#### 自定义缓存管理器

​	要删除配置文件中关于缓存管理器的配置，之后在配置代码中注入`redisCacheManager`类

```java
//自定义Redis缓存管理器
@Bean(name = "cacheManager")
@Primary
public CacheManager initRedisCacheManager(){
	//Redis加入写入锁
	RedisCacheWriter writer = RedisCacheWriter.lockingRedisCacheWriter(connectionFactory);
	//启动Redis缓存默认配置
	RedisCacheConfiguration config = RedisCacheConfiguration.defaultCacheConfig();
	//设置序列化器为GenericJackson2JsonRedisSerializer
	config = config.serializeValuesWith(RedisSerializationContext.SerializationPair.fromSerializer(new GenericJackson2JsonRedisSerializer()));
	RedisCacheManager redisCacheManager = new RedisCacheManager(writer, config);
	return redisCacheManager;
	//通过builder
	//return RedisCacheManager.builder(connectionFactory).cacheDefaults(config).build();
}
```

#### 缓存自调用失效

​	同数据库事务中的自调用失效

## Spring MVC开发

### 注解

#### @ReqestMapping

- `value`和`path`：都是用来设置请求的URL路径，可以使用正则
- `method`：用来设置HTTP请求类型，如GET，POST
- `params`：当存在对应的 HTTP 参数时才响应请求
- `headers`：限定请求头存在对应的参数时才响应
- `consumes`：限定 HTTP 请求体提交类型，如`application/json`、`text/html`
- `produces`：限定返回的内容类型，仅当HTTP请求头中的（Accept）类型中包含该指定类型时才返回

#### @GetMapping

- 专门用来响应GET方法

#### @PostMapping

- 专门用来响应POST方法

### 获取请求参数

#### 无注解情况

- 要求参数名称和HTTP请求参数名保持一致
- 如果java方法参数是一个类，springboot也会自动尝试注入属性

#### @RequestParam

- 可以在java方法参数前加入注释来确定映射关系
  - 如：`public User getUser(@RequestParam("int_val") Integer intVal)`，将`intVal`映射到`int_val`上

#### 传递数组

- Spring MVC可以接受数组的参数
- 每个数组元素只需要通过逗号分隔
  - 如请求url：`http://localhost/getUser?intArr=1,2,3&longArr=4,5,6`

#### @RequestBody

- 通过在java方法参数前加入注解，Spring MVC会将json请求体转换成对应的类
  - 如`public User getUser(@RequestBody User user) `：将会把json转换成User对象

#### @PathVariable

- 在一些网站中，提出了REST风格，这时参数往往通过URL进行传递

- 如要获取编号为1的用户，URL为`/user/1`

- 通过在java方法参数前加入注解，来获取URL中的参数

  - ```java
    //用{...}表明参数的位置
    @GetMapping("/{id}")
    @ResponseBody
    public User get(@PathVariable("id") Long id){
        return userService.getUser(id);
    }
    ```

#### 获取格式化参数

##### @DateTimeFormat

- 通过在java方法参数前加入注解，可以根据约定的格式把数据转换出来
  - 如`public void getDate(@DateTimeFormat(iso=ISO.DATE) Date date)`：可以解析形如`2017-08-08`
- Spring Boot中也可以在配置文件中设置日期格式，而不用注解
  - `spring.mvc.date-format=yyyy-MM-dd`

##### @NumberFormat

- 通过在java方法参数前加入注解，可以根据约定的格式把数据转换出来
  - 如`public void getNum(@NumberFormate(pattern = "#,###.##" Double number))`：可以解析形如`1,234,567.89`

### 返回类型

#### @ResponseBody

- 将返回类型转换成json格式

### 自定义参数转换规则

![image-20210209214059916](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210209214059916.png)

- 其中Converter、Formatter、GenericConverter都是转化器
- Spring Boot会自动找出所有的转换器，注册到Bean中

#### 一对一转换器|Converter

- 将一种类型转换成另一种类型

- 接口定义

  - ```java
    public interface Converter<S, T>{
        T convert(S source);
    }
    ```

- 在实现了这个接口后，Spring Boot会自动装配，在Controller中也会自动调用

#### 集合和数组转换|GenericConverter

- 会自动寻找对应的Converter转换器

### 数据验证

#### 启用验证

- 使用`@Valid`来启用验证

```java
/***
 * @Valid会开启验证，通过属性上的注解来验证
 * Errors errors是验证POJO后自动填充的
***/
public String validate(@Valid @RequestBody User,Errors errors){
    ...
}
```

#### JSR-303

- 注解在变量的定义上

```java
public class User{
    @NotNull(message = "id不能为空")
    private Long id;
}
```

##### 一些注解

| 注解                        | 作用                                                         |
| --------------------------- | ------------------------------------------------------------ |
| @Null                       | 必须为null                                                   |
| @NotNull                    | 必须非null                                                   |
| @AssertTrue                 | 必须为true                                                   |
| @AssertFalse                | 必须为false                                                  |
| @Min(value)                 | 必须为一个数字，且大于设定的最小值                           |
| @Max(value)                 | 必须为一个数字，且小于设定的最大值                           |
| @DecimalMin(value)          | 必须为一个数字，且大于设定的最小值，且支持BigDecimal等高精度 |
| @DecimalMax(value)          | 必须为一个数字，且小于设定的最大值，且支持BigDecimal等高精度 |
| @Size(max,min)              | 必须在设定的范围内                                           |
| @Digits(integer, faraction) | 必须是一个数字，且在可接受的范围内                           |
| @Past                       | 必须是一个过去的日期                                         |
| @Future                     | 必须是一个将来的日期                                         |
| @Pattern                    | 必须符合指定的正则表达式                                     |

<center>Bean Validation中内置的constraint</center>

| 注解      | 作用                           |
| --------- | ------------------------------ |
| @Email    | 必须是邮箱地址                 |
| @Lenght   | 长度必须在指定范围内           |
| @NotEmpty | 字符串不为空                   |
| @Range    | 被注释的元素必须在合适的范围内 |

<center> Hibernate Validator附加的constraint</center>

### 自定义参数验证

- Spring除了可以注册转换器，还能注册验证器

  - 接口定义

  - ```java
    public interface Validator{
        //用来判断当前验证器是否支持该Class类型
        boolean supports(Class<?> clazz);
        //如果是支持的类型，就执行这个方法来验证
        //Errors为错误对象
        void validate(Object target, Errors errors);
    }
    ```

#### 实例

**自定义用户验证器**

```java
public class UserValidator implements Validator{
    @Override
    public boolean supports(Class<?> clazz){
        return clazz.equals(User.class);
    }
    //验证逻辑
    @Override
    public void validate(Object target, Errors errors){
        //对象为空
        if(target==null){
            //直接在参数处报错，不进入控制器的方法
            errors.rejectValue("",null,"用户不能为空");
            return;
        }
        User user=(User) target;
        if(StringUtils.isEmpty(user.getUserName())){
            //增加错误，可以进入控制器方法
            errors.rejectValue("userName",null,"用户名不能为空")
        }
    }
}
```

**绑定验证器**

- 使用`@InitBinder`注解可以改变WebDataBinder流程
- 处理器会先执行被注解的方法，可以将WebDataBinder作为参数传入
- 在执行完被注解的方法之后，才会执行控制器方法

```java
public class UserController{
    //调用控制器前先执行这个方法
    @InitBinder
    public void initBinder(WebDataBinder binder){
        //绑定验证器
        binder.setValidator(new UserValidator());
        //定义日期参数格式，参数不再需用注解@DateTimeFormat,boolean参数辨识是否允许为空
        binder.registerCustomEditor(Date.class, neew CustomDateEditor(new SimpleDateFormat("yyyy-MM-dd"), false));
    }
}
```

- 在使用注解`＠Valid`标注`User`参数后，Spring MVC就会去遍历对应的验证器，当遍历到UserValidator时，会去执行它的 supports 方法
- 返回`true`后，Spring MVC会使用这个验证器去验证User类的数据

### 数据模型

### 视图和视图解析器

### 文件上传

#### Spring MVC对文件上传的支持

​	使用适配器模式，将HttpServletRequest接口对象转换为MultipartHttpServletRequest对象。MultipartHttpServletRequest接口拓展了HttpServletRequest的所以方法，并**添加了操作文件的方法**。

![image-20210217195755803](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210217195755803.png)

#### 配置文件

```properties
#是否启用Spring MVC多部分上传功能
spring.servlet.multipart.enabled=true
#将文件写入磁盘的阈值。可以用"MB"、"KB"表示大小
spring.servlet.mutipart.file-size-threshold=0
#指定默认上传的文件夹
spring.servlet.multipart.location=
#限制单个文件最大大小
spring.servlet.multipart.max-file-size
#限制所有文件最大大小
spring.servlet.mutipart.max-request-size=
#是否延迟多部件文件请求的参数和文件的解析
spring.servlet.multipart.resolve-lazily=false
```

#### 实例

```java
@Controller
public class FileController{
    //使用HttpServletRequest作为参数
    @PostMapping("/HttpServletRequest")
    public boolean uploadRequest(HttpServletRequest req){
        //强制转换为MultipartHttpServletRequest接口对象
        if(request instanceof MultipartHttpServletRequest){
            mreq = (MultipartHttpServletRequest)req;
        }else{
            return false;
        }
        //获取MultipartFile文件信息
        MultipartFile mf = mreq.getFile("file");
        //获取文件名，用文件名创建文件
        File file = new File(mf.getOriginalFilename);
        try{
            //保存文件
            mf.transferTo(file);
        }catch(Exception e){
            ...
        }
        ...
    }
    //使用Spring MVC的MultipartFile类作为参数
    @PostMapping("/MultipartFile")
    public boolean uploadRequest(MultipartFile file){
        //使用方法和上面一致
        ...
    }
    //使用Part作为参数
    @PostMapping("/Part")
    public boolean uploadPart(Part file){
        //获取提交文件名称
        String fileName = file.getSubmittedFileName();
        try{
            //写入文件
            file.write(fileName);
        }catch(Exception e){
            ...
        }
        ...
    }
}
```

### 拦截器

#### 拦截器设计

![image-20210218174038154](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210218174038154.png)

- 拦截器接口定义

  - ```java
    public interface HandlerInterceptor{
        //处理器执行前方法
        default boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
            return true;
        }
        //处理器处理后方法
        default void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, @Nullable ModelAndView modelAndView) throw Exception{
        }
        //处理器完成后方法
        default void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, @Nullable Exception ex) throws Exception{
        }
    }
    ```

#### 实例

**自定义拦截器**

```java
package com.studyspringboot.ch10.inteceptor;

import ...

public class MyInterceptor implements HandlerInterceptor {
	@Override
	public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
		System.out.println("pre");
		return true;
	}

	@Override
	public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
		System.out.println("post");
	}

	@Override
	public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
		System.out.println("after");
	}
}
```

**注册拦截器**

```java
package com.studyspringboot.ch10.inteceptor;

import ...

@SpringBootApplication
public class Application implements WebMvcConfigurer {
	public static void main(String[] args) {
		SpringApplication.run(Application.class,args);
	}

	@Override
	public void addInterceptors(InterceptorRegistry registry) {
		//注册拦截器到MVC机制，然会一个拦截器的注册
		InterceptorRegistration ir = registry.addInterceptor(new MyInterceptor());
		//指定拦截匹配模式
		ir.addPathPatterns("/interceptor/*");
	}
}
```

**控制器**

```java
package com.studyspringboot.ch10.inteceptor;

import ...

@Controller
@RequestMapping("/interceptor")
public class MyController {
	@RequestMapping("test")
	@ResponseBody
	public boolean test(){
		return true;
	}
}
```

#### 拦截顺序

- 对于处理器前方法采用先注册先执行
- 而处理器后方法和完成方法则是先注册后执行的规则

#### 拦截器与过滤器的区别

>1. 拦截器是基于java的**反射机制**的，而过滤器是基于**函数回调**。
>2. 拦截器不依赖与servlet容器，过滤器依赖与servlet容器。
>3. 拦截器只能对action请求起作用，而过滤器则可以对几乎所有的请求起作用。
>4. 拦截器可以访问action上下文、值栈里的对象，而过滤器不能访问。
>5. 在action的生命周期中，拦截器可以多次被调用，而过滤器只能在容器初始化时被调用一次
>
>**执行顺序** ：过滤前 - 拦截前 - Action处理 - 拦截后 - 过滤后。

### 国际化

### Spring MVC拾遗

#### 获取请求头参数

- 使用`@RequestHeader`注解

- 例如

  - ```java
    @RequestMapping("/test")
    @ResponseBody
    public User headerUser(@RequestHeader("id") Long id){
        return userService.getUser(id);
    }
    ```

#### 跨域访问

@CrossOrigin

## 构建REST风格网站

## Spring Security

自定义认证服务->

UserDetailsBuilder：用户详情构造器

Principal

### 使用WebSecurityConfigurerAdapter自定义

​	总的来说，Spring Security通过`SecurityConfigurrer`接口来配置Spring Security。而`WebSecurityConfigurerAdapter`抽象类默认实现了基本的设置，用户也可以通过继承重写他的方法来自定义功能，而不用从零开始配置。

**WebSecurityConfigurerAdapter中的三个默认方法**

```java
...
//AuthenticationManagerBuilder是签名器构造器，用于构建用户的具体权限控制
//用来配置用户签名服务，可以重写这个方法来自定义用户服务器、加密编码器等
protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        this.disableLocalConfigureAuthenticationBldr = true;
}
//用来配置Filter链
public void configure(WebSecurity web) throws Exception {
}
//用来配置拦截保护的请求，比如什么需要放行什么需要验证
protected void configure(HttpSecurity http) throws Exception {
    http.authorizeRequests((requests) -> {
        ((AuthorizedUrl)requests.anyRequest()).authenticated();
    });
    //启用默认的登录
    http.formLogin();
    http.httpBasic();
}
...
```

### 自定义认证服务

- 我们可以通过重写第一个方法来自定义密码编码器和用来读取用户信息的方式
- 有多种密码编码器，这里介绍两种
  - BCryptPasswordEncoder：是一种单向哈希值，但是如果设置了简单的密钥，任意被枚举来反向猜出未加密的密码
  - Pbkdf2PasswordEncoder：使用基于口令的密钥派生算法，可以设置密钥，只有拿到密钥才能通过加密算法对密码进行匹配。

- 有多种读取用户权限信息的方式，可以用`AuthenticationManagerBuilder`类的方法来定义

  - `inMemoryAuthentication()`：将用户信息存储在内存中
  - `jdbcAuthentication()`：可以通过它的方法来设定数据源和查询语句，来从数据库从匹配用户信息
  - `userDetailsService()`：通过自定义实现了`UserDetailsService`接口的类来读取用户信息，我主要使用了这个

  从上文我们了解到，我们只要实现了`UserDetailsService`接口，就可以使用我们想用的任何方法来存储用户权限信息

**UserDetailsService接口**

```java
public interface UserDetailsService {
	UserDetails loadUserByUsername(String username) throws UsernameNotFoundException;
}
```

​	我们发现，这个接口就一个方法，这个方法是通过传入**用户名**来查询出一个实现了`UserDetails`接口的类，之后再通这个类来判断当前用户的权限信息

**UserDetails接口**

```java
public interface UserDetails extends Serializable {
	//权限列表，存储了当前用户的权限
	Collection<? extends GrantedAuthority> getAuthorities();
	//获取用户密码
	String getPassword();
	//获取用户名
	String getUsername();
	...
}
```

​	这个接口有3个实现类：![image-20210224202924680](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224202924680.png)

我使用了他的第三个实现类`User`

**User类**

```java
public class User implements UserDetails, CredentialsContainer {
	...
    //用户名
	private String password;
	//密码
	private final String username;
	//用户权限表
	private final Set<GrantedAuthority> authorities;
	//账号是否过期
	private final boolean accountNonExpired;
	//账号是否被锁定
	private final boolean accountNonLocked;
	//账号凭证是否过期
	private final boolean credentialsNonExpired;
	//账号是否被禁用
	private final boolean enabled;
	//通过用户名、密码和权限表来构造
	public User(String username, String password, Collection<? extends GrantedAuthority> authorities) {
		this(username, password, true, true, true, true, authorities);
	}
	//通过以上信息来构造
	public User(String username, String password, boolean enabled, boolean accountNonExpired,
			boolean credentialsNonExpired, boolean accountNonLocked,
			Collection<? extends GrantedAuthority> authorities) {
		Assert.isTrue(username != null && !"".equals(username) && password != null,
				"Cannot pass null or empty values to constructor");
		this.username = username;
		this.password = password;
		this.enabled = enabled;
		this.accountNonExpired = accountNonExpired;
		this.credentialsNonExpired = credentialsNonExpired;
		this.accountNonLocked = accountNonLocked;
		this.authorities = Collections.unmodifiableSet(sortAuthorities(authorities));
	}
...
}
```

​	我只列出了他的属性和构造函数，我们发现，我们只要有**用户名**，**密码**和**权限表**，就可以创建出一个UserDetails了

- 所以总的来说，想要自定义一个认证服务，只要一下几点
  - 再数据库或用其他任何方法保存用户名、密码和对应的权限。当然，我们可以把他定义的User类的所有信息都存储到数据库中，但是这里进行了简化，数据库就存储了用户表、权限表和用户权限表。
  - 我们自己写一个类实现**UserDetailsService接口**，他可以通过传入一个用户名来从数据库中查出用户信息，并封装成`UserDetails`类
  - 最后认证服务通过我们的**UserDetailsService接口的实现类**，可以通过用户名来查询用户权限信息，并比较用户权限了

#### 实现

##### 数据库表

**t_role**

​	其中权限的前缀`Role_`为Spring Security中默认要拥有的，而后面的权限名可以随意

![image-20210224215233068](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224215233068.png)

```sql
CREATE TABLE `t_role` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `role_name` varchar(60) NOT NULL,
  `note` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`)
) 
```

**t_user**

![image-20210224215419492](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224215419492.png)

```sql
CREATE TABLE `t_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(60) NOT NULL,
  `pwd` varchar(100) NOT NULL,
  `available` int(1) DEFAULT '1',
  `note` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_name_UNIQUE` (`user_name`)
)
```

**t_user_role**

![image-20210224215451960](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224215451960.png)

```sql
CREATE TABLE `t_user_role` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `role_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `role_user` (`role_id`,`user_id`),
  KEY `FK1_idx` (`role_id`),
  KEY `FK2_idx` (`user_id`),
  CONSTRAINT `FK1` FOREIGN KEY (`role_id`) REFERENCES `t_role` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK2` FOREIGN KEY (`user_id`) REFERENCES `t_user` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
)
```

##### 实现UserDetailsService接口

- 实现一个UserDetailsServiceImpl类
  - UserRoleService是访问数据库的服务层，可以从中获取数据库的用户信息
  - 我使用Mybatis来实现访问数据库，用Redis缓存用户信息

**UserDetailsServiceImpl类**

```java
package com.studyspringboot.ch12.user.service;

import ...

@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    //注入UserRoleService，可以通过用户名查询用户信息和权限列表
	@Autowired
	UserRoleService userRoleService;

	@Override
	public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException {
        //MyUser为业务的用户实体类，可以获取用户名、密码，与t_user表对应
		MyUser user = userRoleService.findUserByName(s);
        //获取权限列表
        //Role为我自定义的权限类，与t_role表对应
		List<Role> roles = userRoleService.findRolesByUserName(s);
        //将以上信息转换为UserDetails
		UserDetails userDetails = changeToUserDetails(user, roles);
		return userDetails;
	}
	private UserDetails changeToUserDetails(MyUser user, List<Role> roles){
        //声明一个权限列表
		List<GrantedAuthority> auths = new ArrayList<>();
        //将查询出的权限表转换为需要的类型
		for(Role role : roles){
            //SimpleGrantedAuthority是一个简易的GrantedAuthority实现类
            //可以通过自定义权限名构造
			GrantedAuthority grantedAuthority = new SimpleGrantedAuthority(role.getRoleName());
            //向list中添加用户
			auths.add(grantedAuthority);
		}
        //构造用户
		UserDetails userDetails = new User(user.getUserName(),user.getPwd(),auths);
		return userDetails;
	}
}
```

**配置AuthenticationManagerBuilder**

```java
package com.studyspringboot.ch12.user.main;

import ...

@Component
public class WebSecurityConfigurer extends WebSecurityConfigurerAdapter {
	@Autowired
	UserDetailsServiceImpl userDetailsService;

    //从配置文件中读取密钥
	@Value("${system.user.password.secret}")
	private String secret = null;

	@Override
	protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        //密码编码器
		PasswordEncoder encoder = new Pbkdf2PasswordEncoder(secret);
        //设置我们自定义的UserDetailsService和密码编码器
		auth.userDetailsService(userDetailsService)
				.passwordEncoder(encoder);
	}
}
```

### 限制请求

- 我们可以给不同的路径设置不同的访问权限，也可以设置权限不足和未登录时的跳转页面
  - 通过重写`configure`方法来实现
  - 也可以通过注解设置权限

#### 通过重写方法

```java
package com.studyspringboot.ch12.user.main;

import ...

@Component
public class WebSecurityConfigurer extends WebSecurityConfigurerAdapter {
    
	@Override
	protected void configure(HttpSecurity http) throws Exception {
        //以下都只是我使用的部分设置
        
        //关闭CSRF防护
        //如果不关闭，所有的POST请求都需要返回一个token才能访问到，这里暂时关闭
		http.csrf().disable();
		//设置访问权限
		http.authorizeRequests()
			.antMatchers("/admin").hasRole("ADMIN")//只有ADMIN可以访问
			.antMatchers("/user").hasAnyRole("ADMIN","USER")//ADMIN或USER都可以访问
			.antMatchers("/logout").authenticated()//登录后才能访问
			.anyRequest().permitAll();//未被配置的路径，所有人都可以访问
        //权限控制还可以通过access方法通过SpEL表达式来控制权限，如
        //http.authorizeRequests().anyRequest().access("hasRole('USER') or hasRole('ADMIN')")

        //启用默认的登录页面
		http.formLogin()
            .loginPage("/login")//设置登录页面，默认为/login
            .loginProcessingUrl("/dologin")//设置登录请求的路径，我们也可以通过post直接请求通过这个路径来登录
            //可以设置登录成功跳转的页面，传入一个AuthenticationSuccessHandler
            //登录失败等页面同理
            .successHandler(new AuthenticationSuccessHandler() {
			@Override
			public void onAuthenticationSuccess(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Authentication authentication) throws IOException, ServletException {
                //通过writer打印一个success代表登录成功
				PrintWriter writer = httpServletResponse.getWriter();
				writer.write(new ObjectMapper().writeValueAsString("success"));
				writer.flush();
				writer.close();
			}
		});
        //后面要改用我们自己的Controller控制登录，要关闭默认的登录
		//http.formLogin().disable();
        //同上
		//http.logout().disable();

		//设置登录后权限不足的页面
		http.exceptionHandling().accessDeniedPage("/accessDenied");
		//设置未登录时的页面
		//LoginUrlAuthenticationEntryPoint是一个AuthenticationEntryPoint的实现类，可以定义登录页面，会自动重定向到登录页
		AuthenticationEntryPoint authenticationEntryPoint = new LoginUrlAuthenticationEntryPoint("/login.html");
		http.exceptionHandling().authenticationEntryPoint(authenticationEntryPoint);
	}
}
```

#### 通过注解

##### @PreAuthorize

- 被注释的方法在**执行前**会被检查是否有权限

- 可以在任何方法，包括`@RequestMapping`注释的方法上，来限制请求

- 参数为一个SpEL表达式

- 如

  - ```java
    @PreAuthorize("#id<10")
    public User find(int id) {
    	System.out.println("find user by id........." + id);
    	return null;
    }
    ```

##### @PostAuthorize

- 在方法**运行后**才进行权限检查，其他基本相同

- 有一个`returnObject`来代表返回的结果

- 如

  - ```java
    @PostAuthorize("returnObject.id%2==0")
    public User find(int id) {
        User user = new User();
        user.setId(id);
    	return user;
    }
    ```

##### @PreFilter

##### @PostFilter

#### SpEL表达式配置权限

| 方法                      | 含义                                           |
| ------------------------- | ---------------------------------------------- |
| `authentication()`        | 用户认证对象                                   |
| `denyAll()`               | 拒绝任何访问                                   |
| `hasAnyRole(String ... )` | 当前用户是否存在参数中列明的对象属性           |
| `hasRole(String)`         | 当前用户是否存在角色                           |
| `hasipAddress(String)`    | 是否请求来自指定的 IP                          |
| `isAnonymous()`           | 是否匿名访问                                   |
| `isAuthenticated()`       | 是否用户通过认证签名                           |
| `isFullyAuthenticated()`  | 是否用户是完整验证，即非”记住我“功能通过的认证 |
| `isRememberMe()`          | 是否是通过”记住我“功能通过的验证               |
| `permitAll()`             | 无条件允许任何访问                             |
| `principal()`             | 用户的 principal 对象                          |

<center>Spring Security中的Spring表达式方法</center>

### 通过自定义Controller进行用户验证

> security的认证判断是通过authenticationManager去判断构造的UsernamePasswordToken，然后生成验证通过后Authentication，将这个Authentication放入SecurityContextHolder中即可实现认证。
>
> 可以在controller层直接注入authenticationManager
>
> 来自[spring security controller层实现登陆](https://blog.csdn.net/qq_34675369/article/details/91499798)

​	我们先来看看用来验证我们的用户信息的`AuthenticationManager`接口

**AuthenticationManager接口**

- AuthenticationManager是一个接口，用来验证传入的`Authentication`

- 他会验证**用户凭证**、是否被禁用，是否被锁定等等
- 如果验证失败就抛出异常
- 验证成功就返回一个完全经过身份验证的对象，包括凭据

```java
public interface AuthenticationManager {
	Authentication authenticate(Authentication authentication) throws AuthenticationException;
}
```

​	我们继续探究传入的`Authentication`，发现它也是一个接口，他有很多实现类：![image-20210224230302448](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224230302448.png)

​	最后一个实现类`UsernamePasswordAuthenticationToken`，他的说明：

> An  link org.springframework.security.core.Authentication implementation that isdesigned for simple presentation of a username and password.

​	大概是一个通过用户名和密码设计的简单实现类，他的其中一个构造函数就是通过账号密码为参数的。

 	所以我们通过账号密码就可以构建一个`Authentication`，之后把构建的类传入`AuthenticationManager`，进行验证，如果通过验证，就会返回一个身份对象，最后我们再将返回的身份对象放入`SecurityContextHolder`的`SecurityContext`中，就完成了用户的验证，并记录了用户的登录信息。

​	通过以上，我们就完成了登录，所以我们现在只要获取到`AuthenticationManager`类就好了。发现在`WebSecurityConfigurerAdapte`中，也就是我们上文中的配置类，就有`AuthenticationManager`，所以我们只要将配置类的`AuthenticationManager`装配到Bean中即可，方法如下：

**配置类**

```java
package com.studyspringboot.ch12.user.main;

import ...

@Component
public class WebSecurityConfigurer extends WebSecurityConfigurerAdapter {
	...
	@Override
	protected void configure(HttpSecurity http) throws Exception {
		...
        //关闭默认的登录配置
		http.formLogin().disable();
		http.logout().disable();
		...
	}
    //将AuthenticationManager装配到Bean中
	@Bean
	@Override
	protected AuthenticationManager authenticationManager() throws Exception {
		return super.authenticationManager();
	}

}
```

**Controller层**

```java
package com.studyspringboot.ch12.user.controller;

import ...

@Controller
public class UserController {
	...
    //注入AuthenticationManager
	@Autowired
	private AuthenticationManager authenticationManager;
    //登录
    //JsonLogin为我自定义的类，保存了账户密码
	@PostMapping("/login")
	@ResponseBody
	public String login(@RequestBody @Valid JsonLogin json){
        //通过用户名密码创建一个token
		UsernamePasswordAuthenticationToken token = new UsernamePasswordAuthenticationToken(json.getUsername(), json.getPassword());
        //验证生成authenticate
		Authentication authenticate = authenticationManager.authenticate(token);
        //将authenticate放入SecurityContextHolder
		SecurityContextHolder.getContext().setAuthentication(authenticate);
		return "success";
	}
    //登出
	@GetMapping("/logout")
	@ResponseBody
	public Map<String, Object>logout(){
        //清除当前用户的上下文
		SecurityContextHolder.clearContext();
		return "success";
	}
}

```

### 关于CSRF

关于csrf：[CSRF攻击与防御](https://blog.csdn.net/stpeace/article/details/53512283)

​	我的实现是使用将随机的token放在cookie中传回，之后通过js在请求头加入我传入的token就可以在前后端分离的情况下完成POST请求

```java
package com.studyspringboot.ch12.user.main;

import ...

@Component
public class WebSecurityConfigurer extends WebSecurityConfigurerAdapter {
    ...
	@Override
	protected void configure(HttpSecurity http) throws Exception {
		...
        //启用csrf，并将其设置为在cookie中传递
		http.csrf().csrfTokenRepository(CookieCsrfTokenRepository.withHttpOnlyFalse());
		...
	}
	...
}
```

​	在完成了上述配置，我们访问页面后，它会多回传一个cookie，key为`XSRF-TOKEN`，如：![image-20210224232222520](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224232222520.png)

​	如果前端想要发送POST请求，就需要在请求头加入一个`X-XSRF-TOKEN`字段，字段值为cookie中的值，之后这个POST就可以响应了，也防止了CSRF攻击

![image-20210224232428015](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210224232428015.png)

### 获取登录的用户信息

- 在Controller中可以在`Principal principal`参数中获取当前登录用户的信息
- 如果用户登录，可以使用`getName()`方法获取用户名
- 如果用户未登录，会返则是一个String类型，值为`"anonymousUser"`

```java
@GetMapping("/admin")
@ResponseBody
public MyUser admin(Principal principal){
    //判断是否登录
	if("anonymousUser".equals(principal)){
		return null;
	}
    //通过getName方法获取用户名
	MyUser user = service.findUserByName(principal.getName());
	return user;
}
```

### 记住我功能

​	上面的登录是通过Session来记录用户的登录状态的，所以当用户关闭页面后，就要重新登录，是否不方便。而remember me可以解决这一问题。

## Spring Cloud

配置

@LoadBalance

开启负载均衡，默认提供轮询负载均衡算法

负载均衡的其他算法

### Ribbon

DiscoveryClient

RestTemplate



### Feign

@FeignClient

### Hystrix

@HystrixCommand

@FeignClient集成Hystrix

### Zuul

@EnableZuulProxy

自带熔断

ZuulFallbackProvider

接口 异常处理

ZuulFilter

接口 过滤器

#### 遇到问题

出现`Load balancer does not have available server for client`

原因：idea maven默认导入的spring cloud不兼容

@SpringCloudApplication

启用spring boot应用、开发服务发现和断路器功能

## REST风格

@PathVariable

## Spring Boot单元测试

### 遇到的坑

#### Test类无法加载自定义的配置文件

原类中的`@PropertySource`路径要加`classpath`