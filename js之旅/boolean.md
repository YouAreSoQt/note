# Boolean

## 条件语句中
其值不是`undefined`或`null`的任意对象(包括其值为`false`的布尔对象)在传递给条件语句时都将计算为`true`。
### 注意区分
```
new Boolean(false) ? 1 : -1;       // 1
Boolean(false) ? 1 : -1;           // -1
```
```
undefined ? 1 : -1;                // -1
null ? 1 : -1;                     // -1
```

## 创建Boolean对象时
如果需要, 作为第一个参数传递的值将转换为布尔值。如果省略该参数或参数值为`0`、`-0`、`null`、`false`、`NaN`、`undefined`或空字符串(`""`), 则该对象具有的初始值为`false`。所有其它值, 包括任何对象, 空数组（`[]`）或字符串 `"false"`, 都会创建一个初始值为 `true` 的对象。
```
new Boolean(0);                    // Boolean {false}
new Boolean(-0);                   // Boolean {false}
new Boolean(+0);                   // Boolean {false}
new Boolean(null);                 // Boolean {false}
new Boolean(false);                // Boolean {false}
new Boolean(NaN);                  // Boolean {false}
new Boolean(undeined);             // Boolean {false}
new Boolean("");                   // Boolean {false}
new Boolean([]);                   // Boolean {true}
new Boolean("false");              // Boolean {true}
new Boolean(new Boolean(false))    // Boolean {true}
```

## 注意
在条件语句中, 直接使用`0`、`-0`、`null`、`false`、`NaN`、`undefined`或空字符串(`""`)表现为`false`。所有其它值, 包括任何对象, 空数组（`[]`）或字符串 `"false"`, 都会表现为 `true`。

## 参考资料
[mdn web docs](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Boolean)