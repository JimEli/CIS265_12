/*************************************************************************
* Title: (CIS265_12) Student Database
* File: student_list.h
* Author: James Eli
* Date: 10/14/2017
*
* Implements a linked-list of Students (struct). Includes enumerations
* for campuses and majors.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   10/14/2017: Initial release. JME
*************************************************************************/
#ifndef _STUDENT_LIST_H_
#define _STUDENT_LIST_H_

// Definitions.
#define MAX_NAME_LENGTH    80     // Maximum student name length.
#define MAX_CAMPUSES       3      // Maximum number of campuses.
#define MAX_MAJORS         4      // Maximum number of majors.
#define MIN_ID_INPUT       0      // Maximum id input value.
#define MAX_ID_INPUT       999999 // Minimum id input value.

// Enumerations for campuses and majors.
enum CAMPUSES { NO_CAMPUS = -1, DOWNTOWN = 0, EAST, WEST };
enum MAJORS { NO_MAJOR = -1, ACCOUNTING = 0, COMPUTER_SCIENCE, CIVIL_ENGINEERING, INTERIOR_DESIGN, };

// Campus and major labels. These match the enumeration order above (starting with index=0).
static const char *campusLabels[MAX_CAMPUSES] = { "Downtown", "East", "West" };
static const char *majorLabels[MAX_MAJORS] = { "Accounting", "Computer Science", "Civil Engineering", "Interior Design", };

// Student structure.
struct Student {
	unsigned int id;                // Student account id.
	char name[MAX_NAME_LENGTH + 1]; // Student name.
	enum MAJORS major;              // Student major (enum).
	enum CAMPUSES campus;           // Student campus (enum).
	struct Student *next;           // Pointer to next structure in list.
};

//
// Function prototypes for Student Linked List.
//
// Add element to list.
bool addStudent(char *);
// Search linked list.
void searchForStudentID(const unsigned int);
// Delete linked list.
void deleteStudents(void);
// Print student list.
void printStudents(void);
// Count student campuses.
void countStudentCampuses(void);

#endif
