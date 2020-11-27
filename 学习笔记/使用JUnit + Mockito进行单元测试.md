# 使用JUnit + Mockito进行单元测试

本文只记录了最基础的单元测试方法，更详细的要查看文档

## JUnit|[Junit5中文文档](https://doczhcn.gitbook.io/junit5/)

JUnit是用于编写和运行可重复的自动化测试**开源**测试项目框架，这样可以保证我们的代码按与其工作。JUnit可广泛用于工业和作为支架（从命令行）或IDE（如IDE）内单独的java程序。

### 安装

**使用maven安装**

```xml
<dependency>
	<groupId>junit</groupId>
	<artifactId>junit</artifactId>
</dependency>
```

### JUnit5注解

**以下是一些JUnit5中常用的注解**

| 注解               | 描述                                                         |
| ------------------ | ------------------------------------------------------------ |
| @Test              | 表示方法是测试方法。                                         |
| @ParameterizedTest | 表示方法是[参数化测试](#参数化测试)。                        |
| @BeforeEach        | 表示被注解的方法应在当前类的**每个**@Test，@RepeatedTest，@ParameterizedTest或@TestFactory方法**之前**执行。 |
| @AfterEach         | 表示被注解的方法应在当前类的**每个**@Test，@RepeatedTest，@ParameterizedTest或@TestFactory方法**之后**执行。 |
| @BeforeAll         | 表示被注解的方法应该在当前类的所有@Test，@RepeatedTest，@ParameterizedTest和@TestFactory方法**之前**执行。与@BeforeEach不同的是每个测试类只执行一次，且只能注释静态方法 |
| @AfterAll          | 表示被注解的方法应该在当前类的所有@Test，@RepeatedTest，@ParameterizedTest和@TestFactory方法**之后**执行。与@BeforeEach不同的是每个测试类只执行一次，且只能注释静态方法 |
| @Disabled          | 用于禁用测试类或测试方法                                     |
| @DisplayName       | 声明测试类或测试方法的自定义显示名称。                       |

### <span id="参数化测试">参数化测试</span>

​	参数化测试可以用不同的参数多次运行测试。它们和普通的`@Test`方法一样声明，但是使用`@ParameterizedTest`注解。另外，您必须声明至少一个将为每次调用提供参数的*来源(source)*。

```java
@ParameterizedTest
@ValueSource(strings = { "racecar", "radar", "able was I ere I saw elba" })
void palindromes(String candidate) {
    assertTrue(isPalindrome(candidate));
}
```

### 测试类

测试类一般都在test文件夹下，而且包结构与被测试类相同

```java
import static org.junit.jupiter.api.Assertions.fail;

import ...
//@SpringBootTest
//如果要使用在SpringBoot中托管，就要加上这个注解
class StandardTests {

    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }

    @Test
    void succeedingTest() {
    }

    @Test
    void failingTest() {
        fail("a failing test");
    }

    @Test
    @Disabled("for demonstration purposes")
    void skippedTest() {
        // not executed
    }

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }

}
```

其中，测试类方法中经常使用**断言**来判断测试结果

### 断言

JUnit提供了许多断言方法，是`org.junit.jupiter.Assertions`中的静态方法。以下列举一些常用方法

| 方法名       | 作用                                                         |
| ------------ | ------------------------------------------------------------ |
| assertEquals | 比较期望和实际是否相同                                       |
| assertTrue   | 判断结果是否为真                                             |
| assertFalse  | 判断结果是否为假                                             |
| assertAll    | 在assertAll中可以加入多个断言，还可以输出提示信息，类似于断言分组。与使用多个assertEquals不同，在前面的断言失败后，之后的断言仍然会被执行，而且全部断言的结果都会被打印出来 |

## Mockito|[Mockito 中文文档](https://github.com/hehonghui/mockito-doc-zh/blob/master/README.md)

Mockito库能够Mock对象、验证结果以及打桩(stubbing)。Mockito经常与JUnit搭配使用。

### Mock的作用

​	Mock 测试就是在测试过程中，对于某些不容易构造（如 HttpServletRequest 必须在Servlet 容器中才能构造出来）或者不容易获取比较复杂的对象（如 JDBC 中的ResultSet 对象），用一个虚拟的对象（Mock 对象）来创建以便测试的测试方法。

如果我想对A进行单元测试，那A依赖于BC，而C又有自己的依赖链，如果要构建A，就需要吧BCDE都构建出来，这样就**失去了单元测试的意义**

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/image004.jpg)

而mock可以将这些依赖解耦，实现真正的单元测试

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/image010.jpg)

### 创建Mock

#### Mock

可以用`mock(class)`方法创建一个mock对象

#### Spy

可以用`spy(class)`方法创建一个监控对象。当你使用这个spy对象时真实的对象也会也调用，除非它的函数被stub了。

即由`spy`创建的对象，在其方法被插桩之前，都是调用原函数的方法。

### 注解创建Mock

#### @Mock

同mock方法

#### @Spy

同spy方法

#### @InjectMocks

