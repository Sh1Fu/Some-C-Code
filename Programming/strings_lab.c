#include <stdio.h>
#include <string.h>

int minim(int a, int b) {
    return (a <= b ? a : b);
}  
char* solve(char* word_1, char* word_2, char* res) {
    int max_count = minim(strlen(word_1), strlen(word_2));
    int count = 1;
    int max = 0;
    int i_ind, j_ind;
    while (count <= max_count) {
        int temp_max = 0;
        int i = strlen(word_1) - count;
        int j = 0;
        while (i < strlen(word_1)) {
            if (j < count) {
                if (word_1[i] == word_2[j]) {
                    temp_max++;
                    i++;
                    j++;
                }
                else {
                    temp_max = 0;
                    j = 0;
                    i++;
                }
            }
            if (temp_max == count) {
                max = count;
            }
        }
        count++;
    }

    for (i_ind = 0; i_ind < strlen(word_1); i_ind++) {
        res[i_ind] = word_1[i_ind];
    }
    for (j_ind = max; j_ind < strlen(word_2); j_ind++) {
        int index = strlen(res);
        res[index] = word_2[j_ind];
    }
    return res;
}

int main(){
    char tmp[100] = "";
    int n, i, j, k, tmp_index;
    scanf_s("%d", &n);
    gets(tmp);
    for (i = 0; i < n; i++){
        char word[100], word_1[100] = " ", word_2[100] = " ", res[100] = " ";
        //split
        int space_index = 0;
        gets(word);
        for (j = 0; j < strlen(word); j++) {
            if (word[j] == ' ') {
                space_index = j;
            }
        }
        for (k = 0; k < space_index; k++) {
            word_1[k] = word[k];
        }
        tmp_index = 0;
        for (k = space_index + 1; k < strlen(word); k++) {
            word_2[tmp_index] = word[k];
            tmp_index++;
        }
        printf("%s\n", solve(word_1, word_2, res));
    }
    return 0;
}