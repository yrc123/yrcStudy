# Redis基础

## 安装Redis

​	使用包管理安装

### 遇到的问题

#### 安装报错

​	如果系统不支持IPV6，那默认配置文件会报错。解决方法是将默认的`bind 127.0.0.1 ::1`改为IPV4地址。

### 开启远程访问

- 绑定IP为`bind 0.0.0.0`
- 关闭保护模式`protected-mode no`
- 可选：设置认证口令`requirepass 密码`
  - 在使用`redis-cli`登录时可以通过`-a`参数添加密码，或者登录后通过`auth 密码`来认证

## Redis类型

​	参考官方手册

## Redis集群

### 主从模式

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-e189fefabf47452bb5855d6bb06e9e08_720w.jpg)

#### 主从复制原理

> - 从服务器连接主服务器，发送SYNC命令；
> - 主服务器接收到SYNC命名后，开始执行BGSAVE命令生成RDB文件并使用缓冲区记录此后执行的所有写命令；
> - 主服务器BGSAVE执行完后，向所有从服务器发送快照文件，并在发送期间继续记录被执行的写命令；
> - 从服务器收到快照文件后丢弃所有旧数据，载入收到的快照；
> - 主服务器快照发送完毕后开始向从服务器发送缓冲区中的写命令；
> - 从服务器完成对快照的载入，开始接收命令请求，并执行来自主服务器缓冲区的写命令；（从服务器初始化完成）
> - 主服务器每执行一个写命令就会向从服务器发送相同的写命令，从服务器接收并执行收到的写命令（从服务器初始化完成后的操作）

#### 主从复制优缺点

>##### 优点
>
>- 支持主从复制，主机会自动将数据同步到从机，可以进行读写分离
>- Slave同样可以接受其它Slaves的连接和同步请求，这样可以有效的分载Master的同步压力。
>- Master Server是以非阻塞的方式为Slaves提供服务。所以在Master-Slave同步期间，客户端仍然可以提交查询或修改请求。
>- Slave Server同样是以非阻塞的方式完成数据同步。在同步期间，如果有客户端提交查询请求，Redis则返回同步之前的数据
>
>##### 缺点
>
>- Redis不具备自动容错和恢复功能，主机从机的宕机都会导致前端部分读写请求失败，需要等待机器重启或者手动切换前端的IP才能恢复。
>- 主机宕机，宕机前有部分数据未能及时同步到从机，切换IP后还会引入数据不一致的问题，降低了系统的可用性。
>- Redis较难支持在线扩容，在集群容量达到上限时在线扩容会变得很复杂。

#### 配置方式

**slave服务器**

```properties
#设置master服务器的ip和端口
slaveof hostname port
#如果master服务器有口令
masterauth password
```

​	可以在master服务器执行`info replication`来查看slave服务器的信息

### Sentinel模式

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-f2f9850cc2954ab511a49151a8faf6c1_720w.jpg)

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-b6690afc29c01d47df094ee2f81fd5de_720w.jpg)

- Redis哨兵默认监听26379，要开放端口，否则哨兵不能通信和商定做什么，故障转移将永不会执行。
- 在配置任何一个sentinel节点的时候，不用配置其他的sentinel，因为sentinel利用了master的发布/订阅机制去自动发现其它也监控了统一master的sentinel节点
- 同样的，sentinel也会自动发现slave节点

#### 哨兵的工作方式

> - 每个Sentinel（哨兵）进程以每秒钟一次的频率向整个集群中的Master主服务器，Slave从服务器以及其他Sentinel（哨兵）进程发送一个 PING 命令。
> - 如果一个实例（instance）距离最后一次有效回复 PING 命令的时间超过 `down-after-milliseconds` 选项所指定的值， 则这个实例会被 Sentinel（哨兵）进程标记为主观下线（SDOWN）
> - 如果一个Master主服务器被标记为主观下线（SDOWN），则正在监视这个Master主服务器的所有 Sentinel（哨兵）进程要以每秒一次的频率确认Master主服务器的确进入了主观下线状态
> - 当有足够数量的 Sentinel（哨兵）进程（大于等于配置文件指定的值）在指定的时间范围内确认Master主服务器进入了主观下线状态（SDOWN）， 则Master主服务器会被标记为客观下线（ODOWN）
> - 在一般情况下， 每个 Sentinel（哨兵）进程会以每 10 秒一次的频率向集群中的所有Master主服务器、Slave从服务器发送 INFO 命令。
> - 当Master主服务器被 Sentinel（哨兵）进程标记为客观下线（ODOWN）时，Sentinel（哨兵）进程向下线的 Master主服务器的所有 Slave从服务器发送 INFO 命令的频率会从 10 秒一次改为每秒一次。
> - 若没有足够数量的 Sentinel（哨兵）进程同意 Master主服务器下线， Master主服务器的客观下线状态就会被移除。若 Master主服务器重新向 Sentinel（哨兵）进程发送 PING 命令返回有效回复，Master主服务器的主观下线状态就会被移除。

