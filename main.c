#include <stdio.h>
#include <stdlib.h>

// Main code src
// Database for a library 

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
                void add_book(FILE *fp);
                break;
            }
            case 2:
            {
                void search_book(FILE *fp);
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



}
