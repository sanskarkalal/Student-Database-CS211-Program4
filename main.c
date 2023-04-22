#include "stdlib.h"
#include "string.h"
#include <stdio.h>

// struct Student contains the student's name, ID, GPA, and credit hours
typedef struct {
  char *name;
  char *id;
  double gpa;
  int creditHours;
} Student;

// struct StudentNode contains a pointer to a Student and a pointer to the next
typedef struct StudentNode {
  Student *pStudent;
  struct StudentNode *pNext;
} StudentNode;


// struct Database contains pointers to the head of each list
typedef struct {
  StudentNode *pIDList;
  StudentNode *pHonorRollList;
  StudentNode *pAcademicProbationList;
  StudentNode *pFreshmanList;
  StudentNode *pSophomoreList;
  StudentNode *pJuniorList;
  StudentNode *pSeniorList;
} Database;


// typedefs for the structs and pointers to the structs
typedef Database *Databaseptr;
typedef StudentNode *StudentNodeptr;
typedef Student *Studentptr;


///@brief: Free the memory allocated for the database
///@param: database - pointer to the database
void FreeMemory(Databaseptr *database) {
  StudentNodeptr curr;
  StudentNodeptr temp;
  curr = (*database)->pIDList;

  // Free the memory allocated for each student in the ID list
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp->pStudent->name);
    free(temp->pStudent->id);
    free(temp->pStudent);
    free(temp);
  }

  // Free the memory allocated for each student in the honor roll list
  curr = (*database)->pHonorRollList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

  // Free the memory allocated for each student in the academic probation list
  curr = (*database)->pAcademicProbationList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

  // Free the memory allocated for each student in the freshman list
  curr = (*database)->pFreshmanList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

  // Free the memory allocated for each student in the sophomore list
  curr = (*database)->pSophomoreList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

  // Free the memory allocated for each student in the junior list
  curr = (*database)->pJuniorList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

  // Free the memory allocated for each student in the senior list
  curr = (*database)->pSeniorList;
  while (curr != NULL) {
    temp = curr;
    curr = curr->pNext;
    free(temp);
  }

}


///@brief: removes a student from the list
///@param: head - pointer to the head of the list
///@param: id - the id of the student to remove
StudentNodeptr removeFromList(StudentNodeptr *head, const char *id) {
  StudentNodeptr curr = *head;
  StudentNodeptr prev = NULL;

  // Traverse the list to find the student with the given ID
  while (curr != NULL) {
    if (strcmp(curr->pStudent->id, id) == 0) {
      if (prev == NULL) {
        *head = curr->pNext;
      } else {
        prev->pNext = curr->pNext;
      }
      return curr;
    }
    prev = curr;
    curr = curr->pNext;
  }

  // If the student is not found, return NULL
  return NULL;
}


///@brief: removes a student from the database
///@param: database - pointer to the database
///@param: id - the id of the student to remove
void deleteStudent(Databaseptr database, const char *id) {
  if (database == NULL || id == NULL) {
    printf("Error: Invalid input.\n");
    return;
  }

    // Remove the student from the ID list
  StudentNodeptr removedNode = removeFromList(&database->pIDList, id);

  // If the student is not found, print an error message
  if (removedNode == NULL) {
    printf("Sorry, there is no student in the database with the id %s.\n", id);
    return;
  }

  // Remove the student from the other lists
  removeFromList(&database->pHonorRollList, id);
  removeFromList(&database->pAcademicProbationList, id);
  removeFromList(&database->pFreshmanList, id);
  removeFromList(&database->pSophomoreList, id);
  removeFromList(&database->pJuniorList, id);
  removeFromList(&database->pSeniorList, id);

  // Free the memory allocated for the student
  free(removedNode->pStudent->name);
  free(removedNode->pStudent->id);
  free(removedNode->pStudent);
  free(removedNode);
}


///@brief: inserts a student in an alphanumeric order
///@param: head - pointer to the head of the list
///@param: newStudent - pointer to the new student to insert
void insertSorted(StudentNodeptr *head, StudentNodeptr *newStudent) {
  // If the list is empty or the new student's ID is less than the current
  // head's ID
  if (*head == NULL ||
      strcmp((*newStudent)->pStudent->id, (*head)->pStudent->id) < 0) {
    (*newStudent)->pNext = *head;
    *head = *newStudent;
  } else {
    // Traverse the list to find the correct position to insert the new student
    StudentNodeptr curr = *head;
    while (curr->pNext != NULL &&
           strcmp((*newStudent)->pStudent->id, curr->pNext->pStudent->id) > 0) {
      curr = curr->pNext;
    }

    // Insert the new student after the current node
    (*newStudent)->pNext = curr->pNext;
    curr->pNext = *newStudent;
  }
}


