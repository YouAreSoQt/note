# Let's Go

## 基本类型
```bool```
```string```
```int```    ```int8```    ```int16```    ```int32```    ```int64```
```uint```   ```uint8```   ```uint32```   ```uint32```   ```uint64```    ```uintptr```
```byte```(uint8的别名)
```rune```(int32的别名,用于表示一个Unicode码点)
```float32```    ```float64```
```complex64```  ```complex128```
```int```, ```uint``` 和 ```uintptr``` 在 32 位系统上通常为 32 位宽，在 64 位系统上则为 64 位宽。 当你需要一个整数值时应使用 int 类型，除非你有特殊的理由使用固定大小或无符号的整数类型。

## 零值
没有明确初始值的变量声明会被赋予它们的零值。
数值类型: ```0```
布尔类型: ```false```
字符串: ```""```
指针: ```nil```
切片: ```nil```
映射: ```nil```

## 类型转换
表达式 T(v) 将值 v 转换为类型 T。
### 例子:
```go
var i int = 42
var f float64 = float64(i)
var u uint = uint(f)
```
*不同类型的项之间赋值时需要显式转换*

## 常量
常量的声明与变量类似，只不过是使用 const 关键字。
常量可以是字符、字符串、布尔值或数值。
常量不能用 := 语法声明。

## 循环(for)
基本的 for 循环由三部分组成，它们用分号隔开：

初始化语句：在第一次迭代前执行
条件表达式：在每次迭代前求值
后置语句：在每次迭代的结尾执行
初始化语句通常为一句短变量声明，该变量声明仅在 for 语句的作用域中可见。

一旦条件表达式的布尔值为 false，循环迭代就会终止。

注意：和 C、Java、JavaScript 之类的语言不同，Go 的 for 语句后面的三个构成部分外没有小括号， 大括号 { } 则是必须的。
### 例子:
```go
for i := 0; i < 10; i++ {
	// ....
}
```
初始化语句和后置语句是可选的。(C系语言的"while"循环)
### 例子
```go
for x > 100 {
	// ...
}
```
### 无限循环
```go
for {
	// ...
}
```

## 流程控制语句(if)
if 语句与 for 循环类似，表达式外无需小括号 ( ) ，而大括号 { } 则是必须的。
### 例子
```go
if x < 0 {
    // ...
}
```
同 for 一样， if 语句可以在条件表达式前执行一个简单的语句。
该语句声明的变量作用域仅在 if 之内。
```go
if v := 0; v < max {
    // ...
}
```
### if 和 else
```go
if condition {
	// ...
} else {
	// ...
}
```

## 流程控制语句(switch)
switch 是编写一连串 if - else 语句的简便方法。它运行第一个值等于条件表达式的 case 语句。

Go 的 switch 语句类似于 C、C++、Java、JavaScript 和 PHP 中的，不过 Go 只运行选定的 case，而非之后所有的 case。 
实际上，Go 自动提供了在这些语言中每个 case 后面所需的 break 语句。 除非以 fallthrough 语句结束，否则分支会自动终止。
Go 的另一点重要的不同在于 switch 的 case 无需为常量，且取值不必为整数。

switch 的 case 语句从上到下顺次执行，直到匹配成功时停止。
### 例子
```go
switch os := runtime.GOOS; os {
case "darwin":
	// ...
case "linux":
	// ...
default:
	// ...
}
```
### 没有条件的 switch
没有条件的 switch 同 switch true 一样。

这种形式能将一长串 if-then-else 写得更加清晰。
#### 例子
```go
switch {
case t.Hour() < 12:
	fmt.Println("Good morning!")
case t.Hour() < 17:
	fmt.Println("Good afternoon.")
default:
	fmt.Println("Good evening.")
}
```

## defer
defer 语句会将函数推迟到外层函数返回之后执行。

