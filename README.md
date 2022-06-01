# Gradebook Implementation
Project 1 in CSCI 2021 (UMN) completed Fall 2021. Had to create a simple gradebook focusing on certain topics in CS.

Basic application programming in C is an essential step downward towards the lower levels of computing. This project explores several fundamental aspects to getting work done in C:

 - Dynamic memory management with \code malloc() and free()
 - Reading and writing data files in both text and binary formats
 - Displaying information to the screen
 - Reading commands from the user in interactive programs
 - Building data structures with the C struct primitive
 
Implement a Gradebook Program based on a binary search tree data structure to store assignment grades for a set of students. Also implement a command-line interface that allows a user to interact with this data structure by adding new scores, searching for existing scores, printing all scores, and reading/writing the assignment scores to/from both binary and text files.

**I only modified the gradebook.c and gradebook_main.c files in this project**

Functions and their purposes:

 - create_gradebook: Create a new gradebook
 - add_score: Add a new score to the gradebook, or overwrite the current score if it already exists
 - find_score: Search for a particular student's score
 - print_gradebook: Display all scores stored in the gradebook on the screen
 - free_gradebook: Deallocate any memory used for the gradebook
 - write_gradebook_to_text: Save gradebook to a text file
 - read_gradebook_from_text: Load a gradebook from a text file
 - write_gradebook_to_binary: Save gradebook to a binary file
 - read_gradebook_from_binary: Load a gradebook from a binary file
