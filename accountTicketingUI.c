/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"accountTicketingUI.h"
#include"commonHelpers.h"
#include"account.h"
#include"ticket.h"/*
using namespace AccountTicketingData;*/
// Load accounts
int loadAccounts(struct Account* account_data, int max_size)
{
	FILE* fp;
	int count = 0;
	char end = NULL;
	fp = fopen("accounts.txt", "r");
	if (fp != NULL) {
		while (end != EOF && count < max_size)
		{
			if (end == '\n')
			{
				count++;
			}
			end = getc(fp);
		}
	}
	fclose(fp);
	return count;
}

//Load Tickets
int loadTickets(struct Ticket* tickets, int max_size)
{
	FILE* fp;
	int count = 0;
	char end = NULL;
	fp = fopen("tickets.txt", "r");
	if (fp != NULL)
	{
		while (end != EOF && count < max_size)
		{
			if (end == '\n')
			{
				count++;
			}
			end = getc(fp);
		}
	}
	fclose(fp);
	return count;
}

int loadArchivedAccounts(int max_size)
{
	FILE* fp;
	int count = 0;
	char end = NULL;
	fp = fopen("accounts_arc.txt", "r");
	if (fp != NULL) {
		while (end != EOF && count < max_size)
		{
			if (end == '\n')
			{
				count++;
			}
			end = getc(fp);
		}
	}
	fclose(fp);
	return count;
}

int loadArchivedTickets(int max_size)
{
	FILE* fp;
	int count = 0;
	char end = NULL;
	fp = fopen("tickets_arc.txt", "r");
	if (fp != NULL) {
		while (end != EOF && count < max_size)
		{
			if (end == '\n')
			{
				count++;
			}
			end = getc(fp);
		}
	}
	fclose(fp);
	return count;
}

int loadmessagesarchived(void)
{
	int i = 0;
	FILE* fp = NULL;
	char character;
	fp = fopen("tickets_arc.txt", "r");
	character = getc(fp);
	while(character != EOF)
	{
		if (character == 'A' || character == 'C')
		{
			character = getc(fp);
			if (character == '|')
			{
				i = i + 1;
			}
		}
		character = getc(fp);
	}
	fclose(fp);
	return i;
}
//Load all the data for accounts from files
void populateAccounts(const char* filename, struct Account* account_data)
{
	/*struct Account accounts[15] = { 0 };*/
	int i = 0;
	char ch;
	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (i < 15 && fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]%c", &account_data[i].account_no, &account_data[i].acc_type, account_data[i].login_data.account_holder, account_data[i].login_data.login_name, account_data[i].login_data.pass, &account_data[i].demo_data.birth_year, &account_data[i].demo_data.hh_income, account_data[i].demo_data.country, &ch) == 9) {
			if (ch != '\n') { while (fgetc(fp) != '\n'); }
			i++;
		}

		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR");
	}
}

//Load all the data for tickets from files
void populateTickets(const char* filename, struct Ticket* ticket)
{
	//struct Ticket* ticket[17] = { 0 };
	int i = 0;
	char ch = { 0 };
	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (i < 17 && fscanf(fp, "%d|%d|%d|%[^|]|%d|", &ticket[i].ticket_no, &ticket[i].account_no, &ticket[i].ticket_status, ticket[i].subject, &ticket[i].counter_msg) == 5)
		{
			int j=0;
			while ( j < ticket[i].counter_msg && fscanf(fp, "%c|%[^|]|%[^|]%c", &ticket[i].array[j].acc_type, ticket[i].array[j].account_holder, ticket[i].array[j].messaage, &ch) == 4)
			{
				j++;
			}
			if (ch != '\n') { while (fgetc(fp) != '\n'); }
			i++;
		}

		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR");
	}
}



// Display formatted table header for summary 
void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

// Display formatted table header for account detail
void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

//Display record data for summary
void displayAccountSummaryRecord(const struct Account* account_data)
{
	printf("%05d %-9s %5d\n", account_data->account_no, account_data->acc_type == 'A' ? "AGENT" : "CUSTOMER", account_data->demo_data.birth_year);
}

