#include<stdio.h>
int main(void)
{
	float i=1.12742143,p=152.0943,y;
	int n,*ptr,number,a1,a2,a3;
	char c,d[9];
	for(n=1;n<=9;n++)
	{
		printf("%010.*g\n",n,i);
		printf("%010.*g\n",n,p);
	}
	for(n=1;n<=9;n++)
	{
		printf("%+.*e\n",n,p);
	}
	y=printf("abcde\n");
	printf("%d\n",y);//printf�ķ���ֵ�� 
	printf("%+ d\n% d\n",123,-123);
	printf("?\n");//�ⲻ��ֱ�������ô 
	scanf("%c%s",&c,d);
	printf("%c\n%s\n",c,d);
	scanf("%2d%3d%d",&a1,&a2,&a3);
	printf("%d\n%d\n%d\n",a1,a2,a3);
	return 0;
}
