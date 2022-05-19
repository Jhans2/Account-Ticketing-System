/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/

#ifndef TICKET_H_
#define TICKET_H_
#include"account.h"
#include"accountTicketingUI.h"
struct Message
{
	char acc_type;
	char account_holder[31];
	char messaage[151];

};

struct Ticket
{
	int ticket_no;
	int account_no;
	int ticket_status;
	char subject[31];
	int counter_msg;
	struct Message array[21];
};

//Display ticket detail header for agent
void displayagentticketheader(void);

//Display tickets details for agent
void displayagentticket(struct Ticket* ticket);

//Display ticket detail header for customer
void displayuserticketheader(void);

//Display ticket detail for customer
void displayuserticket(struct Ticket* ticket);

// Display message as per respective ticket number
void message(struct Ticket* ticket);

//Prompt user for new ticket details
void getTicket(struct Ticket* ticket, int greatest);

//modify an existing ticket
void updateTicket(struct Ticket* ticket, const char* holder);

//modify ticket from agent menu
void updateTicketAgent(struct Ticket* ticket, const char* holder); //struct AccountTicketingData* account_tic

#endif // !TICKET_H_