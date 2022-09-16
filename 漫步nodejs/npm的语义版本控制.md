# npm的语义版本控制
## 包版本格式格式及意义
所有的版本编号都由3个数字来构成：x.y.z
1. 第一个数字表示主版本号
2. 第二个数字表示次版本号
3. 第三个数字表示补丁版本号

## 版本号相关的符号规则
* ^: 不允许修改版本号中最左侧的非0版本号。
    * ^1.2.3 === >=1.2.3 && <2.0.0
    * ^0.2.3 === >=0.2.3 && <0.3.0
    * ^0.0.3 === >=0.0.3 && <0.0.4
    When parsing caret ranges, a missing patch value desugars to the number 0, but will allow flexibility within that value, even if the major and minor versions are both 0.
    * ^0.0   === >=0.0.0 && <0.1.0
    * ^0.0.x === >=0.0.0 && <0.1.0
    * ^1.2.x === >=1.2.0 && <2.0.0
    A missing minor and patch values will desugar to zero, but also allow flexibility within those values, even if the major version is zero.
    * ^1.x   === >=1.0.0 && <2.0.0
    * ^0.x   === >=0.0.0 && <1.0.0
* ~: 如果指定了次要版本，则允许补丁级别的更改；如果没有，则还允许进行次要版本的更改。
    * ~1.2.3 === >=1.2.3 && <1.3.0
    * ~1.2   === >=1.2.0 && <1.3.0
    * ~1     === >=1.0.0 && <2.0.0
    * ~0.2.3 === >=0.2.3 && <0.3.0
    * ~0.2   === >=0.2.0 && <0.3.0
    * ~0     === >=0.0.0 && <1.0.0
* ||: 或。用于组合
    * <2.1 || >2.8
* -: 范围。
    * 2.1.0 - 2.6.2 === >=2.1.0 && <=2.6.2