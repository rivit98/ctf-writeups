#include <iostream>
#include <fstream>
#include <bitset>
#include <cmath>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
#include <cstring>

//constexpr uint32_t SEED = 0x0000000063553944;
constexpr uint32_t SEED = 1665570905;

std::string read_flag(std::string fname) {
	std::ifstream t(fname);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str;
}

std::string to_binary(std::string flag) {
	std::string ret = std::bitset<7>(flag[0]).to_string();

	for (char c: flag.substr(1)) {
		ret += std::bitset<8>(c).to_string();
	}

	return ret;
}

std::string pad_flag(std::string flag) {
	std::string padded = to_binary(flag);
	int flag_len = padded.size();

	srand(SEED);

	for (int i = 2;; ++i) {
		if (sqrt(flag_len) < (double) i)
			break;
		if (!(flag_len % i)) {
			int v10 = rand() % 0xC;
			for (int j = 0; j < v10; j++) {
				uint64_t v = (unsigned int) (rand() % 256);
				padded += std::bitset<8>(v).to_string();
			}
			i = 1;
			flag_len = padded.size();
		}
	}

	return padded;
}

int pad_flag_fast(int _flag_len) {
	int flag_len = _flag_len * 8 - 1;

	for (int i = 2;; ++i) {
		if (sqrt(flag_len) < (double) i)
			break;
		if (!(flag_len % i)) {
			int v10 = rand() % 0xC;
			for (int j = 0; j < v10; j++) {
				rand();
				flag_len += 8;
			}
			i = 1;
		}
	}

	return flag_len;
}

void save_flag(const std::string &out) {
	std::ofstream f("flag_my.enc", std::ios::binary | std::ios::out);

	f << static_cast<uint8_t>(std::bitset<8>(out.substr(0, 7)).to_ulong());

	for (unsigned int i = 7; i < out.size(); i += 8) {
		std::string part = out.substr(i, 8);
		if (strlen(part.c_str()) != 8) {
			part = std::string(part.c_str()) + '0';
		}
		f << static_cast<uint8_t>(std::bitset<8>(part).to_ulong());
	}
}

std::string decode(const std::string &out) {
	try {
		std::string res = "";
		for (unsigned int i = 0; i < out.size(); i += 8) {
			std::string part = out.substr(i, 8);
			if (strlen(part.c_str()) != 8) {
				part = std::string(part.c_str()) + '0';
			}
//			std::cout << i << ". " << part << '\n';
			res += static_cast<char>(std::bitset<8>(part).to_ulong());
		}
		return res;
	} catch (...) {
		return "decode failed";
	}
}

std::string encrypt(std::string flag) {
	flag = pad_flag(flag);
	int flag_len = flag.size();

	int rand_val;
	auto pow_data = std::vector<int>(flag_len);
	for (int i = 0; i < flag_len - 1; i++) {
		pow_data[0] = 1;
		rand_val = rand() % flag_len - 1;
		for (int ii = 1; ii < flag_len; ii++) {
			int idx = 0;
			int val = 1;
			do {
				idx++;
				val = rand_val * val % flag_len;
			} while (idx < ii);
//			std::cout << "rand val: " << std::hex << rand_val << " " << val << '\n';
			pow_data[ii] = val;
		}

		std::unordered_set<int> uniq(pow_data.begin(), pow_data.end());
		if (uniq.size() == flag_len - 1) {
			break;
		}
	}

	auto out = std::vector<int>(flag_len);
	out[0] = flag[1];
	for (int i = 1; i < flag_len - 1; i++) {
		out[i] = flag[pow_data[i]];
	}

	std::stringstream outstr;
	std::string delimiter = "";
	std::copy(out.begin(), out.end(), std::ostream_iterator<char>(outstr, delimiter.c_str()));

	std::cout << "Plain: " << flag << '\n';
	std::cout << "Encrypted: " << outstr.str() << '\n';

	return outstr.str();
}

std::vector<int> get_translate_table(int flag_len) {
	int rand_val;
	auto pow_data = std::vector<int>(flag_len);
	for (int i = 0; i < flag_len - 1; i++) {
		pow_data[0] = 1;
		rand_val = rand() % flag_len - 1;
		for (int ii = 1; ii < flag_len; ii++) {
			int idx = 0;
			int val = 1;
			do {
				idx++;
				val = rand_val * val % flag_len;
			} while (idx < ii);
//			std::cout << "rand val: " << std::hex << rand_val << " " << val << '\n';
			pow_data[ii] = val;
		}

		std::unordered_set<int> uniq(pow_data.begin(), pow_data.end());
		if (uniq.size() == flag_len - 1) {
			return pow_data;
		}
	}

	return {};
}

void brute() {
	int expected_len = 0x19 * 8 - 1;
	for (int seed = SEED; seed > SEED - 14 * 86400; seed--) {
		for (int i = 10; i < 80; i++) {
			srand(seed);
			int padded_len = pad_flag_fast(i);

			if (padded_len == expected_len) {
				auto encrypted_ = read_flag("flag.enc");
				std::string encrypted = to_binary(encrypted_);

				auto pow_data = get_translate_table(encrypted.size());
				if (pow_data.empty()) {
					continue;
				}

				auto out = std::vector<char>(encrypted.size());
				out[0] = encrypted[1];
				for (int ii = 1; ii < encrypted.size(); ii++) {
					out[pow_data[ii]] = encrypted[ii];
				}

				std::stringstream outstr;
				std::string delimiter = "";
				std::copy(out.begin(), out.end(), std::ostream_iterator<char>(outstr, delimiter.c_str()));
				auto recovered = decode("0" + outstr.str());
				std::cout << "Seed: " << seed << "  flag_len: " << i << '\n';
				std::cout << out.size() << " " << recovered << '\n';
			}
		}
	}
}

int main(int argc, char **argv) {
//	auto flag = read_flag(argv[1]);
//	std::string enc = encrypt(flag);
//	save_flag(enc);
//	std::cout << std::endl;
//	std::cout << std::endl;

	brute();

	return 0;
}