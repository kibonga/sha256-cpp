// sha256-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>
#include "SHA256.h"
using namespace std;

unsigned int K1[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
		0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
		0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
		0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
		0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
		0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};
unsigned int static H0 = 0x6a09e667;
unsigned int static H1 = 0xbb67ae85;
unsigned int static H2 = 0x3c6ef372;
unsigned int static H3 = 0xa54ff53a;
unsigned int static H4 = 0x510e527f;
unsigned int static H5 = 0x9b05688c;
unsigned int static H6 = 0x1f83d9ab;
unsigned int static H7 = 0x5be0cd19;

int main()
{
	/*cout << "Output = ";
	string str = "To calculate the message length of 2^64, we first need to determine the number of bits required to represent this number. 2^64 is a very large number, and it will have 65 digits if we write it out as 18,446,744,073,709,551,616.";
	vector<unsigned char> block;
	uint32_t init_block[16];

	to_bitset(block, str);

	for (int i = 0; i < block.size(); i++) {
		cout << static_cast<int>(block[i]) << " ";
	}
	pad_512(block);
	resize_block(init_block, block);

	cout << endl << "Resized block = ";
	for (int i = 0; i < 16; i++) {
		cout << init_block[i] << " ";
	}*/
	string s = "Lorem psum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	sha256(s);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
