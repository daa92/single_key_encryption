//
//             					SYMMETRIC CIPHER
//
//          SENDER                                   PATH                                       RECEIVER
//	
//    PLAIN TEXT MESSAGE ----> CIPHER TEXT ############################ CIPHER TEXT ------> PLAIN TEXT MESSAGER
//	         ENCRYPTION ALGORITHM                                          DECRYPTION ALGORITHM
//	              CIPHER KEY....................................................SAME CIPHER KEY
//  

// NOTE: There is no space " " character included here


#include <iostream>
#include <string>

using namespace std;

string ascii_char () {
	string result = "";
	for (int i = 33; i < 127; ++i) result += char(i); // we start at 33 and end at 126 because using the CLI, there is some invisible characters
	return result;
}

string char_list = ascii_char(); // this list consists of ASCII characters
// Therefore, we only have 94 characters

//with the convention of C++11, modulus '%' can give result both negative and posistive forms
//with absolutely don't want that and that's exactly what this function solves
//EXAMPLE: with '%': (-6) mod [94] = -6 // -6 is not an index in our characters list
//	   with this function: (-6) mod [94] = 88 // 88 is an index in this list :-)
int mod (int a, int b) {
        return (a % b + b) % b;
}


string encryption (string plaintext, int key) {
	string ciphertext = "";

	for (unsigned int i = 0; i < plaintext.size(); ++i) {
		for (unsigned int j = 0; j < char_list.size(); ++j) {
			if (plaintext[i] == char_list[j]) ciphertext += char_list [mod ((j + key), char_list.size ())];
		}
	}

	return ciphertext;
}

string decryption (string ciphertext, int key) {
        string plaintext = "";

        for (unsigned int i = 0; i < ciphertext.size(); ++i) {
                for (unsigned int j = 0; j < char_list.size(); ++j) {
                        if (ciphertext[i] == char_list[j]) plaintext += char_list [mod ((j - key), char_list.size ())];
                }
        }

        return plaintext;
}

// Used when we only have the cipher text
void brute_force (string ciphertext) {
	cout << "Attempts of deciphering a cipher text without knowing the key..." << endl << endl;
	for (int i = 0; i < char_list.size(); ++i) cout << "\tKEY = " << i << " mod[26]  ==> ' " << decryption (ciphertext, i) << " '" << endl;
}

// More efficient when we also know the correspondent plaintext
// LOGIC: with the first letter of the ciphertext, we are goign to guess
// the key and after that, if the decryption of that ciphertext == plaintext
// we confirm that the key is right
int cryptanalysis_known_plaintext (string ciphertext, string plaintext) {
	int guessed_key;
	if (ciphertext.size () != plaintext.size()) return -1;
	int plain_position, cipher_position;
	for (int i = 0; i < char_list.size (); ++i) {
		if (plaintext[0] == char_list[i]) {
			plain_position = i;
			break;
		}
	}
	for (int j = 0; j < char_list.size(); ++j) {
		if (ciphertext[0] == char_list[j]) {
			cipher_position = j;
			break;
		}
	}

	guessed_key = cipher_position - plain_position;
	guessed_key = mod (guessed_key, char_list.size ());
	//if (guessed_key < 0) guessed_key = guessed_key * (-1);

	if (encryption (plaintext, guessed_key) != ciphertext) return -1;

	return guessed_key;
} 



int main () {

	string plain = "dylan,meetmeafterthetogaparty";
	int key = 86;

	string cipher = encryption (plain, key);
	
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "EXAMPLE: plain text = '"<< plain << "'\t key = '" << key << "'" << endl;
	cout << "\t\t cipher text = << " << cipher << " >>" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "EXAMPLE: cipher text = '"<< cipher << "'\t key = '" << key << "'" << endl;
	cout << "\t\t plain text = << " << decryption (cipher, key) << " >>" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	brute_force (cipher);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Using a cryptanalysis algorithm, we believe that the key of encryption of\n\t PLAIN TEXT = '"<< plain <<"' \tCIPHER TEXT '" << cipher << "'\nis: KEY = " << cryptanalysis_known_plaintext (cipher, plain) << " mod [" << char_list.size () << "]" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	return 0;
}
