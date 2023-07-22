#pragma once
#include <string>
#include <vector>
using namespace std;

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;
const int g = 6;
const int h = 7;
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
uint32_t H[8] = { 0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19 };

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

void message_schedule(uint32_t(&W)[64], uint8_t(&block_64_bit)[64]) {
	for (int i = 0; i < 16; i++) {
		W[i] =  ( block_64_bit [i * 4]  <<  24)     |
				( block_64_bit [i * 4 + 1]  <<  16) |
				( block_64_bit [i * 4 + 2]  <<  8)  |
				( block_64_bit [i * 4 + 3]);
	}

	for (int i = 16; i < 64; i++) {
		W[i] =	little_sigma_1( W [i - 2] )  +  W[i - 7]  +
				little_sigma_0( W [i - 15] )  +  W[i - 16];
	}
}

uint32_t choice(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (~x & z);
}

uint32_t majority(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

void round(uint32_t(&H)[8], uint32_t round_constant, uint32_t schedule_word) {
	uint32_t T1 =	H[h] +
					big_sigma_1(H[e]) +
					choice(H[e], H[f], H[g]) +
					round_constant +
					schedule_word;

	uint32_t T2 =	big_sigma_0(H[a]) +
					majority(H[a], H[b], H[c]);

	for (int i = 7; i > 0; i--) {
		H[i] = H[i - 1];
	}

	H[a] = T1 + T2;
	H[e] += T1;
}
void compress_block(uint32_t(&H)[8], uint8_t(&block_64_bit)[64]) {
	uint32_t W[64];
	uint32_t h[8];

	message_schedule(W, block_64_bit);

	for (int i = 0; i < 8; i++) h[i] = H[i];
	for (int i = 0; i < 64; i++) round(h, W[i], K[i]);
	for (int i = 0; i < 8; i++) H[i] += h[i];
}

void sha256(string m) {
	vector<uint8_t> message(m.begin(), m.end());
	int N = 1;
	int l = (message.size() * 8);
	message.push_back(128);

	if ((l + 64) > 512) {
		N += ((l + 64) / 512);
	}
	for (int i = l; i < ((N * 512) - 8 - 64); i += 8) {
		message.push_back(0);
	}
	for (int i = 0; i < 8; ++i) {
		message.push_back((uint8_t)((((unsigned long long) l) >> (56 - (8 * i))) & 0xFFu));
	}

	uint8_t block[64];
	for (int i = 0; i < N; i++) {
		std::copy(reinterpret_cast<uint8_t*>(&message[i * 64]),
			reinterpret_cast<uint8_t*>(&message[(i * 64) + 63]),
			block);

		block[63] = message[(i * 64) + 63];
		compress_block(H, block);
	}
}

