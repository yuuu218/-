#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <random>
using std::string;
using std::random_device;
using std::default_random_engine;
using namespace std;
#define bit 16
string strRand(int length);
string sm3(string str);
void birthday_attck();
//������ת��Ϊʮ�����ƺ���ʵ��
string BinToHex(string str) {
	string hex = "";//�����洢������ɵ�ʮ��������
	int temp = 0;//�����洢ÿ����λ����������ʮ����ֵ
	while (str.size() % 4 != 0) {//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
		str = "0" + str;//���λ��0ֱ������Ϊ4�ı�������
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//�жϳ�4λ����������ʮ���ƴ�СΪ����
		if (temp < 10) {//���õ���ֵС��10ʱ������ֱ����0-9������
			hex += to_string(temp);
		}
		else {//���õ���ֵ����10ʱ����Ҫ����A-F��ת��
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
string HexToBin(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

//������ת��Ϊʮ���Ƶĺ���ʵ��
int BinToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string DecToBin(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
int HexToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
string DecToHex(int str) {
	string hex = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}

string padding(string str) {//�����ݽ������ 
	string res = str;
	//for (int i = 0; i < str.size(); i++) {//���Ƚ�����ֵת��Ϊ16�����ַ���
	//res += DecToHex((int)str[i]);
	//}
	//cout << "�����ַ�����ASCII���ʾΪ��" << endl;
	//for (int i = 0; i < res.size(); i++) {
		////cout << res[i];
		//if ((i + 1) % 8 == 0) {
		//	cout << "  ";
		//}
		//if ((i + 1) % 64 == 0 || (i + 1) == res.size()) {
			//cout << endl;
		//}
	//}
	//cout << endl;
	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
	while (res.size() % 128 != 112) {
		res += "0";//��0���������
	}
	string res_len = DecToHex(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) {//ʵ��ѭ������lenλ����
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) {//ʵ��������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) {//ʵ�������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) {//ʵ�ֻ����
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) {//ʵ�ַǲ���
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32����ĺ���ʵ��
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BinToHex(res);
}

string P1(string str) {//ʵ���û�����P1��X��
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//����Tj����ֵ�ĺ���ʵ��
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//ʵ�ֲ�������FF����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//ʵ�ֲ�������GG����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) {//��Ϣ��չ����
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	//cout << "��չ�����Ϣ��" << endl;
	//cout << "W0,W1,����,W67����Ϣ��" << endl;
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << res.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}*/
	//cout << res.substr(512, 8) << "  " << res.substr(520, 8) << "  " << res.substr(528, 8) << "  " << res.substr(536, 8) << endl;
	//cout << endl;
	for (int i = 0; i < 64; i++) {//���ݹ�ʽ����64λW'ֵ
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	/*cout << "W0',W1',����,W63'����Ϣ��" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << res.substr(544 + i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;*/
	return res;
}

string compress(string str1, string str2) {//��Ϣѹ������
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	/*cout << "����ѹ���м�ֵ: " << endl;
	cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;*/
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		//cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	}
	string res = (A + B + C + D + E + F + G + H);
	//cout << endl;
	return res;
}

string iteration(string str) {//����ѹ������ʵ��
	int num = str.size() / 128;
	//cout << "��Ϣ�������֮���� " + to_string(num) + " ����Ϣ���顣" << endl;
	//cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		//cout << "�� " << to_string(i + 1) << " ����Ϣ���飺" << endl;
		//cout << endl;
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}
string sm3(string str)
{
	//cout << endl;
	string paddingValue = padding(str);
	/*cout << "�������ϢΪ��" << endl;
	for (int i = 0; i < paddingValue.size() / 64; i++) {
		for (int j = 0; j < 8; j++) {
			cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;*/
	string result = iteration(paddingValue);
	string jieguo = "";

	for (int i = 0; i < 8; i++) {
		jieguo += result.substr(i * 8, 8);
	}
	return jieguo;
}
int main() {//������
	double start = clock();
	birthday_attck();
	double end = clock();
	double time = end - start;
	cout << "ʱ��Ϊ" << time << endl;
}
string strRand(int length) {			// length: �����ַ����ĳ���
	char tmp;							// tmp: �ݴ�һ�������
	string buffer;						// buffer: ���淵��ֵ
	int size = (rand() % length)+1;
	// ���������бȽ���Ҫ:
	random_device rd;					// ����һ�� std::random_device ���� rd
	default_random_engine random(rd());	// �� rd ��ʼ��һ������������� random

	for (int i = 0; i <size; i++) {
		tmp = random() % 16;	// ���һ��С�� 16 ��������0-9��A-Z �� 36 ���ַ�
		if (tmp < 10) {			// ��������С�� 10���任��һ�����������ֵ� ASCII
			tmp += '0';
		}
		else {				// ���򣬱任��һ����д��ĸ�� ASCII
			tmp -= 10;
			tmp += 'A';
		}
		buffer += tmp;
	}
	return buffer;
}
//ʵ�����չ���
void birthday_attck() {

	while (1) {
		long long bigsum = pow(2, bit);
		for (long long i = 0; i < bigsum; i++)
		{
			string hash1 = strRand(bit / 4);
			string hash2 = strRand(bit / 4);
			string sm3_hash1(sm3(hash1), 0, bit / 4);
			string sm3_hash2(sm3(hash2), 0, bit / 4);
			if (sm3_hash1 == sm3_hash2 && hash1 != hash1)
			{
				cout << hash1 << endl;
				cout << hash2 << endl;
				cout << sm3_hash2 << endl;
				cout << "�ɹ�" << endl;
				return;
			}
			else
				cout << "ʧ��" << endl;
		}
	}

}