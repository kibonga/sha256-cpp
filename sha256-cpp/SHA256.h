#pragma once
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;
const uint32_t K[64] = {
		1116352408, 1899447441, 3049323471, 3921009573, 961987163, 1508970993, 2453635748, 2870763221,
		3624381080, 310598401, 607225278, 1426881987, 1925078388, 2162078206, 2614888103, 3248222580,
		3835390401, 4022224774, 264347078, 604807628, 770255983, 1249150122, 1555081692, 1996064986,
		2554220882, 2821834349, 2952996808, 3210313671, 3336571891, 3584528711, 113926993, 338241895,
		666307205, 773529912, 1294757372, 1396182291, 1695183700, 1986661051, 2177026350, 2456956037,
		2730485921, 2820302411, 3259730800, 3345764771, 3516065817, 3600352804, 4094571909, 275423344,
		430227734, 506948616, 659060556, 883997877, 958139571, 1322822218, 1537002063, 1747873779,
		1955562222, 2024104815, 2227730452, 2361852424, 2428436474, 2756734187, 3204031479, 3329325298
};
const uint32_t H[8] = { 0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19 };
uint32_t right_rotate(uint32_t x, uint32_t n) {
	return (x >> n) | (x << (32 - n));
}
uint32_t little_sigma_0(uint32_t x) {
	return right_rotate(x, 7) ^ right_rotate(x, 18) ^ (x >> 3);
}
uint32_t little_sigma_1(uint32_t x) {
	return right_rotate(x, 17) ^ right_rotate(x, 19) ^ (x >> 10);
}
uint32_t big_sigma_0(uint32_t x) {
	return right_rotate(x, 2) ^ right_rotate(x, 13) ^ right_rotate(x, 22);
}
uint32_t big_sigma_1(uint32_t x) {
	return right_rotate(x, 6) ^ right_rotate(x, 11) ^ right_rotate(x, 25);
}
void message_schedule(uint32_t(&W)[64], char(&A)[64]) {
	for (int i = 0; i < 16; i++) {
		W[i] = (A[i * 4] << 24) |
			(A[i * 4 + 1] << 16) |
			(A[i * 4 + 2] << 8) |
			(A[i * 4 + 3]);
	}
	for (int i = 16; i < 64; i++) {
		W[i] = little_sigma_1(W[i - 2]) + W[i - 7] +
			little_sigma_0(W[i - 15]) + W[i - 16];
	}
}
uint32_t choice(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (~x & z);
}
uint32_t majority(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}
void round(uint32_t(&state)[8], uint32_t round_constant, uint32_t schedule_word) {
	uint32_t T1 = state[7] +
		big_sigma_1(state[4]) +
		choice(state[4], state[5], state[6]) +
		round_constant +
		schedule_word;
	uint32_t T2 = big_sigma_0(state[0]) +
		majority(state[0], state[1], state[2]);
	for (int i = 7; i > 0; i--) {
		state[i] = state[i - 1];
	}
	state[0] = T1 + T2;
	state[4] += T1;
}
void compress_block(uint32_t(&initial_state)[8], char(&block)[64]) {
	uint32_t W[64];
	uint32_t state[8];
	for (int i = 0; i < 8; i++) state[i] = initial_state[i];
	message_schedule(W, block);
	for (int i = 0; i < 64; i++) round(state, W[i], K[i]);
	for (int i = 0; i < 8; i++) initial_state[i] += state[i];
}
void to_bitset(vector<unsigned char> &block, string message) {
	for (int i = 0; i < message.size(); i++) {
		bitset<8> b = message[i];
		block.push_back(b.to_ulong());
	}
}
void pad_5122(vector<unsigned char> &block) {
	unsigned char initial_byte = 128;
	uint64_t l = block.size() * 8; // Message size as 64bit number
	int x = 512;
	while ((x < l)) {
		x *= 2;
	}
	int k = (448 - 8) - l; // l + 1 + k = 448 mod 512

	block.push_back(initial_byte);

	// Pad the rest of the bits with 0 (up until last 64bits)
	for (int i = 1; i <= k; i += 8) {
		block.push_back(0);
	}

	// Add last 64bits that represent message size
	for (int i = 7; i >= 0; i--) {
		block.push_back((l >> (8 * i))& (0xff));
	}
}

void resize_block(uint32_t* block, vector<unsigned char> &input) {
	for (int i = 0; i < 16; i++) {
		block[i] =	(input[i * 4] << 24) |
					(input[i * 4 + 1] << 16) |
					(input[i * 4 + 2] << 8) |
					(input[i * 4 + 3]);
	}
}
std::string vectorToBinaryString(const std::vector<unsigned char>& vec) {
	std::string binaryString;
	for (const unsigned char& value : vec) {
		std::bitset<8> bits(value); // Convert the unsigned char value to binary (8 bits)
		binaryString += bits.to_string(); // Append the binary representation to the string
	}
	return binaryString;
}

void pad_512(vector<unsigned char> message) {
	/*cout << "Message=" << message << endl;
	cout << "Length=" << length;*/
	cout << "Message Size = " << message.size() * 8 << endl;
	cout << "Message" << endl;
	for (int i = 0; i < message.size(); i++) {
		cout << message.at(i);
	}
	cout << endl;

	int N = 1;
	int size = message.size();
	int l = (size * 8);
	message.push_back(128);

	if (l + 64 > 512) {
		N += (l / 512);
	}
	for (int i = l; i < ((N * 512) - 8 - 64); i += 8) {
		message.push_back(0);
	}
	for (int i = 0; i < 8; ++i) {
		message.push_back((unsigned char)((((unsigned long long) l) >> (56 - (8 * i))) & 0xFFu));
	}

	string res = vectorToBinaryString(message);
	std::cout << "Binary representation " << endl << res << std::endl;
	cout << endl << "Total Bits Size = " << res.size();

	
}

void sha256(string message) {
	vector<unsigned char> block(message.begin(), message.end());
	pad_512(block);
}

