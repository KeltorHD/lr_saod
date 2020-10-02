#define _CRT_SECURE_NO_WARNINGS
#define MAX_LETTER_NEED 10
#define MAX_LETTER_WORD 40
#define COUNT_SEPARATOR 10

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

bool is_separator(const char* stop_word, char element);

int main()
{
	system("chcp 1251>nul");

	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");
	if (!input || !output)
	{
		printf("Ошибка открытия файлов!\n");
		return 0;
	}

	const char stop_word[COUNT_SEPARATOR]{ ' ', ',', '.', '!', '?', ';', '(', ')', '\n', '-' }; /*все сепараторы*/
	bool isFirstWrite{ true }; /*для отслеживания первой записи*/
	size_t counter_letter{}; /*счетчик букв слова*/
	size_t word_counter[MAX_LETTER_NEED]{}; /*счетчик слов с длиной до 10 символов включительно*/
	char* string = (char*)malloc(MAX_LETTER_WORD * sizeof(char)); /*строка для возможного вывода в файл при ее длине > 8 символов*/
	if (!string)
		return 0;

	/*выполнение задания*/
	while (!feof(input))
	{
		string[counter_letter] = fgetc(input);

		if (is_separator(stop_word, string[counter_letter]) || (counter_letter >= MAX_LETTER_WORD))
			/*если слово закончилось или достигнута максимальная длина слова*/
		{
			if (counter_letter < MAX_LETTER_NEED && counter_letter > 0) /*если длина слова меньше 10, учитываем это слово*/
				word_counter[counter_letter]++;

			if (counter_letter > 9) /*если длина слова больше 8, печатаем его в файлик*/
			{
				if (!isFirstWrite)
				{
					fprintf(output, ", ");
				}
				for (size_t i = 0; i < counter_letter; i++)
				{
					fprintf(output, "%c", string[i]);
				}
				if (isFirstWrite) isFirstWrite = false;
			}

			if (counter_letter)
			{
				for (size_t i = 0; i < counter_letter; i++)
				{
					printf("%c", string[i]);
					//printf("%c", string[i]);
				}printf("- слово, %d\n", counter_letter);
			}
			counter_letter = 0;
		}
		else
		{
			counter_letter++;
		}
	}
	if (!isFirstWrite)
		fprintf(output, ".\n");

	/*вывод информации о длинах слов*/
	for (size_t i = 0; i < MAX_LETTER_NEED; i++)
	{
		fprintf(output, "Количество слов с длиной %d: %d\n", i + 1, word_counter[i]);
	}

	printf("Задание успешно выполнено!\n");

	free(string);
	fclose(input);
	fclose(output);

	return 1;
}

bool is_separator(const char* stop_word, char element)
{
	bool is_sep{ false };
	for (size_t i = 0; i < COUNT_SEPARATOR; i++)
	{
		//printf("%c, %c, %d\n", stop_word[i], element, stop_word[i] == element);
		if (stop_word[i] == element)
		{
			is_sep = true;
			break;
		}
	}
	return is_sep;
}
