# JVM

## 概述

**Java虚拟机**

![image-20200607205751748](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200607205751748.png)

## Java内存区域与内存溢出异常

### 运行时数据区域

![image-20200608000044625](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200607224519737.png)

​	其中方法区、堆、执行引擎和本地库接口是由所有线程共享的数据区，而虚拟机栈、本地方法栈、程序计数器是线程隔离的数据区。

### 程序计数器

- 线程私有。随线程而生，随线程而灭。

- 用来记录当前线程字节码的行号，字节码解释器通过改变他来选取下一条需要执行的字节码指令。
- 由于Java虚拟机的多线程是通过线程轮流切换、分配处理器执行时间的方式来实现的，所以每条线程都有一个单独的程序计数器。
- 如果执行的是Java方法，它记录的是正在执行的虚拟机字节码指令的地址。
- 如果执行的是本地(Native)方法，它为空(Undefined)。

### Java虚拟机栈

- 线程私有。随线程而生，随线程而灭。
- 当每个方法执行时，Java虚拟机都会为它创建一个**栈帧**(Stack Frame)用来存储方法的信息，当方法执行完毕后出栈。
- 存储了包括存储局部变量表、操作数栈、动态连接、方法出口等信息。
- 局部变量表存储了编译器可知的**Java基本类型**。以局部**变量槽(**Slot)为单位。64位长的类型会占用2个变量槽。
- 当进入一个方法时，这个方法需要在栈帧中分配多大的局部变量空间是完全确定的，在方法运行期间不会改变局部变量表的大小。
- 一个变量槽实际的占用空间的大小由虚拟机实现。

###  本地方法栈

- 线程私有。随线程而生，随线程而灭。
- 同虚拟机栈类似，区别是保存的不是字节码而是本地方法。

###  Java堆

- 被所有线程共享。
- 在虚拟机启动时创建。
- 唯一目的是存放对象实例。
- 被垃圾收集器管理。
- 可被实现为固定大小，也可为可拓展大小，主流为可拓展大小。

### 方法区

- 被所有线程共享。
- 用于存储被虚拟机加载的类型信息、常量、静态变量等数据。
- 用堆实现。
- 该区域内存回收主要是针对常量池的回收和类型的卸载。

### 运行时常量池

- 为方法区的一部分。
- 常量池表用来存储编译期生成的字面量和符号引用，在类加载后存放到常量池中。
- 具有动态性，可以在常量可以在非编译期产生。

### 对象的创建

1. **Java虚拟机遇到new指令**。
2. **检查类是否存在**。检查指令的参数是否在常量池内定位到一个类的符号引用，检查这个符号引用的类是否被加载、解析、初始化过。若没有则执行类的加载过程。
3. **虚拟机为新生对象分配内存**。分配内存的方法有两种：**指针碰撞**和**空闲列表**，使用那种方法主要看Java堆**是否规整**并且垃圾收集器是否有**空间压缩整理**的能力。同时还要考虑线程安全。
4. 对象进行初始化为零值。
5. 对对象进行设置。如对象是哪个类的实例、对象的GC分带年龄信息等将被存放到对象头中。
6. 执行构造函数。

### 对象的内存布局

- 分为3部分：对象头、实例数据、对齐填充。
- 对象头包含两类信息：第一类是存储对象自身运行时数据，第二类是类型指针
  - 运行时数据包含如GC分布带、锁状态标志位、线程持有的锁等信息，这些信息被存储在32位或64位的Mark Word中。
  - Java虚拟机通过类型指针来确定对象是哪个类的实例。
- 实例数据是对象存储的有效信息，即文默在代码中定义的各种类型字段。
- 对齐填充是为了满足Java虚拟机要求的对象起始位置必须是8字节的整数倍。

### 对象的访问定位

- 主流的访问粉丝有使用句柄访问和直接指针两种
- 使用句柄访问，好处是当对象被移动，只会改变句柄中的实例数据指针，而reference不需要修改。

![image-20200608113045602](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200608113045602.png)



- 使用直接指针访问，好处是节省一次指针定位的时间。

![image-20200608113135243](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200608113135243.png)

### 内存溢出实例

- Java堆溢出：

  > Java堆内存的OutOfMemoryError异常是实际应用中最常见的内存溢出异常情况。出现Java堆内存 溢出时，异常堆栈信息“java.lang.OutOfMemoryError”会跟随进一步提示“Java heap space”。

- 虚拟机栈和本地方法栈溢出：

  >1）如果线程请求的栈深度大于虚拟机所允许的最大深度，将抛出StackOverflowError异常。
  >2）如果虚拟机的栈内存允许动态扩展，当扩展栈容量无法申请到足够的内存时，将抛出 OutOfMemoryError异常。

- 方法区和运行时常量池溢出：

  > 运行时常量池溢出时，在OutOfMemoryError异常后面跟随的提示信息是“PermGen space”。

- 本机直接内存溢出：

  >由直接内存导致的内存溢出，一个明显的特征是在Heap Dump文件中不会看见有什么明显的异常 情况，如果读者发现内存溢出之后产生的Dump文件很小，而程序中又直接或间接使用了 DirectMemory（典型的间接使用就是NIO），那就可以考虑重点检查一下直接内存方面的原因了。

## 垃圾收集器与内存分配策略

### 引用计数器算法

​	该方法的原理是在对象中添加一个引用计数器，当被引用时计数器加一，当引用失效时计数器减一，当计数器为零时，说明对象不可再被引用。

​	该方法的优点是原理简单，判定高效，但是当对象相互引用，形成一个环时，就无法正确的释放空间。

​	主流的Java虚拟机不使用这个方法。

### 可达性分析算法

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


### 引用

#### 强引用|Strongly Reference

- 是指在程序代码之中普遍存在的引用赋值，即类似“Object obj=new Object()”这种引用关系。
- 被强引用所引用的对象永远不会被垃圾收集器回收。
- Vector类的clear方法是通过把引用赋值为null来实现清理工作。

#### 软引用|Soft Reference

- 如果一个对象具有软引用，内存空间足够，垃圾回收器就不会回收它。
- 在系统将要发生内存溢出异常前，会把被软引用的对象列进回收范围之中进行第二次回收。
- 软引用可用来实现内存敏感的高速缓存，比如网页缓存、图片缓存等。

#### 弱引用|Weak Reference

- 弱引用也是用来描述非必需对象的。
- 当JVM进行垃圾回收时，无论内存是否充足，都会回收被弱引用关联的对象。

#### 虚引用|Phantom Reference

- 虚引用并不影响对象的生命周期。
- 虚引用只是为了能在这个对象被收集器回收时收到一个系统通知。
- 无法通过虚引用来取得一个对象实例 。

### 回收方法区

- 方法区的垃圾收集主要分为两部分：废弃的常量和不再使用的类型。

- 判定一个常量是否废弃：

  1. 该类所有的实例都已经被回收，也就是Java堆中不存在该类及其任何派生子类的实例。

  2. 加载该类的类加载器已经被回收。

  3. 该类对应的java.lang.Class对象没有在任何地方被引用，无法在任何地方通过反射访问该类的方
     法。

- 常量池中其他类(接口)、方法、字段的符号引用也与此类似。

### 垃圾收集算法

#### 标记清除算法

1. 首先标记出所有需要回收的对象。

2. 在标记完成后，统一回收掉所有被标记的对象。

- 缺点
  - 执行效率不稳定。
  - 内存空间碎片化。

#### 标记复制算法

- 内存被分成大小相等的两块，每次只使用一块。
- 当一块用完，就将存活的对象复制到另一块内存上，然后把已使用的内存空间一次清理掉。
- 实现简单，运行高效。
- 缺点
  - 如果大部分对象存活，复制对象的消耗过大。
  - 可使用的内存缩小一半。

#### 标记整理算法

1. 首先标记出所有需要回收的对象。

2. 在标记完成后，让存活的对象向内存一端移动。

3. 直接清理掉边界以外的内存。

- 缺点
  - 如果回收时有大量对象存活，移动存活对象开销大。
  - 移动对象的操作要求全程暂停用户应用。

#### 分带收集算法

- 根据内存中对象的存活周期不同，在JVM中一般把内存划分为**新生代**和**老年代**。
- 老年代的特点是每次垃圾收集时只有少量对象需要被回收。
- 新生代的特点是每次垃圾回收时都有大量的对象需要被回收。

- 在新生代一般使用标记复制算法，并且不是按1:1的比例来划分内存。
- 在年老代一般使用的是标记整理算法。

- 创建对象时一般在新生代中分配内存空间，当新生代垃圾收集器回收几次之后仍然存活的对象会被移动到年老代内存中。
- 当大对象在新生代中无法找到足够的连续内存时也直接在年老代中创建。
- **永久代**用来存放class类、常量、方法描述等。对永久代的回收主要回收两部分内容：废弃常量和无用的类。

### HotSpot的算法细节实现

#### 根节点枚举

​	查找引用链可以并发，而枚举根节点时要**暂停**用户线程

**准确式GC**

