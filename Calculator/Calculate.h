/* ���ڰ�����Calcutor��solve��������һЩ���⣬���Ҵ���Ƚ��Ѷ�
 * ������Щ���ѣ���������д������࣬�ú�׺���ʽ��ֵ�ķ�����
 * ʵ��solve;
 * ԭ����׺���ʽ��ֵ���Ȱ���׺���ʽתΪ��׺���ʽ��Ȼ�����ú�׺���ʽ���
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

