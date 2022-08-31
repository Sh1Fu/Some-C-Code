#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#define Ng 7
#define Ns 9
#define Fsym 13
#define k 7
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
        ull x = modexp(a,t,N);
        if(x == 1 || x == N - 1){
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

void task_5678() {
    printf("Tasks 5,6,7,8\n");
    int p = 443;
    int q = 941;
    int n = p * q;
    int f_n = (p - 1) * (q - 1);
    int e = 31;
    
    // ed mod f_n == 1;
    int d; // 40111
    for (d = 1; ; d++) {
        if (e * d % f_n == 1 && nod(d, f_n) == 1)  break;
    }
    printf("N: %d e: %d d: %d\n",n ,e, d);
    char message[4] = "CTF";
    ull encrypt[3] = { 0 };
    ull decrypt[3] = { 0 };
    ull check[3] = {0};
    // Конечно, тут, как и во всех лабораторной работе, стоит понимать, что такие операции комп не возьмет,
    // Степени слишком большие, поэтому нужно написать отдельную функцию modexp()
    for (int i = 0; i < 3; i++) {
        printf("%c -> %d ", message[i], (int)message[i]);
    }
    printf("\nEncrypt: ");
    for (int i = 0; i < 3; i++) {
        encrypt[i] = modexp((int)message[i], e, n);
        printf("%lld ", encrypt[i]);
    }
    printf("\nDecrpyt: ");
    for (int j = 0; j < 3; j++) {
        decrypt[j] = modexp(encrypt[j], d, n);
        printf("%lld ", decrypt[j]);
    }
    printf("\n");

    // Task 7
    // s = modexp(x, d) (mod n)
    // x = modexp)(s, e) (mod n)
    int s = 0, count = 0;
    for(int i = 0; i < 3; i++){
        s = modexp(message[i],d,n);
        check[i] = modexp(s, e, n);
        if(message[i] == check[i]) count++;
    }
    (count == 3 ? printf("Cert is correct\n") : printf("Invalid cert\n"));

    // Task 8
    srand(time(NULL));
    ull a = rand();
    ull x = rand() % f_n;
    ull y = rand() % f_n;
    ull A = modexp(a, x, n);
    ull B = modexp(a, y, n);
    ull user_a = modexp(B, x, n);
    ull user_b = modexp(A, y, n);
    ull result = modexp(a, x*y, n);
    printf("a: %llu\nx: %llu\ny: %llu\nA: %llu\nB: %llu\nA_res: %llu\nB_res: %llu\n", a, x, y, A, B, user_a, user_b);
    int final_check = (modexp(a, x*y, n) == modexp(a, y*x, n) && modexp(a, x*y, n) == modexp(a, x*y, n) ? 1 : 0);
    printf("Check: %d\nFinal_check: %d\n", (user_a == user_b ? 1 : 0), final_check);
}

void task_4() {
    int N = 17726;
    int N_prime = 613;
    printf("\nTask 4:\n");
    printf("N = 17726 is %d\n", MillerTest(N, 15));
    printf("N = 613 is %d\n", MillerTest(N_prime, 15));
    printf("N = 612 is %d\n", MillerTest(612, 15));
    printf("N = 101 is %d\n\n", MillerTest(101, 15));
}

void task_3() {
    ull A = pow((double)Ng * ((8 + Ns) % 7), 2);
    ull B = 16052003;
    printf("Task 3: %lld %lld\n", A, B);
    printf("NOD(A, B mod 95 + 900) = %llu\n", nod(A, (B % 95) + 900)); // 441 943
    printf("NOD(A, B + 50 mod 97 + 700) = %llu\n", nod(A, (((B + 50) % 97) + 700)));
    printf("NOD(A, (B+20) mod 101 + 1500, (B-40) mod 103 + 2500) = 1\nHere B1: 1593, B2: 2531\n");
}

void task_2() {
    unsigned char string[] = "GalkinKlimentiiKonstantinovich"; unsigned char sym;
    for (int i = 0; i < strlen(string); i++) {
        sym = string[i];
        if ('a' <= sym <= 'z') {
            sym = sym + k;
            if (sym > 'z') sym = sym - 'z' + 'a' - 1;
        }
        else if ('A' <= sym <= 'Z') {
            sym = sym + k;
            if (sym > 'Z') sym = sym - 'Z' + 'A' - 1;
        }
        string[i] = sym;
    }
    printf("Task 2: %s\n", string);
}

void task_1() {
    ull r = pow((double)(Ng + Ns), 11) + 13;
    printf("Task 1: %llu \n", r % 11);
}

int main() {
    task_1();
    task_2();
    task_3();
    task_4();
    task_5678();
}
