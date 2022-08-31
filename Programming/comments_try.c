#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void gen_out_name(char *file_name, char *new_name)
{ //Формирование нового названия файла
	strcpy(new_name, file_name)	;
	new_name[strlen(file_name) - 1] = 'w'; new_name[strlen(file_name)] = 'c';
}

int is_string(char prev, char sym, int m_quote, int it, int s_quote)
{ // Проверка на то, что перед нами строка, а не, например, символ кавычки внутри строки
	if (sym == '"' && prev != '\\' && s_quote == 0) return 1;
	if (sym == '"' && prev == '\\' && s_quote == 0 && m_quote == 0) return 1;
	if (m_quote == 1 && sym == '\n' && prev == '\\') return 0;
	if (m_quote == 1 && sym == '\n' && prev != '\\' )  return 1;
	if (prev == '"' && it == 1) return 1;
	return 0;
}
int is_string_o(char prev, char sym, int m_quote, int it, int s_quote) {
	if (sym == '\'' && prev != '\\' && m_quote == 0) return 1;
	if (s_quote == 1 && sym == '\n' && prev != '\\') return 1;
	if (prev == '\'' && it == 1) return 1;
	return 0;
}

void solve(char *file_name)
{
	char prev_sym, sym; char out_file[256] = " ";
	int s_comment = 0, m_quote = 0, m_comment = 0, s_quote = 0, m_comment_sym = 0;
	FILE *sin, *sout;
	if(file_name[strlen(file_name) - 1] == '\n') file_name[strlen(file_name) - 1] = '\0';
	int it = 0;
	gen_out_name(file_name, out_file);
	sin = fopen(file_name, "r");
	sout = fopen(out_file, "w");
	prev_sym = fgetc(sin);
	while (!feof(sin))
	{
		sym = fgetc(sin);
		it++;
		if (is_string(prev_sym, sym, m_quote, it, s_quote))
		{
			if (m_quote == 1) m_quote = 0; // Пояснение: если флаг присутствия кавычки = 1 --> значит, что кавычки уже открыты и следовательно сейчас мы в конце строки
			else if (m_comment == 0 && s_comment == 0 && s_quote == 0) m_quote = 1;
		}
		if (is_string_o(prev_sym, sym, m_quote, it, s_quote))
		{
			if (s_quote == 1) s_quote = 0; // Пояснение: если флаг присутствия кавычки = 1 --> значит, что кавычки уже открыты и следовательно сейчас мы в конце строки
			else if (m_comment == 0 && s_comment == 0 && m_quote == 0) s_quote = 1;
		}
		if ((s_quote == 0 && m_quote == 0) && prev_sym == '/' && sym == '*' && s_comment == 0) {
			m_comment = 1; // Старт многострочного комментария
			prev_sym = sym;
			sym = fgetc(sin);
			while (1) {
				m_comment_sym++;
				prev_sym = sym;
				sym = fgetc(sin);
				if (((prev_sym == '*' && sym == '/') || feof(sin)) && m_comment_sym != 0) break;
			}
		}
		if ((s_quote == 0 && m_quote == 0) && prev_sym == '/' && sym == '/' && m_comment == 0) s_comment = 1; // Старт однострочного комментария
		if (m_comment == 0 && s_comment == 0) {
			fputc(prev_sym, sout);
			if (feof(sin)) break;
		}
		if (m_comment == 1 && m_comment_sym != 0)
		{
			sym = fgetc(sin);
			m_comment = 0; // Проходим мимо символа без его записи в файл. Многострочный комментарий закончился
			m_comment_sym = 0;
			fputc(' ', sout);
		}
		if (s_comment == 1 && prev_sym != '\\' && sym == '\n')
		{ // Проверка однострочного комментария на символ переноса строки. Нахождение конца однострочного комментария
			s_comment = 0;
			fputc('\n', sout);
		}
		prev_sym = sym;
	}
	fclose(sin);
	fclose(sout);
}

int main(void)
{
	FILE *start_file;
	int count_of_files, i = 0;
	char file_name[256] = " ";
	start_file = fopen("project.txt", "r");
	fscanf(start_file, "%d", &count_of_files);
	fgets(file_name, 256, start_file);
	while (i < count_of_files)
	{
		fgets(file_name, 256, start_file);
		solve(file_name);
		memset(file_name, 0, strlen(file_name));
		i++;
	}
	fclose(start_file);
	return 0;
}