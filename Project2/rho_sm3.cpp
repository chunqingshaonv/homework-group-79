#include"rho_sm3.h"
#include<time.h>

string padding_value;
string checking_list[65535];
string list2[65535];

int main() {
	cout << "生日攻击正在运行中，请稍后" << endl;
	clock_t start = clock();
	int a = 0;
	int rho = 0;
	for (int i = 0; i < 65535; i++) {
		if (rho != -1) {
			rho = rho * 2 + 1;	
		}
		else rho = ++a;
		checking_list[i] = to_string(rho);
		list2[i] = iteration(padding(checking_list[i]));
		for (int j = 0; j < i; j++) {
			if (checking_list[i] != checking_list[j] &&list2[j].substr(0, 4) == list2[i].substr(0, 4)) {
				cout << endl << "可得到碰撞值是" << to_string(i) << "时，" << "哈希值是" << endl;
				for (int k = 0; k < 8; k++) {
					cout << list2[i].substr(k * 8, 8) << "  ";
				}
				cout << endl << "可得到碰撞值是" << to_string(j) << "时，" << "哈希值是" << endl;
				for (int i = 0; i < 8; i++) {
					cout << list2[j].substr(i * 8, 8) << "  ";
				}
				clock_t ends = clock();
				cout << endl << "所用时间为：" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;
				return 0;
			}
		}
	}
	cout << "攻击失败未找到碰撞";
	clock_t ends = clock();
	cout << endl << "所用时间为：" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

