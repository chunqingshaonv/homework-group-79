#include"rho_sm3.h"
#include<time.h>

string padding_value;
string checking_list[65535];
string list2[65535];

int main() {
	cout << "���չ������������У����Ժ�" << endl;
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
				cout << endl << "�ɵõ���ײֵ��" << to_string(i) << "ʱ��" << "��ϣֵ��" << endl;
				for (int k = 0; k < 8; k++) {
					cout << list2[i].substr(k * 8, 8) << "  ";
				}
				cout << endl << "�ɵõ���ײֵ��" << to_string(j) << "ʱ��" << "��ϣֵ��" << endl;
				for (int i = 0; i < 8; i++) {
					cout << list2[j].substr(i * 8, 8) << "  ";
				}
				clock_t ends = clock();
				cout << endl << "����ʱ��Ϊ��" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;
				return 0;
			}
		}
	}
	cout << "����ʧ��δ�ҵ���ײ";
	clock_t ends = clock();
	cout << endl << "����ʱ��Ϊ��" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

