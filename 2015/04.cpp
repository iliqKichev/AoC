#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::basic_string<unsigned char> ustring;

unsigned leftrotate(unsigned x, unsigned n) {
  return ((x << n) | (x >> (32 - n)));
}

ustring pad_msg(std::string &msg) {
  unsigned char tmpChar{0x80};
  union {
    uint64_t ull;
    unsigned char ch[8];
  } size;
  size.ull = msg.size() * 8;
  ustring message;

  for (char c : msg) {
    message += c;
  }
  message += tmpChar;

  std::size_t paddingSize = (56 - (msg.size() + 1) % 64) % 64;

  message.insert(message.end(), paddingSize, 0);

  for (int j = 0; j < 8; j++) {
    message += size.ch[j];
  }

  return message;
}

std::vector<uint32_t> split_words(ustring &msg, std::size_t chunkId) {
  std::vector<uint32_t> word(16, 0);
  for (int i = 0; i < 16; i++) {
    // Ensure little-endian byte ordering
    word[i] = static_cast<uint32_t>(msg[chunkId + i * 4 + 0]) |
              (static_cast<uint32_t>(msg[chunkId + i * 4 + 1]) << 8) |
              (static_cast<uint32_t>(msg[chunkId + i * 4 + 2]) << 16) |
              (static_cast<uint32_t>(msg[chunkId + i * 4 + 3]) << 24);
  }
  return word;
}

void print_number(std::stringstream &ss, unsigned num) {
  union {
    unsigned u;
    unsigned char uc[4];
  } n;
  n.u = num;

  ss << std::setfill('0') << std::setw(2) << std::hex
     << (unsigned short)n.uc[0];
  ss << std::setfill('0') << std::setw(2) << std::hex
     << (unsigned short)n.uc[1];
  ss << std::setfill('0') << std::setw(2) << std::hex
     << (unsigned short)n.uc[2];
  ss << std::setfill('0') << std::setw(2) << std::hex
     << (unsigned short)n.uc[3];
}

std::string get_MD5_hex(std::string msg) {

  // s specifies the per-round shift amounts
  unsigned s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                  5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

  unsigned K[64] = {
      0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
      0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
      0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
      0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
      0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
      0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

  // Initialize variables:
  unsigned a0 = 0x67452301L; // A
  unsigned b0 = 0xefcdab89L; // B
  unsigned c0 = 0x98badcfeL; // C
  unsigned d0 = 0x10325476L; // D

  ustring message = pad_msg(msg);

  for (std::size_t chunkId = 0; chunkId < message.size(); chunkId += 64) {

    std::vector<unsigned> word = split_words(message, chunkId);

    uint32_t A = a0;
    uint32_t B = b0;
    uint32_t C = c0;
    uint32_t D = d0;
    uint32_t F;
    int g;
    for (int i = 0; i < 64; i++) {
      if (i < 16) {
        F = D ^ (B & (C ^ D));
        g = i;
      } else if (i < 32) {
        F = C ^ (D & (B ^ C));
        g = (5 * i + 1) % 16;
      } else if (i < 48) {
        F = B ^ C ^ D;
        g = (3 * i + 5) % 16;
      } else {
        F = C ^ (B | (~D));
        g = (7 * i) % 16;
      }
      // Be wary of the below definitions of a,b,c,d
      F = F + A + K[i] + word[g]; // M[g] must be a 32-bit block
      A = D;
      D = C;
      C = B;
      B = B + leftrotate(F, s[i]);
    }
    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;
  }

  std::stringstream ss;
  print_number(ss, a0);
  print_number(ss, b0);
  print_number(ss, c0);
  print_number(ss, d0);
  return ss.str();
}

int main() {
  /// TEST abcdef -> 609043 CORRECT!
  /// TEST pqrstuv -> 1048970 CORRECT!
  std::string msg = "ckczppom";
  for(unsigned long long i = 1; i < 1e7; i ++){
    auto res = get_MD5_hex(msg + std::to_string(i));
    bool key = true;
    for(int j = 0; j < 6; j ++){
      if(res[j] != '0'){
        key = false;
        break;
      }
    }
    if(key) {
      std::cout << i << std::endl;
      break;
    }
  } 
  return 0;
}