///@brief: inserts a student in an alphabetical order
///@param: head - pointer to the head of the list
///@param: newStudent - pointer to the new student to insert
void insertSortedByName(StudentNodeptr *head, StudentNodeptr *newStudent) {
  // If the list is empty or the new student's name is less than the current
  // head's name
  if (*head == NULL ||
      strcmp((*newStudent)->pStudent->name, (*head)->pStudent->name) < 0) {
    (*newStudent)->pNext = *head;
    *head = *newStudent;
  } else {
    // Traverse the list to find the correct position to insert the new student
    StudentNodeptr curr = *head;
    while (curr->pNext != NULL && strcmp((*newStudent)->pStudent->name,
                                         curr->pNext->pStudent->name) > 0) {
      curr = curr->pNext;
    }

    // Insert the new student after the current node
    (*newStudent)->pNext = curr->pNext;
    curr->pNext = *newStudent;
  }
}


///@brief: inserts a student in a GPA order
///@param: head - pointer to the head of the list
///@param: newStudent - pointer to the new student to insert
void insertSortedByGPA(StudentNodeptr *head, StudentNodeptr *newStudent) {
  // If the list is empty or the new student's GPA is less than the current
  // head's GPA
  if (*head == NULL || (*newStudent)->pStudent->gpa < (*head)->pStudent->gpa) {
    (*newStudent)->pNext = *head;
    *head = *newStudent;
  } else {
    // Traverse the list to find the correct position to insert the new student
    StudentNodeptr curr = *head;
    while (curr->pNext != NULL &&
           (*newStudent)->pStudent->gpa > curr->pNext->pStudent->gpa) {
      curr = curr->pNext;
    }

    // Insert the new student after the current node
    (*newStudent)->pNext = curr->pNext;
    curr->pNext = *newStudent;
  }
}


///@brief: prints the student information
///@param: student - pointer to the student to print
void printStudentInfo(Studentptr student) {
  if (student == NULL) {
    printf("Error: No student to print.\n");
    return;
  }

  printf("%s:\n", student->name);
  printf("    ID - %s\n", student->id);
  printf("    GPA - %.2lf\n", student->gpa);
  printf("    Credit Hours - %d\n\n", student->creditHours);
}


