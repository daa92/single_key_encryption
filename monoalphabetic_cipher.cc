#include <iostream>
#include <string>
#include <algorithm> // 'shuffle ()' function to permute
#include <random> //random integer

using namespace std; 

string ascii () {
	string result = "";
	for (int i = 33; i < 127; ++i) result += char(i);
	return result;
}

string char_list = ascii ();

//string char_list = "abcdefghijklmnopqrstuvwxyz";

string random_permutation (const string& char_list) {
	string result = char_list;
	random_device rd;
	mt19937 g(rd());
	shuffle(result.begin(), result.end(), g);
	return result;
}
string key = random_permutation (char_list);

string encryption (string char_list, string plain) {
	string cipher = "";
	for (int i = 0; i < plain.size(); ++i) {
		for (int j = 0; j < char_list.size (); ++j) {
			if (plain [i] == char_list[j]) cipher += key[j]; 
		}
	}

	return cipher;
}

string decryption (string key, string cipher) {
	string plain = "";
	for (int i = 0; i < cipher.size(); ++i) {
		for (int j = 0; j < key.size(); ++j) {
			if (cipher [i] == key[j]) plain += char_list[j];
		}
	}
	return plain;
}


int main () {
	string plain = "itwasdisclosedyesterdaythatseveralinformalbutdirectcontactshavebeenmadewithpoliticalrepresentatives of the viet cong in moscow";
	string cipher = encryption (char_list, plain);

	cout << "PLAIN TEXT:\t" << plain << endl << endl;

	cout << "ENCRYPTION:\t" << cipher << endl;
	cout << "DECRYPTION:\t" << decryption (key, cipher) << endl;

	float cipher_size = cipher.size();
	return 0;
}
