// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   4
//  Description: Main logic/tester
//
// ===================================================================================
/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"accountTicketingUI.h"
#include"commonHelpers.h"
#include"account.h"
#include"ticket.h"

// Display and prompt user for account information.
void getAccount(struct Account* account_data, int greatest)
{

	/*printf("\nAccount Data: New Record\n");
	printf("----------------------------------------\n");
	printf("Enter the account number: ");
	account_data->account_no = getInteger();*/
	account_data->account_no = greatest;
	printf("\nNew Account Data (Account#:%d)", account_data->account_no);
	printf("\n");
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account_data->acc_type = getCharOption("AC");
}

// Display and prompt user for user login data
void getUserLogin(struct UserLogin* login_data)
{

	int valid = 0;
	printf("\nUser Login Data Input\n");
	printf("----------------------------------------\n");
	do
	{
		int space = 0;
		printf("Enter user login (10 chars max): ");
		getCString(login_data->login_name, 0, 10);
		int i;
		for (i = 0; login_data->login_name[i] != '\0'; i++)
		{
			if (isspace(login_data->login_name[i]))
			{
				space++;
			}
		}
		if (space > 0)
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			valid = 0;
		}
		else
		{
			valid = 1;
		}

	} while (valid == 0);
	printf("Enter the display name (30 chars max): ");
	getCString(login_data->account_holder, 0, 30);
	do
	{
		int digit = 0, upper = 0, lower = 0, symbol = 0, length;
		printf("Enter the password (must be 8 chars in length): ");
		getCString(login_data->pass, 8, 8);
		length = strlen(login_data->pass);
		int i;
		for (i = 0; i < length; i++)
		{
			if (isdigit(login_data->pass[i]))
			{
				digit++;
			}
			else if (isupper(login_data->pass[i]))
			{
				upper++;
			}
			else if (islower(login_data->pass[i]))
			{
				lower++;
			}
			else if (login_data->pass[i]!='(' && login_data->pass[i] != ')')
			{
				symbol++;
			}
		}
		if (digit == 2 && upper == 2 && lower == 2 && symbol == 2)
		{
			valid = 1;
		}
		else
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%c%c&*\n", 37, 94);
			valid = 0;
		}
		clearStanadardInputBuffer();
	} while (!valid);
}

//Display and prompt user for demographic data
void getDemographic(struct Demographic* demo_data)
{
	printf("\nDemographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	demo_data->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);
	printf("Enter the household Income: $");
	demo_data->hh_income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(demo_data->country, 0, 30);
	int i;
	for (i = 0; demo_data->country[i] != '\0'; i++)
	{
		demo_data->country[i] = toupper(demo_data->country[i]);
	}
	clearStanadardInputBuffer();
}

//Modify specific members of Account
void updateAccount(struct Account* account_data)
{
	int keepgo = 0;
	printf("\n");
	do
	{
		int selection;
		printf("Account: %d - Update Options\n", account_data->account_no);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account_data->acc_type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		if (selection == 1)
		{
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			account_data->acc_type = getCharOption("AC");
			/*printf("\n");*/
		}
		else if (selection == 2)
		{
			updateUserLogin(&account_data->login_data);
			printf("\n");
		}
		else if (selection == 3)
		{
			int dob = account_data->demo_data.birth_year;
			updateDemographic(&account_data->demo_data);
			account_data->demo_data.birth_year = dob;
			printf("\n");
		}
		else if (selection == 0)
		{
			keepgo = 1;
		}
	} while (keepgo == 0);
}

//Modify specific members of userlogin
void updateUserLogin(struct UserLogin* login_data)
{
	int valid = 0;
	do {
		int select;
		printf("\nUser Login: %s - Update Options\n", login_data->login_name);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", login_data->account_holder);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);
		if (select == 1)
		{
			printf("\nEnter the display name (30 chars max): ");
			getCString(login_data->account_holder, 0, 30);
		}
		if (select == 2)
		{
			int keepgoing = 0;
			do
			{
				int digit = 0, upper = 0, lower = 0, symbol = 0, length;
				printf("\nEnter the password (must be 8 chars in length): ");
				getCString(login_data->pass, 8, 8);
				length = strlen(login_data->pass);
				int i;
				for (i = 0; i < length; i++)
				{
					if (isdigit(login_data->pass[i]))
					{
						digit++;
					}
					else if (isupper(login_data->pass[i]))
					{
						upper++;
					}
					else if (islower(login_data->pass[i]))
					{
						lower++;
					}
					else
					{
						symbol++;
					}
				}
				if (digit == 2 && upper == 2 && lower == 2 && symbol == 2)
				{
					keepgoing = 1;
				}
				else
				{
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%c%c&*", 37, 94);
					keepgoing = 0;
				}
			} while (!keepgoing);
		}
		if (select == 0)
		{
			valid = 1;
		}
	} while (valid == 0);
}

//Modify specific members of Demographic
void updateDemographic(struct Demographic* demo_data)
{
	printf("\n");
	int valid = 0;
	do {
		int selection;
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%1.2lf)\n", demo_data->hh_income);
		printf("2) Country (current value: %s)\n", demo_data->country);
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);

		if (selection == 1)
		{
			printf("\nEnter the household Income: $");
			demo_data->hh_income = getPositiveDouble();
			printf("\n");
		}
		if (selection == 2)
		{
			printf("\nEnter the country (30 chars max.): ");
			getCString(demo_data->country, 0, 30);
			printf("\n");
			int i;
			for (i = 0; demo_data->country[i] != '\0'; i++)
			{
				demo_data->country[i] = toupper(demo_data->country[i]);
			}
		}
		if (selection == 0)
		{
			/*printf("\n");*/
			valid = 1;
		}
	} while (valid == 0);
}