#include"sm3.h"
#include<time.h>

string result;
string padding_value;
string checking_list[65535];

int main() {
	cout << "���չ������������У����Ժ�" << endl;
	clock_t start = clock();

	for (int i = 0; i < 65535; i++) {
		padding_value = padding(to_string(i));
		result = iteration(padding_value);
		for (int j = 0; j < i; j++) {
			if (checking_list[j].substr(0, 5) == result.substr(0, 5)) {
				cout << endl<< "�ɵõ���ײֵ��" << to_string(i) <<"ʱ��" << "��ϣֵ��" << endl;
				for (int i = 0; i < 8; i++) {
					cout << result.substr(i * 8, 8) << "  ";
				}
				cout << endl << "�ɵõ���ײֵ��" << to_string(i) << "ʱ��" << "��ϣֵ��" << endl;
				for (int i = 0; i < 8; i++) {
					cout << checking_list[j].substr(i * 8, 8) << "  ";
				}
				clock_t ends = clock();
				cout << endl << "����ʱ��Ϊ��" << (double)(ends - start) / CLOCKS_PER_SEC <<"s" << endl;
				return 0;
			}
		}
		checking_list[i] = result;
	}
	cout << "����ʧ��δ�ҵ���ײ";
	clock_t ends = clock();
	cout << endl << "����ʱ��Ϊ��" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