//Display record data for account detail
void displayAccountDetailRecord(const struct Account* account_data)
{
	int length = 0, i = 0;
	for (i = 0; account_data->login_data.pass[i] != '\0'; i++)
	{
	}
	length = i;
	char password[9];

	for (i = 0; i < length; i++)
	{

		if (i % 2 == 0)
			password[i] = account_data->login_data.pass[i];
		else
			password[i] = '*';
	}
	password[length] = '\0';
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account_data->account_no, account_data->acc_type == 'A' ? "AGENT" : "CUSTOMER", account_data->demo_data.birth_year, account_data->demo_data.hh_income, account_data->demo_data.country, account_data->login_data.account_holder, account_data->login_data.login_name, password);
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStanadardInputBuffer();
	putchar('\n');
}

void applicationStartup(struct AccountTicketingData* account_tic)
{
	const char account_file[] = "accounts.txt";
	populateAccounts(account_file, account_tic->accounts);
	const char ticket_file[] = "tickets.txt";
	populateTickets(ticket_file, account_tic->tickets);
	int indexing;
	do {
		indexing = menuLogin(account_tic);
		if (indexing != -1) {
			if (account_tic->accounts[indexing].acc_type == 'A')
			{
				menuAgent(account_tic, &account_tic->accounts[indexing]);
			}
			else
			{
				menuCustomer(account_tic, indexing);
			}
		}

	} while (indexing != -1);
	if (indexing == -1)
	{
		printf("==============================================\n");
		printf("Account Ticketing System - Terminated\n");
		printf("==============================================\n");
	}

}

int menuLogin(struct AccountTicketingData* account_tic)
{
	int keepgo = 0;
	int index = 0;
	do
	{
		int selection;
		char  login_input[11] = { 0 };
		char password[9] = { 0 };
		char exit;
		int result1, result2;

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 1);
		if (selection == 0)
		{
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			exit = getCharOption("yYnN");
			printf("\n");
			if (exit == 'Y' || exit == 'y')
			{
				index = -1;
				keepgo = 1;
			}
		}
		else if (selection == 1)
		{
			int count = 3;
			int valid = 0;
			do
			{

				index = findAccountIndexByAcctNum(0, account_tic, 1);
				printf("User Login    : ");
				scanf(" %s", login_input);
				result1 = strcmp(account_tic->accounts[index].login_data.login_name, login_input);
				clearStanadardInputBuffer();
				printf("Password      : ");
				scanf(" %s", password);
				clearStanadardInputBuffer();
				result2 = strcmp(account_tic->accounts[index].login_data.pass, password);
				if (result1 != 0 || result2 != 0)
				{
					count--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", count);
					valid = 0;
				}
				else if (result1 == 0 && result2 == 0)
				{
					valid = 1;
					keepgo = 1;
					printf("\n");
				}
				if (count == 0)
				{
					valid = 1;
					printf("\nERROR:  Login failed!\n\n");
					pauseExecution();
				}
			} while (!valid);

		}
	} while (keepgo == 0);
	return index;
}

//Update changes to tickets file
void updateTicketFile(const char* filename, struct Ticket* ticket, int size)
{
	int i = 0;
	FILE* fp = fopen(filename, "w");
	if (fp != NULL)
	{
		while (i < size )
		{
			if (ticket[i].ticket_no > 0) 
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", ticket[i].ticket_no, ticket[i].account_no, ticket[i].ticket_status, ticket[i].subject, ticket[i].counter_msg);
				int j = 0;
				while (j < ticket[i].counter_msg)
				{
					fprintf(fp, "%c|%s|%s|", ticket[i].array[j].acc_type, ticket[i].array[j].account_holder, ticket[i].array[j].messaage);
					j++;
				}
				fprintf(fp, "\n");
			}
			i++;
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR\n");
	}
}

void ArchiveTicketFile(const char* filename, struct Ticket* ticket, int size,int i)
{
	FILE* fp = fopen(filename, "a");
	if (fp != NULL)
	{
		/*while (i < size && ticket[i].ticket_no > 0)
		{*/
		if (ticket[i].ticket_no > 0) 
		{
			fprintf(fp, "%d|%d|%d|%s|%d|", ticket[i].ticket_no, ticket[i].account_no, ticket[i].ticket_status, ticket[i].subject, ticket[i].counter_msg);
			int j = 0;
			while (j < ticket[i].counter_msg)
			{
				fprintf(fp, "%c|%s|%s|", ticket[i].array[j].acc_type, ticket[i].array[j].account_holder, ticket[i].array[j].messaage);
				j++;
			}
			fprintf(fp, "\n");
		}
		
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR\n");
	}
}