可以把`mock`或`spy`注入被注解的对象的`@Autowired`成员中。因为在单元测试中，无法把`mock`或`spy`的对象进行注入，所以可以使用`@InjectMocks`进行注入。使用方法见[实例](#实例)

### 验证行为

`verify(对象[, times(执行次数)]).方法(参数...)`

一旦mock对象被创建了，mock对象会记住所有的交互。

### 测试桩

测试桩有两种风格

#### when...then

`when(对象.方法(...)).[then,thenAnwser,thenReturn,thenThrow](返回)`

```java
// 你可以mock具体的类型,不仅只是接口
LinkedList mockedList = mock(LinkedList.class);

// 测试桩
when(mockedList.get(0)).thenReturn("first");
when(mockedList.get(1)).thenThrow(new RuntimeException());
when(mockedList.show(anyString)).then(new Answer() {
			@Override
			public Object answer(InvocationOnMock invocationOnMock) throws Throwable {
				return "mock show: "+invocationOnMock.getArgument(0);
			});

// 输出“first”
System.out.println(mockedList.get(0));

// 抛出异常
System.out.println(mockedList.get(1));
    
// 返回"mock show: test"
System.out.println(mockedList.show("test");

// 因为get(999) 没有打桩，因此输出null
System.out.println(mockedList.get(999));

// 验证get(0)被调用的次数
verify(mockedList).get(0);
```

#### do...when

`[doReturn,doThrow,doAnswer,doNothing,doCallRealMethod](返回).when(对象).方法(参数)`

| 方法                  | 作用                                                    |
| --------------------- | ------------------------------------------------------- |
| doReturn(Object)      | 返回指定的值                                            |
| doThrow(Throwable...) | 抛出一个异常                                            |
| doAnswer(Answer)      | 为回调做一个测试桩                                      |
| doNothing()           | 什么也不会返回                                          |
| doCallRealMethod()    | 会调用`mock`对象的真实方法，类似于`spy`的未被插桩的方法 |

#### 区别

如果是spy对象，要使用do...when来插桩，如果使用when...then，会调用原对象的方法，而do...when则是直接返回，不会调用原方法。

### 参数匹配器

Mockito以自然的java风格来验证参数值: 使用equals()函数。

当为mock对象做测试桩时，可以为有参数的方法指定参数类型而不仅仅是一个值。

```java
// 使用内置的anyInt()参数匹配器
when(mockedList.get(anyInt())).thenReturn("element");

// 使用自定义的参数匹配器( 在isValid()函数中返回你自己的匹配器实现 )
//ArgumentMatcher<T>实现了isValid()接口
when(mockedList.contains(argThat(isValid()))).thenReturn("element");

// 输出element
System.out.println(mockedList.get(999));

// 你也可以验证参数匹配器
verify(mockedList).get(anyInt());
```

### <span id="实例">实例</span>

```java
package com.demo.JUnit;

public class User {
    @Autowired
    public Phone phone;

    private Long id;
    private String username;
    private String password;

    public String callPhoneNum(String num){
        return this.phone.call(num);
    }
    public String usePhone(){
        return this.phone.use();
    }
    
    public String callPhoneNum(String num){
        return this.phone.call(num);
    }
    /**Getter and Setter**/
}
```

```java
package com.demo.JUnit;

public class Phone {
    
	public String use(){
		return "use phone.";
	}
    
	public String call(String num){
		return "call: "+num;
	}
    
	public String show(Phone phone){
		return phone.toString();
	}

}
```

```java
package com.demo.JUnit;

inport ...

@SpringBootTest
@RunWith(SpringRunner.class)
class UserTest {

	@Spy
	Phone phone;

	@InjectMocks
	User user;

	@BeforeEach
	public void init(){
		user.setId(1L);
        
        //对方法进行回调插桩，回调函数为一个实现了Anwser的类
		doAnswer(new Answer() {
			@Override
			public Object answer(InvocationOnMock invocationOnMock) throws Throwable {
				return "mock call: "+invocationOnMock.getArgument(0);
			}
		}).when(phone).call(anyString());
        
        //自定义参数类型
        doReturn("mock show").when(phone).show(argThat(new ArgumentMatcher<Phone>() {
			@Override
			public boolean matches(Phone phone) {
                //返回true就返回插桩的方法，返回false就使用原类的方法或返回null
				return true;
			}
		}));
        
		//调用一次usePhone()
		user.usePhone();
	}
	@Test
	@DisplayName("😅")
	public void call() {
		assertAll("测试call",
				()->assertEquals("call: 12345",user.callPhoneNum("12345")),		//失败，原方法被覆盖
				()->assertEquals("mock call: 12345",user.callPhoneNum("12345"))	//通过
				);
	}

	@Test
	void getId() {
		assertEquals(1,user.getId());	//通过
	}

	@Test
	void usePhone(){
		assertEquals("use phone.",user.phone.use());//通过，使用了spy，调用了原类中的方法
	}

	@Test
	void usePhoneTimes(){
		assertAll("使用手机次数",
				()->verify(phone).use(),
				()->verify(phone,times(1)).use(),	//通过
				()->verify(phone,times(2)).use()	//失败，phone.use()只执行了一次
		);
	}
    
   	@Test
	void testShow(){
		assertEquals("mock show",this.phone.show(phone));	//通过
	}
}
```