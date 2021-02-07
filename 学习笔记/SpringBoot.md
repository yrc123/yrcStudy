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

##### 使用@MapperScan装配MyBatis

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