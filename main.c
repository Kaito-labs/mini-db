#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 40

// Database for a library format id name author

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


//proto for main
void add_book(FILE *fp);
void search_book(FILE *fp);


// main 
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
        printf("\n3) Exit\n\n");

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
                search_book(fp);
                break;
            }
            
            //add modify book based on ID
            
            //add databse stats
            
            case 3:
            {
                printf("\nClosing the program, Goodbye!\n");
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



// Menu func: 
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

void search_book(FILE *fp)
{
    int id,flag;
    char Sbook_name[DIM], tmp_name[DIM];
    char Sbook_author[DIM], tmp_author[DIM];

    rewind(fp);
    flag = 0;

    printf("\n\n=== Search book ===");
    printf("\nEnter book name: ");
    fgets(Sbook_name, DIM, stdin);
    fgets(Sbook_name, DIM, stdin);
    Sbook_name[strcspn(Sbook_name, "\n")] = '\0'; // remove the \n 

    printf("\nEnter new book author: ");
    fgets(Sbook_author, DIM, stdin);
    Sbook_author[strcspn(Sbook_author, "\n")] = '\0';

    while (fscanf(fp, "%d %39s %39s", &id, tmp_name, tmp_author) == 3 && !flag) {
        if(strcmp(Sbook_name,tmp_name) == 0 && strcmp(Sbook_author,tmp_author) == 0) {
            flag = 1;
        }
    }
    
    if(flag == 1) 
        printf("\nBook found!\nBook id = %d\n",id);
    else {
        printf("\nBook not found!\n");
    }
}
