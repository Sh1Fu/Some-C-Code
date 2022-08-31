#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ull unsigned long long

ull nod(ull a, ull b)
{
    while (a > 0 && b > 0)
        if (a > b)
            a %= b;
        else
            b %= a;
    return a + b;
}

ull modexp(ull a, ull n, ull m) {
    ull res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= m;
        }
        a *= (a % m);
        a %= m;
        n >>= 1;
    }
    return res % m;
}

int MillerTest(ull N, ull rounds) {
    srand(time(NULL));
    if (N == 2 || N == 3) return 1;
    if (N % 2 == 0 || N < 2) return 0;
    ull t = N - 1;
    ull s = 0;
    while (t % 2 == 0) {
        t = t / 2;
        s = s + 1;
    }
    for (int i = 0; i < rounds; i++) {
        int a = 2 + rand() % (N - 2);
        ull x = modexp(a, t, N);
        if (x == 1 || x == N - 1) {
            continue;
        }
        for (int j = 1; j < s; j++) {
            x = modexp(x, 2, N);
            if (x == 1) return 0;
            if (x == N - 1) break;
        }
        if (x != N - 1) return 0;
    }
    return 1;
}

int enc(char sym, int public_key[8]) {
    int tmp_sum = 0;
    for (int bit = 7; bit >= 0; bit--) {
        if (sym & (1 << bit)) {
            tmp_sum += public_key[7-bit];
        }
    }
    return tmp_sum;
}

int convert(ull n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * (int)pow(2, i);
        ++i;
    }
    return dec;
}

int dec(int enc_sym, int private_key[8], int rev_n, int m) {
    int dec_sym = 0;
    ull tmp_value;
    tmp_value = enc_sym * rev_n % m;
    for (int j = 7; j >= 0; j--) {
        if (tmp_value >= private_key[j]) {
            tmp_value -= private_key[j];
            dec_sym += (int)pow(10, 7 - j);
        }
        if (tmp_value == 0) return convert(dec_sym);
    }
}

void generate_keys(int private_key[8], int public_key[8], ull *m, ull *n, ull *rev_n) {
    srand(time(NULL));
    ull sum = 0;
    int range = 10;
    for (int i = 0; i < 8; i++) {
        do {
            if (i == 0) private_key[i] = rand() % range;
            if (i > 0) private_key[i] = private_key[i-1] + rand() % range;
        } while (private_key[i] <= sum);
        sum += private_key[i];
        if (sum >= range) range *= 10;
    }
    for (ull j = sum; ; j++) {
        if (MillerTest(j, 15) == 1) {
            (*m) = j;
            break;
        }
    }
    for ((*n) = 11; ; (*n)++) {
        if (nod((*n), (*m)) == 1) break;
    }
    for (int j = 0; j < 8; j++) {
        public_key[j] = (private_key[j] * (*n)) % (*m);
    }
    for ((*rev_n) = 1; ; (*rev_n)++) {
        if ((*rev_n) * (*n) % (*m) == 1) break;
    }

}
int main() {
    char message[1000] = "";
    ull m, n, rev_n;
    int command = 999;
    int private_key[8], public_key[8];
    int encrypt[1000];
    int decrypt[1000];
    memset(encrypt, -1, 100);
    memset(decrypt, -1, 100);
    generate_keys(private_key, public_key, &m, &n, &rev_n);
    printf("Keys are generated to this session. Welcome back!");
    while (1) {
        printf("\nWhat do you want to do:\nEncrypt - 1\nDecrypt - 2\nRefresh all arrays - 3\nExit - 0\n");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            getc(stdin);
            printf("Enter the message: ");
            gets(message);
            printf("Main message in digit form: ");
            for (int i = 0; message[i] != '\0'; i++) {
                printf("%d ", message[i]);
            }
            printf("\nEncrypted message in digit form: ");
            for (int i = 0; message[i] != '\0'; i++) {
                encrypt[i] = enc(message[i], public_key);
                printf("%d ", encrypt[i]);
            }
            break;

        case 2:
            printf("Enter the encrypted message like integers with 0 in the end: ");
            int j = 0;
            while (1) {
                scanf("%d", &encrypt[j]);
                if (encrypt[j] == 0) break;
                j++;
            }
            printf("\nDecrypt message in digit form: ");
            for (int i = 0; encrypt[i] != 0; i++) {
                decrypt[i] = dec(encrypt[i], private_key, rev_n, m);
                printf("%d ", decrypt[i]);
            }
            break;

        case 3:
            memset(message, 0, strlen(message));
            memset(encrypt, -1, 100);
            memset(decrypt, -1, 100);
            printf("All arrays are refreshed\n");
            break;

        default:
            exit(0);
            break;
        }
    }
}
    
