#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<stack>
#include<cstdio>
#include<cstdlib>
using namespace std;
const double PI = M_PI;
const double e = 2.718281828;

void input_equation(char input[])
//����ȥ���ո�
{
	char tmp;
	int len = 0;
	while ((tmp = getchar()) != '\n')
		if (tmp != ' ')
			input[len++] = tmp;
	input[len] = '\0';
	return;
}

bool check_bracket(char input[])
//��������Ƿ����
{
	stack<char> stk;
	stk.push('\0');
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == '(')
			stk.push('(');
		else if (input[i] == ')')
		{
			if (stk.top() == '(')
				stk.pop();
			else
				return false;
		}
	}
	if (stk.top() == '\0')
		return true;
	return false;
}

bool check(char input[])
//������������Ƿ�Ϸ�
{
	if (input[strlen(input) - 1] != '=')
		return false;
	if (!check_bracket(input))
		return false;
	return true;
}

bool unary_operation(int op, double& x)
//��Ŀ�����
{
	switch (op)
	{
	case 0: return true;
	case 8: x=sin(x); return true;
	case 9: x=cos(x); return true;
	case 10: x=tan(x); return true;
	case 11: if (x <= 0.0) return false; x = log10(x); return true;
	case 12: if (x <= 0.0) return false; x = log(x); return true;
	case 13: x = -x; return true;
	}
}

bool binocular_operation(int op, double& x, double y)//ǰ׺��Ŀ����������㶨��
//˫Ŀ�����
{
	switch (op)
	{
	case 2: x = x + y; return true;
	case 3: x = x - y; return true;
	case 4: x = x * y; return true;
	case 5: if (fabs(y - 0.0) < 1e-10) return false; else x = x / y; return true;
	case 6: x = pow(x, y); return true;
	}
}

bool priority(int op_in_stk, int op_to_be_pushed)
//�������ȼ�
{
	if (op_in_stk == 14)
    //���������Ż���ջ���������վ����������ȼ��ߣ���ֱ����ջ
		return false;
    if (op_in_stk <= 6 && op_to_be_pushed <= 6)
    //���߶���˫Ŀ�����
    {
        if (op_in_stk / 2 < op_to_be_pushed / 2)
        //0��1ͬ���ȼ���2��3ͬ���ȼ���4��5ͬ���ȼ���6���ȼ����
            return false;
        else
            return true;
    }
	else if (op_in_stk <= 6 && op_to_be_pushed > 6)
        return false;
    else if (op_in_stk > 6 && op_to_be_pushed <= 6)
        return true;
    else
    //���߶��ǵ�Ŀ���������ֱ��ѹջ
        return false;
}

bool calculate(char input[])
{
	stack<double> number;
	stack<int> operation;
	operation.push(0);//�ѵȺ�ѹ��ջ��

	for (int i = 0; i < strlen(input); i++)
	{
		if ((input[i] == 'p' || input[i] == 'P') && (input[i + 1] == 'i' || input[i + 1] == 'I'))
		//�����û����ִ�Сд������pi
		{
			number.push(PI);
			i++;
		}
		else if (input[i] == 'e')
		//����e
			number.push(e);
		else if (input[i] >= '0' && input[i] <= '9' || input[i] == '.')
		//����
		{
			double num = 0.0;
			while (input[i] >= '0' && input[i] <= '9')
			{
				num = num * 10 + input[i] - '0';
				i++;
			}
			if (input[i] == '.')
			{
				double power = 1;
				i++;
				while (input[i] >= '0' && input[i] <= '9')
				{
					power /= 10;
					num += power * (input[i] - '0');
					i++;
				}
			}
			number.push(num);
			i--;
		}
		else
        //���������
		{
			int op_to_be_pushed = -1;
			char s_opration[15][5] = { "=", ")", "+", "-", "*", "/", "^", "\0", "sin", "cos", "tan", "log", "ln", "~", "(" };
			for (int j = 0; j <= 14; j++)
				if (j == 7) continue;
				else if (strncmp(&input[i], s_opration[j], strlen(s_opration[j])) == 0)
				{
					op_to_be_pushed = j;
					i += strlen(s_opration[j]) - 1;
					break;
				}
			if (op_to_be_pushed == -1)
            //����û��ƥ��
				return false;
			while (!operation.empty() && priority(operation.top(), op_to_be_pushed))
			{
				int op_in_stk = operation.top();
				operation.pop();
				if (op_in_stk >= 8 && op_in_stk <= 13 || op_in_stk == 0)
				//��Ŀ������Ĵ���
				{
					double num;
					if (!number.empty())
					{
						num = number.top();
						number.pop();
					}
					else
						return false;
					if (!unary_operation(op_in_stk, num))
                        return false;
					number.push(num);
				}
				else
                //˫Ŀ������Ĵ���
				{
					double num1, num2;
					if (!number.empty())
					{
						num1 = number.top();
						number.pop();
					}
					else
						return false;
					if (!number.empty())
					{
						num2 = number.top();
						number.pop();
					}
					else
						return false;
					if (!binocular_operation(op_in_stk, num2, num1))
                        return false;
					number.push(num2);
				}
			}
			if (op_to_be_pushed == 1)
            //����ջ�����Ϊ���������ջ���������Ÿ�����
				operation.pop();
			else
			//����ѹջ
				operation.push(op_to_be_pushed);
		}
	}
	if (number.size() != 1)
        return false;
	cout << input;
	if (fabs(ceil(number.top())-number.top()) < 1e-8)
        cout << ceil(number.top()) << endl;
    else if (fabs(floor(number.top())-number.top()) < 1e-8)
        cout << floor(number.top()) << endl;
    //��������������ֵС��10^-8���������
    else
        cout << number.top() << endl;
	return true;
}

int main(void)
{
	char input[1000];
	bool flag;
	cout << "�򵥼����� ver.yjbbrqw\n"
        << "����ʹ��˵����\n"
        << "1.������������ʵ�ֻ����ļӼ��˳��˷��������Լ�sin, cos, tan, ln, log���㡣\n"
        << "2.������ʽʱ�����пո񽫱����ԣ����뱣֤��ʽĩβΪ'='����������ƥ�䣨����ʡ����ʽĩβ��')'��\n"
        << "3.�ṩ����������pi��e����ֱ�����롣\n"
        << "4.��Ҫ���븺�ŷǼ��ţ�������~�����渺�š�\n"
        << "5.��Ҫ�������뱣֤������������0��\n"
        << "6.����������������Ϊ�㣬�����ʡ������㣬����.1234\n"
        << "7.����exit�س������˳�����\n";
    system("pause");
	while (1)
    {
        cout << "��������ʽ��\n";
		input_equation(input);
		if (strcmp(input, "exit") == 0)
            return 0;
		flag = check(input);
		if (flag)
			flag = calculate(input);
		if (!flag)
			cout << "�����������������롣\n";
	}
	return 0;
}

