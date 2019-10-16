# Calcutor
阿超的四则运算生成器 v2.0(C++版本)
## 1. 升级说明
由于v1.0版本的Calcutor的solve方法存在一些问题，而且代码比较难懂，调试有些困难，所以我添加了Calculate类，用后缀表达式求值的方法来实现solve函数。

**原理：**
* [后缀表达式求值](https://blog.csdn.net/Meloor/article/details/86755633)
* 先把中缀表达式转为后缀表达式
* 然后在用后缀表达式求解
## 2. 原需求
* 程序接收一个命令行参数 n，然后随机产生 n 道加减乘除（分别使用符号+ - * /来表示）练习题，每个数字在 0 和 100 之间，运算符在2个 到 3 个 之间。
* 由于阿超的孩子才上一年级，并不知道分数所以软件所出的练习题在运算过程中不得出现非整数，比如不能出现 3÷5 + 2 = 2.6 这样的算式。
* 练习题生成好后，将生成的n道练习题及其对应的正确答案输出到一个文件 subject.txt 中。
## 3. 功能说明
目前实现了前两个功能
- Calculate类
	* 有一个静态Solve(string formula)函数
		* 用于计算传入表达式的值。
		* 如果计算过程中出现小数，返回错误信息
- Calculator类
	* 	MakeFormula()函数
		* 返回一个满足需求一的式子
	*  MakeCorrectFormula()函数
		* 返回一个满足需求二的式子
## 4. 项目地址
https://github.com/Meloor/Calculator/tree/cplusplus