//Update changes to tickets file
void updateAccountFile(const char* filename, struct Account* account_data, int size)
{
	int i=0;
	FILE* fp = fopen(filename, "w");
	if (fp != NULL)
	{
		while (i < size ) 
		{
			if (account_data[i].account_no > 0) 
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s", account_data[i].account_no, account_data[i].acc_type, account_data[i].login_data.account_holder, account_data[i].login_data.login_name, account_data[i].login_data.pass, account_data[i].demo_data.birth_year, account_data[i].demo_data.hh_income, account_data[i].demo_data.country);
				fprintf(fp, "\n");
			}
			i++;
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR\n");
	}
}

void ArchiveAccountFile(const char* filename, struct Account* account_data, int size, int index)
{
	FILE* fp = fopen(filename, "a");
	if (fp != NULL)
	{
		/*while (i < size && account_data[i].account_no > 0)
		{*/
			fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s", account_data[index].account_no, account_data[index].acc_type, account_data[index].login_data.account_holder, account_data[index].login_data.login_name, account_data[index].login_data.pass, account_data[index].demo_data.birth_year, account_data[index].demo_data.hh_income, account_data[index].demo_data.country);
			fprintf(fp, "\n");
		/*}*/
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR\n");
	}
}

void menuAgent(struct AccountTicketingData* account_tic, const struct Account* user_detail)
{
	int keepgoing = 0;
	do {
		int selection;
		int index;
		printf("%s: %s (%d)\n", user_detail->acc_type == 'A' ? "AGENT" : "CUSTOMER", user_detail->login_data.account_holder, user_detail->account_no);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 12);
		if (selection == 1)
		{
			index = findAccountIndexByAcctNum(0, account_tic, 0);
			/*printf("\n");*/
			if (index == -1)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
			else
			{
				int greatest = 0;
				int i;
				for (i = 0; i < account_tic->ACCOUNT_MAX_SIZE; i++)
				{
					if (account_tic->accounts[i].account_no > greatest)
					{
						greatest = account_tic->accounts[i].account_no;
					}
				}
				getAccount(&account_tic->accounts[index], greatest + 1);
				getUserLogin(&account_tic->accounts[index].login_data);
				getDemographic(&account_tic->accounts[index].demo_data);
				printf("\n*** New account added! ***\n\n");
				pauseExecution();
			}
		}
		else if (selection == 2)
		{
			index = findAccountIndexByAcctNum(0, account_tic, 1);
			updateAccount(&account_tic->accounts[index]);
			printf("\n");
		}
		else if (selection == 3)
		{
			char exit;
			index = findAccountIndexByAcctNum(0, account_tic, 1);
			if (account_tic->accounts[index].account_no == user_detail->account_no)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else 
			{
				displayAccountDetailHeader();
				displayAccountDetailRecord(&account_tic->accounts[index]);
				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				exit = getCharOption("YN");
				if (exit == 'N')
				{
					printf("\n*** No changes made! ***\n\n");
					pauseExecution();
				}
				else if (exit == 'Y')
				{
					const char account_archive_file[] = "accounts_arc.txt";
					ArchiveAccountFile(account_archive_file, account_tic->accounts, account_tic->ACCOUNT_MAX_SIZE, index);
					printf("\n*** Account Removed! ***\n\n");
					int i;
					for (i = 0; i < account_tic->ACCOUNT_MAX_SIZE; i++)
					{
						
						if (account_tic->accounts[index].account_no == account_tic->tickets[i].account_no && account_tic->tickets[i].ticket_status == 0)
						{
							const char ticket_archive_file[] = "tickets_arc.txt";
							ArchiveTicketFile(ticket_archive_file,account_tic->tickets,account_tic->ACCOUNT_MAX_SIZE, i);
							account_tic->tickets[i].ticket_no = 0;
						}
						else if (account_tic->accounts[index].account_no == account_tic->tickets[i].account_no && account_tic->tickets[i].ticket_status == 1)
						{
							account_tic->tickets[i].ticket_no = 0;
						}

					}
					account_tic->accounts[index].account_no = 0;
					pauseExecution();
				}

			}
		}
		else if (selection == 4)
		{
			displayAllAccountSummaryRecords(account_tic);
		}
		else if (selection == 5)
		{
			displayAllAccountDetailRecords(account_tic);
		}
		else if (selection == 6)
		{
			printf("\n");
			do {
				displayagentticketheader();
				int i, valid = 0;/*
				int index = 0;*/
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++)
				{
					if (account_tic->tickets[i].counter_msg == 1 && account_tic->tickets[i].ticket_status == 1)
					{
						displayagentticket(&account_tic->tickets[i]);/*
						index = i;*/
					}
				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
				puts("Enter the ticket number to view the messages or");
				printf("0 to return to previous menu: ");
				selection = getPositiveInteger();
				
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++) {
					if (selection == account_tic->tickets[i].ticket_no && selection != 0)
					{
						message(&account_tic->tickets[i]);
						valid = 1;
					}
				}
				if (valid == 0 && selection != account_tic->tickets[i].ticket_no && selection != 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();

				}
				

			} while (selection != 0);
			printf("\n");

		}

		else if (selection == 7)
		{
			printf("\n");
			do {
				displayagentticketheader();
				int i, valid = 0;
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++)
				{
					if (account_tic->tickets[i].ticket_status == 1 && account_tic->tickets[i].ticket_no > 0)
					{
						displayagentticket(&account_tic->tickets[i]);
					}
				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
				puts("Enter the ticket number to view the messages or");
				printf("0 to return to previous menu: ");
				selection = getPositiveInteger();
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++) {
					if (selection == account_tic->tickets[i].ticket_no && selection != 0)
					{
						message(&account_tic->tickets[i]);
						valid = 1;
					}
				}
				if (valid == 0 && selection != account_tic->tickets[i].ticket_no && selection != 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();

				}
			} while (selection != 0);
			printf("\n");
		}
		else if (selection == 8)
		{
			printf("\n");
			do {
				displayagentticketheader();
				int i, valid = 0;
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++)
				{
					if (account_tic->tickets[i].ticket_status == 0 && account_tic->tickets[i].ticket_no > 0)
					{
						displayagentticket(&account_tic->tickets[i]);
					}
				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
				puts("Enter the ticket number to view the messages or");
				printf("0 to return to previous menu: ");
				selection = getPositiveInteger();
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++) {
					if (selection == account_tic->tickets[i].ticket_no && selection != 0)
					{
						message(&account_tic->tickets[i]);
						valid = 1;
					}
				}
				if (valid !=1 && selection != account_tic->tickets[i].ticket_no && selection != 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();

				}

			} while (selection != 0);
			printf("\n");
		}
		else if (selection == 9)
		{
			int choice, valid = 0;
			int n;
			printf("\nEnter ticket number: ");
			choice = getPositiveInteger();

			for (n = 0; n < account_tic->TICKET_MAX_SIZE && valid == 0; n++)
			{
				if (choice == account_tic->tickets[n].ticket_no)
				{
					valid = 1;
					updateTicketAgent(&account_tic->tickets[n], user_detail->login_data.account_holder);
				}
			}
		}
		else if (selection == 10)
		{
			char choice;
			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			choice = getCharOption("YN");
			int i,tickets_archived=0;
			for (i = 0; i < account_tic->TICKET_MAX_SIZE && choice == 'Y'; i++)
			{
				if (account_tic->tickets[i].ticket_status == 0 && account_tic->tickets[i].ticket_no > 0 )
				{
				const char ticket_archive_file[] = "tickets_arc.txt";
				ArchiveTicketFile(ticket_archive_file, account_tic->tickets, account_tic->ACCOUNT_MAX_SIZE, i);
				account_tic->tickets[i].ticket_no = 0;
				tickets_archived++;
				}
			}
			printf("\n*** %d tickets archived ***\n\n", tickets_archived);
			pauseExecution();
		}
		else if (selection == 11)
		{
			int accounts_archived=0;
			accounts_archived = loadArchivedAccounts(account_tic->ACCOUNT_MAX_SIZE);
			printf("\nThere are %d account(s) currently archived.\n\n", accounts_archived);
			pauseExecution();

		}
		else if (selection == 12)
		{
			int tickets_archived=0;
			int messages_archived = 0;
			tickets_archived = loadArchivedTickets(account_tic->ACCOUNT_MAX_SIZE);
			messages_archived = loadmessagesarchived();
		
			printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", tickets_archived, messages_archived);
			pauseExecution();
		}
		else if (selection == 0)
		{
			keepgoing = 1;
		}
	} while (keepgoing == 0);
	const char account_file[] = "accounts.txt";
	int accounts_saved = 0;
	updateAccountFile(account_file, account_tic->accounts, account_tic->ACCOUNT_MAX_SIZE);
	accounts_saved = loadAccounts(account_tic->accounts, account_tic->ACCOUNT_MAX_SIZE);
	const char ticket_file[] = "tickets.txt";
	int tickets_saved = 0;
	updateTicketFile(ticket_file, account_tic->tickets, account_tic->TICKET_MAX_SIZE);
	tickets_saved = loadTickets(account_tic->tickets, account_tic->TICKET_MAX_SIZE);
	printf("\nSaving session modifications...\n");
	printf("   %d account saved.\n", accounts_saved);
	printf("   %d tickets saved.\n", tickets_saved);
	printf("### LOGGED OUT ###\n\n");
};


