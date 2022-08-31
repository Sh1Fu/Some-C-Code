#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#define ull unsigned long long
#define ui unsigned int
#define uc unsigned char
char *FILE_NAME = "data.txt";

ull flen(char *file_name)
{
    ull size = 0;
    FILE *f = fopen(file_name, "r");
    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    fclose(f);
    return size;
}

void print_results(ui result)
{
    printf("result of CRC in 16: 0x%x\n", result);
    printf("result of CRC in 10: %u\n", result);
    printf("result of CRC in 2: ");
    for (int i = 31; i >= 0; i--)
        printf("%d", (result >> i) & 1);
    printf("\n");
}

void controlsum()
{
    FILE *f = fopen(FILE_NAME, "r");
    ull sum = 0;
    char sym;
    while (!feof(f))
    {
        sym = fgetc(f);
        sum += (int)sym;
    }
    sum %= 256;
    fclose(f);
    printf("%lld\n", sum);
}

void crc32()
{
    /* Init default polynome, data folder, file len etc. */
    ui polynome = 0x04C11DB7, crc = 0;
    uc work_sym, *data;
    ull len = flen(FILE_NAME); // flen(FILE_NAME) + 4

    FILE *f = fopen(FILE_NAME, "r");
    data = (uc *)malloc((len + 1) * sizeof(uc));
    // memset(data, 0, len);

    /* Fill data from FILE_NAME */
    ull i = 0;
    for (i = 0; !feof(f); i++)
        data[i] = fgetc(f);

    /* Fill register crc */
    int index;
    for (index = 0; index < 3; ++index)
    {
        crc += data[index];
        crc <<= 8;
    }
    crc += data[index];
    len -= 4;
    while (len--)
    {
        index++;
        for (uint8_t j = 0; j < 8; j++)
        {
            /* Start working with symbol and register */
            work_sym = data[index] / (uc)pow(2, (7 - j));
            work_sym %= 2;
            /* Check first bit of crc */
            ((crc >> 31) & 1 ? (crc = (crc * 2 + work_sym) ^ polynome) : (crc = (crc * 2 + work_sym)));
        }
    }
    for (i = 0; i < 32; ++i)
    {
        if ((crc >> 31) & 1)
        {
            crc <<= 1;
            crc ^= polynome;
        }
        else
        {
            crc <<= 1;
        }
    }
    print_results(crc);
    fclose(f);
    free(data);
}

void bincrc32()
{
    /* Init default polynome, data folder, file len etc. */
    ui polynome = 0x04C11DB7, crc = 0;
    uc work_sym, *data;
    ull len = flen(FILE_NAME);

    FILE *f = fopen(FILE_NAME, "r");
    data = (uc *)malloc((len + 1) * sizeof(uc));
    // memset(data, 0, len + 1);

    /* Fill data from FILE_NAME */
    ull i = 0;
    for (i = 0; !feof(f); i++)
        data[i] = fgetc(f);

    /* Fill register crc */
    int index;
    for (index = 0; index < 3; ++index)
    {
        crc += data[index];
        crc <<= 8;
    }
    crc += data[index];
    len -= 4;
    while (len--)
    {
        index++;
        for (int j = 0; j < 8; j++)
        {
            /* Start working with symbol and register */
            work_sym = data[index];
            work_sym <<= j;
            work_sym >>= 7;
            /* Check first bit of crc */
            ((crc >> 31) & 1 ? (crc = ((crc << 1) + work_sym) ^ polynome) : (crc = ((crc << 1) + work_sym)));
        }
    }
    for (i = 0; i < 32; ++i)
    {
        if ((crc >> 31) & 1)
        {
            crc <<= 1;
            crc ^= polynome;
        }
        else
        {
            crc <<= 1;
        }
    }
    print_results(crc);
    fclose(f);
    free(data);
}

int main()
{
    controlsum();
    printf("\nCRC32 results\n\n");
    crc32();
    printf("\nBin CRC32 results\n\n");
    bincrc32();
}