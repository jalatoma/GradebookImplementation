#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gradebook.h"

gradebook_t *create_gradebook(const char *class_name) {
    gradebook_t *new_book = malloc(sizeof(gradebook_t));
    if (new_book == NULL) {
        return NULL;
    }

    strcpy(new_book->class_name, class_name);
    new_book->root = NULL;
    return new_book;
}

const char *get_gradebook_name(const gradebook_t *book) {
    if(book != NULL){
        return book->class_name;
    } else {
        return NULL;
    }
    return NULL;
}

node_t *createNode(const char *name, int score){
    node_t *newNode = malloc(sizeof(node_t));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

int add_score(gradebook_t *book, const char *name, int score) {

    if (book->root == NULL){
        book->root = createNode(name, score);
        return 0;
    } else if (book->root->score > score){
        book->root = book->root->left;
        add_score(book, name, score);
    } else {
        book->root = book->root->right;
        add_score(book, name, score);
    }

    return -1;
}


int find_score(const gradebook_t *book, const char *name) {

    if(book->root == NULL || book->root->name == name) {
        return book->root->score;
    }
    else if (book->root->name < name){
        return find_score(*book.root->right, name);
    }
    else if (book->root->name > name){
        return find_score(*book.root->left, name);
    } else{
        return -1;
    }
}

void print_gradebook(const gradebook_t *book) {
    printf("Scores for all students in %s:\n", book->class_name);

}

void free_gradebook(gradebook_t *book) {
    free(book);
}

// Helper function to allow recursion for writing out tree
int write_gradebook_to_text_aux(const node_t *current, FILE *f) {
    if (current == NULL) {
        return 0;
    }

    // Each line is formatted as "<name> <score>"
    fprintf(f, "%s %d\n", current->name, current->score);

    if (current->left != NULL) {
        if (write_gradebook_to_text_aux(current->left, f) != 0) {
            return -1;
        }
    }

    if (current->right != NULL) {
        if (write_gradebook_to_text_aux(current->right, f) != 0) {
            return -1;
        }
    }

    return 0;
}

int write_gradebook_to_text(const gradebook_t *book) {
    char file_name[MAX_NAME_LEN + strlen(".txt")];
    strcpy(file_name, book->class_name);
    strcat(file_name, ".txt");

    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        return -1;
    }

    int result = write_gradebook_to_text_aux(book->root, f);
    fclose(f);
    return result;
}

gradebook_t *read_gradebook_from_text(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        return NULL;
    }

    char s[strlen(file_name) + 1];
    strcpy(s, file_name);
    s[strlen(file_name) - 4] = '\0';
    create_gradebook(s);



    return NULL;
}

int write_gradebook_to_binary(const gradebook_t *book) {
    char file_name[MAX_NAME_LEN + strlen(".bin")];
    strcpy(file_name, book->class_name);
    strcat(file_name, ".bin");

    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        return -1;
    }

    int result = write_gradebook_to_text_aux(book->root, f);
    fclose(f);
    return result;
}

gradebook_t *read_gradebook_from_binary(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        return NULL;
    }

    return NULL;
}
