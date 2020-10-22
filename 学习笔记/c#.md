# c#

## 委托

- delegate

- 当方法有相同的签名(指相同的返回类型和参数列表)，可以使用委托

### 多播委托

- 实现广播

## 泛型

### c++与c#泛型区别

- c++在编译时就将类型确定
- c#在运行期间才确定类型

### var

- 编译器会根据上下文来判断你到底是想用什么类型的

-  必须在定义时初始化

- 一但初始化完成，就不能再给变量赋与初始化值类型不同的值了。

- var要求是局部变量。

- 使用var定义变量和object不同，它在效率上和使用强类型方式定义变量完全一样。

- ```c#
  /*
    * add时装箱为object类型
    * 可以添加不同类型的变量
    * 在运行期间可能产生类型转换异常
  */
  var  list=new ArrayList();
  
  /*
    * 类型安全
    * 不再进行装箱和拆箱操作
    * 
  */
  var  list=new List<int>();
  
  ```

### default

- 使用：default(变量名)
- 如果变量为值类型设置为0，引用类型设置为空

### 对引用类型的约束

- 如`class myClass<T>:fatherClass where T:anotherClass , anotherInterface`
- ![image-20200924090438740](https://gitee.com/lin_haoran/Picgo/raw/master/img/image-20200924090438740.png)
- 如果使用new()作约束，它就必须是为类型指定的最后一个约束

### foreach

- 要使用foreach，就要实现GetEnumerator()方法或实现IEnumerator接口

- 关于IEnumerable与IEnumerator

  - IEnumerable是一个非常简单的接口，它仅仅包含了一个返回IEnumerator接口对象的抽象方法：GetEnumerator()。

  - ```c#
    IEnumerator IEnumerable.GetEnumerator(){
    	for (int i = 0; i < person.Length; i++){
    		yield return person[i];
    	}
    }
    //yield return 可以记录函数状态
    ```

- 而IEnumerator接口提供了一个属性和两个抽象方法分别是：

    - ```c#
      object Current { get; }
      bool MoveNext();
      void Reset();
      /*
       *Current表示遍历的集合的当前元素
       *MoveNext()实现移动Enumerator（枚举器）到下一个位置
       *Reset()即重置枚举器。
       */
      ```


- 非继承类的隐式\显示转换

  - ```c#
      //显示声明的myclass转int类处理方法
      public static explicit operator int(myclass mc){
      	return mc.value;
      }
      //隐式声明的int转myclass类处理方法
      public static implicit operator myclass(int value){
      	return new myclass(value);
      }
      //隐式声明的myclass转string类处理方法
      public static implicit operator string(myclass mc){
      	return ("定义的myclass类string类型转化结果");
      }
      ```

### 协变和抗变

- 指对参数和返回值的类型进行转换

- 本质上是向上转型

- out

  - 指泛型接口为协变的

  - 如果一个泛型接口IFoo\<T>，IFoo\<TSub>可以转换为IFoo\<TParent>的话，我们称这个过程为协变，IFoo支持对参数T的协变。

  - 协变的参数只能用于方法的返回值

  - ```c#
    //方法的返回值等同于
    TParent parent = TSub thisVar;
    ```

- in

  - 指泛型接口为抗变的

  - 如果一个泛型接口IFoo\<T>，IFoo\<TParent>可以转换为IFoo\<TSub>的话，我们称这个过程为逆变，IFoo支持对参数T的抗变。

  - 抗变的参数只能用于方法的参数

  - ```c#
    //方法的参数等同于
    TParent thisVar = TSub sub;
    ```

## Dispose、Close和析构函数

|          | 析构函数                         | Dispose方法                     | Close方法          |
| -------- | -------------------------------- | ------------------------------- | ------------------ |
| 意义     | 销毁对象                         | 销毁对象                        | 关闭对象资源       |
| 调用方法 | 不能被显示调用，在GC回收时被调用 | 要显示调用，用using语句         | 需要显示调用       |
| 调用时机 | 不确定                           | 确定，显示调用或离开using程序块 | 确定，在显示调用时 |

## 多线程

### Thread

- Thread的构造方法需要一个参数，用于指定线程的入口

  - ```c#
    Thread   compressThread=new  Thread(entryPoint);
    //其中Thread构造函数为:public Thread ( ThreadStart start ) 
    //委托定义为void ThreadStart()
    ```

- Thread类的常用属性

  - CurrentThread：获取当前正在运行的线程
  - IsAlive：示当前线程的执行状态，如果此线程已启动并且尚未正常终止，则为 true；否则为 false。
  - IsBackground：指示该线程是否为后台线程。
  - Name：线程名
  - Poiority：线程优先级
    - ThreadPriority.Highest

    - AboveNormal

    - Normal
    - BelowNormal
    - Lowest

- 给线程传递数据

  - 使用带ParameterizedThreadStart委托参数的Thread构造函数
  - ParameterThreadStart的定义为void ParameterizedThreadStart(object state)

- 前台与后台线程

  - 只要有一个前台线程在运行，应用程序的进程就在运行
  - 在默认情况下，用Thread类创建的线程是前台线程，线程池中的线程总是后台线程
  - 通过设置线程的属性IsBackground可以确定该线程是前台线程还是后台线程

- 线程池ThreadPool

### Task

- 任务在后台使用ThreadPool

- 在安排需要完成的工作时，任务提供了非常大的灵活性。

  - 可以定义连续的工作，在一个任务完成后需要执行什么工作
  - 可以在层次结构中安排任务，例如父任务可以创建新的子任务，这可以创建一种依赖关系

- 可以使用TaskFactory类或Task类的构造函数和Start()方法 

  - ```c#
     // using task factory
      	TaskFactory tf = new TaskFactory();
        Task t1 = tf.StartNew(TaskMethod);
    // using the task factory via a task
        Task t2 = Task.Factory.StartNew(TaskMethod);
    // using Task constructor
        Task t3 = new Task(TaskMethod);
    // t3.Start();
        t3.RunSynchronously();//任务也会启动，但是在调用者的当前线程中运行，调用者需要一直等待该任务结束
    ```

- TaskCreationOptions选项

  - 设置LongRunning选项，可以通知任务调度器，该任务需要较长时间运行，这样调度器更可能使用新线程
  - 如果该任务关联到父任务上，而父任务取消了，该任务也要取消，此时应设置AttachToParent选项
  - 如果任务应以公平的方式与所有其他任务一起处理，应设置该选项为PreferFairness

- 连续的任务

  - 通过任务，可以指定在任务完成后，应开始运行另一个特定任务 。例如，一个使用前一个任务的结果的新任务，如果前一个任务失败了，这个任务就应执行一些清理工作

  - 连续处理程序有一个Task类型的参数

  - ```c#
    Task t1 = new Task(DoOnFirst);
    Task t2 = t1.ContinueWith(DoOnSecond);
    Task t3 = t1.ContinueWith(DoOnSecond);
    //连续任务通过在任务上调用ContinueWith( )来定义，
    //也可以使用TaskFactory类来定义
    //调用DoOnSecond方法的新任务应在任务t1结束时立即启动
     //在一个任务结束时，可以启动多个任务
     //连续任务也可以有另一个连续任务
    
    ```

  - 无论前一个任务是如何结束的，连续任务总是在前一个任务结束时启动

  - 使用TaskContinuationOptions枚举中的值，可以指定任务只有在起始任务成功（或失败）结束时启动

  - ```c#
    Task t5 = t1.ContinueWith(DoOnError,TaskContinuationOptions.OnlyOnFaulted);
    
    ```

- 父任务和子任务

  - 一个任务在另一个任务内部创建，并**显示的绑定父进程**构成父子关系

  - 如果父任务在子任务之前结束，父任务的状态就显示为WaitingForChildrenToComplete。子任务也结束时，父任务的状态就显示为RanToCompletion

  - 如果父任务使用TaskCreationOptions枚举中的DetachedFromParent创建子任务，以上就无效
  - 取消父任务就会取消子任务

- 任务的结果