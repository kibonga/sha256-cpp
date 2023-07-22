#include <bitset>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

std::string uintArrToBinaryString(const unsigned int arr[], int n) {
	std::string binaryString;
	for (int i = 0; i < n; i++) {
		std::bitset<8> bits(arr[i]);
		binaryString += bits.to_string();
	}
	return binaryString;
}
void display_final_state_as_hex() {
	cout << endl << "Final state (H) as hex = ";
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << std::hex << H[i];
		std::string res(ss.str());
		std::cout << res << " ";
	}
}
void display_final_state_H_as_uint() {
	cout << endl << "Final state (H) as uints = ";
	for (int i = 0; i < 8; i++) {
		cout << H[i] << " ";
	}
}

void display_final_state_H_as_bits() {
	string output = uintArrToBinaryString(H, 8);
	cout << endl << "Final state (H) as bits = " << output;
}