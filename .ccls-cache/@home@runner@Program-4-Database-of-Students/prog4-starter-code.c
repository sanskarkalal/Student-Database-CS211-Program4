#include <stdio.h>

typedef struct {
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode{
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {
	StudentNode* pIDList;
	StudentNode* pHonorRollList;
	StudentNode* pAcademicProbationList;
	StudentNode* pFreshmanList;
	StudentNode* pSophomoreList;
	StudentNode* pJuniorList;
	StudentNode* pSeniorList;
} Database;

int main() {

	printf("CS 211, Spring 2023\n");
	printf("Program 4: Database of Students\n\n");

	printf("Enter E to start with an empty database, \n");
	printf("or F to start with a database that has information on students from a file.\n");
	printf("Your choice --> ");
	printf("Sorry, that input was invalid. Please try again.\n");
	
	printf("Enter the name of the file you would like to use: ");

	printf("\nEnter: \tC to create a new student and add them to the database,\n");
	printf("\tR to read from the database,\n");
	printf("\tD to delete a student from the database, or\n");
	printf("\tX to exit the program.\n");
	printf("Your choice --> ");
	printf("Invalid option. Try again.\n");

	printf("Enter the name of the new student: ");
	printf("Enter the ID of the new student: ");
	printf("Enter the GPA of the new student: ");
	printf("Enter the credit hours of the new student: ");
	printf("Successfully added the following student to the database!\n");

	printf("Select one of the following: \n");
	printf("\t1) Display the head (first 10 rows) of the database\n");
	printf("\t2) Display students on the honor roll, in order of their GPA\n");
	printf("\t3) Display students on academic probation, in order of their GPA\n");
	printf("\t4) Display freshmen students, in order of their name\n");
	printf("\t5) Display sophomore students, in order of their name\n");
	printf("\t6) Display junior students, in order of their name\n");
	printf("\t7) Display senior students, in order of their name\n");
	printf("\t8) Display the information of a particular student\n");
	printf("Your choice --> ");
	printf("Sorry, that input was invalid. Please try again.\n");
	
	printf("There are no students matching that criteria.\n\n");

	printf("Enter the id of the student to find: ");
	printf("Sorry, there is no student in the database with the id 6ABCDEFGH.\n");

	printf("Thanks for playing!\n");
	printf("Exiting...\n");
	
	return 0;
}