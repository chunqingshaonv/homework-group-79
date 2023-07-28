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


	cout << "请输入原始字符串：";
	cin >> initial_string;
	cout << "请输入拓展字符串: ";
	cin >> extended_string;

	clock_t start = clock();

	initial_padding = padding(initial_string);
	extended_padding = padding(extended_string);

	initial_hash = iteration(initial_padding);
	cout<<endl << "原始的哈希值为： " << initial_hash ;

	IV = iteration(initial_padding);
	linked_padding = DecToHex(HexToDec(extended_padding) + int(initial_padding.length()));
	
	for (int i = 0; i < linked_padding.size() / 128; i++) {
		str = linked_padding.substr(i * 128, 128);//截取从128i开始的128个字符
		extended_str = extension(str);//对这128个字符进行长度拓展
		compressed_str = compress(extended_str, IV);//对长度拓展后的结果进行消息压缩
		IV = XOR(IV, compressed_str);
	}

	extended_hash = IV;
	cout<<endl << "拓展后的哈希值为： " << extended_hash << endl << endl;
	if (extended_hash == initial_hash) cout << "攻击成功找到碰撞" << endl ;
	else cout << "攻击失败未找到碰撞" << endl ;
	clock_t ends = clock();
	cout << endl << "所用时间为：" << (double)(ends - start) / CLOCKS_PER_SEC << "s" << endl;

}
