#include <iostream>
#include <string>

using namespace std;

string ascii () {
	string result = "";
	for (int i = 33; i < 127; ++i) result += char(i);
	return result;
}

//string char_list = ascii ();
string char_list = "abcdefghijklmnopqrstuvwxyz";

void warnings (string a, string b) {
	if (a.size() != b.size()) {
		cout << "ERROR: lenghts are not the same!" << endl;
		exit (1);
	}
}

int mod (int a, int b) {
	return (a % b + b) % b;
} // for getting those modulus positively... Check ceaser_cipher.cc for more explanation

string encryption (string plain, string key) {
	warnings (plain, key);
	string cipher = "";

	int char_posi_key [key.size()];
	int char_posi_plain [plain.size()];

	for (int i = 0; i < key.size(); ++i) {
		for (int j = 0; j < char_list.size(); ++j) {
			if (key[i] == char_list[j]) char_posi_key [i] = j;
		}
	}

	for (int i = 0; i < plain.size(); ++i) {
		for (int j = 0; j < char_list.size(); ++j) {
			if (plain[i] == char_list[j]) char_posi_plain[i] = j;
		}
	}

	for (int i = 0; i < plain.size(); ++i) cipher += char_list[mod ((char_posi_key[i] + char_posi_plain[i]), char_list.size())];

	return cipher;
}


string decryption (string cipher, string key) {
        warnings (cipher, key);
        string plain = "";

        int char_posi_key [key.size()];
        int char_posi_cipher [cipher.size()];

        for (int i = 0; i < key.size(); ++i) {
                for (int j = 0; j < char_list.size(); ++j) {
                        if (key[i] == char_list[j]) char_posi_key [i] = j;
                }
        }

        for (int i = 0; i < cipher.size(); ++i) {
                for (int j = 0; j < char_list.size(); ++j) {
                        if (cipher[i] == char_list[j]) char_posi_cipher[i] = j;
                }
        }

        for (int i = 0; i < cipher.size(); ++i) plain += char_list[mod ((char_posi_cipher[i] - char_posi_key[i]), char_list.size())];

        return plain;
}

string cryptanalysis (string cipher, string plain) {
	warnings (cipher, plain);
        string key = "";

        int char_posi_plain [plain.size()];
        int char_posi_cipher [cipher.size()];

        for (int i = 0; i < plain.size(); ++i) {
                for (int j = 0; j < char_list.size(); ++j) {
                        if (plain[i] == char_list[j]) char_posi_plain [i] = j;
                }
        }

        for (int i = 0; i < cipher.size(); ++i) {
                for (int j = 0; j < char_list.size(); ++j) {
                        if (cipher[i] == char_list[j]) char_posi_cipher[i] = j;
                }
        }

        for (int i = 0; i < cipher.size(); ++i) key += char_list[mod ((char_posi_cipher[i] - char_posi_plain[i]), char_list.size())];

        return key;
}

int main () {
	cout << "\tWARNINGS: The plain text must have the same lenght!" << endl;
	string plain = "cryptography", key = "pwomnipwomni", cipher = encryption (plain, key);

	cout << "PLAIN TEXT: '" << plain << "' KEY: '" << key << "'\t\t ENCRYPTION: '" << cipher << "'" << endl;
	cout << "\nCIPHER TEXT: '" << cipher << "' KEY: '" << key << "'\t\t DECRYPTION: '" << decryption (cipher, key) << "'" << endl;
	cout << "\nCIPHER TEXT: 'rnmbgwvnobug' PLAIN TEXT: 'cryptography'\t\t KEY: '" << cryptanalysis ("rnmbgwvnobug", "cryptography") << "'" << endl;
	return 0;
}
