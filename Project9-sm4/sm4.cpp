#include<iostream>
#include<time.h>
#include"sm4.h"

int main()
{
    unsigned int Plaintext[4] = { 0x01234567,0x89abcdef,0xfedcba98,0x76543210 };//明文
    unsigned int X[36]; //存储中间结果
    unsigned int MK[4] = { 0x01234567,0x89abcdef,0xfedcba98,0x76543210 };  //加密密钥
    unsigned int res[4]; //密文
    unsigned int rk[32]; //轮密钥
    clock_t start, finish;

    Key_Ex(MK, rk);  //生成轮密钥
    SM4Enc(Plaintext, res, rk, X);  //加密

    //输出轮密钥
    printf("正在输出轮密钥……\n轮密钥为： \n");
    for (int i = 0; i < 32; i++) printf("%#x\n", rk[i]);

    //输出中间结果
    printf("\n\n正在输出中间结果……\n中间结果为：\n");
    for (int i = 0; i < 32; i++) printf("%#x\n", X[i + 4]);

    //输出密文
    printf("\n\n正在输出加密一次后的密文……\n加密一次后的密文为：\n");
    for (int i = 0; i < 4; i++) printf("%#x ", res[i]);


    //计时加密1000000次时间
    start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        SM4Enc(Plaintext, Plaintext, rk, X);
    }
    finish = clock();
    printf("\n\n加密1000000次后密文为：");
    for (int i = 0; i < 4; i++) printf("%#x ", Plaintext[i],"\n");
    printf("\n加密1000000次所用的时间为：%d 秒", (double)(finish - start) / CLOCKS_PER_SEC);
    return 0;
}