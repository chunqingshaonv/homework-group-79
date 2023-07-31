#include<iostream>
#include"aes_256.h"
#include<time.h>
using namespace std;
int main()//进行AES-256算法效率测试时使用
{
    int test = 1;
    cout << "***************AES加密算法正在运行中***************" << endl;
    while (test) {
        Input(1);  //输入明文 
        Input(2);  //输入密钥 
        unsigned char result[17];
        clock_t start, finish;
        cout << "***************将输入明文加密***************" << endl;
        start = clock();
        Cipher(original_key, input, result);
        finish = clock();
        cout << "所用时间为：\t" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl << "***************将加密结果解密***************" << endl;
        cout << "解密过程如下所示：" << endl;
        start = clock();
        DeCipher(result, result);
        finish = clock();
        cout << "所用时间为：\t" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
        system("pause");
        cout << "(0)退出  (1)继续测试:  ";
        cin >> test;
    }
    return 0;
}