///@brief: adds a student to the database
///@param: database - pointer to the database
///@param: name - the name of the student
///@param: id - the id of the student
///@param: gpa - the gpa of the student
///@param: creditHours - the credit hours of the student
void addContact(Databaseptr *database, char *name, char *id, double gpa, int creditHours) {

    // making the student Node for the new Student
  StudentNodeptr newStudentForIDList = (StudentNodeptr)malloc(sizeof(StudentNode));

  // allocating memory for the new student
  newStudentForIDList->pStudent = (Student *)malloc(sizeof(Student));
  newStudentForIDList->pStudent->name = malloc(strlen(name) + 1);
  newStudentForIDList->pStudent->id = malloc(strlen(id) + 1);
  strcpy(newStudentForIDList->pStudent->name, name);
  strcpy(newStudentForIDList->pStudent->id, id);
  newStudentForIDList->pStudent->gpa = gpa;
  newStudentForIDList->pStudent->creditHours = creditHours;
  newStudentForIDList->pNext = NULL;

  // inserting the new student into the ID list
  insertSorted(&(*database)->pIDList, &newStudentForIDList);

  // inserting the new student into the honor roll list
  if (newStudentForIDList->pStudent->gpa >= 3.50) {
    StudentNodeptr newStudentForHonorRollList =
        (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForHonorRollList->pStudent = newStudentForIDList->pStudent;
    newStudentForHonorRollList->pNext = NULL;
    insertSortedByGPA(&(*database)->pHonorRollList,
                      &newStudentForHonorRollList);
  }

  // inserting the new student into the academic probation list
  if (newStudentForIDList->pStudent->gpa < 2.00) {
    StudentNodeptr newStudentForAcademicProbationList =
        (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForAcademicProbationList->pStudent =
        newStudentForIDList->pStudent;
    newStudentForAcademicProbationList->pNext = NULL;
    insertSortedByGPA(&(*database)->pAcademicProbationList,
                      &newStudentForAcademicProbationList);
  }

  // inserting the new student into the freshman list
  if (newStudentForIDList->pStudent->creditHours >= 0 &&
      newStudentForIDList->pStudent->creditHours <= 29) {
    StudentNodeptr newStudentForFreshmanList =
        (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForFreshmanList->pStudent = newStudentForIDList->pStudent;
    newStudentForFreshmanList->pNext = NULL;
    insertSortedByName(&(*database)->pFreshmanList, &newStudentForFreshmanList);
  }
  // inserting the new student into the sophomore list
  else if (newStudentForIDList->pStudent->creditHours >= 30 &&
             newStudentForIDList->pStudent->creditHours <= 59) {
    StudentNodeptr newStudentForSophomoreList =
        (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForSophomoreList->pStudent = newStudentForIDList->pStudent;
    newStudentForSophomoreList->pNext = NULL;
    insertSortedByName(&(*database)->pSophomoreList,
                       &newStudentForSophomoreList);
  }
  // inserting the new student into the junior list
  else if (newStudentForIDList->pStudent->creditHours >= 60 && newStudentForIDList->pStudent->creditHours <= 89) {
    StudentNodeptr newStudentForJuniorList = (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForJuniorList->pStudent = newStudentForIDList->pStudent;
    newStudentForJuniorList->pNext = NULL;
    insertSortedByName(&(*database)->pJuniorList, &newStudentForJuniorList);
  }
  // inserting the new student into the senior list
  else if (newStudentForIDList->pStudent->creditHours >= 90) {
    StudentNodeptr newStudentForSeniorList = (StudentNodeptr)malloc(sizeof(StudentNode));
    newStudentForSeniorList->pStudent = newStudentForIDList->pStudent;
    newStudentForSeniorList->pNext = NULL;

    insertSortedByName(&(*database)->pSeniorList, &newStudentForSeniorList);
  }

}

///@brief: finds a student by their ID
///@param: head - pointer to the head of the list
///@param: targetID - the ID of the student to find
Studentptr findStudentByID(StudentNodeptr head, const char *targetID) {
  StudentNodeptr curr = head;

  // traversing the list
  while (curr != NULL) {
    if (strcmp(curr->pStudent->id, targetID) == 0) {
      return curr->pStudent;
    }
    curr = curr->pNext;
  }

  // if the student is not found
  return NULL;
}


///@brief: reads in a file and adds the students to the database
///@param: database - pointer to the database
void useFile(Databaseptr *database) {
  char filename[81];
  printf("Enter the name of the file you would like to use: ");
  scanf("%s", filename);
  FILE *filePtr = fopen(filename, "r");

  if (filePtr == NULL) {
    printf("Error: could not open %s for reading\n", filename);
    exit(-1);
  }

  char line[100];
  char *token;
  char *delim = ",";
  char *endptr;
  char name[100];
  char id[11];
  double gpa;
  int creditHours;

  // reading in the first line of the file
  fgets(line, 100, filePtr);

  // reading in the rest of the file
  while (fgets(line, 100, filePtr) != NULL) {

    // getting the name
    token = strtok(line, delim);
    strcpy(name, token);

    // getting the id
    token = strtok(NULL, delim);
    strcpy(id, token);

    // converting the gpa to a 4.0 scale
    token = strtok(NULL, delim);
    gpa = strtof(token, &endptr);

    // converting the credit hours to an integer
    token = strtok(NULL, delim);
    creditHours = strtol(token, &endptr, 10);

    // adding the student to the database
    addContact(database, name, id, gpa, creditHours);
  }
  // Close the file
  fclose(filePtr);
}

int main() {
  char choice[81];

  // creating the database
  Databaseptr database = (Databaseptr)malloc(sizeof(Database));

  // initializing the database
  database->pAcademicProbationList = NULL;
  database->pFreshmanList = NULL;
  database->pSeniorList = NULL;
  database->pHonorRollList = NULL;
  database->pSophomoreList = NULL;
  database->pIDList = NULL;
  database->pJuniorList = NULL;

  printf("CS 211, Spring 2023\n");
  printf("Program 4: Database of Students\n\n");

  printf("Enter E to start with an empty database, \n");
  printf("or F to start with a database that has information on students from "
         "a file.\n");
  printf("Your choice --> ");
  scanf("%s", choice);
  while (1) {
      // if the user wants to use a file
    if (strcmp(choice, "F") == 0) {
      useFile(&database);
      break;
    }
    // if the user wants to start with an empty database
    if (strcmp(choice, "E") == 0) {
      break;
    } else {
      printf("Sorry, that input was invalid. Please try again.\n");
      continue;
    }
  }
  while (1) {

    // printing the menu
    char choice2[100];
    printf(
        "\nEnter: \tC to create a new student and add them to the database,\n");
    printf("\tR to read from the database,\n");
    printf("\tD to delete a student from the database, or\n");
    printf("\tX to exit the program.\n");
    printf("Your choice --> ");
    scanf("%s", choice2);

    // if the user wants to create a new student
    if (strcmp(choice2, "C") == 0) {
      char name[1000];
      int i = 0;
      char ID[100];
      int hours;
      double GPA;
      getchar();
      printf("Enter the name of the new student: ");

      // reading in the name
      fgets(name, sizeof(name), stdin);
      while (name[i] != '\n') {
        i++;
      }
      name[i] = '\0';

      printf("Enter the ID of the new student: ");
      scanf("%s", ID);
      printf("Enter the GPA of the new student: ");
      scanf("%lf", &GPA);
      printf("Enter the credit hours of the new student: ");
      scanf("%d", &hours);
      printf("Successfully added the following student to the database!\n");

      // adding the student to the database
      addContact(&database, name, ID, GPA, hours);

      // printing the student's information
      printStudentInfo(findStudentByID(database->pIDList, ID));
      continue;
    }

    // if the user wants to read from the database
    if (strcmp(choice2, "R") == 0) {
      printf("Select one of the following: \n");
      printf("\t1) Display the head (first 10 rows) of the database\n");
      printf(
          "\t2) Display students on the honor roll, in order of their GPA\n");
      printf("\t3) Display students on academic probation, in order of "
             "their GPA\n");
      printf("\t4) Display freshmen students, in order of theirname\n");
      printf("\t5) Display sophomore students, in order of their name\n");
      printf("\t6) Display junior students, in order of their name\n");
      printf("\t7) Display senior students, in order of their name\n");
      printf("\t8) Display the information of a particular student\n");
      while (1) {
        char choice3[100];
        printf("Your choice --> ");
        scanf("%s", choice3);


        // if the user wants to display the top 10 students in the IdList
        if (strcmp(choice3, "1") == 0) {
          StudentNodeptr curr = database->pIDList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          int i = 0;
          while (i < 10 && curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
            i++;
          }
          break;
        }

        // if the user wants to display the honor roll list
        if (strcmp(choice3, "2") == 0) {
          StudentNodeptr curr = database->pHonorRollList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the academic probation list
        if (strcmp(choice3, "3") == 0) {
          StudentNodeptr curr = database->pAcademicProbationList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the freshman list
        if (strcmp(choice3, "4") == 0) {
          StudentNodeptr curr = database->pFreshmanList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the sophomore list
        if (strcmp(choice3, "5") == 0) {
          StudentNodeptr curr = database->pSophomoreList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the junior list
        if (strcmp(choice3, "6") == 0) {
          StudentNodeptr curr = database->pJuniorList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the senior list
        if (strcmp(choice3, "7") == 0) {
          StudentNodeptr curr = database->pSeniorList;
          if (curr == NULL) {
            printf("There are no students matching that criteria.\n\n");
          }
          while (curr != NULL) {
            printStudentInfo(curr->pStudent);
            curr = curr->pNext;
          }
          break;
        }

        // if the user wants to display the information of a particular student
        if (strcmp(choice3, "8") == 0) {
          char targetID[100];
          printf("Enter the id of the student to find: ");
          scanf("%s", targetID);
          Studentptr foundStudent =
              findStudentByID(database->pIDList, targetID);

          if (foundStudent != NULL) {
            printStudentInfo(foundStudent);
          } else {
            printf(
                "Sorry, there is no student in the database with the id %s.\n",
                targetID);
          }
          break;
        } else {
          printf("Sorry, that input was invalid. Please try again.\n");
          continue;
        }
      }
      continue;
    }

    // if the user wants to delete a student from the database
    if (strcmp(choice2, "D") == 0) {

      char targetID[11];
      printf("Enter the id of the student to be removed: ");
      scanf("%s", targetID);
      deleteStudent(database, targetID);
      continue;
    }

    // if the user wants to exit the program
    if (strcmp(choice2, "X") == 0) {

      break;
    } else {
      printf("Invalid option. Try again.\n");
      continue;
    }

  }

  // freeing the memory
  FreeMemory(&database);
  free(database);

  printf("Thanks for playing!\n");
  printf("Exiting...\n");

  return 0;
}