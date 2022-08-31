#include <stdio.h>
#include <string.h>

int isgl(char sym) {
    char gl[6] = { 'a', 'e', 'i', 'o', 'u', 'y' };
    int i;
    for (i = 0; i < 6; i++) {
        if (sym == gl[i]) { return 1; }
    }
    return 0;
}

void find_gl(char* word, char* gls) {
    int mas_ind = 0;
    int i, j = 0;
    for (i = 0; i < strlen(word); i++) {
        if (isgl(word[i])) {
            gls[mas_ind] = word[i];
            mas_ind++;
        }
    }
    while (j < strlen(gls) - 1) { 
        if (gls[j + 1] > gls[j]) {
            gls[j + 1] = 0x20;
            break;
        }
        j++;
    }
}

int in(char sym, char* arr) {
    int j;
    for (j = 0; j < strlen(arr); j++) {
        if (sym == arr[j]) {
            arr[j] = 0x20;
            return 1; 
        }
    }
    return 0;
}

int sovle_first(char* word, int res_index, char* res) { // Ќужно удалить максмальный элемент возрастающей последовательности символов
    int i = 0;
    int count = 0;
    int k = 0;
    for (int j = 0; j < strlen(word); j++) {
        k = j + 1;
        if (word[j] <= word[k] || (j == strlen(word)-1 && word[j] == word[j-1])) {
            res[res_index] = word[j];
            res_index++;
        }
        else if (word[j] > word[k]) {
            j++;
            for (int u = j; u < strlen(word); u++) {
                res[res_index] = word[u];
                res_index++;
            }
            return res_index;
        }

    }
    return res_index;
}

void solve_second(char *word, int res_index, char* res){ //Ќужно удалить наибольшую среди последовательно идущих гласную
    int i = 0;
    char gls[1000] = { " " };
    find_gl(word, gls);
    while (i < strlen(word)) {
        if (isgl(word[i])) {
            if (in(word[i], gls)) {
                res[res_index] = word[i];
                res_index++;
            }
            i++;
        }
        if (!isgl(word[i])) {
            res[res_index] = word[i];
            res_index++;
            i++;
        }
    }
}

void split(char* start_string, char* word_1, char* word_2) {
    int space_index = 0;
    int k, j, tmp_index;
    for (j = 0; j < strlen(start_string); j++) {
        if (start_string[j] == ' ') {
            space_index = j;
        }
    }
    for (k = 0; k < space_index; k++) {
        word_1[k] = start_string[k];
    }
    tmp_index = 0;
    for (k = space_index + 1; k < strlen(start_string); k++) {
        word_2[tmp_index] = start_string[k];
        tmp_index++;
    }
}

int main() {
    char res[1000] = " ", start_string[1000] = " ", word_1[1000] = " ", word_2[1000] = " ";
    while (1) {
        int res_index = 0;
        gets(start_string);
        split(start_string, word_1, word_2);
        res_index = sovle_first(word_1, res_index, res);
        solve_second(word_2, res_index, res);
        printf("%s\n", res);
        memset(start_string, 0, strlen(start_string));
        memset(word_1, 0, strlen(word_1));
        memset(word_2, 0, strlen(word_2));
        memset(res, 0, strlen(res));
    }
    return 0;
}