// menu for customer
void menuCustomer(struct AccountTicketingData* account_tic, int index)
{
	int selection;
	do {
		printf("CUSTOMER: %s (%05d)\n", account_tic->accounts[index].login_data.account_holder, account_tic->accounts[index].account_no);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 4);
		if (selection == 1) {
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(&account_tic->accounts[index]);
			printf("\n");
			pauseExecution();

		}
		else if (selection == 2)
		{
			int greatest = 0;
			int i;
			int valid = 0;
			for (i = 0; i < account_tic->tickets[i].ticket_no; i++)
			{
				if (i + 1 >= account_tic->TICKET_MAX_SIZE)
				{
					printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
					pauseExecution();
					valid = 0;
				}
				else if (account_tic->tickets[i].ticket_no > greatest)
				{
					greatest = account_tic->tickets[i].ticket_no;
					valid = 1;
				}
			}
			if (valid == 1)
			{
				account_tic->tickets[i].account_no = account_tic->accounts[index].account_no;
				strcpy(account_tic->tickets[i].array->account_holder, account_tic->accounts[index].login_data.account_holder);
				getTicket(&account_tic->tickets[i], greatest);
			}
		}
		else if (selection == 3)
		{

			int choice, valid = 0;
			int n;
			printf("\nEnter ticket number: ");
			choice = getPositiveInteger();

			for (n = 0; n < account_tic->TICKET_MAX_SIZE && valid == 0; n++)
			{

				if (choice == account_tic->tickets[n].ticket_no && account_tic->accounts[index].account_no == account_tic->tickets[n].account_no && account_tic->tickets[n].ticket_status == 0)
				{
					printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
					pauseExecution();
					valid = 1;
					break;
				}
				else if (choice == account_tic->tickets[n].ticket_no && account_tic->accounts[index].account_no == account_tic->tickets[n].account_no)
				{
					valid = 1;
					updateTicket(&account_tic->tickets[n], account_tic->accounts[index].login_data.account_holder);

				}
			}
			if (valid != 1)
			{
				valid = 0;
				printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
				pauseExecution();
			}
		}
		else if (selection == 4)
		{
			int choicing;
			int m = 0;
			printf("\n");
			do {
				displayuserticketheader();
				int i, valid = 0;
				for (i = 0; account_tic->tickets[i].ticket_no > 0 && m == 0; i++)
				{
					if (account_tic->accounts[index].account_no == account_tic->tickets[i].account_no)
					{
						displayuserticket(&account_tic->tickets[i]);
						m = 0;
					}
				}
				printf("------ ------ ------------------------------ --------\n\n");
				puts("Enter the ticket number to view the messages or");
				printf("0 to return to previous menu: ");
				choicing = getPositiveInteger();
				for (i = 0; i < account_tic->TICKET_MAX_SIZE; i++) {

					if (choicing == account_tic->tickets[i].ticket_no && account_tic->accounts[index].account_no == account_tic->tickets[i].account_no && choicing != 0)
					{
						message(&account_tic->tickets[i]);
						valid = 1;
					}
				}

				if (valid == 0 && (choicing != account_tic->tickets[i].ticket_no || account_tic->accounts[index].account_no != account_tic->tickets[i].account_no) && choicing != 0)
				{
					printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					pauseExecution();
				}

			} while (choicing != 0);
			printf("\n");
		}

	} while (selection != 0);

	const char ticket_file[] = "tickets.txt";
	int tickets_saved=0;
	updateTicketFile(ticket_file, account_tic->tickets, account_tic->TICKET_MAX_SIZE);
	tickets_saved = loadTickets(account_tic->tickets, account_tic->TICKET_MAX_SIZE);
	printf("\nSaving session modifications...\n");
	printf("   %d tickets saved.\n",tickets_saved);
	printf("### LOGGED OUT ###\n\n"); 

	
}


