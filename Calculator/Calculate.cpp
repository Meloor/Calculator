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

bool Calculate::IsOperator(char a) {//�ж��Ƿ�Ϊ����� 
	return (a == '+' || a == '-' || a == '*' || a == '/');
}
bool Calculate::Priority(char a, char b) {//�ж����ȼ� 
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
//��׺ת��׺
string Calculate::InfixToSuffix(string ifx) {
	stack<char> optr;//�����
	string sfx = "";
	while (optr.empty() == false) optr.pop();

	for (int i = 0; i< ifx.length(); i++) {
		if (isdigit(ifx[i])) {//��������ֱ�������sfx 
			sfx = sfx + ifx[i];
			if (!isdigit(ifx[i + 1]))
				sfx = sfx + ' ';//������һ����������ʱ������ո�		
		}
		else if (ifx[i] == '(') {//����ǰ����ֱ����ջ 
			optr.push(ifx[i]);
		}
		else if (ifx[i] == ')') {//���������� ����ջ��ֱ������ǰ���� 
			while (optr.top() != '(') {
				sfx = sfx + optr.top();
				sfx = sfx + ' ';
				optr.pop();
			}optr.pop();
		}
		else if (IsOperator(ifx[i])) {//��������� 
			if (optr.empty())//ջΪ��ʱֱ����ջ 
				optr.push(ifx[i]);
			else {
				while (Priority(optr.top(), ifx[i])) { //��ջΪ��ʱ,����top()����� 
					sfx = sfx + optr.top();
					sfx = sfx + ' ';
					optr.pop();
					if (optr.empty())//������һ��,�������� 
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
//����һ�� 
double Calculate::CalOnce(int a, char optr, int b) {
	switch (optr) {
		case '+':return a + b;
		case '-':return a - b;
		case '*':return a * b;
		case '/':return a / b;
	}
}
//�ú�׺���ʽ������ 
//12 23 37 14 - * +
//�����һ��������
string Calculate::Solve(string formula) {
	Calculate *calc = new Calculate();//��̬��������ֱ�ӵ��Ǿ�̬��Ա����
	string sfx = calc->InfixToSuffix(formula);
	string ans_str = "";
	stack<double> dig;//������ջ
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
		else {//���������� 
			b = dig.top(); dig.pop();
			a = dig.top(); dig.pop();//����ջ�ļ���ʱӦ����ǰ�� 
			ans = calc->CalOnce(a, sfx[i], b);
			if (sfx[i] == '/') {//ֻ�г����Ż����С�������Գ�����ʱ���ǷǷ���ʽ��
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