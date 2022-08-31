/* 
ƒл€ малых размеров массива (N) быстра€ сортировка может работать медленнее простых методов.
ќтсюда по€вл€етс€ иде€ улучшить быструю сортировку - если N становитс€ меньше некоторого числа M (константы отсечени€), то можно переключитьс€ на простую сортировку.
«адача - написать программу, вычисл€ющую константу отсечени€ M.
ƒл€ этого несколько раз сортируйте большие случайные массивы и определите среднюю константу отсечени€ и выведите ее в стандартный поток вывода.
ѕримечание. ѕростой метод сортировки выбирайте на свое усмотрение. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <time.h>
#define ull unsigned long long

int shell(int *mas, int num)
{
    for (int gap = num / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < num; i += 1)
        {
            int temp = mas[i];
            int j;
            for (j = i; j >= gap && mas[j - gap] > temp; j -= gap)
                mas[j] = mas[j - gap];

            mas[j] = temp;
        }
    }
    return 0;
}

void quick(int left, int right, int *mas)
{
    int i, j;
    int mid, tmp;
    i = left;
    j = right;
    mid = mas[(left + right) / 2];
    do
    {
        while (mas[i] < mid)
            i++;
        while (mas[j] > mid)
            j--;
        if (i <= j)
        {
            tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > left)
        quick(left, j, mas);
    if (i < right)
        quick(i, right, mas);
}

int main()
{
    int m_mas[100], tmp_1[100], tmp_2[100]; // ћассивы дл€ сортировок
    int res[100], len = 2, max = 0, res_m = 0; // ћассив со всеми константами отсечени€, изначальна€ длина массива, две переменные дл€ результата
    int filter_res[200] = { 0 }; // —татистический массив дл€ анализа самой частой константы отсечени€
    ull simple_start = 0, simple_end = 0, simple_res = 0; // ѕеременные дл€ записи результатов __rdtsc()
    ull quick_start = 0, quick_res = 0, quick_end = 0;
    int M = 0;
    for (int i = 0; i < 100; i++) // ƒелаю 100 итераций дл€ удобства и точности
    {
        srand(time(NULL));
        for (int j = 0; j < 100; j++) // √енераци€ значений массива
        {
            m_mas[j] = rand() % 10000;
        }
        len = 2;
        M = 0;
        simple_res = 0; quick_res = 0;
        do // —ортировка массива и его наращивание дл€ определени€ константы отсечени€
        {
            for (int i = 0; i < len; i++)
            {
                tmp_1[i] = m_mas[i];
                tmp_2[i] = m_mas[i];
            }

            simple_start = __rdtsc();
            shell(tmp_1, len);
            simple_end = __rdtsc();
            simple_res = simple_end - simple_start;

            quick_start = __rdtsc();
            quick(0, len - 1, tmp_2);
            quick_end = __rdtsc();
            quick_res = quick_end - quick_start;
            len++;
            M = len;
        } while (simple_res <= quick_res && len < 101); // ”словие, при котором можно записывать константу отчесени€
        res[i] = M; // ≈е запись в массив с результатами
    }
    quick(0, 100 - 1, res);
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 100; j++) {
            if (res[j] == i && i != res[99]) { // —читаем количество определенных результатов в массиве
                filter_res[i]++;
            }
        }
    }
    for (int k = 0; k < 200; k++) { // «десь индекс = длина массива 
        if (filter_res[k] >= max) { // Ќахождение самого частого
            max = filter_res[k];
            res_m = k;
        }
    }
    printf("%d", res_m);
}