////search the array received in argument 2 for a match on a desired account number.
int findAccountIndexByAcctNum(int account_no, struct AccountTicketingData* account_tic, int prompt)
{
	int i = 0;
	int index;
	int keepGo = 0;
	int acc;

	if (prompt != 0)
	{
		printf("\nEnter the account#: ");
		acc = getInteger();
	}
	else if (prompt == 0)
	{
		acc = account_no;
	}
	do
	{
		if (account_tic->accounts[i].account_no == acc)
		{
			keepGo = 1;
			index = i;
		}
		i++;
	} while (keepGo == 0 && i < account_tic->ACCOUNT_MAX_SIZE);

	if (keepGo == 0)
	{
		index = -1;
	}
	return index;
}



//Display a summary view of all the valid account records.
void displayAllAccountSummaryRecords(const struct AccountTicketingData account_tic[])
{
	printf("\n");
	displayAccountSummaryHeader();
	int i;
	for (i = 0; i <= account_tic->ACCOUNT_MAX_SIZE; i++) {
		if (account_tic->accounts[i].account_no > 0)
		{
			displayAccountSummaryRecord(&account_tic->accounts[i]);
		}
	}
	printf("\n");
	pauseExecution();
}


//Display a detailed view of all the valid account records.
void displayAllAccountDetailRecords(const struct AccountTicketingData account_tic[])
{
	printf("\n");
	displayAccountDetailHeader();
	int i;
	for (i = 0; i <= account_tic->ACCOUNT_MAX_SIZE; i++)
	{
		if (account_tic->accounts[i].account_no > 0)
		{
			displayAccountDetailRecord(&account_tic->accounts[i]);
		}

	}
	printf("\n");
	pauseExecution();
}

