// sha256-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SHA256.h"
using namespace std;

int main()
{
	uint32_t initial_state[] = {
		2918946378, 1679978889, 1678006433,  650957219,
		379281712, 2112907926, 1775216060, 2152648190
	};
	char block[] = {
		109,  97, 110,  97,  116, 101, 101,  32,
		102, 111, 120,  32,  117, 110, 105,  99,
		111, 114, 110,  32,  111,  99, 116, 111,
		112, 117, 115,  32,  100, 111, 103,  32,
		102, 111, 120,  32,  102, 111, 120,  32,
		108, 108,  97, 109,  97,   32, 118, 117,
		108, 116, 117, 114,  101,  32, 106,  97,
		103, 117,  97, 114,  32,  120, 101, 110
	};

	cout << "Compress block " << endl;
	uint32_t* A = compress_block(initial_state, block);
	for (int i = 0; i < 8; i++) {
		cout << A[i] << endl;
	}
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
