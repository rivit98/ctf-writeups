#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <wincrypt.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t expected[] = {
    115,
 227,
 103,
 149,
 7,
 204,
 129,
 151,
 246,
 101,
 253,
 91,
 70,
 245,
 83,
 33,
 207,
 137,
 187,
 130,
 140,
 215,
 187,
 66,
 75,
 24,
 23,
 52,
 212,
 104,
 112,
 151,
 9,
 212,
 144,
 133,
 134,
 140,
 218,
 27,
 152,
 146,
 185,
 71,
 153,
 158,
 79,
 100
};


char* check(char* k) {
    HCRYPTPROV hProv = NULL;
    HCRYPTHASH hHash = NULL;
    HCRYPTKEY hKey = NULL;
    BOOL result;
    DWORD dwDataLen;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        return 0;
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return 0;
    }

    if (!CryptHashData(hHash, (const BYTE*)k, 8, 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 0;
    }

    if (!CryptDeriveKey(hProv, CALG_AES_128, hHash, 0, &hKey)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 0;
    }

    uint8_t* to_dec = (uint8_t*) malloc(sizeof(expected));
    memcpy(to_dec, expected, sizeof(expected));
    dwDataLen = sizeof(expected);
    if (!CryptDecrypt(hKey, 0, TRUE, 0, to_dec, &dwDataLen)) {
        CryptDestroyKey(hKey);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        free(to_dec);
        return 0;
    }

    CryptDestroyKey(hKey);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return (char*) to_dec;
}

int main()
{
    for (size_t i1 = 0; i1 < 7; i1++)
    {
        for (size_t i2 = 0; i2 < 3; i2++)
        {
            for (size_t i3 = 0; i3 < 9; i3++)
            {
                for (size_t i4 = 0; i4 < 6; i4++)
                {
                    for (size_t i5 = 0; i5 < 9; i5++)
                    {
                        for (size_t i6 = 0; i6 < 8; i6++)
                        {
                            for (size_t i7 = 0; i7 < 4; i7++)
                            {
                                for (size_t i8 = 0; i8 < 5; i8++)
                                {
                                    char buf[9];
                                    sprintf(buf, "%c%c%c%c%c%c%c%c", i1 + '0', i2 + '0', i3 + '0', i4 + '0', i5 + '0', i6 + '0', i7 + '0', i8 + '0');
                                    char* res = check(buf);
                                    if (res && res[0] == 'B' && res[1] == 'H' && res[2] == 'F' && res[3] == 'l' && res[4] == 'a' && res[5] == 'g') {
                                        puts(res);
                                        return 0;
                                    }
                                    free(res);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // BHFlagY{ca11ing_n4tiv3_c0d3_fr0m_j5_vb5_ps}
}