推迟调用的函数其参数会立即求值，但直到外层函数返回前该函数都不会被调用。
### defer 栈
推迟的函数调用会被压入一个栈中。当外层函数返回时，被推迟的函数会按照后进先出的顺序调用。
### 例子
```go
for i := 0; i < 10; i++ {
	defer fmt.Println(i)
}
```

## 指针
指针保存了值的内存地址。
类型 ```*T``` 是指向 ```T``` 类型值的指针。其零值为 ```nil```。
```&``` 操作符会生成一个指向其操作数的指针。
```*``` 操作符表示指针指向的底层值。
与 C 不同，Go 没有指针运算。
### 例子
```go
i, j := 42, 2701

p := &i         // 指向 i
fmt.Println(*p) // 通过指针读取 i 的值
*p = 21         // 通过指针设置 i 的值
fmt.Println(i)  // 查看 i 的值

p = &j         // 指向 j
*p = *p / 37   // 通过指针对 j 进行除法运算
```

## 结构体
一个结构体（struct）就是一组字段（field）。

结构体字段使用点号来访问。

结构体字段可以通过结构体指针来访问。
如果我们有一个指向结构体的指针 p，那么可以通过 (*p).X 来访问其字段 X。Go允许使用隐式间接引用，直接写 p.X 就可以。

使用 Name: 语法可以仅列出部分字段。（字段名的顺序无关。）
特殊的前缀 & 返回一个指向结构体的指针。
### 例子
```go
type Vec2 struct {
	X int
	Y int
}

v := Vec2{1, 2}
v.X = 4

p := &v
p.X = 111
fmt.Println(v)

var (
	v1 = Vertex{1, 2}  // 创建一个 Vertex 类型的结构体
	v2 = Vertex{X: 1}  // Y:0 被隐式地赋予
	v3 = Vertex{}      // X:0 Y:0
	p  = &Vertex{1, 2} // 创建一个 *Vertex 类型的结构体（指针）
)
```

## 数组
类型 [n]T 表示拥有 n 个 T 类型的值的数组。
### 例子
变量 a 声明为拥有 10 个整数的数组。
```go
var a [10]int
```
```go
var a [2]string
a[0] = "Hello"
a[1] = "World"
fmt.Println(a[0], a[1])
fmt.Println(a)

primes := [6]int{2, 3, 5, 7, 11, 13}
fmt.Println(primes)
```

## 切片(简单理解为C++中的Vector)
每个数组的大小都是固定的。而切片则为数组元素提供动态大小的、灵活的视角。
类型 []T 表示一个元素类型为 T 的切片。

切片通过两个下标来界定，即一个上界和一个下界，二者以冒号分隔: a[low : high]
它会选择一个半开区间，包括第一个元素，但排除最后一个元素。
以下表达式创建了一个切片，它包含 a 中下标从 1 到 3 的元素：
```go
a[1:4]
```
### 例子
```go
primes := [6]int{2, 3, 5, 7, 11, 13}

var s []int = primes[1:4]
fmt.Println(s)
```
切片就像数组的引用
切片并不存储任何数据，它只是描述了底层数组中的一段。

更改切片的元素会修改其底层数组中对应的元素。

与它共享底层数组的切片都会观测到这些修改。
### 例子
```go
names := [4]string{
	"John",
	"Paul",
	"George",
	"Ringo",
}
fmt.Println(names)

a := names[0:2]
b := names[1:3]
fmt.Println(a, b)

b[0] = "XXX"
fmt.Println(a, b)
fmt.Println(names)
```
### 切片文法
切片文法类似于没有长度的数组文法。

这是一个数组文法：
```go
[3]bool{true, true, false}
```

下面这样则会创建一个和上面相同的数组，然后构建一个引用了它的切片：
```go
[]bool{true, true, false}
```

### 切片的默认行为
在进行切片时，你可以利用它的默认行为来忽略上下界。
切片下界的默认值为 0，上界则是该切片的长度。

