#pragma once
#include <stdint.h>
const uint32_t K[] = {
	1116352408, 1899447441, 3049323471, 3921009573, 961987163, 1508970993, 2453635748, 2870763221,
	3624381080, 310598401, 607225278, 1426881987, 1925078388, 2162078206, 2614888103, 3248222580,
	3835390401, 4022224774, 264347078, 604807628, 770255983, 1249150122, 1555081692, 1996064986,
	2554220882, 2821834349, 2952996808, 3210313671, 3336571891, 3584528711, 113926993, 338241895,
	666307205, 773529912, 1294757372, 1396182291, 1695183700, 1986661051, 2177026350, 2456956037,
	2730485921, 2820302411, 3259730800, 3345764771, 3516065817, 3600352804, 4094571909, 275423344,
	430227734, 506948616, 659060556, 883997877, 958139571, 1322822218, 1537002063, 1747873779,
	1955562222, 2024104815, 2227730452, 2361852424, 2428436474, 2756734187, 3204031479, 3329325298
};
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
void message_schedule(uint32_t W[], char A[]) {
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
void round(uint32_t state[], uint32_t round_constant, uint32_t schedule_word) {
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
uint32_t* compress_block(uint32_t initial_state[], char block[]) {
	uint32_t* state = new uint32_t[8]();
	uint32_t W[64];
	for (int i = 0; i < 8; i++) state[i] = initial_state[i];
	message_schedule(W, block);
	for (int i = 0; i < 64; i++) round(state, W[i], K[i]);
	for (int i = 0; i < 8; i++) state[i] = state[i] + initial_state[i];
	return state;
}