​	保守式GC和准确式GC的区别就是，GC时是否知道内存上的某个位置数据到底是引用类型还是别的什么类型

​	在扫描栈上的内存时，保守式GC因为不知道那些内存是引用，哪些是别的类型，所以要遍历扫描，而且还要要猜测（是否是能被4整除等等）来判断当前数据是否是指针，这样不但效率不高，而且可以会导致已经死亡的对象不能被释放。

​	而准确式的GC就是通过了一个**外部表OopMap**来记录内存中对应数据对应的类型

​	值得一提的是，HotSpot是**为了实现准确式的GC**才使用了OopMap，顺便加快了GC速度

**OopMap**

​	一旦类加载动作完成的时候， HotSpot就会把对象内什么偏移量上是什么类型的数据计算出来，也会在特定的位置记录下栈里和寄存器里哪些位置是引用

​	有了OopMap，在枚举根节点的时候只要枚举引用类型即可

#### 安全点

​	因为很多操作都会导致OopMap被修改，如果每次碰到就生成新的OopMap，代价很大。

​	所以引入了安全点，只有在安全点处对OopMap进行统一更新，意味着只有在安全点除OopMap才是准确的

​	为了保证在垃圾收集的时候所有线程都到达安全点，可以使用抢先式中断或主动式中断。

- **抢先式中断**是系统在垃圾收集时主动中断所有用户线程，之后再恢复未到安全点的线程。这个方法几乎没有被使用
- **主动式中断**是设置一个标记位，所有线程轮询这个标志，发现为真时到最近的一个安全点主动挂起

#### 安全区域

​	遇到这样一个问题，如果当前线程没有到达安全点，但是同时又长时间没有被分配cpu时间，导致其无法自己运行到安全点挂起。所以要引入安全区域（Safe Region）。

​	安全区域是指能够确保在某一段代码片段之中，引用关系不会发生变化，因此，在这个区域中任意地方开始垃圾收集都是安全的。

​	在用户线程进入安全区时，会标识自己进入安全区。在出安全区时，会判断现在是否完成了根节点枚举，如果没有就等到收到离开安全区信号才能离开安全区

#### 记忆集与卡表

​	因为对象可能会**跨代引用**：老年代引用新生代的对象，导致一次Minor GC要额外遍历整个老年代，反之亦然。而为了避免把整个老年代加入GC Roots进行扫描，要使用**记忆集**。

​	**记忆集**的定义：记忆集是一种用于记录从**非收集区域指向收集区域**的指针集合的**抽象**数据结构。抽象意味着它只是一个**定义**，而没有说明实现方式。而其中一种实现方式是**卡表**。

> 记忆集的精度
>
> **字长精度**：每个记录精确到一个机器字长（就是处理器的寻址位数，如常见的32位或64位，这个精度决定了机器访问物理内存地址的指针长度），该字包含跨代指针。 
>
> **对象精度**：每个记录精确到一个对象，该对象里有字段含有跨代指针。 
>
> **卡精度**：每个记录精确到一块内存区域，该区域内有对象含有跨代指针。

​	第三种“卡精度”所指的是用一种称为“卡表”的方式去实现记忆集。

```c++
//卡表数组的结构
//这个实现将地址右移9位，即一个卡页的大小为2^9字节
CARD_TABLE [this address >> 9] = 0;
```

​	字节数组CARD_TABLE的每一个元素都对应着其标识的内存区域中一块特定大小的内存块，这个内存块被称作**卡页**。

​	一个**卡页**的内存中通常包含不止一个对象，只要卡页内至少有一个对象的字段存在着跨代指针，那就将对应卡表的数组元素的值标识为1，没有则标识为0。只要筛选出卡表中变脏的元素，就能得出哪些卡页内存块中包含跨代指针，把它们加入GC Roots中一并扫描。

#### 写屏障

​	由于只有在**其他分带引用了待清理分带**内的对象时，卡页才会变脏。这就必须找到一个在机器码层面的手段，把维护卡表的动作放到每一 个赋值操作之中。

​	在HotSpot虚拟机里是通过写屏障技术维护卡表状态的。写屏障类似于AOP中的切面，而一般都是在**写后屏障（Post-Write Barrier）**中对卡表进行更新，简单来说就是在有**跨代引用**改变的语句后，都自动加一句将对应卡表更新的语句。

**伪共享**

​	由于现代中央处理器的缓存系统中是以缓存行为单位存储的，而多个卡表可能都在同一个缓存行中，同时写入一个缓存行导致性能下降。

​	最简单的解决办法是在**写入前**判断当前页表是否已经脏了（在前面加一个if判断）。

> 在JDK 7之后，HotSpot虚拟机增加了一个新的参数`-XX：+UseCondCardMark`，用来决定是否开启卡表更新的条件判断

#### 并发的可达性分析

