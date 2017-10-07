# Pima CC CIS265 Week #12 Project

Develop a C program to work with structures and enumerations. The project uses the comma separated values(CSV) “student database.txt”

The user will be given a menu to choose from the following options:
```Text
  1 - Press(D) to display all students records information
  2 - Press(S) to search and display a student information by student ID
  3 - Press(C) to provide a count of students per campus
  4 - Press(Q) to quit
```
Students’ information should be loaded from the “student database.txt” into an array of structs.

For user option# 1, display students record(one record per line).

For user option#2, prompt the user to enter an ID and search for it in the array of structs that contain the students’ information.If found, display the student record otherwise print that student ID does not exist.

For user option#3, display the count of students per campus. You are required to create an enum with the college campuses(Downtown, East, and West) and use them in a switch statement to perform the count. For this 
option your display will look like the following example
```Text
  East Campus : 5 students
  West Campus : 3 students
  Downtown Campus : 4 students
```
After every operation completion, you need to re-display the menu until the user selects option# 4 to quit the program.

Notes:
* Needs more input validation.
* Implements a linked-list of Students (struct).
* Compiled with MS Visual Studio 2017 Community (v141), using C language options.
