/*************************************************************************
* Title: (CIS265_12) Student Database
* File: student_list.c
* Author: James Eli
* Date: 10/14/2017
*
* Implements basic functions for a linked-list of Students (struct).
*
* Notes:
*  (1) Needs more input validation.
*  (2) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   10/14/2017: Initial release. JME
*************************************************************************/
#include "student_list.h"

#ifdef _DEBUG
// Debug memory allocation routines.
#include "debugMalloc.h"

// Macros defined after our replacement functions.
#define malloc(size) _debugMalloc(size, __FILE__, __LINE__)
#define free(p) _debugFree(p, __FILE__, __LINE__)
#define exit(s) _debugExit(s)
#endif

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

// List pointers.
struct Student *head = NULL, *tail = NULL;

// Match string to Majors enumeration.
static enum MAJORS enumMajor(const char *s) {
	for (int i = 0; i < MAX_MAJORS; i++)
		if (strstr(s, majorLabels[i]))
			return (enum MAJORS)i;
	return NO_MAJOR;
}

// Match string to Campuses enumeration.
static enum CAMPUS enumCampus(const char *s) {
	for (int i = 0; i < MAX_CAMPUSES; i++)
		if (strstr(s, campusLabels[i]))
			return (enum CAMPUS)i;
	return NO_CAMPUS;
}

// Fill structure data items.
static bool fillStructure(struct Student *s, char *buffer) {
	assert(s != NULL);
	assert(buffer != NULL);

	// Minimal validation conducted here.
	unsigned int id = atoi(strtok(buffer, ","));
	if (id >= MIN_ID_INPUT && id <= MAX_ID_INPUT)
		s->id = id;
	else
		return false;
	strncpy(s->name, strtok(NULL, ","), MAX_NAME_LENGTH);
	s->major = enumMajor(strtok(NULL, ","));
	s->campus = enumCampus(strtok(NULL, ",\n"));

	s->next = NULL;
	return true;
}

// Add element to list.
bool addStudent(char *buffer) {
	struct Student *s = (struct Student*)malloc(sizeof(struct Student));
	if (s == NULL) {
		fputs("Insufficient memory available.\n", stderr);
		return false;
	}

	// Fill structure data items.
	if (!fillStructure(s, buffer))
		return false;

	// Special case of first student.
	if (head == NULL)
		head = tail = s;

	// Set as end of list.
	tail->next = s;
	tail = s;

	return true; // Success.
}

// Search linked list for id match.
void searchForStudentID(const unsigned int id) {
	struct Student *s = head; // Set to start.

	// Walk the list looking for an id match.
	while (s != NULL) {
		if (s->id == id) {
			fprintf(stdout, "%s ID: %6d  Major: %0s  Campus: %s\n",
				s->name, s->id, majorLabels[s->campus], campusLabels[s->campus]);
			return;
		}
		s = s->next; // Advance to next element.
	}
	fprintf(stdout, "No student with ID: %06d found.\n", id);
	// No macth found.
	return;
}

// Delete linked list.
void deleteStudents(void) {
	struct Student *d = head, *s = head;

	// Walk list and delete the elements.
	while (s != NULL) {
		d = s->next;
		free(s);
		s = d;
	}
	head = tail = NULL;
}

// Print student list.
void printStudents(void) {
	struct Student *s = head;

	// Print header.
	fprintf(stdout, "%-16s %-8s %-18s %s\n", "Name", "ID", "Major", "Campus");
	// Iterate list and display data.
	while (s != NULL) {
		fprintf(stdout, "%-16s %-8d %-18s %-12s\n",
			s->name, s->id, majorLabels[s->major], campusLabels[s->campus]);
		s = s->next;
	}
}

// Count student campuses.
void countStudentCampuses(void) {
	struct Student *s = head;             // Start of list.
	int downtown = 0, east = 0, west = 0; // Campus counters.

	// Iterate list, and count campuses.
	while (s != NULL) {
		switch (s->campus) {
		case DOWNTOWN:
			downtown++;
			break;

		case EAST:
			east++;
			break;

		case WEST:
			west++;
			break;

		default:
			break;
		}
		s = s->next;
	}
	// Display accumulated count.
	fprintf(stdout, "East Campus: %d students\nWest Campus: %d students\n"
		"Downtown Campus: %d students\n", east, west, downtown);
}
