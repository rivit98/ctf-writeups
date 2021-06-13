// gcc solve.c -o solve && ./solve | grep bca
#include <stdio.h>

int print_flag(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, int a19, int a20, int a21, int a22, int a23, int a24, int a25, int a26, int a27, int a28, int a29, int a30, int a31, int a32, int a33, int a34)
{
   int i;                // [rsp+28h] [rbp-D8h]
   int v39[36];          // [rsp+40h] [rbp-C0h]
   char s[128];            // [rsp+D0h] [rbp-30h] BYREF

   v39[21] = a1;
   v39[28] = a2;
   v39[7] = a3;
   v39[12] = a4;
   v39[6] = a5;
   v39[14] = a6;
   v39[8] = a7;
   v39[25] = a8;
   v39[17] = a9;
   v39[29] = a10;
   v39[19] = a11;
   v39[16] = a12;
   v39[31] = a13;
   v39[20] = a14;
   v39[15] = a15;
   v39[32] = a16;
   v39[5] = a17;
   v39[33] = a18;
   v39[11] = a19;
   v39[18] = a20;
   v39[26] = a21;
   v39[9] = a22;
   v39[3] = a23;
   v39[22] = a24;
   v39[30] = a25;
   v39[1] = a26;
   v39[0] = a27;
   v39[4] = a28;
   v39[13] = a29;
   v39[2] = a30;
   v39[27] = a31;
   v39[23] = a32;
   v39[24] = a33;
   v39[10] = a34;
   for(int v36 = 0; v36 < 60; v36++){
      for (i = 0; i <= 33; ++i)
         s[i] = (v39[i] >> v36) - v36 * i + 21;
   
      puts(s);
   }
}



int main(){
   print_flag(
    467,
    520,
    390,
    452,
    459,
    426,
    179,
    517,
    257,
    351,
    265,
    447,
    389,
    538,
    231,
    575,
    365,
    682,
    210,
    440,
    330,
    389,
    337,
    510,
    554,
    322,
    309,
    415,
    401,
    323,
    574,
    298,
    511,
    397);
}
