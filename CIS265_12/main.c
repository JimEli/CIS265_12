/*************************************************************************
* Title: (CIS265_12) Student Database
* File: main.c
* Author: James Eli
* Date: 9/11/2017
*
* Develop a C program to work with structures and enumerations. The project 
* uses the comma separated values(CSV) “student database.txt”
*
* The user will be given a menu to choose from the following options:
*   1 - Press(D) to display all students records information
*   2 - Press(S) to search and display a student information by student ID
*   3 - Press(C) to provide a count of students per campus
*   4 - Press(Q) to quit
*
* Students’ information should be loaded from the “student database.txt” 
* into an array of structs.
*
* For user option# 1, display students record(one record per line).0
*
* For user option#2, prompt the user to enter an ID and search for it in the 
* array of structs that contain the students’ information.If found, display 
* the student record otherwise print that student ID does not exist.
*
* For user option#3, display the count of students per campus. You are 
* required to create an enum with the college campuses(Downtown, East, and 
* West) and use them in a switch statement to perform the count. For this 
* option your display will look like the following example
*   East Campus : 5 students
*   West Campus : 3 students
*   Downtown Campus : 4 students
*
* After every operation completion, you need to re-display the menu until 
* the user selects option# 4 to quit the program.
*
* Notes:
*  (1) Needs more input validation.
*  (2) Implements a linked-list of Students (struct).
*  (3) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/11/2017: Initial release. JME
*   10/06/2017: Removed some unused code. JME
*   10/14/2017: Moved linked list code to separate file. JME
*************************************************************************/
#include "student_list.h"

// Debug memory allocation routines.
#include "dbgMalloc.h"

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

// Definitions.
#define MAX_INPUT_ATTEMPTS 3      // Maximum input attempts before aborting.

#define MENU_TEXT "\nProgram Menu:\n"    \
	"D - Display all student records.\n" \
	"S - Search for student record.\n"   \
	"C - Student campus Count.\n"        \
	"Q - Quit.\n"                        \
	"Enter D, S, C or Q: "

// Attempt to open & read text content of file.
bool readFile(const char *fileName) {
	FILE *filePtr = NULL;
	char buffer[80];

	// Attempt to open file.
	if ((filePtr = fopen(fileName, "r")) == NULL) {
		printf("Error opening file (%u).", errno);
		return false;
	}

	// Attempt to read file contents line by line & add to list.
	while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
		if (!addStudent(buffer)) {
			fputs("Corrupt file data encountered.\n", stdout);
			deleteStudents();
			return false;
		}
	}

	// Close the file.
	fclose(filePtr);
	return true;
}

// Menu search command.
void cmdSearch(void) {
	int attempts = MAX_INPUT_ATTEMPTS; // Input attempt counter.
	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		char input[8];  // Holds user input as string.

		// Prompt and grab user input.
		fputs("Enter a student ID to search for (0 to 999999): ", stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remaining characters.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			unsigned int id = 0; // Number converted to octal.

			// Catch obvious nonvalid student IDs.
			if (strlen(input) != 7) { // Length includes '\n' inserted by fgets().
				fputs("A student ID is 6 digits.\n", stdout);
				continue;
			}
			// Attempt to convert from string to int, and validate.
			else if (sscanf_s(input, "%d", &id)) {
				if (id >= MIN_ID_INPUT && id <= MAX_ID_INPUT) {
					searchForStudentID(id);
					break; // Exit.
				}
				else
					fputs("Value entered is outside allowable range.\n", stdout);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}
}

// Command entry handled here.
char fetchCommand(void) {
	// Prompt and grab user input.
	fputs(MENU_TEXT, stdout);
	char command = getchar();
	while (getchar() != '\n')
		; // clear remaining characters & newline.
	if (strchr("sScCdDqQ", command))
		return tolower(command);
	else
		return '\0';
}

// Program starts here.
int main(int argc, char *argv[]) {
	char fileName[80] = "student database.txt"; // Default db file.

	// Check command line arguments 
	if (argc == 2)
		// Open commandline passed file name. 
		strcpy(fileName, argv[1]);

	// Attempt to open filename.
	if (!readFile(fileName)) {
		fputs("Usage: CIS265_12 database.txt\n", stderr);
		exit(EXIT_FAILURE);
	}

	// Main command dispatch loop.
	while (1) {
		switch (fetchCommand()) {
		case 's':
			// Search for student id.
			cmdSearch();
			break;

		case 'd':
			// Display students.
			printStudents();
			break;

		case 'c':
			// Count campus totals.
			countStudentCampuses();
			break;

		case 'q':
			// Quit.
			fputs("\nTerminating program.\n", stdout);
			deleteStudents(); // Free allocated memory.
			exit(EXIT_SUCCESS);
			break;

		case '\0':
			/* no break */
		default:
			// Unsupported command.
			fputs("\nUnsupported command entered.\n", stdout);
			break;
		}
	}
}
