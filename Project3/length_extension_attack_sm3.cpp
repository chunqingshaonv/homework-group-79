#include"length_extension_attack_sm3.h"
#include<time.h>


int main() {
	string initial_string;
	string extended_string;
	string initial_padding;
	string extended_padding;
	string IV;
	string linked_padding;
	string str;
	string extended_str;
	string compressed_str;
	string extended_hash;
	string initial_hash;


	cout << "������ԭʼ�ַ�����";
	cin >> initial_string;
	cout << "��������չ�ַ���: ";
	cin >> extended_string;

	clock_t start = clock();

	initial_padding = padding(initial_string);
	extended_padding = padding(extended_string);

	initial_hash = iteration(initial_padding);
	cout<<endl << "ԭʼ�Ĺ�ϣֵΪ�� " << initial_hash ;

	IV = iteration(initial_padding);
	linked_padding = DecToHex(HexToDec(extended_padding) + int(initial_padding.length()));
	
	for (int i = 0; i < linked_padding.size() / 128; i++) {
		str = linked_padding.substr(i * 128, 128);//��ȡ��128i��ʼ��128���ַ�
		extended_str = extension(str);//����128���ַ����г�����չ
		compressed_str = compress(extended_str, IV);//�Գ�����չ��Ľ��������Ϣѹ��
		IV = XOR(IV, compressed_str);
	}

	extended_hash = IV;
	cout<<endl << "��չ��Ĺ�ϣֵΪ�� " << extended_hash << endl << endl;
	if (extended_hash == initial_hash) cout << "�����ɹ��ҵ���ײ" << endl ;
	else cout << "����ʧ��δ�ҵ���ײ" << endl ;
	clock_t ends = clock();
	cout << endl << "����ʱ��Ϊ��" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;

}