#### 哨兵模式的优缺点

> ##### 优点
>
> - 哨兵模式是基于主从模式的，所有主从的优点，哨兵模式都具有。
> - 主从可以自动切换，系统更健壮，可用性更高。
> - 哨兵节点会自动连接slave节点，如果master节点下线，sentinel会自动配置一个slave节点，同时让它成为master节点
>
> ##### 缺点
>
> - Redis较难支持在线扩容，在集群容量达到上限时在线扩容会变得很复杂。

#### 配置方式

**sentinel服务器**

```properties
#master-groupj-name：master名称
#quorm：票数，Sentinel需要协商同意master事实下线的票数
sentinel monitor [master-group-name] [ip] [port] [quorum]
#auth-pass如果有口令要设置口令
sentinel auth-pass [master-group-name] [password]
#可选，如果不配置，sentinel之间默认识别为内网ip
sentinel announce-ip [ip]
```

**启动sentinel服务器**

​	两种方法是等价的

```shell
redis-sentinel 配置文件路径
redis-server 配置文件路径 --sentinel
```

**查看sentinel信息**

```shell
info Sentinel
```

**遇到的问题**

- 端口未开启
- 如果redis版本较低，则sentinel不支持`auth`，如果设置`requirepass`，不同sentinel也不能通信。高版本的支持通过不同sentinel设置相同的`requirepass`情况下，可以通信。(详情见github：[fa675256](https://github.com/redis/redis/commit/fa675256c127963c74ea68f8bab22ef105bada02))
- master变成slave后，未给其设置masterauth导致数据无法同步

### Cluster模式

![img](https://gitee.com/lin_haoran/Picgo/raw/master/img/v2-b1e71951facd61a9ff2fd84e67bdf6a2_720w.jpg)

#### 特点

> - 所有的redis节点彼此互联(PING-PONG机制),内部使用二进制协议优化传输速度和带宽。
> - 节点的fail是通过集群中超过半数的节点检测失效时才生效。
> - 客户端与redis节点直连,不需要中间代理层.客户端不需要连接集群所有节点,连接集群中任何一个可用节点即可。
> - 所有的节点相互连接；
> - 集群消息通信通过集群总线通信，，集群总线端口大小为客户端服务端口+10000，这个10000是固定值；
> - 节点与节点之间通过二进制协议进行通信；
> - 客户端和集群节点之间通信和通常一样，通过文本协议进行；
> - 集群节点不会代理查询；

#### 工作方式

> 在redis的每一个节点上，都有这么两个东西，一个是插槽（slot），它的的取值范围是：0-16383。还有一个就是cluster，可以理解为是一个集群管理的插件。当我们的存取的key到达的时候，redis会根据crc16的算法得出一个结果，然后把结果对 16384 求余数，这样每个 key 都会对应一个编号在 0-16383 之间的哈希槽，通过这个值，去找到对应的插槽所对应的节点，然后直接自动跳转到这个对应的节点上进行存取操作。
>
> 为了保证高可用，`redis-cluster`集群引入了主从模式，一个主节点对应一个或者多个从节点，当主节点宕机的时候，就会启用从节点。当其它主节点ping一个主节点A时，如果半数以上的主节点与A通信超时，那么认为主节点A宕机了。如果主节点A和它的从节点A1都宕机了，那么该集群就无法再提供服务了。
>
> 应当给每个节点配置至少一个备用节点，保证集群的稳定性

#### 集群的投票机制

>- 投票过程是集群中所有master参与,如果半数以上master节点与master节点通信超时(cluster-node-timeout)认为当前master节点挂掉.
>- 什么时候整个集群不可用(cluster_state:fail)
>  - 如果集群任意master挂掉，且当前master没有slave，集群进入fail状态。也可以理解成集群的slot映射[0-16383]不完整时进入fail状态
>  - redis-3.0.0.rc1加入cluster-require-full-coverage参数,默认关闭,打开集群兼容部分失败。
>  - 如果集群超过半数以上master挂掉，无论是否有slave，集群进入fail状态。
>
>

#### 配置方式

​	集群至少要求3个master节点

**开启集群支持**

```properties
cluster-enabled yes
```

**创建集群**

​	可能需要安装ruby

```shell
#redis-5.0.0版本前
redis-trib.rb create --replicas [每个节点的slave节点数] [ip:port] [ip:port] ...
#redis-5.0.0版本后
redis-cli --cluster create  [ip:port] [ip:port] ... --cluster-replicas [每个节点的slave节点数]
#cluster会自动分配主从节点
```

**进入集群**

​	`redis-cli`加上`-c`参数可以进入集群

**查看集群信息**

```shell
cluster nodes
```

**集群对节点的操作**

```shell
#添加节点
cluster meet [ip] [port]
#移除节点
cluster forget [node_id]
#为节点设置不同的工作目录
cluster-config-file [file]
```

**遇到的问题**

- 未开启总线端口，总线端口为当前端口+10000，例如当前端口为6379则总线端口为16379
- 出现`Node [ip:port] is not empty`
  - 要删除dump.rdb、node.conf等
  - 文件位置为配置文件中`dir`的值
- 新添加的节点是没有哈希曹的，所以并不能正常存储数据，需要给新添加的节点分配哈希槽。
  - 可以用`redis-cli --cluster rebalance [ip:port] --cluster-use-empty-masters`给空节点重新分配哈希槽
- `redis-cli --cluster help`可以查看cluster的对应手册，其他同理

### 参考文章

[Redis官方中文文档](http://redisdoc.com/topic/index.html)

[Redis Sentinel实现的机制与原理详解](https://www.cnblogs.com/williamjie/p/9505782.html)

[Redis集群的 3 种方式，各自优缺点分析](https://zhuanlan.zhihu.com/p/257845445)

[redis三种集群策略](https://zhuanlan.zhihu.com/p/102629075)

## 附录

### redis-cli --cluster help

```shell
redis-cli --cluster help
Cluster Manager Commands:
  create         host1:port1 ... hostN:portN   #创建集群
                 --cluster-replicas <arg>      #从节点个数
  check          host:port                     #检查集群
                 --cluster-search-multiple-owners #检查是否有槽同时被分配给了多个节点
  info           host:port                     #查看集群状态
  fix            host:port                     #修复集群
                 --cluster-search-multiple-owners #修复槽的重复分配问题
  reshard        host:port                     #指定集群的任意一节点进行迁移slot，重新分slots
                 --cluster-from <arg>          #需要从哪些源节点上迁移slot，可从多个源节点完成迁移，以逗号隔开，传递的是节点的node id，还可以直接传递--from all，这样源节点就是集群的所有节点，不传递该参数的话，则会在迁移过程中提示用户输入
                 --cluster-to <arg>            #slot需要迁移的目的节点的node id，目的节点只能填写一个，不传递该参数的话，则会在迁移过程中提示用户输入
                 --cluster-slots <arg>         #需要迁移的slot数量，不传递该参数的话，则会在迁移过程中提示用户输入。
                 --cluster-yes                 #指定迁移时的确认输入
                 --cluster-timeout <arg>       #设置migrate命令的超时时间
                 --cluster-pipeline <arg>      #定义cluster getkeysinslot命令一次取出的key数量，不传的话使用默认值为10
                 --cluster-replace             #是否直接replace到目标节点
  rebalance      host:port                                      #指定集群的任意一节点进行平衡集群节点slot数量 
                 --cluster-weight <node1=w1...nodeN=wN>         #指定集群节点的权重
                 --cluster-use-empty-masters                    #设置可以让没有分配slot的主节点参与，默认不允许
                 --cluster-timeout <arg>                        #设置migrate命令的超时时间
                 --cluster-simulate                             #模拟rebalance操作，不会真正执行迁移操作
                 --cluster-pipeline <arg>                       #定义cluster getkeysinslot命令一次取出的key数量，默认值为10
                 --cluster-threshold <arg>                      #迁移的slot阈值超过threshold，执行rebalance操作
                 --cluster-replace                              #是否直接replace到目标节点
  add-node       new_host:new_port existing_host:existing_port  #添加节点，把新节点加入到指定的集群，默认添加主节点
                 --cluster-slave                                #新节点作为从节点，默认随机一个主节点
                 --cluster-master-id <arg>                      #给新节点指定主节点
  del-node       host:port node_id                              #删除给定的一个节点，成功后关闭该节点服务
  call           host:port command arg arg .. arg               #在集群的所有节点执行相关命令
  set-timeout    host:port milliseconds                         #设置cluster-node-timeout
  import         host:port                                      #将外部redis数据导入集群
                 --cluster-from <arg>                           #将指定实例的数据导入到集群
                 --cluster-copy                                 #migrate时指定copy
                 --cluster-replace                              #migrate时指定replace
  help           

For check, fix, reshard, del-node, set-timeout you can specify the host and port of any working node in the cluster.
```

