#include <stdio.h>
#include <string.h>

char *solve(char* start_string, char *res){
    int i = 0, j;
    char word[1500] = "", tmp_word[1500] = "";
    int res_ind = 0, word_ind, cmp_ind = 0;
    for(i = 0; i < strlen(start_string); i++){

        if (start_string[i] == ' ' || start_string[i] == ',' || start_string[i] == '.' || !start_string[i] || start_string[i] == '\0'){
            for (word_ind = strlen(word) - 1; word_ind >= 0; word_ind--) {
                res[res_ind] = word[word_ind];
                res_ind++;
            }
            res[res_ind] = start_string[i];
            res_ind++;
            memset(word, 0, strlen(word));
            cmp_ind = 0;
        }
        else{
            word[cmp_ind] = start_string[i];
            cmp_ind++;
        }
    }
    return res;
}

int main(){
    char start_string[1500]= "", res[1500]="";
    gets(start_string);
    printf("%s",solve(start_string, res));
    return 0;
}