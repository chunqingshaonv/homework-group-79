#include<iostream>
#include"aes_256.h"
#include<time.h>
using namespace std;
int main()//����AES-256�㷨Ч�ʲ���ʱʹ��
{
    int test = 1;
    cout << "***************AES�����㷨����������***************" << endl;
    while (test) {
        Input(1);  //�������� 
        Input(2);  //������Կ 
        unsigned char result[17];
        clock_t start, finish;
        cout << "***************���������ļ���***************" << endl;
        start = clock();
        Cipher(original_key, input, result);
        finish = clock();
        cout << "����ʱ��Ϊ��\t" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl << "***************�����ܽ������***************" << endl;
        cout << "���ܹ���������ʾ��" << endl;
        start = clock();
        DeCipher(result, result);
        finish = clock();
        cout << "����ʱ��Ϊ��\t" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
        system("pause");
        cout << "(0)�˳�  (1)��������:  ";
        cin >> test;
    }
    return 0;
}



