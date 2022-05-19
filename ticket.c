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
#include"ticket.h"

void getTicket(struct Ticket* ticket, int greatest)
{
	ticket->ticket_no = greatest + 1;
	printf("\nNew Ticket (Ticket#:%06d)", ticket->ticket_no);
	printf("\n----------------------------------------\n");
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(ticket->subject, 0, 30);
	printf("\n");
	printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(ticket->array->messaage, 0, 150);
	clearStanadardInputBuffer();
	printf("\n*** New ticket created! ***\n\n");
	ticket->array[ticket->counter_msg].acc_type = 'C'; // changes**************************************************8
	ticket->counter_msg++;
	ticket->ticket_status = 1;
	pauseExecution();
}

void updateTicket(struct Ticket* ticket, const char* holder)
{
	int keepgo = 0;
	printf("\n");
	do
	{
		int selection;
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticket_no);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->ticket_status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticket->subject);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		printf("\n");
		if (selection == 1)
		{
			printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
			getCString(ticket->subject, 0, 30);
			printf("\n");
		}
		else if (selection == 2)
		{
			if (ticket->counter_msg >= 20)
			{
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
			}
			else
			{
				int index;
				index = ticket->counter_msg;
				printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(ticket->array[index].messaage, 0, 150);
				/*strcpy(ticket->array[index].account_holder, ticket->array[index - 1].account_holder);*/
				strcpy(ticket->array[index].account_holder, holder);
				/*strcpy(ticket->array[index].acc_type, ticket->array[index - 1].acc_type);*/ //changes*************
				ticket->array[ticket->counter_msg].acc_type = 'C';
				ticket->counter_msg++;
				printf("\n");
			}

		}
		else if (selection == 3)
		{
			char close;
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			close = getCharOption("YN");
			if (close == 'Y')
			{
				if (ticket->counter_msg < 20)
				{
					char messages;
					printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
					messages = getCharOption("YN");
					if (messages == 'Y') {
						int index = ticket->counter_msg;
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(ticket->array[index].messaage, 0, 150);
						/*strcpy(ticket->array[index].account_holder, ticket->array[index - 1].account_holder);*/
						strcpy(ticket->array[index].account_holder, holder);
						/*strcpy(ticket->array[index].acc_type, ticket->array[index - 1].acc_type);*/ //changes*************
						ticket->array[ticket->counter_msg].acc_type = 'C';
						ticket->counter_msg = ticket->counter_msg + 1;
						clearStanadardInputBuffer();
					}
					else if (messages == 'N')
					{
					}
				}
				else if (ticket->counter_msg >= 20)
				{
				}
				ticket->ticket_status = 0;
				printf("\n*** Ticket closed! ***\n\n");
				keepgo = 1;
				pauseExecution();
			}
			else if (close == 'N')
			{
				printf("\n*** No changes made! ***\n\n");
				pauseExecution();
			}
		}
		else if (selection == 0)
		{
			pauseExecution();
			keepgo = 1;
		}
	} while (keepgo == 0);
}

void updateTicketAgent(struct Ticket* ticket,const char* holder)
{
	int keepgoing = 0;
	printf("\n");
	do
	{
		int selection;
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticket_no);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->ticket_status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticket->subject);
		printf("Acct#   : %d\n", ticket->account_no);
		printf("Customer: %s\n", ticket->array->account_holder);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		printf("\n");

		if (selection == 1)
		{
			if (ticket->ticket_status == 0)
			{
				printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
			}
			else
			{
				if (ticket->counter_msg >= 20)
				{
					printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
				}
				else
				{
					int index;
					index = ticket->counter_msg;
					printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(ticket->array[index].messaage, 0, 150);
					/*strcpy(ticket->array[index].account_holder, ticket->array[index - 1].account_holder);*/
					strcpy(ticket->array[index].account_holder, holder);
					ticket->array[ticket->counter_msg].acc_type = 'A';
					printf("\n");
					ticket->counter_msg++;
				}
			}

		}
		else if (selection == 2)
		{
			if (ticket->ticket_status == 0)
			{
				printf("ERROR: Ticket is already closed!\n\n");
			}
			else {
				char close;
				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				close = getCharOption("YN");
				if (close == 'Y')
				{
					if (ticket->counter_msg < 20)
					{
						int index;
						index = ticket->counter_msg;
						char messages;
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
						messages = getCharOption("YN");
						if (messages == 'Y') {
							printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
							getCString(ticket->array[index].messaage, 0, 150);
							/*strcpy(ticket->array[index].account_holder, ticket->array[index - 1].account_holder);*/
							strcpy(ticket->array[index].account_holder, holder);
							ticket->array[ticket->counter_msg].acc_type = 'A';
							ticket->counter_msg = ticket->counter_msg + 1;
							clearStanadardInputBuffer();
						}
						else if (messages == 'N')
						{
						}
					}
					else if (ticket->counter_msg >= 20)
					{
					}
					ticket->ticket_status = 0;
					printf("\n*** Ticket closed! ***\n\n");
				}
				else if (close == 'N')
				{
					printf("\n*** No changes made! ***\n\n");
				}
			}
		}
		else if (selection == 3)
		{
			if (ticket->ticket_status == 0)
			{


				char choice;
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				choice = getCharOption("YN");
				if (choice == 'Y')
				{
					ticket->ticket_status = 1;
					printf("\n*** Ticket re-opened! ***\n\n");
				}
				else if ('N')
				{
					printf("\n");
				}
			}
			else if (ticket->ticket_status == 1)
			{
				printf("ERROR: Ticket is already active!\n\n");
			}
		}
		else if (selection == 0)
		{
			keepgoing = 1;
		}
	} while (keepgoing == 0);
}