对于数组
```go
var a [10]int
```
来说，以下切片是等价的：
```go
a[0:10]
a[:10]
a[0:]
a[:]
```
### 切片的长度与容量
切片拥有**长度**和**容量**。

切片的长度就是它所包含的元素个数。
切片的容量是从它的第一个元素开始数，到其底层数组元素末尾的个数。
切片 s 的长度和容量可通过表达式 ```len(s)``` 和 ```cap(s)``` 来获取。
### 用 make 创建切片
切片可以用内建函数 make 来创建，这也是你创建动态数组的方式。
make 函数会分配一个元素为零值的数组并返回一个引用了它的切片：
```go
a := make([]int, 5)  // len(a)=5
```
要指定它的容量，需向 make 传入第三个参数：
```go
b := make([]int, 0, 5) // len(b)=0, cap(b)=5

b = b[:cap(b)] // len(b)=5, cap(b)=5
b = b[1:]      // len(b)=4, cap(b)=4
```
### 向切片追加元素
```go
func append(s []T, vs ...T) []T
```
append 的第一个参数 s 是一个元素类型为 T 的切片，其余类型为 T 的值将会追加到该切片的末尾。
append 的结果是一个包含原切片所有元素加上新添加元素的切片。
当s的底层数组太小，不足以容纳所有给定的值时，它就会分配一个更大的数组。返回的切片会指向这个新分配的数组。
### Range
for 循环的 range 形式可遍历切片或映射。
当使用 for 循环遍历切片时，每次迭代都会返回两个值。第一个值为当前元素的下标，第二个值为该下标所对应元素的一份副本。
```go
for i, v := range pow {
	fmt.Printf("2**%d = %d\n", i, v)
}
```
可以将下标或值赋予 _ 来忽略它。
```go
for i, _ := range pow
for _, value := range pow
```
若你只需要索引，忽略第二个变量即可。
```go
for i := range pow
```

## 映射
映射将键映射到值。

映射的零值为nil 。nil映射既没有键，也不能添加键。
make函数会返回给定类型的映射，并将其初始化备用。
```go
type Vertex struct {
	Lat, Long float64
}

var m map[string]Vertex

func main() {
	m = make(map[string]Vertex)
	m["Bell Labs"] = Vertex{
		40.68433, -74.39967,
	}
	fmt.Println(m["Bell Labs"])
}
```

```go
type Vertex struct {
	Lat, Long float64
}

var m = map[string]Vertex{
	"Bell Labs": Vertex{
		40.68433, -74.39967,
	},
	"Google": Vertex{
		37.42202, -122.08408,
	},
}
```
若顶级类型只是一个类型名，你可以在文法的元素中省略它。
```go
type Vertex struct {
	Lat, Long float64
}

var m = map[string]Vertex{
	"Bell Labs": {40.68433, -74.39967},
	"Google":    {37.42202, -122.08408},
}
```

在映射 m 中插入或修改元素：
m[key] = elem
获取元素：
elem = m[key]
删除元素：
delete(m, key)
通过双赋值检测某个键是否存在：
elem, ok = m[key]
### 例子
```go
m := make(map[string]int)

m["Answer"] = 42
fmt.Println("The value:", m["Answer"])

m["Answer"] = 48
fmt.Println("The value:", m["Answer"])

delete(m, "Answer")
fmt.Println("The value:", m["Answer"])

v, ok := m["Answer"]
fmt.Println("The value:", v, "Present?", ok)
```

## 函数
### 函数值
函数也是值。它们可以像其它值一样传递。
函数值可以用作函数的参数或返回值。
### 例子
```go
func compute(fn func(float64, float64) float64) float64 {
	return fn(3, 4)
}

func main() {
	hypot := func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}
	fmt.Println(hypot(5, 12))

	fmt.Println(compute(hypot))
	fmt.Println(compute(math.Pow))
}
```
### 函数的闭包
Go 函数可以是一个闭包。闭包是一个函数值，它引用了其函数体之外的变量。该函数可以访问并赋予其引用的变量的值，换句话说，该函数被这些变量“绑定”在一起。
例如，函数 adder 返回一个闭包。每个闭包都被绑定在其各自的 sum 变量上。
```go
 func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}

func main() {
	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		fmt.Println(
			pos(i),
			neg(-2*i),
		)
	}
}
```

