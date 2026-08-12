#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 40

// Main code src
// Database for a library

typedef struct {
    int id;
    char book_name[DIM];
    char book_author[DIM];
} Element;

typedef struct node{
    Element d;
    struct node *next;
} Node;

typedef struct Node *LINK;

//struct declaration for book

//proto for main
void add_book(FILE *fp);
void search_book(FILE *fp);

int main(int argc, char *argv[])
{
    int menu;

    if(argc != 2) {
        printf("Error: databse name missing\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r+");
    if(fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        printf("\n=== MAIN MENU ===\n");
        printf("\n1) Enter new book");
        printf("\n2) Search book");
        printf("\n3) Exit\n");

        scanf("%d",&menu);

        switch(menu)
        {
            case 1:
            {
                add_book(fp);
                break;
            }
            case 2:
            {
                //search_book(fp);
                break;
            }
            //add modify book based on ID
            //add databse stats
            case 3:
            {
                exit(EXIT_SUCCESS);
                break;
            }
            default:
                printf("\nEnter a valid number");
        }


    }

    fclose(fp);

    return 0;
}

void add_book(FILE *fp)
{
    char buffer[DIM];
    int id,next_id;
    char book_name[DIM];
    char book_author[DIM];

    next_id = 0;

    rewind(fp);
    while (fscanf(fp, "%d %39s %39s", &id, book_name, book_author) == 3) {
        next_id = id + 1;
    }

    printf("\n\n=== New book ===");
    fprintf(fp,"%d",next_id);

    printf("\nEnter new book name: ");
    fgets(buffer, DIM, stdin);
    fgets(buffer, DIM, stdin);
    fprintf(fp,"\n%s",buffer);

    printf("\nEnter new book author: ");
    fgets(buffer, DIM, stdin);
    fprintf(fp,"%s",buffer);

    return;
}