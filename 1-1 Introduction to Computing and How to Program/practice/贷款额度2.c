#include<stdio.h>
int min(double a, double b)
{
	if (a > b) return b;
	else return a;
}
int main()
{
	double price, area, balance1, balance2, ratio1, ratio2, ratio3, ratio4, deposit1, deposit2, repayment;
	double a, b, c, d, ans, x, y;
	char m, n, o, p;
	int month;
	printf("������ס���ܼۣ�����ԪΪ��λ����ͬ��\n");
	scanf("%lf", &price);
	getchar();
	printf("�����뷿�����\n");
	scanf("%lf", &area);
	getchar();
	printf("�������������\n");
	scanf("%d", &month);
	getchar();
	printf("�Ƿ�ʹ����ż������\na---��\nb---��\n");
	scanf("%c", &m);
	getchar();
	printf("�����������Ƿ�Ϊ������ס��\na---��\nb---��\n");
	scanf("%c", &p);
	getchar();
	printf("�ڼ��׷���\na---��һ��\nb---�ڶ���\nc---�����׼�����\n");
	scanf("%c", &n);
	getchar();
	printf("�����뱾�˹��������\n");
	scanf("%lf", &balance1);
	getchar();
	printf("�����뱾�˹������½ɴ��\n");
	scanf("%lf", &deposit1);
	getchar();
	printf("�����뱾�˹�����λ�ɴ����\n");
	scanf("%lf", &ratio1);
	getchar();
	printf("�����뱾�˹�������˽ɴ����\n");
	scanf("%lf", &ratio2);
	getchar();
	if (p =='a') b = price*0.7;
	else
	{
		if (n =='a')
		{
			if (area <= 90) b = price*0.8;
			else b = price*0.7;
		}
		else if (n =='b') b = price*0.5;
		else if (n =='c') b = 0;
	}
	if (m =='a')
	{
		printf("��������ż���������\n");
		scanf("%lf", &balance2);
		getchar();
		if (balance1 + balance2 >= 2) c = 10 * (balance1 + balance2);
		else c = 20;
		printf("��������ż�������½ɴ��\n");
		scanf("%lf", &deposit2);
		getchar();
		printf("��������ż������λ�ɴ����\n");
		scanf("%lf", &ratio3);
		getchar();
		printf("��������ż��������˽ɴ����\n");
		scanf("%lf", &ratio4);
		getchar();
		printf("���������˫�����д�����Ӧ�����ܶ�\n");
		scanf("%lf", &repayment);
		getchar();
		a = ((deposit1 / (ratio1 + ratio2) + deposit2 / (ratio3 + ratio4) + deposit1*ratio1 + deposit2*ratio3)*0.4 - repayment)*month;
		printf("���˼���ż�Ƿ��в��乫����\na---��\nb---��\n");
		scanf("%c", &o);
		getchar();
		if (o =='a')d = 70;
		else d = 60;
	}
	else if (m =='b')
	{	
		printf("�����뱾�����д�����Ӧ�����ܶ�\n");
		scanf("%lf", &repayment);
		getchar();
		a = ((deposit1 / (ratio1 + ratio2) + deposit1*ratio1)*0.4 - repayment)*month;
		if (balance1>= 2.0) c = 10 * balance1;
		else c = 20;
		printf("�����Ƿ��в��乫����\na---��\nb---��\n");
		scanf("%c", &o);
		getchar();
		if (o =='a') d = 50;
		else if (o =='b') d = 40;
	}
	x=min(a,b);
	y=min(c,d);
	ans = min(x, y);
	if ((int)(ans * 10000) % 1000 > 0)ans += 0.1;
	printf("%.1lf��Ԫ\n", ans);
	printf("%lf\n",a);
	printf("%lf\n",b);
	printf("%lf\n",c);
	printf("%lf\n",d);
}