//Display ticket detail header for agent
void displayagentticketheader(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");

}

//Display tickets detail for agent
void displayagentticket(struct Ticket* ticket)
{
	printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket->ticket_no, ticket->account_no, ticket->array->account_holder, ticket->ticket_status == 1 ? "ACTIVE" : "CLOSED", ticket->subject, ticket->counter_msg);
}


//Display ticket detail header for customer
void displayuserticketheader(void)
{

	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");


}

void displayuserticket(struct Ticket* ticket)
{
	printf("%06d %-6s %-30s %5d\n", ticket->ticket_no, ticket->ticket_status == 1 ? "ACTIVE" : "CLOSED", ticket->subject, ticket->counter_msg);
}

void message(struct Ticket* tickets)
{

	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", tickets->ticket_no, tickets->ticket_status == 1 ? "ACTIVE" : "CLOSED", tickets->subject);
	printf("================================================================================\n");
	int i;
	for (i = 0; i < tickets->counter_msg; i++)
	{
		printf("%s (%s):\n", tickets->array[i].acc_type == 'A' ? "AGENT" : "CUSTOMER", tickets->array[i].account_holder);
		printf("   %s\n", tickets->array[i].messaage);
		printf("\n");
		if ((i + 1) % 5 == 0 && (i != 0 && i != 19) && tickets->counter_msg > 5)
		{
			pauseExecution();
		}
	}
	pauseExecution();
}