## 方法
Go 没有类。不过你可以为结构体类型定义方法。
方法就是一类带特殊的 接收者 参数的函数。
方法接收者在它自己的参数列表内，位于 func 关键字和方法名之间。
在此例中，Abs 方法拥有一个名为 v，类型为 Vertex 的接收者。
```go
type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
	v := Vertex{3, 4}
	fmt.Println(v.Abs())
}
```
### 方法即函数
记住：方法只是个带接收者参数的函数。

现在这个Abs的写法就是个正常的函数，功能并没有什么变化。
```go
type Vertex struct {
	X, Y float64
}

func Abs(v Vertex) float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
	v := Vertex{3, 4}
	fmt.Println(Abs(v))
}
```
可以为非结构体类型声明方法。
在此例中，我们看到了一个带 Abs 方法的数值类型 MyFloat。
你只能为在同一包内定义的类型的接收者声明方法，而不能为其它包内定义的类型（包括 int 之类的内建类型）的接收者声明方法。
```go
type MyFloat float64

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

func main() {
	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs())
}
```
### 指针接收者
可以为指针接收者声明方法。
这意味着对于某类型 T，接收者的类型可以用 *T 的文法。（此外，T 不能是像 *int 这样的指针。）
例如，这里为 *Vertex 定义了 Scale 方法。
指针接收者的方法可以修改接收者指向的值（就像 Scale 在这做的）。由于方法经常需要修改它的接收者，指针接收者比值接收者更常用。
试着移除第 16 行 Scale 函数声明中的 *，观察此程序的行为如何变化。
若使用值接收者，那么 Scale 方法会对原始 Vertex 值的副本进行操作。（对于函数的其它参数也是如此。）Scale 方法必须用指针接受者来更改 main 函数中声明的 Vertex 的值。
```go
type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func main() {
	v := Vertex{3, 4}
	v.Scale(10)
	fmt.Println(v.Abs())
}
```
使用指针接收者的原因有二：
* 首先，方法能够修改其接收者指向的值。
* 其次，这样可以避免在每次调用方法时复制该值。若值的类型为大型结构体时，这样做会更加高效。

## 接口
接口类型 是由一组方法签名定义的集合。

接口类型的变量可以保存任何实现了这些方法的值。
### 例子
```go
type Abser interface {
	Abs() float64
}
```
类型通过实现一个接口的所有方法来实现该接口。既然无需专门显式声明，也就没有“implements”关键字。
隐式接口从接口的实现中解耦了定义，这样接口的实现可以出现在任何包中，无需提前准备。
因此，也就无需在每一个实现上增加新的接口名称，这样同时也鼓励了明确的接口定义。
```go
type I interface {
	M()
}

type T struct {
	S string
}

// 此方法表示类型 T 实现了接口 I，但我们无需显式声明此事。
func (t T) M() {
	fmt.Println(t.S)
}

func main() {
	var i I = T{"hello"}
	i.M()
}
```
### 接口值
接口也是值。它们可以像其它值一样传递。

接口值可以用作函数的参数或返回值。

在内部，接口值可以看做包含值和具体类型的元组：(value, type)
接口值保存了一个具体底层类型的具体值。
接口值调用方法时会执行其底层类型的同名方法。
### 空接口
指定了零个方法的接口值被称为 *空接口：*
```go
interface{}
```
空接口可保存任何类型的值。（因为每个类型都至少实现了零个方法。）

