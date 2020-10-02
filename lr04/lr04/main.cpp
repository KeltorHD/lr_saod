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
		printf("������ �������� ������!\n");
		return 0;
	}

	const char stop_word[COUNT_SEPARATOR]{ ' ', ',', '.', '!', '?', ';', '(', ')', '\n', '-' }; /*��� ����������*/
	bool isFirstWrite{ true }; /*��� ������������ ������ ������*/
	size_t counter_letter{}; /*������� ���� �����*/
	size_t word_counter[MAX_LETTER_NEED]{}; /*������� ���� � ������ �� 10 �������� ������������*/
	char* string = (char*)malloc(MAX_LETTER_WORD * sizeof(char)); /*������ ��� ���������� ������ � ���� ��� �� ����� > 8 ��������*/
	if (!string)
		return 0;

	/*���������� �������*/
	while (!feof(input))
	{
		string[counter_letter] = fgetc(input);

		if (is_separator(stop_word, string[counter_letter]) || (counter_letter >= MAX_LETTER_WORD))
			/*���� ����� ����������� ��� ���������� ������������ ����� �����*/
		{
			if (counter_letter < MAX_LETTER_NEED && counter_letter > 0) /*���� ����� ����� ������ 10, ��������� ��� �����*/
				word_counter[counter_letter]++;

			if (counter_letter > 9) /*���� ����� ����� ������ 8, �������� ��� � ������*/
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
				}printf("- �����, %d\n", counter_letter);
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

	/*����� ���������� � ������ ����*/
	for (size_t i = 0; i < MAX_LETTER_NEED; i++)
	{
		fprintf(output, "���������� ���� � ������ %d: %d\n", i + 1, word_counter[i]);
	}

	printf("������� ������� ���������!\n");

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
