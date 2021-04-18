# Shiro安全框架

## [总体框架](http://shiro.apache.org/architecture.html#detailed-architecture)

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/ShiroArchitecture.png)

- SecurityManager
  - 是Shiro体系结构的核心
  - 用于协调其托管组件以确保它们能够顺利协同工作
- SecurityUtils
  - 包含了一个静态属性和三个静态方法
    - 静态属性：SecurityManager
    - 静态方法：getSubject，setSecurityManger，getSecurityManger
  - getSubject是从上下文中获取的。如果上下文（ThreadContext）中不存在，就build一个新的Subject并在ThreadContext中绑定
- Subject
  - 当前与软件交互的实体
  - 可以从SecurityUtils获取当前的Subject
  - 可以通过Subject进行登录、登出、判断当前实体是否登录和判断当前实体的权限等等
- Realm
  - 业务数据和Shiro之间的桥梁
  - 本质上是定制的DAO
- Authenticator
  - 用户认证
  - 用来实现用户验证（登录）的功能。数据从Realms获取
- Authorizer
  - 用户授权
  - 判断Subject是否有权限进行相关操作，需要使用Realms进行权限信息判断

## Realm

​	Realm可以访问特定的数据（如用户，角色和权限），并将数据转换成Shiro能识别的格式的组件。

​	在源码的注释中还说明了Realm拥有身份验证的职责

> This allows a Realm to perform both authentication and authorization duties for a single datasource, which caters to the large majority of applications.

```java
public interface Realm {
    String getName();
    boolean supports(AuthenticationToken token);
    AuthenticationInfo getAuthenticationInfo(AuthenticationToken token) throws AuthenticationException;
}
```

- getName
  - 
- supports
  - 用来判断是否支持传入的token类型
  - 如果支持返回true，会调用`getAuthenticationInfo`方法，不支持返回false
  - 如我们的系统支持用户名密码的token登录，如果传入一个生物信息的token，就返回false
- getAuthenticationInfo