空接口被用来处理未知类型的值。
```go
func main() {
	var i interface{}
	describe(i)

	i = 42
	describe(i)

	i = "hello"
	describe(i)
}

func describe(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
```
### 类型断言
类型断言 提供了访问接口值底层具体值的方式。
**t := i.(T)**
该语句断言接口值 i 保存了具体类型 T，并将其底层类型为 T 的值赋予变量 t。
为了 判断 一个接口值是否保存了一个特定的类型，类型断言可返回两个值：其底层值以及一个报告断言是否成功的布尔值。
**t, ok := i.(T)**
### 类型选择
类型选择 是一种按顺序从几个类型断言中选择分支的结构。
类型选择与一般的 switch 语句相似，不过类型选择中的 case 为类型（而非值）， 它们针对给定接口值所存储的值的类型进行比较。
```
switch v := i.(type) {
case T:
    // v 的类型为 T
case S:
    // v 的类型为 S
default:
    // 没有匹配，v 与 i 的类型相同
}
```
类型选择中的声明与类型断言 i.(T) 的语法相同，只是具体类型 T 被替换成了关键字 type。

此选择语句判断接口值 i 保存的值类型是 T 还是 S。在 T 或 S 的情况下，变量 v 会分别按 T 或 S 类型保存 i 拥有的值。在默认（即没有匹配）的情况下，变量 v 与 i 的接口类型和值相同。
```go
func do(i interface{}) {
	switch v := i.(type) {
	case int:
		fmt.Printf("Twice %v is %v\n", v, v*2)
	case string:
		fmt.Printf("%q is %v bytes long\n", v, len(v))
	default:
		fmt.Printf("I don't know about type %T!\n", v)
	}
}

func main() {
	do(21)
	do("hello")
	do(true)
}
```

## Stringer(类似java基类Object中的toString方法)
fmt 包中定义的 Stringer 是最普遍的接口之一。
```go
type Stringer interface {
    String() string
}
```
Stringer 是一个可以用字符串描述自己的类型。fmt 包（还有很多包）都通过此接口来打印值。

# 错误(error)
Go 程序使用 error 值来表示错误状态。

与 fmt.Stringer 类似，error 类型是一个内建接口：
```go
type error interface {
    Error() string
}
```
（与 fmt.Stringer 类似，fmt 包在打印值时也会满足 error。）
通常函数会返回一个 error 值，调用的它的代码应当判断这个错误是否等于 nil 来进行错误处理。
```go
i, err := strconv.Atoi("42")
if err != nil {
    fmt.Printf("couldn't convert number: %v\n", err)
    return
}
fmt.Println("Converted integer:", i)
```
error 为 nil 时表示成功；非 nil 的 error 表示失败。

## Reader
io 包指定了 io.Reader 接口，它表示从数据流的末尾进行读取。
io.Reader 接口有一个 Read 方法：
```go
func (T) Read(b []byte) (n int, err error)
```
Read 用数据填充给定的字节切片并返回填充的字节数和错误值。在遇到数据流的结尾时，它会返回一个 io.EOF 错误。
示例代码创建了一个 strings.Reader 并以每次 8 字节的速度读取它的输出。
```go
func main() {
	r := strings.NewReader("Hello, Reader!")

	b := make([]byte, 8)
	for {
		n, err := r.Read(b)
		fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
		fmt.Printf("b[:n] = %q\n", b[:n])
		if err == io.EOF {
			break
		}
	}
}
```

## 图像
image 包定义了 Image 接口：
```go
type Image interface {
    ColorModel() color.Model
    Bounds() Rectangle
    At(x, y int) color.Color
}
```

## goroutine
Go 程（goroutine）是由 Go 运行时管理的轻量级线程。
```go f(x, y, z)```会启动一个新的 Go 程并执行```f(x, y, z)```
f, x, y 和 z 的求值发生在当前的 Go 程中，而 f 的执行发生在新的 Go 程中。
**Go 程在相同的地址空间中运行，因此在访问共享的内存时必须进行同步。**

