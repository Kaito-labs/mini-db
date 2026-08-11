#include <stdio.h>
#include <stdlib.h>

// Main code src
// Database for a library 


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

                break;
            }
            case 2:
            {

                break;
            }
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