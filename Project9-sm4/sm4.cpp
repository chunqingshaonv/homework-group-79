#include<iostream>
#include<time.h>
#include"sm4.h"

int main()
{
    unsigned int Plaintext[4] = { 0x01234567,0x89abcdef,0xfedcba98,0x76543210 };//����
    unsigned int X[36]; //�洢�м���
    unsigned int MK[4] = { 0x01234567,0x89abcdef,0xfedcba98,0x76543210 };  //������Կ
    unsigned int res[4]; //����
    unsigned int rk[32]; //����Կ
    clock_t start, finish;

    Key_Ex(MK, rk);  //��������Կ
    SM4Enc(Plaintext, res, rk, X);  //����

    //�������Կ
    printf("�����������Կ����\n����ԿΪ�� \n");
    for (int i = 0; i < 32; i++) printf("%#x\n", rk[i]);

    //����м���
    printf("\n\n��������м�������\n�м���Ϊ��\n");
    for (int i = 0; i < 32; i++) printf("%#x\n", X[i + 4]);

    //�������
    printf("\n\n�����������һ�κ�����ġ���\n����һ�κ������Ϊ��\n");
    for (int i = 0; i < 4; i++) printf("%#x ", res[i]);


    //��ʱ����1000000��ʱ��
    start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        SM4Enc(Plaintext, Plaintext, rk, X);
    }
    finish = clock();
    printf("\n\n����1000000�κ�����Ϊ��");
    for (int i = 0; i < 4; i++) printf("%#x ", Plaintext[i],"\n");
    printf("\n����1000000�����õ�ʱ��Ϊ��%d ��", (double)(finish - start) / CLOCKS_PER_SEC);
    return 0;
}