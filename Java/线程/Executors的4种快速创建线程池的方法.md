# Executors的4种快速创建线程池的方法

## newSingleThreadExecutor

Creates an Executor that uses a single worker thread operating off an unbounded queue. (Note however that if this single thread terminates due to a failure during execution prior to shutdown, a new one will take its place if needed to execute subsequent tasks.) Tasks are guaranteed to execute sequentially, and no more than one task will be active at any given time. Unlike the otherwise equivalent ```newFixedThreadPool(1)``` the returned executor is guaranteed not to be reconfigurable to use additional threads.

## newFixedThreadPool

Creates a thread pool that reuses a fixed number of threads operating off a shared unbounded queue. At any point, at most nThreads threads will be active processing tasks. If additional tasks are submitted when all threads are active, they will wait in the queue until a thread is available. If any thread terminates due to a failure during execution prior to shutdown, a new one will take its place if needed to execute subsequent tasks. The threads in the pool will exist until it is explicitly shutdown.

## ```shutdown``` vs ```shutdownNow```

执行```shutdown()```方法后，线程池状态变为```SHUTDOWN```，此时线程池将拒绝新任务，不能再往线程池中添加新任务，否则会抛出```RejectedExecutionException```异常。此时，线程池不会立刻退出，直到添加到线程池中的任务都已经处理完成才会退出。还有一个与```shutdown()```类似的方法，叫作```shutdownNow()```，执行```shutdownNow```()方法后，线程池状态会立刻变成```STOP```，并试图停止所有正在执行的线程，并且不再处理还在阻塞队列中等待的任务，会返回那些未执行的任务。

## ThreadPoolExecutor构造函数的各个参数说明

### ```corePoolSize```
核心池的大小。

核心池中的线程会一致保存在线程池中(即使线程空闲), 除非调用allowCoreThreadTimeOut方法允许核心线程在空闲后一定时间内销毁, 该时间由构造方法中的keepAliveTime和unit参数指定.

在创建了线程池后, 默认情况下, 线程池中并没有任何线程, 而是等待有任务到来才创建线程去执行任务, 除非调用```prestartAllCoreThreads()```或者```prestartCoreThread()```方法, 从这两个方法的名字就可以看出, 是**预创建线程**的意思, 即在没有任务到来之前就创建corePoolSize个线程(prestartAllCoreThreads)或者一个线程(prestartCoreThread).

### ```maximumPoolSize```

线程池允许的最大线程数。这个参数也是一个非常重要的参数, 它表示在线程池中最多能创建多少个线程。

默认情况下, 在创建了线程池后, 线程池中的线程数为0, 当有任务来之后，就会创建一个线程去执行任务, 当线程池中的线程数目达到corePoolSize后,就会把新加入的任务放到缓存队列当中,缓存队列由构造方法中的workQueue参数指定,如果入队失败(队列已满)则尝试创建临时线程,但临时线程和核心线程的总数不能超过maximumPoolSize,当线程总数达到maximumPoolSize后会拒绝新任务.所以有两种方式可以让任务绝不被拒绝:

1. 将maximumPoolSize设置为Integer.MAX_VALUE(线程数不可能达到这个值),CachedThreadPool就是这么做的；
2. 使用无限容量的阻塞队列(比如LinkedBlockingQueue),所有处理不过来的任务全部排队去,FixedThreadPool就是这么做的。

### ```keepAliveTime```

表示线程没有任务执行时最多保持多久时间会终止。

默认情况下,只有当线程池中的线程数大于corePoolSize时,keepAliveTime才会起作用.当线程池中的线程数大于corePoolSize时,如果一个线程空闲的时间达到keepAliveTime,则会被销毁,直到线程池中的线程数不超过corePoolSize。但是如果调用了```allowCoreThreadTimeOut(true)```方法,在线程池中的线程数不大于corePoolSize时,keepAliveTime参数也会起作用,直到线程池中的线程数为0.

### ```unit```

参数keepAliveTime的时间单位，有7种取值，在TimeUnit类中有7种静态属性:

```java
TimeUnit.DAYS;              //天
TimeUnit.HOURS;             //小时
TimeUnit.MINUTES;           //分钟
TimeUnit.SECONDS;           //秒
TimeUnit.MILLISECONDS;      //毫秒
TimeUnit.MICROSECONDS;      //微妙
TimeUnit.NANOSECONDS;       //纳秒
```

并发库中所有时间表示方法都是以TimeUnit枚举类作为单位

### ```workQueue```

一个阻塞队列(BlockingQueue接口的实现类),用来存储等待执行的任务,一般来说,这里的阻塞队列有以下几种选择:

```java
ArrayBlockingQueue    // 数组实现的阻塞队列，数组不支持自动扩容。所以当阻塞队列已满
                      // 线程池会根据handler参数中指定的拒绝任务的策略决定如何处理后面加入的任务
 
LinkedBlockingQueue   // 链表实现的阻塞队列，默认容量Integer.MAX_VALUE(不限容)，
                      // 当然也可以通过构造方法限制容量
 
SynchronousQueue      // 零容量的同步阻塞队列，添加任务直到有线程接受该任务才返回
                      // 用于实现生产者与消费者的同步，所以被叫做同步队列
 
PriorityBlockingQueue // 二叉堆实现的优先级阻塞队列
 
DelayQueue          // 延时阻塞队列，该队列中的元素需要实现Delayed接口
                    // 底层使用PriorityQueue的二叉堆对Delayed元素排序
                    // ScheduledThreadPoolExecutor底层就用了DelayQueue的变体"DelayWorkQueue"
                    // 队列中所有的任务都会封装成ScheduledFutureTask对象(该类已实现Delayed接口)
```

### ```threadFactory```

线程工厂,主要用来创建线程.默认情况都会使用Executors工具类中定义的默认工厂类DefaultThreadFactory。可以实现ThreadFactory接口来自己控制创建线程池的过程(比如设置创建线程的名字、优先级或者是否为Deamon守护线程)

### ```handler```

表示当拒绝处理任务时的策略,有以下四种取值(默认为```AbortPolicy```):

```java
ThreadPoolExecutor.AbortPolicy: 丢弃任务并抛出RejectedExecutionException异常。
ThreadPoolExecutor.DiscardPolicy：也是丢弃任务，但是不抛出异常。
ThreadPoolExecutor.DiscardOldestPolicy：丢弃队列最前面的任务，然后重新尝试执行任务（重复此过程）
ThreadPoolExecutor.CallerRunsPolicy：由调用线程处理该任务
```

可通过实现```RejectedExecutionHandler```接口来自定义任务拒绝后的处理策略