/*
Assignment #2 Milestone #4
Name: Jatin hans
student ID number: 141560201
Seneca email address: jhans2@myseneca.ca
course section code: ZDD
*/
#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_

#define LOWER_BOUND_PR -3;
#define UPPER_BOUND_PR 11;
int currentYear(void);
void clearStanadardInputBuffer(void);

// 1 This function get a valid integer from keyboard
int getInteger(void);

// 2
int getPositiveInteger(void);

//3 
double getDouble(void);

//4 
double getPositiveDouble(void);

//5
int getIntFromRange(int lower_bound, int upper_bound);

//6
char getCharOption(const char c_string_array[]);

//7
void getCString(char* name, int min_ch, int max_ch);

#endif // !COMMONHELPERS_H_