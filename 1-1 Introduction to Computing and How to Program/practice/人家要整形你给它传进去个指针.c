#include<stdio.h>
void fun(int*x)//����ԭ����ˣ���� 
{
	printf("%d",++*x);
}
int main(void)
{
	int a=25;
	fun(&a);
	return 0;
}
