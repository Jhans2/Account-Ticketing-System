/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/
#include"commonHelpers.h"
#include"account.h"
#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_

struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array 
};

// Display formatted table header for summary 
void displayAccountSummaryHeader(void);

// Display formatted table header for account detail
void displayAccountDetailHeader(void);

//Display record data for summary
void displayAccountSummaryRecord(const struct Account* account_data);

//Display record data for account detail
void displayAccountDetailRecord(const struct Account* account_data);

//the entry point to the application logic.
void applicationStartup(struct AccountTicketingData* account_tic);

//Prompt the user to select option in main menu.
int menuLogin(struct AccountTicketingData* account_tic);

//main menu for an agent to manage the accounts
void menuAgent(struct AccountTicketingData* account_tic, const struct Account* user_detail);

// menu for customer
void menuCustomer(struct AccountTicketingData* account_tic, int index);

//search the array received in argument 2 for a match on a desired account number.
int findAccountIndexByAcctNum(int account_no, struct AccountTicketingData* account_tic, int prompt);

//Display a summary view of all the valid account records.
void displayAllAccountSummaryRecords(const struct AccountTicketingData account_tic[]);

//Display a detailed view of all the valid account records.
void displayAllAccountDetailRecords(const struct AccountTicketingData account_tic[]);

// Pause execution until user enters the enter key. 
void pauseExecution(void);

//load accounts
int loadAccounts(struct Account* account_data, int max_size);

//load tickets
int loadTickets(struct Ticket* tickets, int max_size);

//load archived accounts
int loadArchivedAccounts(int max_size);

//load archived tickets
int loadArchivedTickets(int max_size);

//Load all the data for tickets from files
void populateTickets(const char* filename, struct Ticket* ticket);

//Load all the data for accounts from files
void populateAccounts(const char* filename, struct Account* account_data);

//Update changes to tickets file
void updateTicketFile(const char* filename, struct Ticket* ticket, int size);

//Update changes to tickets file
void updateAccountFile(const char* filename, struct Account* account_data, int size);

#endif // !ACCOUNTTICKETINGUI_H_
