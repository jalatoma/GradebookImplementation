#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "gradebook.h"

#define MAX_CMD_LEN 128

// This is in general similar to the list_main file seen in lab
// One big difference is the notion of switching between gradebooks in one
// run of the program.
// You have to create or load a gradebook from a file before you can do things
// like add, lookup, or write.
// Also, the user must explicitly clear the current gradebook before
// they can create or load in a new one.
int main(int argc, char **argv) {
    gradebook_t *book = NULL;
    bool echo = false;
    if (argc > 1 && strcmp("-echo", argv[1]) == 0) {
        echo = true;
    }
    // TODO Support file name as a possible command line argument
    char *file_name = argv[1];
    in len = strlen(file_name);

    if (strcmp(&file_name[len-4], ".txt") == 0) {
        book = read_gradebook_from_text(file_name);
        if (book != NULL){
            printf("Gradebook loaded from text file\n");
        } else {
            printf("Failed to read gradbook from text file\n");
        }
    } else if (strcmp(&file_name[len-4], ".bin") == 0) { 
        book = read_gradebook_from_binary(file_name);
        if (book != NULL){
            printf("Gradebook loaded from text file\n");
        } else {
            printf("Failed to read gradbook from text file\n");
        }
    } else {
        printf("Error: Unknown gradebook file extension\n");
    }

    printf("CSCI 2021 Gradebook System\n");
    printf("Commands:\n");
    printf("  create <name>:          creates a new class with specified name\n");
    printf("  class:                  shows the name of the class\n");
    printf("  add <name> <score>:     adds a new score\n");
    printf("  lookup <name>:          searches for a score by student name\n");
    printf("  clear:                  resets current gradebook\n");
    printf("  print:                  shows all scores, sorted by student name\n");
    printf("  write_text:             saves all scores to text file\n");
    printf("  read_text <file_name>:  loads scores from text file\n");
    printf("  write_bin:              saves all scores to binary file\n");
    printf("  read_bin <file_name>:   loads scores from binary file\n");
    printf("  exit:                   exits the program\n");

    char cmd[MAX_CMD_LEN];
    while (true) {
        printf("gradebook> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            if (echo) {
                printf("exit\n");
            }
            break;
        }

        else if (strcmp("create", cmd) == 0) {
            scanf("%s", cmd);
            if (echo) {
                printf("create %s\n", cmd);
            }

            if (book != NULL) {
                printf("Error: You already have a gradebook.\n");
                printf("You can remove it with the \'clear\' command\n");
            } else {
                book = create_gradebook(cmd);
                if (book == NULL) {
                    printf("Gradebook creation failed\n");
                }
            }
        }

        else if (strcmp("add", cmd) == 0) {
            int score;
            scanf("%s %d", cmd, &score);
            if (echo) {
                printf("add %s %d\n", cmd, score);
            }

            if (book == NULL) {
                printf("Error: You must create or load a gradebook first\n");
            } else {
                if (add_score(book, cmd, score) < 0) {
                    printf("Error: You must enter a score in the valid range (0 <= score)\n");
                }
            }
        }

        else if (strcmp("class", cmd) == 0) {
            if (echo) {
                printf("class\n");
            }

            if (book == NULL){
                printf("Error: You must create or load a gradebook first\n");
            } else {
                printf("%c\n", *get_gradebook_name(book));
            }
        }

        else if (strcmp("lookup", cmd) == 0) {
            int score;
            scanf("%s", cmd);
            if (echo) {
                printf("lookup %s\n", cmd);
            }

            score = find_score(book, cmd);

            if (score == -1){
                printf("No score for '%s' found\n", cmd);
            } else {
                printf("%s: %d", cmd, score);
            }
        }

        else if (strcmp("clear", cmd) == 0) {
            if (echo) {
                printf("clear\n");
            }

            if (book == NULL) {
                printf("Error: no gradebook to clear\n");
            } else {
                free_gradebook(book);
            }
        }

        else if (strcmp("print", cmd) == 0) {
            if (echo) {
                printf("print\n");
            }

            if (book == NULL){
                printf("Error: You must create or load a gradebook first\n");
            } else {
                print_gradebook(book);
            }
        }

        else if (strcmp("write_text", cmd) == 0) {
            if (echo) {
                printf("write_text\n");
            }

            if (book == NULL) {
                printf("Error: You must create or load a gradebook first\n");
            } else {
                if (write_gradebook_to_text(book) == -1){
                    printf("Failed to write gradebook to text file\n");
                } else {
                    printf("Gradebook successfully written to %c.txt", *get_gradebook_name(book));
                }
            }
        }

        else if (strcmp("read_text", cmd) == 0) {
            scanf("%s", cmd);

            if (echo) {
                printf("read_text %s\n", cmd);
            }

            if (book != NULL) {
                printf("Error: You must clear current gradbook first\n");
            }

            if (read_gradebook_from_text(cmd) == NULL) {
                printf("Failed to read gradbook from text file\n");
            } else {
                printf("Gradebook loaded from text file\n");
            }
        }

        else if (strcmp("write_bin", cmd) == 0) {
            if (echo) {
                printf("write_bin\n");
            }

            if (book == NULL) {
                printf("Error: You must create or load a gradebook first\n");
            } else {
                if (write_gradebook_to_binary(book) == -1) {
                    printf("Failed to write gradebook to binary file\n");
                } else {
                    printf("Gradebook successfully written to %c.txt\n", *get_gradebook_name(book));
                }
            }
        }

        else if (strcmp("read_bin", cmd) == 0) {
            scanf("%s", cmd);

            if (echo) {
                printf("read_bin %s\n", cmd);
            }

            if (book != NULL) {
                printf("Error: You must clear current gradbook first\n");
            }

            if (read_gradebook_from_text(cmd) == NULL) {
                printf("Failed to read gradbook from text file\n");
            } else {
                printf("Gradebook loaded from text file\n");
            }
        }


        else {
            if (echo) {
                printf("%s\n", cmd);
            }
            printf("Unknown command %s\n", cmd);
        }
    }

    free_gradebook(book);
    return 0;
}