## 信道
信道是带有类型的管道，你可以通过它用信道操作符 <- 来发送或者接收值。（“箭头”就是数据流的方向。）
```go
ch := make(chan int)
ch <- v    // 将 v 发送至信道 ch。
v := <-ch  // 从 ch 接收值并赋予 v。
```
默认情况下，发送和接收操作在另一端准备好之前都会阻塞。这使得 Go 程可以在没有显式的锁或竞态变量的情况下进行同步。
以下示例对切片中的数进行求和，将任务分配给两个 Go 程。一旦两个 Go 程完成了它们的计算，它就能算出最终的结果。
```go
func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum // 将和送入 c
}

func main() {
	s := []int{7, 2, 8, -9, 4, 0}

	c := make(chan int)
	go sum(s[:len(s)/2], c)
	go sum(s[len(s)/2:], c)
	x, y := <-c, <-c // 从 c 中接收

	fmt.Println(x, y, x+y)
}
```
### 带缓冲的信道
信道可以是 带缓冲的。将缓冲长度作为第二个参数提供给 make 来初始化一个带缓冲的信道：
```go 
ch := make(chan int, 100)
```
仅当信道的缓冲区填满后，向其发送数据时才会阻塞。当缓冲区为空时，接受方会阻塞。
### range 和 close
发送者可通过 close 关闭一个信道来表示没有需要发送的值了。接收者可以通过为接收表达式分配第二个参数来测试信道是否被关闭：若没有值可以接收且信道已被关闭，那么在执行完
```go
v, ok := <-ch
```
之后 ok 会被设置为 false。
循环 ```for i := range c```会不断从信道接收值，直到它被关闭。
**注意：** 只有发送者才能关闭信道，而接收者不能。向一个已经关闭的信道发送数据会引发程序panic。
**还要注意：** 信道与文件不同，通常情况下无需关闭它们。只有在必须告诉接收者不再有需要发送的值时才有必要关闭，例如终止一个 range 循环。
```go
func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	close(c)
}

func main() {
	c := make(chan int, 10)
	go fibonacci(cap(c), c)
	for i := range c {
		fmt.Println(i)
	}
}
```
### select语句
select 语句使一个 Go 程可以等待多个通信操作。
select 会阻塞到某个分支可以继续执行为止，这时就会执行该分支。当多个分支都准备好时会随机选择一个执行。
```go
func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x:
			x, y = y, x+y
		case <-quit:
			fmt.Println("quit")
			return
		}
	}
}

func main() {
	c := make(chan int)
	quit := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0
	}()
	fibonacci(c, quit)
}
```
#### 默认选择
当 select 中的其它分支都没有准备好时，default 分支就会执行。
为了在尝试发送或者接收时不发生阻塞，可使用 default 分支：
```go
select {
case i := <-c:
    // 使用 i
default:
    // 从 c 中接收会阻塞时执行
}
```
### sync.Mutex
Go 标准库中提供了 sync.Mutex 互斥锁类型及其两个方法：
* Lock
* Unlock
```go
// SafeCounter 的并发使用是安全的。
type SafeCounter struct {
	v   map[string]int
	mux sync.Mutex
}

// Inc 增加给定 key 的计数器的值。
func (c *SafeCounter) Inc(key string) {
	c.mux.Lock()
	// Lock 之后同一时刻只有一个 goroutine 能访问 c.v
	c.v[key]++
	c.mux.Unlock()
}

// Value 返回给定 key 的计数器的当前值。
func (c *SafeCounter) Value(key string) int {
	c.mux.Lock()
	// Lock 之后同一时刻只有一个 goroutine 能访问 c.v
	defer c.mux.Unlock()
	return c.v[key]
}

func main() {
	c := SafeCounter{v: make(map[string]int)}
	for i := 0; i < 1000; i++ {
		go c.Inc("somekey")
	}

	time.Sleep(time.Second)
	fmt.Println(c.Value("somekey"))
}
```