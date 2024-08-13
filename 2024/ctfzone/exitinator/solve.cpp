#include <iostream>
#include <bit>
#include <cstdint>

uint8_t expected[] = {
    153,
 60,
 137,
 115,
 49,
 185,
 161,
 155,
 129,
 39,
 95,
 145,
 153,
 54,
 161,
 51,
 55,
 125,
 19,
 57,
 171,
 134
};

int rots[] =  {
    149,
 137,
 133,
 132,
 136,
 142,
 149,
 137,
 133,
 132,
 136,
 142,
 149,
 137,
 133,
 132,
 136,
 142,
 149,
 137,
 133,
 132
};

int
main(int argc, char *argv[])
{
   for(int i = 0; i < sizeof(expected); i++) {
    std::cout << std::rotl(expected[i], rots[i]);
   }
}
