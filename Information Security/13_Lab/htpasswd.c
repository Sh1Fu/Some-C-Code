#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_upper(char *password){
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < strlen(password); j++){
            if(password[j] == upper[i]) return 1;
        }
    }
    return 0;
}
int check_lower(char *password){
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < strlen(password); j++){
            if(password[j] == lower[i]) return 1;
        }
    }
    return 0;
}
int check_nums(char *password){
    char nums[] = "0123456789";
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < strlen(password); j++){
            if(password[j] == nums[i]) return 1;
        }
    }
    return 0;

}
int check_spec(char* password) {
    char spec[] = "!@#$%^&*()_-+=~`.,/?><;:{}[]|\\";
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < strlen(password); j++) {
            if (password[j] == spec[i]) return 1;
        }
    }
    return 0;
}
int main(int argc, char *argv[]){
    char command[300] = "";
    char password[1000] = "";
    short correct = 0;
    while (!correct) {
        scanf("%s", password);
        if (check_nums(password) && check_spec(password) && check_lower(password) && check_upper(password) && strlen(password) >= 10) {
            correct = 1;
            printf("Good password\n");
            sprintf(command, ".\\htpasswd.exe -b -p %s %s %s", argv[1], argv[2], password); // argv[1] - место htpasswd, argv[2] - имя пользователя
            system(command);
            break;
        }
        else {
            printf("Bad password\nCheck some points:\n1. More than 10 symbols\n2. With uppercase and lowercase\n3. With digits and special symbols\nPassword >> ");
            correct = 0;
        }
    }
    return 0;
}