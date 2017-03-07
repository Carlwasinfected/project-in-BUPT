#include<iostream>
#define MAX_WIDTH 4
#define MAX_INPUT 20
#define MAX_WEIGHT 255
using namespace std;

enum state { Z00 , Z01 , Z10 , Z11 }; // �Ĵ���״̬��
typedef enum state STATE;
enum data { D00 , D01 , D10 ,D11 };  // ���ݼ� ��2,1,3������� ��{0,1} -> {DATA} ��ӳ��
typedef enum data DATA;
struct path_node
{
    STATE last_state; // ��һ��״̬
    int total_weight; // ��ǰȨ��
    DATA data_chose; // �����Ȼѡ��
    int bit_chose; // ����ѡ��
};
typedef struct path_node PATH_NODE;

PATH_NODE mat[MAX_WIDTH][MAX_INPUT]; // ״̬ת�ƾ���
PATH_NODE output[MAX_INPUT]; // ���·��
DATA d_input[MAX_INPUT/2]; // DATA��ʽ�ľ�������
int ham_mat[MAX_WIDTH][MAX_WIDTH] = {0,1,1,2,
                                     1,0,2,1,
                                     1,2,0,1,
                                     2,1,1,0}; // ���ݼ��ϵĺ�������

void init_mat(int input[]) // ���üĴ�����ʼ��״̬Ϊ00
{
    mat[1][0] = {Z11,MAX_WEIGHT,D10,0};
    mat[3][0] = {Z11,MAX_WEIGHT,D10,0};
    if(input[0] == 1 && input[1] == 1)
    {
        mat[0][0] = {Z00,2,D00,0};
        mat[2][0] = {Z00,0,D11,1};
    }
    else if((input[0] == 1 && input[1] == 0) ||
            (input[0] == 0 && input[1] == 1))
    {
        mat[0][0] = {Z00,1,D00,0};
        mat[2][0] = {Z00,1,D11,1};
    }
    else
    {
        mat[0][0] = {Z00,0,D00,0};
        mat[2][0] = {Z00,2,D11,1};
    }
}

int ham(DATA d1 , DATA d2) // �ɺ���������ټ��㺣������
{
    return ham_mat[d1][d2];
}

DATA int_to_bi(int i,int j)
{
    if(i==1&&j==1)
        return D11;
    if(i==1&&j==0)
        return D10;
    if(i==0&&j==1)
        return D01;
    return D00;
}

void crr(int input[] , int len , int &num_t , STATE &end_state) // viterbi�������
{
    int t;
    DATA bi_data;
    int mini_weight = MAX_WEIGHT;
    for(int i = 2 ; i<=len-1;i+=2 )
    {
        t = i/2;
        bi_data = int_to_bi(input[i],input[i+1]);
        //cout<<"bidata:"<<bi_data<<endl;
        if( ham(bi_data,D00) + mat[Z00][t-1].total_weight < ham(bi_data,D11) + mat[Z01][t-1].total_weight ) // ö��Z00��ǰһ״̬�������㵱ǰ��СȨ�أ���¼·��ѡ��
        {
            mat[Z00][t].total_weight = ham(bi_data,D00) + mat[Z00][t-1].total_weight; // �������ܵ�·��ѡȨ����С��
            mat[Z00][t].last_state = Z00; // ��¼·��
            mat[Z00][t].data_chose = D00; // ��¼״̬ѡ��
            mat[Z00][t].bit_chose = 0; // ��¼����ѡ��
        }
        else
        {
            mat[Z00][t].total_weight = ham(bi_data,D11) + mat[Z01][t-1].total_weight;
            mat[Z00][t].last_state = Z01;
            mat[Z00][t].data_chose = D11;
            mat[Z00][t].bit_chose = 0;
        }
        if( ham(bi_data,D10) + mat[Z10][t-1].total_weight < ham(bi_data,D01) + mat[Z11][t-1].total_weight ) // ͬ�ϣ�ö��Z01
        {
            mat[Z01][t].total_weight = ham(bi_data,D10) + mat[Z10][t-1].total_weight;
            mat[Z01][t].last_state = Z10;
            mat[Z01][t].data_chose = D10;
            mat[Z01][t].bit_chose = 0;
        }
        else
        {
            mat[Z01][t].total_weight = ham(bi_data,D01) + mat[Z11][t-1].total_weight;
            mat[Z01][t].last_state = Z11;
            mat[Z01][t].data_chose = D01;
            mat[Z01][t].bit_chose = 0;
        }
        if( ham(bi_data,D11) + mat[Z00][t-1].total_weight < ham(bi_data,D00) + mat[Z01][t-1].total_weight ) // ͬ�ϣ�ö��Z10
        {
            mat[Z10][t].total_weight = ham(bi_data,D11) + mat[Z00][t-1].total_weight;
            mat[Z10][t].last_state = Z00;
            mat[Z10][t].data_chose = D11;
            mat[Z10][t].bit_chose = 1;
        }
        else
        {
            mat[Z10][t].total_weight = ham(bi_data,D00) + mat[Z01][t-1].total_weight;
            mat[Z10][t].last_state = Z01;
            mat[Z10][t].data_chose = D00;
            mat[Z10][t].bit_chose = 1;
        }
        if( ham(bi_data,D01) + mat[Z10][t-1].total_weight < ham(bi_data,D10) + mat[Z11][t-1].total_weight ) // ͬ�ϣ�ö��Z11
        {
            mat[Z11][t].total_weight = ham(bi_data,D01) + mat[Z10][t-1].total_weight;
            mat[Z11][t].last_state = Z10;
            mat[Z11][t].data_chose = D01;
            mat[Z11][t].bit_chose = 1;
        }
        else
        {
            mat[Z11][t].total_weight = ham(bi_data,D10) + mat[Z11][t-1].total_weight;
            mat[Z11][t].last_state = Z11;
            mat[Z11][t].data_chose = D10;
            mat[Z11][t].bit_chose = 1;
        }
    }
    num_t = t;
    //cout<<"t"<<t<<endl;
    for(int i = 0 ;i <=MAX_WIDTH -1 ;i++)
    {
        //cout<<mat[i][t].total_weight<<" ";
        if(mat[i][t].total_weight < mini_weight)
        {
            end_state = (STATE)i;
            mini_weight = mat[i][t].total_weight;
        }
    }
    //cout<<"end_s: "<<end_state<<endl;
}