见 [#如果没有重新标记产生的问题](#并发的可达性分析)

### 经典垃圾收集器

#### Seria收集器

![image-20201117114457175](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201117114457175.png)

- 使用一个线程去完成垃圾收集
- 优点
  - 简单高效
  - 适合运行在客户端下的虚拟机
  - 内存占用小
- 缺点
  - 要暂停用户线程

#### ParNew收集器

![image-20201117114508651](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201117114508651.png)

- ParNew收集器除了支持多线程**并行**收集之外，其他与Serial收集器相比并没有太多创新之处
- 并行与并发
  - **并行**描述的是多条垃圾收集器线程之间的关系，说明同一时间有多条这样的线程在协同工作，通常默认此时用户线程是处于**等待状态**
  - **并发**描述的是垃圾收集器线程与用户线程之间的关系，说明同一时间垃圾收集器线程与用户线程**都在运行**

#### Parallel Scavenge收集器

- 基于标记-复制算法
- 目标是达到一个可控制的**吞吐量**

$$
吞吐量=\frac{运行用户代码时间}{运行用户代码时间+运行垃圾搜集时间}
$$

#### Serial Old收集器

![image-20201120084853671](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120084853671.png)

- Serial的老年代版本

- 使用标记整理算法

#### Parallel Old收集器

![image-20201120090101325](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120090101325.png)

- Parallel Old是Parallel Scavenge收集器的老年代版本
- 支持多线程并发收集
- 基于标记-整理算法实

#### CMS收集器

![image-20201120090230703](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20201120090230703.png)

- 概念
  - Minor GC（新生代）
  - Major GC（老年代）
  - Full GC（整个Java堆）
  - CMS只能执行其中一种GC
- CMS（Concurrent Mark Sweep）收集器是一种以获取最短回收停顿时间为目标的收集器。
- 基于标记-清除算法
- 收集分为四个部分
  - 初始标记(要暂停用户线程)
  - 并发标记
  - 重新标记(要暂停用户线程)
  - 并发清除
- 四个部分的作用
  - 初始标记用来**标记GC Roots**能直接关联到的对象
  - 并发标记是从GC Roots直接关联对象遍历整个对象图
  - 重新标记是为了修正并发期间的数据不一致
  - 并发清除是清除掉标记阶段被判断成死亡的对象
- 缺点
  - 无法处理"浮动垃圾"，即在并发标记和并发清理生成的垃圾
  - 因为在并发的时候用户线程还在运行，所以CMS不能等到老年代几乎满了才进行搜集。
  - 要预留空间，不然会出现"并发失败"，要暂停用户线程，并临时使用Serial Old来收集
  - 因为是标记清除算法，会产生很多碎片，触发一次Full GC，**而Full GC要暂停用户线**程

**<a id="并发的可达性分析">如果没有重新标记产生的问题</a>**

> **白色**：表示对象尚未被垃圾收集器访问过。。 
>
> **黑色**：表示对象已经被垃圾收集器访问过，且这个对象的所有引用都已经扫描过。
> **灰色**：表示对象已经被垃圾收集器访问过，但这个对象上**至少存在一个**引用还没有被扫描过。

**问题的产生**

![image-20210408161404679](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210408161404679.png)

<center>初始状态</center>

![image-20210408161437842](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210408161437842.png)

<center>扫描过程中状态改变</center>

​	状态的改变是左边黑点加上了对下面白点的引用，之后把右边灰点的引用删除。

​	可以看到，因为左边黑点已经被扫描了，所以之后不会被扫描。而右边灰点在进行扫描之前，把引用删除，所以之后的也不会扫描到下面这个点。最后导致下面这个点被错误标记为不可达。

>对象消失的两个条件
>
>- 赋值器插入了一条或多条从黑色对象到白色对象的新引用；
>- 赋值器删除了全部从灰色对象到该白色对象的直接或间接引用。

**解决方法**

- 增量更新

  - 破坏第一条件，即记录添加的
  - 当黑色对象插入新的指向白色对象的引用关系时，就将这个新插入的引用记录下来
  - 等并发扫描结束之后，将这些记录过的引用关系中的黑色对象为根，重新扫描一次

- 原始快照

  - 破坏第二个条件，即记录删除的
  - 当灰色对象要删除指向白色对象的引用关系时，就将这个要删除的引用**记录下来**
  - 在并发扫描结束之后，再将这些记录过的引用关系中的灰色对象为根，重新扫描

  CMS是基于增量更新 来做并发标记的，G1、Shenandoah则是用原始快照来实现

#### Garbage First(G1) 收集器

> 它并非纯粹地追求低延迟，官方给它设定的目标是在延迟可控的情况下获得尽可能高的吞吐量

![image-20210406114807671](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210406114807671.png)

- 可以执行Mixed GC（不用决定是面向新生代，老年代还是Java堆）
- 将内存空间分为很多相等大小的区域（Region），每个Region既可以是新生代也可以是老年代。
- Region中还有一类特殊的Humongous区域，专门用来存储大对象。如果对象超出一个Region的大小，会被存放在N个连续的Humongous Region中。
- 收集分为四个部分
  - 初始标记(要暂停用户线程)
  - 并发标记
  - 最终标记(要暂停用户线程)
  - 筛选回收(要暂停用户线程)
- 四个部分的作用
  - 暂停用户线程，标记GC Roots能直接关联到的对象
  - 并发的进行可达性分析
  - 暂停用户线程，处理并发阶段结束后仍遗留下来的最后那少量的SATB记录（**原始快照**中被记录的点）
  - 暂停用户线程，对各个Region的回收价值和成本进行排序，根据用户所期望的停顿时间来制定回收计划。然后把决定回收的那一部分Region的**存活对象复制**到空的Region中，再清理掉整个旧Region的全部空间

**为什么筛选回收阶段也要暂停用户线程**

- 实现麻烦
- 不仅追求低延迟，还要保证**吞吐量**
- 后面也有低延迟的实现 - ZGC

### 低延迟垃圾收集算法

- 低延迟收集算法主要追求的是停顿时间可控
- 所以总的收集时间可能会比其他收集器长

#### Shenandoah收集器

- 使用“连接矩阵”来代替记忆集。

- 因为没有分带，所有连接矩阵记录的是跨Region的引用关系

**gc过程**

- 初始标记：标记GC Root，要暂停用户线程
- 并发标记
- 最终标记：用原始标记来保证正确，有一小段停顿
- 并发清理：清理**没有任何**存活对象的Region
- 并发回收：将Region中存活的对象**并发地**复制到**未被使用**的Region中。因为用户线程仍然会对移动的对象不断进行读写，导致指向对象的引用还是**旧的地址**。Shenandoah将会通过读屏障和被称为“Brooks Pointers”的转发指针来解决
- 初始引用更新：有一小段停顿，设立这个阶段只是为了建立一个线程集合点，确保**所有**并发回收阶段中进行的收集器线程都**已完成**分配给它们的对象移动任务。
- 并发引用更新：引用更新。并发引用更新与并发标记不同，它不再需要沿着对象图来搜索，只需要按照内存物理地址的顺序，线性地搜索出引用类型，把旧值改为新值。
- 最终引用更新：最后一次停顿，用来修正GC Roots中的引用。
- 并发清理：回收集中再无存活对象，清理回收集。

![image-20210415112817281](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210415112817281.png)

**转发指针 **

**原理**

- 在原有对象布局结构的最前面统一增加一个**新的引用字段**，在正常不处于并发移动的情况下，该引用**指向对象自己**

![image-20210417164041889](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210417164041889.png)

- 当对象有拷贝时，只要修改这个指针即可完成指针转发。具体实现是将旧对象内的引用字段由指向自己修改到指向**拷贝对象**的地址

**多线程竞争**

- 使用CAS保证并发的正确性

#### ZGC收集器

> ZGC收集器是一款基于Region内存布局的，**（暂时） 不设分代**的，使用了**读屏障**、染色指针和**内存多重映射**等技术来实现可并发的**标记-整理**算法的，以低	延迟为首要目标的一款垃圾收集器

**内存布局**

- 小型Region：2MB，用于存放小于256KB的对象
- 中型Region：32MB，用于存放256KB~4MB的对象
- 大型Region：大小不固定，一个大型Region**只能存放一个对象**，不会被**重分配**

**指针染色技术**

> ​	从前，如果我们要在对象上存储一些额外的、只供收集器或者虚拟机本身使用的数据，通常会在对象头中**增加额外的存储字段**，如对象的哈希码、分代年龄、锁记录等就是这样存储的。但如果对象**存在被移动过的可能性**，即**不能保证对象访问**能够成功呢？ 又或者有一些根本就不会去访问对象，但又希望得知该对象的某些信息的应用场景呢？能不能**从指针或者与对象内存无关的地方得到这些信息**，譬如是否能够看出来对象被移动过?
>
> ​	ZGC的染色指针是最直接的、最纯粹的，它直接把**标记信息记在引用对象的指针**上，这时，与其说可达性分析是遍历对象图来标记对象，还不如说是遍历“引用图”来标记“引用”了。

- 从**指针中**拿出高四位来作为标志位
  - 染色指针可以使得一旦某个Region的存活对象被移走之后，这个Region**立即就能够被释放和重用**
    **掉**，而不必等待整个堆中所有指向该Region的引用都被修正后才能清理。
  - 由于多使用了4位为标志位，导致4TB的内存限制。
  - 不能在32位平台使用

![image-20210509201508645](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210509201508645.png)

<center>染色指针示意</center>

- 为什么高18位不能使用？

> 实际上，基于需求、性能和成本的考虑，在AMD64架构中**只支持到52位**（4PB）的地址总线和**48位**（256TB）的虚拟地址空间，所以目前64位的硬件实际能够支持的最大内存只有256TB。此外，操作系统一侧也还会施加自己的约束，64位的Linux则分别支持**47位（128TB）的进程虚拟地址空间**和**46位（64TB）的物理地址空间**，64位的Windows系统甚至只支持44位（16TB）的物理地址空间。

**ZGC清理过程**

![image-20210509204709328](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210509204709328.png)

- 并发标记（Concurrent Mark）
  - 与G1、Shenandoah类似，但是是**直接在指针**上进行的，而不是对象
  - 标记阶段会更新染色指针中的**Marked 0、Marked 1**标志位
- 并发预备重分配（Concurrent Prepare for Relocate）
  - 统计出本次收集过程**要清理哪些Region**
  - ZGC每次回收都会扫描**所有**的Region，用范围更大的扫描成本换取省去G1中记忆集的维护成本
  - ZGC的**重分配集**只是决定了里面的存活对象会被重新复制到其他的Region中，**而并不能说回收行为就只是针对这个集合里面的Region进行**
- 并发重分配（Concurrent Relocate）
  - 这个过程要把重分配集中的存活对象复制到新的Region上，并为重分配集中的每个Region维护一个**转发表**
  - ZGC收集器能**仅从引用**上就得知一个对象是否处于重分配集之中
  - 由于[指针自愈](#指针自愈)，只有**第一次**访问旧对象会陷入转发，而且只要某个Region分配完成后，就可以**立即释放**用于新对象的分配，但是还要**保存转发表**。
- 并发重映射（Concurrent Remap）
  - 重映射所做的就是修正整个堆中指向重分配集中旧对象的所有引用
  - 但ZGC的**并发重映射**并不是一个必须要“迫切”去完成的任务。因为**指针自愈**，重映射之前只是多了一次**转发**和**修正**，而不会占用多余的内存。
  - 所以ZGC地并发重映射阶段要做的工作，合并到了下一次垃圾收集循环中的并发标记阶段里去完成，节省了一次遍历对象图的开销。
  - 一旦所有指针都被修正之后，原来记录新旧 对象关系的转发表就可以释放掉了。

**<a id="指针自愈">指针自愈</a>**

**比较传统GC和ZGC**

- 对象状态
  - 传统GC：想要知道对象的状态，仅仅依靠指针是不行的，所以要通过指针访问对象
  - ZGC：由于在指针有标记位，所以无需访问对象就可以知道对象知否被移动，是否要转发等等。
- 回收Region
  - 传统GC（如Shenandoah）：在并发回收的时候，转发需要知道**Brooks Pointer**，而由于**Brooks Pointer**保存在对象头中，**所以在并发索引更新完成之前，是不能将某个完成回收的的对象清理掉**。
  - ZGC：由于在指针有标记位，只要知道指针就可以知道是否要转发，这次访问将会被预置的内存屏障所截获，然后立即根据Region上的转发表记录将访问转发到新复制的对象上，并同时修正更新该引用的值，使其**直接指向新对象**，所以只有第一次访问旧对象会陷入转发，也就是**只慢一次**。而在**某个Region完成重分配后，就可以释放空间**，因为仅仅通过指针就可以知道对象是否要转发，通过转发表就知道要转发到哪里，而不要知道对象的具体信息。

## 虚拟机执行子系统

### 类文件结构

#### Class类文件的结构

> - 无符号数：**属于基本的数据类型**，以u1、u2、u4、u8来分别代表1个字节、2个字节、4个字节和8个字节的无符号数，无符号数可以用来描述数字、索引引用、数量值或者按照UTF-8编码构成字符串
>   值。
> - 表：**是由多个无符号数或者其他表作为数据项构成的复合数据类型**，为了便于区分，所有表的命名都习惯性地以“_info”结尾。表用于描述有层次关系的复合结构的数据，整个Class文件本质上也可以视作是一张表

| 类型           | 名称                | 数量                  |
| -------------- | ------------------- | --------------------- |
| u4             | magic               | 1                     |
| u2             | minor_version       | 1                     |
| u2             | major_version       | 1                     |
| u2             | constant_pool_count | 1                     |
| cp_info        | constant_pool       | constant_pool_count-1 |
| u2             | access_flags        | 1                     |
| u2             | this_class          | 1                     |
| u2             | super_class         | 1                     |
| u2             | interfaces_count    | 1                     |
| u2             | interfaces          | interfaces_count      |
| u2             | fields_count        | 1                     |
| field_info     | fields              | fields_count          |
| u2             | methods_count       | 1                     |
| method_info    | methods             | methods_count         |
| u2             | attributes_count    | 1                     |
| attribute_info | attributes          | attributes_count      |

<center>Class文件格式</center>

##### 结构示例

- jdk版本：openjdk 15.0.2 2021-01-19
- 编译代码：

```java
public class TestClass {
    private int m;
    public int inc() {
        return m + 1;
    }
}
```

- Class文件：

![image-20210510114508658](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210510114508658.png)

###### 魔数和Class文件的版本

**magic**

![image-20210510112839729](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210510112839729.png)

- 长度：4字节

- 作用：魔数，用来标识当前文件是一个可以被虚拟机接受的文件。很多文件格式标准中都有使用魔数来进行身份识别的习惯，譬如GIF或者JPEG等在文件头中都存有魔数

**minor_version**

![image-20210516193309646](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516193309646.png)

- 长度：2字节
- 作用：标识Class文件**次版本号**。在一段时间内废弃，现在通过设置为65535来标识为启用了预览功能的Class文件

**major_version**

![image-20210510113453182](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210510113453182.png)

- 长度：2字节
- 作用：标识Class文件**主版本号**。当前使用jdk15，Class文件版本号为59（00 00 00 3B）

###### 常量池

**constant_pool_count**

![image-20210516193353519](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516193353519.png)

- 长度：2字节

- 作用：常量池计数值。容量计数是从1而不是0开始。当前值为22（00 16），代表常量池有21个常量，索引为1~21。0是有特殊含义：不引用任何一个常量池项目

**constant_pool**

![](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516194228190.png)

- 长度：不定
- 常量池主要包含**字面量**和**符号引用**。
  - 字面量：如文本字符串、被声明为final的常量值等。
  - 符号引用：类和接口的**全限定名**、**字段的名称**和**描述符**、**方法的名称**和**描述符**等。[描述符](#描述符)

- 截至JDK13，共有17种不同的常量，其中4种是后期加入的，为了支持动态语言调用。起始为一个u1的标志位，标志当前常量的类型

| 类别                             | 标志 | 描述                         |
| -------------------------------- | ---- | ---------------------------- |
| CONSTANT_Utf8_info               | 1    | UTF-8编码的字符串            |
| CONSTANT_Integer_info            | 3    | 整型字面量                   |
| CONSTANT_Float_info              | 4    | 浮点型字面量                 |
| CONSTANT_Long_info               | 5    | 长整型字面量                 |
| CONSTANT_Double_info             | 6    | 双精度浮点型字面量           |
| CONSTANT_Class_info              | 7    | 类或接口的符号引用           |
| CONSTANT_String_info             | 8    | 字符串类型字面量             |
| CONSTANT_Fieldref_info           | 9    | 字段的符号引用               |
| CONSTANT_Methodref_info          | 10   | 类中方法的符号引用           |
| CONSTANT_InterfaceMethodref_info | 11   | 接口中方法的符号引用         |
| CONSTANT_NameAndType_info        | 12   | 字段或方法的部分符号引用     |
| CONSTANT_MethodHandle_info       | 15   | 表示方法句柄                 |
| CONSTANT_MethodType_info         | 16   | 表示方法类型                 |
| CONSTANT_Dynamic_info            | 17   | 表示一个动态计算常量         |
| CONSTANT_InvokeDynamic_info      | 18   | 表示一个动态方法调用点       |
| CONSTANT_Module_info             | 19   | 表示一个模块                 |
| CONSTANT_Package_info            | 20   | 表示一个模块中开放或导出的包 |

<center>常量池标志表</center>

​	可以使用Class字节码文件分析工具：`javap`来分析常量表。使用`javap -verbose`来查看

- <a id="汇编指令">输出的结果</a>：

```
  Last modified 2021年5月10日; size 353 bytes
  SHA-256 checksum 8605de9615dedd01cecf93d3555a84e9daa456944c8fac979f1903aa1973894d
  Compiled from "TestClass.java"
public class TestClass
  minor version: 0
  major version: 59
  flags: (0x0021) ACC_PUBLIC, ACC_SUPER
  this_class: #8                          // TestClass
  super_class: #2                         // java/lang/Object
  interfaces: 0, fields: 1, methods: 2, attributes: 1
Constant pool:
   #1 = Methodref          #2.#3          // java/lang/Object."<init>":()V
   #2 = Class              #4             // java/lang/Object
   #3 = NameAndType        #5:#6          // "<init>":()V
   #4 = Utf8               java/lang/Object
   #5 = Utf8               <init>
   #6 = Utf8               ()V
   #7 = Fieldref           #8.#9          // TestClass.m:I
   #8 = Class              #10            // TestClass
   #9 = NameAndType        #11:#12        // m:I
  #10 = Utf8               TestClass
  #11 = Utf8               m
  #12 = Utf8               I
  #13 = Utf8               Code
  #14 = Utf8               LineNumberTable
  #15 = Utf8               LocalVariableTable
  #16 = Utf8               this
  #17 = Utf8               LTestClass;
  #18 = Utf8               inc
  #19 = Utf8               ()I
  #20 = Utf8               SourceFile
  #21 = Utf8               TestClass.java
{
  public TestClass();
    descriptor: ()V
    flags: (0x0001) ACC_PUBLIC
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 1: 0
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0       5     0  this   LTestClass;

  public int inc();
    descriptor: ()I
    flags: (0x0001) ACC_PUBLIC
    Code:
      stack=2, locals=1, args_size=1
         0: aload_0
         1: getfield      #7                  // Field m:I
         4: iconst_1
         5: iadd
         6: ireturn
      LineNumberTable:
        line 5: 0
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0       7     0  this   LTestClass;
}
So
```

​	其他细节查看书

###### 访问标志

**access_flags**

![image-20210516194251923](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516194251923.png)

长度：2字节

作用：标识类的信息，当前为`0x0021`，`ACC_SUPER`和`ACC_PUBLIC`为真，代表当前类为public且在JDK1.0.2之后编译

| 标志名称       | 标志值 | 含义                                                         |
| -------------- | ------ | ------------------------------------------------------------ |
| ACC_PUBLIC     | 0x0001 | 是否为public                                                 |
| ACC_INAL       | 0x0010 | 是否为final，只有类可设置                                    |
| ACC_SUPER      | 0x0020 | 是否允许invokespecial字节码的新语义，在JDK1.0.2后，invokespecial语义发生变化，所有JDK1.0.2后的class此位为真 |
| ACC_INTERFACE  | 0x0200 | 标识这是一个接口                                             |
| ACC_ABSTRACT   | 0x0400 | 是否为abstract类型                                           |
| ACC_SYNTHETIC  | 0x1000 | 标志这个类并非为用户代码生成                                 |
| ACC_ANNOTATION | 0x2000 | 标识这是一个注解                                             |
| ACC_ENUM       | 0x4000 | 标识这是一个枚举                                             |
| ACC_MODULE     | 0x8000 | 标识这是一个模块                                             |

###### 类索引、父类索引和接口索引集合

**this_class**

![image-20210516194546590](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516194546590.png)

长度：2字节

作用：确定这个类的全限定名当前为`0x0008`，从上面的常量表中可以看出指向指向`#8 = Class #10 // TestClass`，即当前类

**super_class**

![image-20210516195425474](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516195425474.png)

长度：2字节

作用：确定这个类的父类的全限定名。父类索引只有一个，除了Object之外，所有的Java类都有父类，而Object的父类索引为0。当前为`0x0002`，指向`java/lang/Object`

**interface_count**

![image-20210516195606739](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516195606739.png)

长度：2字节

作用：接口计数器。当前为`0x0000`，因为没有实现任何接口

**interface**

长度：不确定

作用：是一组u2类型的数据的集合。些被实现的接口将按implements关键字后的接口顺序从左到右排列在接口索引集合中。

###### 字段表集合

**fields_count**

![image-20210516195729107](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516195729107.png)

长度：2字节

作用：字段计数器。当前为`0x0001`，代表只有一个字段，即`private int m;`

**fields**

长度：不确定

作用：字段表，类型为`fild_info`。字段包括**类级变量**以及**实例级变量**，但**不包括在方法内部声明的局部变量**

**fild_info**

| 类型           | 名称             | 数量             |
| -------------- | ---------------- | ---------------- |
| u2             | access_flags     | 1                |
| u2             | name_index       | 1                |
| u2             | descriptor_index | 1                |
| u2             | attributes_count | 1                |
| attribute_info | attributes       | attributes_count |

<center>表字段结构</center>

| 标志名称      | 标志值 | 含义                     |
| ------------- | ------ | ------------------------ |
| ACC_PUBIC     | 0x0001 | 字段是否public           |
| ACC_PRIVATE   | 0x0002 | 字段是否private          |
| ACC_PROTECTED | 0x0004 | 字段是否protected        |
| ACC_STATIC    | 0x0008 | 字段是否static           |
| ACC_FINAL     | 0x0010 | 字段是否final            |
| ACC_VOLATILE  | 0x0040 | 字段是否vaolatile        |
| ACC_TRANSIENT | 0x0080 | 字段是否transient        |
| ACC_SYNTHETIC | 0x1000 | 字段是否由编译器自动产生 |
| ACC_ENUM      | 0x4000 | 字段是否enum             |

<center>字段访问标志</center>

- 全限定名
  - 将类全名中的`.`换成`/`，且结尾为`;`
  - 如对于类`com.demo.TestClass`的全限定名为`com/demo/TestClass;`
- <a id="描述符">描述符</a>
  - 用来描述字段的**数据类型**、**方法的参数列表**和**返回值**
  - 参数列表包括数量、类型以及顺序
  - **基本数据类型**以及代表无返回值的`void`类型都用一个大写字符来表示，而对象类型则用字符`L`加对象的全限定名来表示
  - 对于数组类型，每一个维度用一个`[`描述，如`java.lang.String[][]`为`[[Ljava/lang/String;`，`int[]`为`[I`
  - 对于方法，按照先参数列表、后返回值的顺序描述，参数列表按照参数的**严格顺序**放在一组小括号之内。如`void inc()`为`()V`，`int indexOf(char[] source, int sourceOffset, int sourceCount, char[] target, int targetOffset)`为`([CII[CI)I`

- 简单名称
  - 简单名称则就是指没有类型和参数修饰 的方法或者字段名称
  - 如`inc()`方法和`m`字段的简单名称分别就是`inc`和`m`

| 标识字符 | 含义                            |
| -------- | ------------------------------- |
| B        | byte                            |
| C        | char                            |
| D        | double                          |
| F        | float                           |
| I        | int                             |
| J        | long                            |
| S        | short                           |
| Z        | boolean                         |
| V        | void                            |
| L        | 对象类型，如`Ljava/lang/Object` |

<center>描述字符含义</center>

![image-20210516201156146](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210516201156146.png)

​	在上图中，我们知道

- fields_count为`0x0001`，代表只有一个字段
- access_flag为`0x0002`，代表字段为私有的
- name_index为`0x000B`，代表字段名，指向常量池中的第五个常量，值为`m`
- descriptor_index为`0x000C`，代表描述字段，指向常量池的`I`

推出原代码定义为`private int m;`

​	字段表集合中**不会**列出从父类或者父接口中**继承而来的字段**，但有可能出现原本Java代码之中不存在的字段，譬如在内部类中**为了保持对外部类的访问性**，编译器就会自动添加**指向外部类实例的字段**

​	在Java语言中字段是**无法重载**的，两个字段的数据类型、修饰符不管是否相同，都必须使用**不一样的名称**，但是对于Class文件格式来讲，只要两个字段的描述符**不是完全相同**，那字段重名就是**合法**的。

###### 方法表集合

- *方法表结构*和*字段结构***一致**
- *方法访问标志*和*字段访问标志***类似**

| 标志名称         | 标志值 | 含义                               |
| ---------------- | ------ | ---------------------------------- |
| ACC_PUBIC        | 0x0001 | 方法是否public                     |
| ACC_PRIVATE      | 0x0002 | 方法是否private                    |
| ACC_PROTECTED    | 0x0004 | 方法是否protected                  |
| ACC_STATIC       | 0x0008 | 方法是否static                     |
| ACC_FINAL        | 0x0010 | 方法是否final                      |
| ACC_SYNCHRONIZED | 0x0020 | 方法是否sychronized                |
| ACC_BRIDGE       | 0x0040 | 方法是否由编译器自动产生的桥接方法 |
| ACC_VARARGS      | 0x0080 | 方法是否接受不定参数               |
| ACC_NATIVE       | 0x0100 | 方法是否native                     |
| ACC_ABSTRACT     | 0x0400 | 方法是否abstract                   |
| ACC_STRICT       | 0x0800 | 方法是否strictfp                   |
| ACC_SYNTHETIC    | 0x1000 | 方法是否编译器自动产生             |

<center>方法访问标志</center>

- 方法的代买再**属性表集合**中的`Code`属性中，而不在**方法表集合**中

- 如果父类方法在子类中**没有被重写**，方法表集合中就**不会**有来自父类方法的信息

- 在Java中，**重载**的要求是

  1. 有相同的简单名称
  2. 有一个与原方法不同的特征签名

  特征签名是一个方法中**各个参数**在常量池中的字段符号引用的集合，不包含返回值。而Class文件格式中的特征签名包含了返回值，所以事实上只有返回值不同是可以在Class文件中共存。 

![image-20210522160025875](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210522160025875.png)

<center>方法表结构实例</center>

​	在上图中，我们知道

- methods_counts为`0x0002`，代表有两个方法，一个为`main`函数一个为编译器自动生成的构造函数
- access_flags为`0x0001`，代表当前方法为`public`
- name_index为`0x0005`，指向常量池的`<init>`
- descriptor_index为`0x0006`，描述符，指向`()V`代表方法无参、返回值为空
- attributes_count为`0x0001`，代表有一个属性
- attribute_name_index为`0x000D`，指向常量池的`Code`

###### 属性表集合

​	属性表和其他表相比，比较宽松，可以不用严格顺序，而且只要不与规定的属性名重名，编译器都可以写入自定义的属性。在Java SE 12中，预定义属性名已经增加到29项。

| 属性名称                             | 使用位置                     | 含义                                                         |
| ------------------------------------ | ---------------------------- | ------------------------------------------------------------ |
| Code                                 | 方法表                       | Java代码编译成的字节码指令                                   |
| ConstantValue                        | 字段表                       | 由final关键字定义的常量值                                    |
| Deprecated                           | 类、方法表、字段表           | 被声明为deprecated的方法和字段                               |
| Exceptions                           | 方法表                       | 方法抛出的异常列表                                           |
| EnclosingMethod                      | 类文件                       | 当一个类为局部类或匿名类时有这个属性，用于标记这个类的外围方法 |
| InnerClasses                         | 类文件                       | 内部类列表                                                   |
| LineNumberTable                      | Code属性                     | Java源码的行号和字节码指令对应的关系                         |
| LocalVariableTable                   | Code属性                     | 方法的局部变量描述                                           |
| stackMapTable                        | Code属性                     | JDK6中新增的属性，供新的类型检查验证器( Type Checker)检查和处理目标方法的局部变量和操作数栈所需要的类型是否匹配 |
| Signature                            | 类、方法表、字段表           | JDK5中新增的属性，用于支持范型情况下的方法签名。在Java语言中，任何类、接口、初始化方法或成员的泛型签名如果包含了类型变量(TypeVariables)或参数化类型( Parameterized Types)，则Signature属性会为它记录泛型签名信息。由于Java的范型采用擦除法实现，为了避免类型信息被擦除后导致签名混乱，需要这个属性记录范型中的相关信息 |
| SourceFile                           | 类文件                       | 记录源文件名称                                               |
| SourceDebugExtension                 | 类文件                       | JDK5中新增的属性，用于存储额外的调试信息。譬如在进行JSP文件调试时，无法通过Java堆栈来定位到JSP文件的行号，JSR45提案为这些非Java语言编写，却需要编译成字节码并运行在Java虚拟机中的程序提供了一个进行调试的标准机制，使用该属性就可以用于存储这个标准所新加入的调试信息 |
| Synthetic                            | 类、方法表、字段表           | 标识方法或字段为编译器自动生成                               |
| LocalVariableTypeTable               | 类                           | JDK5中新增的属性,它使用特征签名代替描述符,是为了引入泛型语法之后能描述泛型参数化类型而添加 |
| RuntimeVisibleAnnotations            | 类、方法表、字段表           | JDK5中新增的属性,为动态注解提供支持。该属性用于指明哪些注解是运行时(实际上运行时就是进行反射调用)可见的 |
| RuntimeInvisibleAnnotations          | 类、方法表、字段表           | JDK5中新增的属性，用于指明哪些注解是运行时不可见的           |
| RuntimeVisibleParameterAnnotations   | 方法表                       | JDK5中新增的属性,作用与 Runtime visibleAnnotations属性类似,只不过作用对象为方法参数 |
| RuntimeInvisibleParameterAnnotations | 方法表                       | 同上                                                         |
| AnnotationDefault                    | 方法表                       | JDK5中新增的属性,用于记录注解类元素的默认值                  |
| BootstrapMethods                     | 类文件                       | JDK7中新增的属性,用于保存invokedynamic指令引用的引导方法限定符 |
| RuntimeVisibleTypeAnnotations        | 类、方法表、字段表、Code属性 | JDK8中新增的属性,为实现JSR308中新增的类型注解提供的支持,用于指明哪些类注解是运行时(实际上运行时就是进行反射调用)可见的 |
| RuntimeInvisibleTypeAnnotations      | 类、方法表、字段表、Code属性 | JDK8中新增的属性,为实现JSR308中新增的类型注解提供的支持,与 Runtime Visible TypeAnnotations属性作用刚好相反,用于指明哪些注解是运行时不可见的 |
| MethodParameters                     | 方法表                       | JDK8中新增的属性,用于支持(编译时加上parameters参数)将方法名称编译进 Class件中,并可运行时获取。此前要获取方法名称(典型的如IDE的代码提示)只能通过 Java Doc中得到 |
| Moduls                               | 类                           | JDK9中新增的属性,用于记录一个 Module的名称以及相关信息( requires、 exports、 opens、usesprovides |
| ModulePackages                       | 类                           | JDK9中新增的属性,用于记录一个模块中所有被exports或者 opens的包 |
| ModuleMainClass                      | 类                           | JDK9中新增的属性,用于指定一个模块的主类                      |
| NestHost                             | 类                           | JDK11中新增的属性,用于支持嵌套类(Java中的内部类)的反射和访问控制的API,一个内部类通过该属性得知自己的宿主类 |
| NestMembers                          | 类                           | JDK11中新增的属性,用于支持嵌套类(Java中的内部类)的反射和访问控制的API.一个宿主类通过该属性得知自己有哪些内部类 |

<center>虚拟机规范定义的属性</center>

- 属性名从常量池中引用

| 类型 | 名称                 | 数量             |
| ---- | -------------------- | ---------------- |
| u2   | attribute_name_index | 1                |
| u4   | attribute_length     | 1                |
| u1   | info                 | attribute_length |

<center>属性表结构</center>

**Code属性**

不是所有方法都有Code属性，如接口和抽象类的方法就不存在Code属性。Code属性用来存储字节码指令。

| 类型           | 名称                   | 数量                   |
| -------------- | ---------------------- | ---------------------- |
| u2             | attribute_name_index   | 1                      |
| u4             | attribute_length       | 1                      |
| u2             | max_statck             | 1                      |
| u2             | max_locals             | 1                      |
| u4             | code_length            | 1                      |
| u1             | code                   | code_length            |
| u2             | exception_table_length | 1                      |
| exception_info | exception_table        | exception_table_length |
| u2             | attributes_count       | 1                      |
| attribute_info | attributes             | attributes_count       |

<center>Code属性表的结构</center>

​	正如上面的[方法表结构实例](#方法表结构实例)中的Code属性，attribute_name_index是指向常量池是索引，为`Code`，，attribute_length指示了属性值的长度，由于属性名称索引与属性长度一共为 6个字节，所以属性值的长度固定为整个属性表长度减去6个字节。

**max_stack**

- 长度：2字节
- 作用：代表了操作数栈深度的最大值

**max_locals**

- 长度：2字节
- 作用：记录了局部变量所需的空间，单位为**变量槽**。
  - 变量槽为局部变量分配内存的**最小单位**，不超过32位的数据类型占用**一个**变量槽，而如double、long等占用64位的变量占用**两个**变量槽。
  - 如方法参数、实例方法中的`this`、显式异常处理程序的参数（try-catch中catch中定义的异常）、方法体中定义的局部变量都与啦局部变量表来存放
  - 编译器会**重用变量槽**，当代码超出变量的作用域时，这个变量占用的变量槽可以给别的变量使用。所以变量槽一般都比变量所需的变量槽少

**code_length**

- 长度：4字节
- 作用：记录字节码长度。虽然理论上可以到达$2^{32}$，但是规范中明确限制了一个方法不允许超过65535条字节码指令，就是实际只使用了2字节。

**code**

- 长度：不确定
- 作用：存储编译后生成的字节码指令
  - 从`javap`处理出的[汇编指令](#汇编指令)中发现，无论是`inc()`还是`<init>()`，`Args_size`的值都为1，尽管他们两个都是无参函数。
  - 因为在任何**实例方法**中，都有一个`this`来指向当前实例，虚拟机调用方法时会自动传入此参数，同时编译器也会留出一个变量槽来存放`this`，所以实例方法至少有一个指向当前实例的局部变量。
  - 如果方法为**静态方法**，就没有`this`，`Args_size`也为实际传入的参数数量。

**exception_table_length**

- 长度：2字节
- 作用：代表异常表集合长度

**exception_table**

- 长度：不确定
- 作用：异常处理表
- 在JDK 1.4.2之前的Javac编译器采用了jsr和ret指令实现finally语句，但1.4.2之后已经改为编译器在每段分支之后都将finally语句块的内容冗余生成一遍来实现。
- 从JDK 7起，已经完全禁止Class文件中出现jsr和ret指令，如果遇到这两条指令，虚拟机会在类加载的字节码校验阶段抛出异常

| 类型 | 名称       | 数量 |
| ---- | ---------- | ---- |
| u2   | start_pc   | 1    |
| u2   | end_pc     | 1    |
| u2   | handler_pc | 1    |
| u2   | catch_type | 1    |

**Exceptions属性**

| 类型 | 名称                  | 数量                 |
| ---- | --------------------- | -------------------- |
| u2   | attribute_name_index  | 1                    |
| u4   | attribute_length      | 1                    |
| u2   | number_of_exceptions  | 1                    |
| u2   | exception_index_table | number_of_exceptions |

- 这里的Exceptions属性是在方法表中与Code属性平级的一项属性
- Exceptions属性的作用是列举出方法中可能抛出的受查异常，也就是方法描述时在throws关键字后面列举的异常

**number_of_exceptions**

- 表示可能抛出的异常种类
- 每种异常使用一个exception_index_table表示，其为一个指向常量池中的索引，代表受查异常的类型

| 类型              | 名称                  | 数量                 |
| ----------------- | --------------------- | -------------------- |
| u2                | attribute_name_index  | 1                    |
| u4                | attribute_length      | 1                    |
| u2                | number_of_exceptions  | 1                    |
| linde_number_info | exception_index_table | number_of_exceptions |

<center>Exceptions属性结构</center>

**LineNumberTable属性**

- 性用于描述Java源码行号与字节码行号（字节码的偏移量）之间的对应关系
- 不是运行时必需的属性
- 调试时的断点、抛出异常时显示行号都依赖这个属性

| 类型             | 名称                 | 数量                     |
| ---------------- | -------------------- | ------------------------ |
| u2               | attribute_name_index | 1                        |
| u4               | attribute_length     | 1                        |
| u2               | line_number_table    | 1                        |
| line_number_info | line_number_table    | line_number_table_length |

<center>LineNumberTable属性结构</center>

- line_number_info：包含start_pc和line_number两个u2类型的数据项，前者是字节码行号，后者是Java源码行号

**LocalVariableTable属性**

- LocalVariableTable属性用于描述栈帧中局部变量表的变量与Java源码中定义的变量之间的关系
- 不是运行时必需的属性
- 如果没有生成这项属性，当其他人引用这个方法时，所有的参数名称都将会丢失。譬IDE将会使用如arg0、arg1之类的占位符代替原有的参数名。且在调试期间无法根据参数名称从上下文中获得参数值

| 类型                | 名称                        | 数量                        |
| ------------------- | --------------------------- | --------------------------- |
| u2                  | attribute_name_index        | 1                           |
| u4                  | attribute_length            | 1                           |
| u2                  | local_variable_table_length | 1                           |
| local_variable_info | local_variable_table        | local_variable_table_length |

<center>LocalVariableTable属性表结构</center>

| 类型 | 名称             | 数量 |
| ---- | ---------------- | ---- |
| u2   | start_pc         | 1    |
| u2   | length           | 1    |
| u2   | name_index       | 1    |
| u2   | descriptor_index | 1    |
| u2   | index            | 1    |

<center>local_variable_info项目结构</center>

- start_pc与length：代表局部变量的生命周期开始的字节码偏移量和其作用范围覆盖 的长度，两者代表了变量的作用域

- name_index：指向常量池，代表名称
- descriptor_index：指向常量池，代表描述符
- index：这个局部变量在栈帧的局部变量表中变量槽的位置。当这个变量数据类型是64位类型时，它占用的变量槽为index和index+1两个。

**LocalVariableTypeTable属性**

- 在JDK 5引入泛型之后，加入了LocalVariableTypeTable属性
- 这个属性结构与LocalVariableTable很相似，仅仅是把记录的字段描述符的descriptor_index替换成了字段的特征签名
- 非泛型类型的**描述符**和**特征签名**能描述的信息是能吻合一致的，但是泛型引入之后，由于描述符中泛型的参数化类型被**擦除**掉，描述符就不能准确描述泛型类型了
- 因此出现了LocalVariableTypeTable属性，使用字段的特征签名来完成泛型的描述。

**SourceFile**

- SourceFile属性用于记录生成这个Class文件的源码文件名称
- 对于大多数的类来说，类名和文件名是一致的，但是有一些特殊情况（如内部类）例外
- 如果不生成这项属性，当抛出异常时，堆栈 中将不会显示出错代码所属的文件名

| 类型 | 名称                 | 数量 |
| ---- | -------------------- | ---- |
| u2   | attribute_name_index | 1    |
| u4   | attribute_length     | 1    |
| u2   | sourcefile_index     | 1    |

- sourcefile_index：指向常量池，代表文件名

**SourceDebugExtension**

- 为了方便在编译器和动态生成的Class中加入供程序员使用的自定义内容
- SourceDebugExtension属性用于存储额外的代码调试信息
- 典型的场景是在进行JSP文件调试时，无法 通过Java堆栈来定位到JSP文件的行号

| 类型 | 名称                               | 数量 |
| ---- | ---------------------------------- | ---- |
| u2   | attribute_name_index               | 1    |
| u4   | attribute_length                   | 1    |
| u1   | debug_extension[attributte_length] | 1    |

**ConstantValue属性**

- ConstantValue属性的作用是通知虚拟机自动为**静态变量**赋值
- 对非`static`类型的变量的赋值是在实例构造器`<init>()`方法中进行的
- 而对于类变量，则有两种方式可以选择：在类构造器`<clinit>()`方法中或者使用ConstantValue属性

- 如果同时使用`final`和`static`来修饰一个变量，并且这个变量的数据类型是**基本类型**或者**java.lang.String**的话，就将会生成ConstantValue属性来进行初始化
- 如果这个变量没有被`final`修饰，或者**并非基本类型及字符串**，则将会选择在`<clinit>()`方法中进行初始化
- 因为Class中常量池只有**基本类型**和**字符串**，而ConstantValue只能指向常量池，所以ConstantValue属性想支持别的类型也无能为力。

| 类型 | 名称                 | 数量 |
| ---- | -------------------- | ---- |
| u2   | attribute_name_index | 1    |
| u4   | attribute_length     | 1    |
| u2   | constantvalue_index  | 1    |

- 它的attribute_length数据项值必须固定为2

- constantvalue_index：指向常量池，代表初始化的值

**InnerClasses属性**

- InnerClasses属性用于记录内部类与宿主类之间的关联
- 如果一个类中定义了内部类，那编译器将会为它以及它所包含的内部类生成InnerClasses属性

| 类型               | 名称                 | 数量              |
| ------------------ | -------------------- | ----------------- |
| u2                 | attribute_name_index | 1                 |
| u4                 | attribute_length     | 1                 |
| u2                 | number_of_classes    | 1                 |
| inner_classes_info | inner_classes        | number_of_classes |

<center>InnerClasses属性结构</center>

- number_of_classes：代表需要记录多少个内部类信息，每一个内部类的信息都由一个inner_classes_info表进行描述

| 类型 | 名称                     | 数量 |
| ---- | ------------------------ | ---- |
| u2   | inner_class_info_index   | 1    |
| u2   | outer_class_info_index   | 1    |
| u2   | inner_name_index         | 1    |
| u2   | inner_class_access_flags | 1    |

<center>inner_classes_info表的结构</center>

- inner_class_info_inde：指向常量池中CONSTANT_Class_info型常量的索引，代表内部类的符号引用
- outer_class_info_index：指向常量池中CONSTANT_Class_info型常量的索引，代表外部类的符号引用
- inner_name_index：指向常量池，代表内部类名称
- inner_class_access_flags：是内部类的访问标志，类似于类的access_flags

| 标志名称       | 标志值 | 含义                           |
| -------------- | ------ | ------------------------------ |
| ACC_PUBLIC     | 0x0001 | 内部类是否为public             |
| ACC_PRIVATE    | 0x0002 | 内部类是否为private            |
| ACC_PROTECTED  | 0x0004 | 内部类是否为protected          |
| ACC_SATATIC    | 0x0008 | 内部类是否为static             |
| ACC_FINAL      | 0x0010 | 内部类是否为final              |
| ACC_INTERFACE  | 0x0020 | 内部类是否为接口               |
| ACC_ABSTRACT   | 0x0400 | 内部类是否为abstract           |
| ACC_SYNTHETIC  | 0x1000 | 内部类是否为并非由用户代码产生 |
| ACC_ANNOTATION | 0x2000 | 内部类是否为一个注解           |
| ACC_ENUM       | 0x4000 | 内部类是否为一个枚举           |

<center>inner_class_access_flags标志</center>

**Deprecated属性**

- 属于标志类型的布尔属性，只存在有和没有的区别
- 用于表示某个类、字段或者方法，已经被程序作者定为不再推荐使用
- 可以通过代码中使用`@Deprecated`注解进行设置

| 类型 | 名称                 | 数量 |
| ---- | -------------------- | ---- |
| u2   | attribute_name_index | 1    |
| u4   | attribute_length     | 1    |

- 其中attribute_length数据项的值必须为0x00000000，因为没有任何属性值需要设置

**Synthetic属性**

- 属于标志类型的布尔属性，只存在有和没有的区别
- 代表此字段或者方法并不是由Java源码直接产生的，而是由编译器自行添加的
- JDK 5之后，标识一个类、字段或者方法是编译器自动产生的，也可以设置它们访问标志中的ACC_SYNTHETIC标志位

- 属性结构同上

**StackMapTable属性**

- 这个属性会在虚拟机类加载的字节码验证阶段被新类型检查验证器使用，目的在于代替以前比较消耗性能的基于数据流分析的 类型推导验证器

- 位于Code属性的属性表中

**Signature属性**

- Signature属性就是为了弥补，Java中使用**擦除法**实现的伪泛型，导致反射时无法获得泛型信息等问题而增设的
- 因为Java语言的泛型采用的是擦除法实现的伪泛型，字节码（Code属性）中所有的泛型信息编译（类型变量、参数化类型）在编译之后都通通被擦除掉。使用擦除法的好处是实现简单（主要修改 Javac编译器，虚拟机内部只做了很少的改动）、非常容易实现Backport，运行期也能够节省一些类型所占的内存空间。但坏处是运行期就无法像C#等有真泛型支持的语言那样，将泛型类型与用户定义的 普通类型同等对待，例如运行期做反射时无法获得泛型信息。

| 类型 | 名称                 | 数量 |
| ---- | -------------------- | ---- |
| u2   | attribute_name_index | 1    |
| u4   | attribute_length     | 1    |
| u2   | signature_index      | 1    |

- signature_index：指向常量池的CONSTANT_Utf8_info结构，表示类签名或方法类型签名或字段类型签名。

**BootstrapMethods属性**

- 这个属性用于保存invokedynamic指令引用的引导方法限定符

**MethodParameters属性**

- MethodParameters的作用是记录方法的各个形参名称和信息
- MethodParameters是在JDK 8时新加入到Class文件格式中的

**模块化相关属性**

- JDK 9的一个重量级功能是Java的模块化功能

**运行时注解相关属性**

- 为了存储源码中注解信息，Class文件同步增加了RuntimeVisibleAnnotations、RuntimeInvisibleAnnotations、RuntimeVisibleParameterAnnotations和RuntimeInvisibleParameterAnnotations四个属性
- 到了JDK 8时期，进一步加强了Java语言的注解使用范围，又新增类型注解 （JSR 308），所以Class文件中也同步增加了RuntimeVisibleTypeAnnotations和RuntimeInvisibleTypeAnnotations两个属性

| 类型       | 名称                 | 数量            |
| ---------- | -------------------- | --------------- |
| u2         | attribute_name_index | 1               |
| u4         | attribute_length     | 1               |
| u2         | num_annotations      | 1               |
| annotation | annotations          | num_annotations |

<center>RuntimeVisibleAnnotations属性结构</center>

- RuntimeVisibleAnnotations是一个变长属性，它记录了类、字段或方法的声明上记录运行时可见注解，当我们使用反射API来获取类、字段或方法上的注解时，返回值就是通过这个属性来取到的。

| 类型               | 名称                    | 数量                    |
| ------------------ | ----------------------- | ----------------------- |
| u2                 | type_index              | 1                       |
| u2                 | num_element_value_pairs | 1                       |
| element_value_pair | element_value_pairs     | num_element_value_pairs |

<center>annotation属性结构</center>

- type_index：指向常量池CONSTANT_Utf8_info常量的索引值，该常量应以字段描述符的形式表示一个注解
- element_value_pairs：每 个元素都是一个键值对，代表该注解的参数和值

#### 字节码指令简介

- 由于Java虚拟机采用 面向操作数栈而不是面向寄存器的架构，所以大多数指令都不包含操作数，只有一个操作码，指令参数都存放在操作数栈中

- 由于限制了Java虚拟机操作码的长度为一个字节（即0～255），这意味着指令集的操作码总数不能够超过256条

##### 字节码与数据类型

- 大多数指令都包含其操作所对应的**数据类型信息**，如`iload`指令用于从局部变量表中加载`int`型的数据到操作数栈中，而`fload`指令加载的则是`float`类型的数据

| 数据类型  | 特殊字符 |
| --------- | -------- |
| long      | l        |
| short     | s        |
| byte      | b        |
| char      | c        |
| float     | f        |
| double    | d        |
| reference | r        |

<center>特殊字符表</center>

- 因为Java虚拟机的操作码长度只有一字节，无法将所有数据类型的操作都包含进去，即并非每种数据类型和每一种操作都有对应的指令
- 如果在表中指令模板与数据类型两列共同确定的格为**空**，则说明虚拟机**不支持**对这种数据类型执行这项操作。
- 如load指令有操作int类型的iload，但是**没有**操作byte类型的同类指令

![image-20210526132231325](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210526132231325.png)

<center>Java虚拟机指令集所支持的数据类型</center>

- 编译器会在编译期或运行期将byte和short类型的数据带符号扩展（Sign-Extend）为相应的int类型数据，其他类型也类似

##### 加载和存储指令

| 操作作用                             | 字节码指令                                                   |
| ------------------------------------ | ------------------------------------------------------------ |
| 将一个局部变量加载到操作栈           | iload<br />iload\_\<n\><br />lload<br />lload\_\<n\><br />fload<br />fload\_\<n\><br />dload<br/>dload\_\<n\><br />aload<br />aload\_\<n\> |
| 将一个数值从操作数栈存储到局部变量表 | istore<br />istore\_\<n\><br />lstore<br />lstore\_\<n\><br />fstore<br/>fstore\_\<n\><br />dstore<br />dstore\_\<n\><br />astore<br />astore\_\<n\> |
| 将一个常量加载到操作数栈             | bipush<br />sipush<br />ldc<br />ldc_w<br />ldc2_w<br />aconst_null<br />iconst_m1<br/>iconst\_\<i\><br />lconst\_\<l\><br />fconst\_\<f\><br />dconst\_\<d\> |
| 扩充局部变量表的访问索引的指令       | wid                                                          |

- 有一部分是以尖括号结尾的，如`iload_<n>`。这些指令助记符实际上代表了一组指令，如例如`iload_<n>`，它代表了`iload_0`、`iload_1`、`iload_2`和`iload_3`这几条指令
- 这几组指令都是某个带有一个操作数的通用指令的特殊形式，对于这几组特殊指令，它们省略掉了**显式**的操作数，**不需要**进行取操作数的动作，因为实际上操作数就隐含在指令中
- 例如`iload_0`的语义与操作数为0时的`iload`指令 语义完全一致

##### 运算指令

| 操作作用         | 字节码指令                                               |
| ---------------- | -------------------------------------------------------- |
| 加法指令         | iadd<br />ladd<br />fadd<br />dadd                       |
| 减法指令         | isub<br />lsub<br />fsub<br />dsub                       |
| 乘法指令         | imul<br />lmul<br />fmul<br />dmul                       |
| 除法指令         | idiv<br />ldiv<br />fdiv<br />ddiv                       |
| 求余指令         | irem<br />lrem<br />frem<br />drem                       |
| 取反指令         | ineg<br />lneg<br />fneg<br />dneg                       |
| 位移指令         | ishl<br />ishr<br />iushr<br />lshl<br />lshr<br />lushr |
| 按位或指令       | ior<br />lor                                             |
| 按位与指令       | iand<br />land                                           |
| 按位异或指令     | ixor<br />lxor                                           |
| 局部变量自增指令 | iinc                                                     |
| 比较指令         | dcmpg<br />dcmpl<br />fcmpg<br />fcmpl<br />lcmp         |

- 数据运算可能会导致溢出
- 只有**除法指令**以及**求余指令**中当出现除数为零时会导致 虚拟机抛出ArithmeticException异常，其余任何整型数运算场景都**不应该抛出运行时异常**

##### 类型转换指令

| 操作作用     | 字节码指令                                                   |
| ------------ | ------------------------------------------------------------ |
| 宽化类型转换 | 无须显式的转换指令                                           |
| 窄化类型转换 | i2b<br />i2c<br />i2s<br />l2i<br />f2i<br />f2l<br />d2i<br />d2l<br />d2f |

##### 对象创建与访问指令

- 虽然类实例和数组都是对象，但Java虚拟机对类实例和数组的创建与操作使用了不同的字节码指令

| 操作作用                                                 | 字节码指令                                                   |
| -------------------------------------------------------- | ------------------------------------------------------------ |
| 创建类实例的指令                                         | new                                                          |
| 创建数组的指令                                           | newarray<br />anewarray<br />multianewarray                  |
| 访问类字段（static字段）和实例字段（非static字段）的指令 | getfield<br />putfield<br />getstatic<br />putstatic         |
| 把一个数组元素加载到操作数栈的指令                       | baload<br />caload<br />saload<br />iaload<br />laload<br />faload<br/>daload<br />aaload |
| 将一个操作数栈的值储存到数组元素中的指令                 | bastore<br />castore<br />sastore<br />iastore<br />fastore<br/>dastore<br />aastore |
| 取数组长度的指令                                         | arraylength                                                  |
| 检查类实例类型的指令                                     | instanceof<br />checkcast                                    |

##### 操作数栈管理指令

| 操作作用                                                   | 字节码指令                                                   |
| ---------------------------------------------------------- | ------------------------------------------------------------ |
| 将操作数栈的栈顶一个或两个元素出栈                         | pop<br />pop2                                                |
| 复制栈顶一个或两个数值并将复制值或双份的复制值重新压入栈顶 | dup<br />dup2<br />dup_x1<br/>dup2_x1<br />dup_x2<br />dup2_x2 |
| 将栈最顶端的两个数值互换                                   | swap                                                         |

##### 控制转移指令

| 操作作用     | 字节码指令                                                   |
| ------------ | ------------------------------------------------------------ |
| 条件分支     | ifeq<br />iflt<br />ifle<br />ifne<br />ifgt<br />ifge<br />ifnull<br />ifnonnull<br />if_icmpeq<br />if_icmpne<br />if_icmplt<br/>if_icmpgt<br />if_icmple<br />if_icmpge<br />if_acmpeq<br />if_acmpne |
| 复合条件分支 | tableswitch<br />lookupswitch                                |
| 无条件分支   | goto<br />goto_w<br />jsr<br />jsr_w<br />ret                |

##### 方法调用和返回指令

| 字节码指令      | 操作作用                                       |
| --------------- | ---------------------------------------------- |
| invokevirtual   | 用于调用对象的实例方法                         |
| invokeinterface | 用于调用接口方法                               |
| invokespecial   | 用于调用一些需要特殊处理的实例方法             |
| invokestatic    | 用于调用类静态方法                             |
| invokedynamic   | 用于在运行时动态解析出调用点限定符所引用的方法 |

##### 异常处理指令

- 而在Java虚拟机中，处理异常不是由字节码指令来实现的（很久之前曾经使用jsr和 ret指令来实现，现在已经不用了），而是采用异常表来完成

##### 同步指令

- Java虚拟机支持**方法级**的同步和**方法内部一段指令序列**的同步
- 方法级同步
  - 方法级的同步是隐式的，无须通过字节码指令来控制，它实现在方法调用和返回操作之中
  - 虚拟机可以从方法常量池中的方法表结构中的`ACC_SYNCHRONIZED`访问标志得知一个方法是否被声明为 同步方法
  - 如果是同步方法，执行线程就要求先**成功持有管程**，然后才能执行方法，最后当方法完成时释放管程
  - 如果一个同步方法执行期间抛出了异常，并且在方法内部无法处理此异常，那这个同步方法所持有的管程将在异常抛到**同步方法边界之外**时自动释放
- 方法内部一段指令序列同步
  - 同步一段指令集序列通常是由Java语言中的`synchronized`语句块来表示的
  - Java虚拟机的指令集中有`monitorenter`和`monitorexit`两条指令来支持`synchronized`关键字的语义
  - 每条`monitorenter`指令都**必须**有其对应的`monitorexit`指令
  - 为了保证在方法异常完成时`monitorenter`和`monitorexit`指令可以正确配对，编译器会**自动产生一个异常处理程序**，这个程序可处理**所有**的异常，它的目的就是用来执行`monitorexit`指令

| 操作作用 | 字节码指令   |
| -------- | ------------ |
| 开始同步 | monitorenter |
| 退出同步 | monitorexit  |

### 虚拟机类加载机制

![类的生命周期](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20210527104218160.png)

<center>类的生命周期</center>

#### 类加载的时机

类初始化**有且仅有**在下列六种情况下会发生

- 遇到`new`、`getstatic`、`putstatic`或`invokestatic`这四条字节码指令时，如果类型没有进行过初始化，则需要先触发其初始化阶段。以下代码能生成这四条指令
  - 使用`new`实例化类
  - 读取或设置一个类型的静态字段。因为被`final`修饰的静态、jvm支持的基础类型是在**常量池**中，所以不会触发类的初始化
- 

