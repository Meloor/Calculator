#include "pch.h"
#include "Calculate.h"
#include<stack>
#include<string>
Calculate::Calculate()
{
}


Calculate::~Calculate()
{
}

bool Calculate::IsOperator(char a) {//判断是否为运算符 
	return (a == '+' || a == '-' || a == '*' || a == '/');
}
bool Calculate::Priority(char a, char b) {//判断优先级 
	int x, y;
	switch (a) {
	case '*':
	case '/':x = 2; break;
	case '+':
	case '-':x = 1; break;
	}
	switch (b) {
	case '*':
	case '/':y = 2; break;
	case '+':
	case '-':y = 1; break;
	}
	if (x >= y)return true;
	else return false;
}
//中缀转后缀
string Calculate::InfixToSuffix(string ifx) {
	stack<char> optr;//运算符
	string sfx = "";
	while (optr.empty() == false) optr.pop();

	for (int i = 0; i< ifx.length(); i++) {
		if (isdigit(ifx[i])) {//遇到数字直接输出到sfx 
			sfx = sfx + ifx[i];
			if (!isdigit(ifx[i + 1]))
				sfx = sfx + ' ';//当后面一个不是数字时才输入空格		
		}
		else if (ifx[i] == '(') {//遇到前括号直接入栈 
			optr.push(ifx[i]);
		}
		else if (ifx[i] == ')') {//遇到后括号 ，出栈，直到遇到前括号 
			while (optr.top() != '(') {
				sfx = sfx + optr.top();
				sfx = sfx + ' ';
				optr.pop();
			}optr.pop();
		}
		else if (IsOperator(ifx[i])) {//遇到运算符 
			if (optr.empty())//栈为空时直接入栈 
				optr.push(ifx[i]);
			else {
				while (Priority(optr.top(), ifx[i])) { //当栈为空时,访问top()会出错 
					sfx = sfx + optr.top();
					sfx = sfx + ' ';
					optr.pop();
					if (optr.empty())//加了这一行,问题解决了 
						break;
				}
				optr.push(ifx[i]);
			}
		}
	}
	while (!optr.empty()) {
		sfx = sfx + optr.top();
		sfx = sfx + ' ';
		optr.pop();
	}
	return sfx;
}
//计算一次 
double Calculate::CalOnce(int a, char optr, int b) {
	switch (optr) {
		case '+':return a + b;
		case '-':return a - b;
		case '*':return a * b;
		case '/':return a / b;
	}
}
//用后缀表达式计算结果 
//12 23 37 14 - * +
//输入的一定是整数
string Calculate::Solve(string formula) {
	Calculate *calc = new Calculate();//静态函数不能直接调非静态成员变量
	string sfx = calc->InfixToSuffix(formula);
	string ans_str = "";
	stack<double> dig;//操作数栈
	while (!dig.empty())dig.pop();
	int x = 0;
	int a, b, ans = 0;

	for (int i = 0; i < sfx.length(); i++) {
		if (sfx[i] == ' ') continue;
		else if (isdigit(sfx[i])) {
			if (isdigit(sfx[i + 1]))
				x = x * 10 + sfx[i] - '0';
			else {
				x = x * 10 + sfx[i] - '0';
				dig.push(x);
				x = 0;
			}
		}
		else {//遇到操作符 
			b = dig.top(); dig.pop();
			a = dig.top(); dig.pop();//先入栈的计算时应该在前面 
			ans = calc->CalOnce(a, sfx[i], b);
			if (sfx[i] == '/') {//只有除法才会出现小数，所以除不尽时就是非法的式子
				if(a%b)
					return "error";
			}				
			dig.push(ans);
		}
	}
	return ans_str + to_string((int)ans);
}
string Calculate::WrongMassage() {
	return "The result of the calculation appears decimal";
}