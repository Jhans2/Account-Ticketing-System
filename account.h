/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/

#include"commonHelpers.h"
#include"ticket.h"
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

struct UserLogin
{
	char account_holder[31];
	char login_name[11];
	char pass[9];
};
struct Demographic
{
	int birth_year;
	double hh_income;
	char country[31];
};
struct Account
{
	int account_no;
	char acc_type;
	struct UserLogin login_data;
	struct Demographic demo_data;
};



// Display and prompt user for account information.
void getAccount(struct Account* account_data, int greatest);

// Display and prompt user for user login data
void getUserLogin(struct UserLogin* login_data);

//Display and prompt user for demographic data
void getDemographic(struct Demographic* demo_data);

//Modify specific members of Account
void updateAccount(struct Account* account_data);

//Modify specific members of userlogin
void updateUserLogin(struct UserLogin* login_data);

//Modify specific members of Demographic
void updateDemographic(struct Demographic* demo_data);
#endif // !ACCOUNT_H_