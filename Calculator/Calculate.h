/* 由于阿超的Calcutor的solve方法存在一些问题，而且代码比较难懂
 * 调试有些困难，所以我另写了这个类，用后缀表达式求值的方法来
 * 实现solve;
 * 原理：后缀表达式求值，先把中缀表达式转为后缀表达式，然后在用后缀表达式求解
 */

#pragma once
#include<iostream>
using namespace std;
class Calculate
{
public:
	Calculate();
	~Calculate();
private:
	double CalOnce(int a, char optr, int b);
	bool Priority(char a, char b);
	bool IsOperator(char a);
	string InfixToSuffix(string ifx);
	string WrongMassage();
public:
	static string Solve(string formula);
};

