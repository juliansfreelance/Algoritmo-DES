// main.cpp
#include <iostream>
#include "DES.cpp"
#include <string>
#include <fstream>
#include <wchar.h>

using namespace std;


bitset<64> charsToBitset(const char s[8])
{
	bitset<64> bits;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			bits[i * 8 + j] = ((s[7 - i] >> j) & 1);
	return bits;
}

char* BitsetToChars(const bitset<64> bits){
	char s[8];
	bitset<8> c;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			c[j] = bits[i * 8 + j];
		}
		s[7 - i] = c.to_ulong();
	}
	return s;
}

int main(){
	setlocale(LC_ALL, "");
	DES des;
	
	// Cifrar y descifrar datos de 64 bits y generar el resultado 
	string p("hóla bro");
	string k("52013141");
	
	bitset<64> plain = charsToBitset(p.c_str());
	bitset<64> key = charsToBitset(p.c_str());
	bitset<64> cipher = des.encrypt(plain, key); 
	
	cout << "plain:   " << plain << "(" << p << ")" << endl << endl;
	cout << "cipher:   " << cipher << endl << endl;
	string s = BitsetToChars(des.decrypt(cipher, key));
	cout << "decrypt: " << s << endl << endl;
	
	// Cifrar y descifrar archivos
	cout << "Waiting to encrypt and decrypt the file \'E://sysu.jpg\'..." << endl;
	cout << endl << "Encrypting..." << endl;
	ifstream in;
	ofstream out;
	in.open("D://archivo/logo.jpg", ios::binary);
	out.open("D://archivo/cipher.txt", ios::binary);
	bitset<64> file_data;
	while(in.read((char*)&file_data, sizeof(file_data))){
		bitset<64> cipher = des.encrypt(file_data, key);
		out.write((char*)&cipher, sizeof(cipher));
		file_data.reset(); // establecido en 0
	}
	cout << "Finish! You can read the cipher in \'E://cipher.txt\'." << endl;
	in.close();
	out.close();

	cout << endl << "Decrypting..." << endl;
	in.open("D://archivo/cipher.txt", ios::binary);
	out.open("D://archivo/logo_decrypt.jpg", ios::binary);
	while(in.read((char*)&file_data, sizeof(file_data)))
	{
		bitset<64> plain = des.decrypt(file_data, key);
		out.write((char*)&plain, sizeof(plain));
		file_data.reset();  // establecido en 0
	}
	cout << "Finish! You can open the file \'E://sysu_decrypt.jpg\' to check." << endl;
	in.close();
	out.close();

	return 0;
}
