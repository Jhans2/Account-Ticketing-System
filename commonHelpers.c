/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"commonHelpers.h"
#include<time.h>

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system int currentYear(void) 

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStanadardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}
}


// This function get a valid integer from keyboard
int getInteger(void)
{
	int value;
	int keepgo;
	char newline = 'x';
	do
	{
		scanf("%d%c", &value, &newline);
		if (newline == '\n')
		{
			keepgo = 1;
		}
		else
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
			keepgo = 0;
		}
	} while (keepgo == 0);
	return value;

}

int getPositiveInteger(void)
{
	int value;
	char newline;
	do
	{
		scanf("%d%c", &value, &newline);
		if (value < 0)
		{
			printf("ERROR: Value must be positive or zero: ");
		}
	} while (value < 0);
	return value;
}

 //s
double getDouble(void) {
char newLine = 'x';
double value;
int valid;
do
{
	scanf("%lf%c", &value, &newLine);
	if (newLine == '\n')
	{
		valid = 1;
		return value;
	}
	else {
		clearStanadardInputBuffer();
		printf("ERROR: Value must be a double floating-point number: ");
		valid = 0;
	}

} while (valid == 0);
return value;
}

double getPositiveDouble(void) {

	double val;
	int valid;
	do
	{
		val = getDouble();

		if (val <= 0.0) {
			printf("ERROR: Value must be a positive double floating-point number: ");
			valid = 0;
		}
		else
		{
			valid = 1;
		}

	} while (valid == 0);
	return val;
}


int getIntFromRange(int lower_bound, int upper_bound)
{
	int value;
	int keepgoing = 1;
	do
	{
		value = getInteger();
		if (value<lower_bound || value > upper_bound)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
			keepgoing = 0;
		}
		else if (value >= lower_bound && value <= upper_bound)
		{
			keepgoing = 1;
		}
		else
		{
			clearStanadardInputBuffer();
		}
	} while (keepgoing == 0);
	return value;
}


char getCharOption(const char c_string_array[])
{
	char nl = 'x';
	char single_ch;
	int keepgoing = 0;

	do
	{
		scanf("%c%c", &single_ch, &nl);
		if (nl == '\n')
		{
			int i;
			for (i = 0; c_string_array[i] != '\0' && !keepgoing; i++)
			{
				if (c_string_array[i] == single_ch)
				{
					keepgoing = 1;
				}
			}
		}
		else
		{
			clearStanadardInputBuffer();
		}
		if (keepgoing == 0)
		{
			printf("ERROR: Character must be one of [%s]: ", c_string_array);
		}
	} while (keepgoing == 0);
	return single_ch;
}


void getCString(char* name, int min_ch, int max_ch)
{
	int length = 0;
	char c_string_array[151];
	int valid = 0;
	do
	{
		scanf(" %[^\n]", c_string_array);
		int i;
		for (i = 0; c_string_array[i] != '\0'; i++)
		{
		}
		length = i;
		if (length != min_ch && min_ch == max_ch)
		{
			printf("ERROR: String length must be exactly %d chars: ", min_ch);
			clearStanadardInputBuffer();
		}
		else if (length > max_ch)
		{
			printf("ERROR: String length must be no more than %d chars: ", max_ch);
			clearStanadardInputBuffer();
		}
		else if (length < min_ch)
		{
			printf("ERROR: String length must be between %d and %d chars: ", min_ch, max_ch);
			clearStanadardInputBuffer();
		}
		else
		{
			valid = 1;
		}
	} while (valid == 0);
	int i = 0;
	for (i = 0; i < max_ch; i++)
	{
		name[i] = c_string_array[i];
	}
	name[max_ch] = '\0';
};