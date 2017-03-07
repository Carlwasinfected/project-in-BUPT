#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

#define MAX_M 3
#define MAX_N 8
#define RAND 9999
#define PI 3.141593

struct cpx // �����ṹ
{
    double re;
    double im;
};
typedef struct cpx CPX;

CPX X[MAX_N]; // �Ĵ������飬��������Ҳ�����

CPX add_cpx(CPX x,CPX y) // �����ӷ�
{
    CPX temp;
    temp.im = x.im + y.im;
    temp.re = x.re + y.re;
    return temp;
}

CPX sub_cpx(CPX x,CPX y) // ��������
{
    CPX temp;
    temp.im = x.im - y.im;
    temp.re = x.re - y.re;
}

CPX mul_with_rtt(CPX x,int exp_W,int width_W) // ���ڲ���FFT��ֻ��Ҫ����ת����W�������˷�
{
    CPX temp;
    temp.re = x.re * cos(2.0 * PI * exp_W / MAX_N) + x.im * sin(2.0 * PI * exp_W / MAX_N);
    temp.im = x.im * cos(2.0 * PI * exp_W / MAX_N) - x.re * sin(2.0 * PI * exp_W / MAX_N);
    return temp;
}

void print_cpx(void) // ��ӡ����
{
    for(int i = 0; i <= MAX_N - 1 ; i++)
        cout<<"X["<<i<<"]: "<<"("<<X[i].re<<")"<<"+"<<"i*("<<X[i].im<<")"<<endl;
}

void inv_input(int len) // ������DIT-FFT ��Ҫʹ���㷨��������е�������
{
    CPX temp;
    int bit_w = MAX_N / 2;
    int step;
    for(int i = 1 ; i<= len-2 ; i++)
    {
        if( i < bit_w )
        {
            temp = X[i];
            X[i] = X[bit_w];
            X[bit_w] = temp;
            cout<<"exchange"<<i<<"->"<<bit_w<<endl;
        }
        step = MAX_N / 2;
        jump:
        if(bit_w < step)
        {
            bit_w += step;
        }
        else
        {
            bit_w -= step;
            step /= 2;
            goto jump;
        }
    }
}
void DIT_FFT(int len,int log_len) // DIT-FFT����
{
    int step; // ��ǰ����
    CPX add1,add2; // ��������������ӷ�Ԫ
    int exp_w; // ��ת����W��ָ��
    for(int L = 1;L<=log_len;L++)
    {
        step = (int)pow(2,L-1);
        for(int j = 0;j<=step - 1;j++)
        {
            exp_w = j * (int)pow(2,log_len-L);
            for(int k = j ; k<=MAX_N -1;k+=2*step)
            {
                add2 = mul_with_rtt(X[k+step],exp_w,MAX_N);
                add1 = X[k];
                X[k] = add_cpx(add1,add2); // �������� ������Ϊstep��ʵ��������ż����
                X[k+step] = sub_cpx(add1,add2);
            }
        }
    }
}

int main(void)
{
    srand(time(NULL));
    cout<<"---   INPUT :"<<endl;
    for(int i = 0 ;i<=MAX_N - 1 ;i++) // �����������ֵ
    {
        X[i].re = rand()%(RAND + 1) / (double)(RAND + 1);
        X[i].im = rand()%(RAND + 1) / (double)(RAND + 1);
    }
    print_cpx();
    inv_input(MAX_N); // ��������
    cout<<"---   INPUT AFTER THE EXCHANGE :"<<endl;
    print_cpx();
    DIT_FFT(MAX_N,MAX_M); // ��2��DIT-FFT
    cout<<"---   RESULT: "<<endl;
    print_cpx();
    return 0;
}
