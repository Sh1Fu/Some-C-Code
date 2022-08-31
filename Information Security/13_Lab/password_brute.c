#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char* encode_base(char *in, char* out){
    static char sym_set[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // All symbols to b64 encode
    int index, bit_size = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;
    for (i = 0; i < strlen(in); i += 3) //  ����� �� ��� ������� �� ����������� ������
        {
            val = 0, count = 0, bit_size = 0;
            
            for (j = i; j < strlen(in) && j <= i + 2; j++) // � val ���������� ��� ���� ���� ��������. 
            { // �� �����, val - 32 ����, ��� ��� ������� ����� �������, ��������� ��� � ������ -> ������������ � val -> ����������
                val = val << 8;
                val = val | in[j];
                count++;
            }

            bit_size = count * 8; //8 ������ ����� ��������� ����� ������, ������� ������ "=" ����� � �����
            padding = bit_size % 3; // �� ����������
            while (bit_size != 0)
            { // ����� ��������� �� ����� �� 6 ���. ������ 6? 2^6 = 64

                if (bit_size >= 6)
                {
                    temp = bit_size - 6;

                    index = (val >> temp) & 63; // 63 � ������� - 111111. ��������� ������ �� sym_set.
                    bit_size -= 6;        
                }
                else
                {
                    temp = 6 - bit_size;

                    index = (val << temp) & 63;
                    bit_size = 0;
                }
                out[k++] = sym_set[index]; // ��������� � �������� ������ ������������ ��������
            }
    }

    for (i = 1; i <= padding; i++)
    {
        out[k++] = '=';
    }
  
    out[k] = '\0';
    return out; 
}

void rstrip(char* password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] == '\n') password[i] = '\0';
    }
}

void brute(char *target) {
    FILE* password;
    password = fopen("passwords.txt", "r");
    char in_passwd[6] = "";
    char out[100]  = "";
    while(!feof(password)){
        fgets(in_passwd, 5, password);
        rstrip(in_passwd);
        if (strcmp(target, encode_base(in_passwd, out)) == 0) {
            printf("%s", in_passwd);
            break;
        }
    }
}

int main(int argc, char *argv[]){
    brute(argv[1]);
}