void make_output(int ed , STATE end_state) // ���򹹽��������
{
    STATE last_s;
    output[ed].data_chose = mat[end_state][ed].data_chose;
    output[ed].bit_chose = mat[end_state][ed].bit_chose;
    last_s = mat[end_state][ed].last_state;
    for(int t = ed - 1 ; t>=0 ; t--)
    {
        output[t].data_chose = mat[last_s][t].data_chose;
        output[t].bit_chose = mat[last_s][t].bit_chose;
        //cout<<"output ["<<t<<"]:"<<output[t]<<"  ";
        last_s = mat[last_s][t].last_state;
        //cout<<"last_s:"<<last_s<<endl;
    }
}

void print_output(int ed) // ��ӡ�����������
{
    cout<<"The decode result is: "<<endl;
    for(int i = 0;i<=ed;i++)
    {
        if(output[i].data_chose == D00)
            cout<<"00 ";
        else if(output[i].data_chose == D01)
            cout<<"01 ";
        else if(output[i].data_chose == D10)
            cout<<"10 ";
        else cout<<"11 ";
    }
    cout<<endl<<"The original info is: "<<endl;
    for(int i = 0;i<=ed;i++)
    {
        cout<<output[i].bit_chose<<" ";
    }
    cout<<endl;
}

void print_mat(int num)
{
    cout<<"mat:"<<endl;
    for(int row = 0;row<=MAX_WIDTH - 1;row++ )
    {
        for(int col = 0;col<=num;col++)
        {
            cout<<" ls: "<<mat[row][col].last_state
            <<" dc: "<<mat[row][col].data_chose
            <<" tw: "<<mat[row][col].total_weight<<"\t";
        }
        cout<<endl;
    }
}
void make_input(int input[],int len) // ����ṹ��ת�����������
{
    int p;
    for(int i = 0;i<=len-1;i+=2)
    {
        p = i/2;
        d_input[p] = int_to_bi(input[i],input[i+1]);
    }
}
int count_err(int num) // ������������
{
    int err = 0;
    for(int i = 0;i<=num;i++)
        err += ham(d_input[i],output[i].data_chose);
    return err;
}
int main(void)
{
    int len;
    int input[MAX_INPUT];
    int err;
    int num;
    STATE end_s;
    cout<<"INPUT YOUR LENTH (EVEN NUMBER) (MAX : 20): "<<endl;
    cin>>len;
    for(int i = 0;i<=len-1;i++)
        cin>>input[i];
    init_mat(input);
    crr(input,len,num,end_s); // �����Ȼԭ��viterbi�㷨������mat����·�����ϣ�
    make_output(num,end_s); // �������·��
    make_input(input,len); // Ϊͳ��������׼��
    print_output(num);
    //print_mat(num);
    err = count_err(num); // ͳ���������
    cout<<"Mistakes:"<<err<<endl;
    return 0;
}
