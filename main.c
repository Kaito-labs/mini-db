#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 40

// Database for a library format: id name author

typedef struct {
    int id;
    char book_name[DIM];
    char book_author[DIM];
} Element;

typedef struct node {
    Element d;
    struct node *next;
} node;

typedef struct node *LINK;


// prototypes
void add_book(FILE *fp);
void search_book(FILE *fp);
FILE *rm_book(FILE *fp);
void print_database_stats(FILE *fp);

int main(int argc, char *argv[])
{
    int menu;

    if (argc != 2) {
        printf("Error: database name missing\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r+");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        printf("\n=== MAIN MENU ===\n");
        printf("\n1) Enter new book");
        printf("\n2) Search book");
        printf("\n3) Remove book");
        printf("\n4) Database stats");
        printf("\n5) Exit\n\n");

        scanf("%d", &menu);

        switch (menu) {
            case 1:
                add_book(fp);
                break;

            case 2:
                search_book(fp);
                break;

            case 3:
                fp = rm_book(fp);
                break;

            case 4:
                print_database_stats(fp);
                break;

            case 5:
                printf("\nClosing the program, Goodbye!\n");
                fclose(fp);
                exit(EXIT_SUCCESS);

            default:
                printf("\nEnter a valid number\n");
        }
    }

    return 0;
}


// option 1 menu
void add_book(FILE *fp)
{
    char buffer[DIM];
    int id, next_id = 0;
    char book_name[DIM];
    char book_author[DIM];

    rewind(fp);

    while (fscanf(fp, "%d %39s %39s", &id, book_name, book_author) == 3) {
        next_id = id + 1;
    }

    printf("\n\n=== New book ===");

    fprintf(fp, "%d", next_id);

    printf("\nEnter new book name: ");
    fgets(buffer, DIM, stdin);
    fgets(buffer, DIM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fprintf(fp, "\n%s", buffer);

    printf("\nEnter new book author: ");
    fgets(buffer, DIM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fprintf(fp, " %s\n", buffer);
}


// op2
void search_book(FILE *fp)
{
    int id, flag = 0;
    char Sbook_name[DIM], tmp_name[DIM];
    char Sbook_author[DIM], tmp_author[DIM];

    rewind(fp);

    printf("\n\n=== Search book ===");

    printf("\nEnter book name: ");
    fgets(Sbook_name, DIM, stdin);
    fgets(Sbook_name, DIM, stdin);
    Sbook_name[strcspn(Sbook_name, "\n")] = '\0';

    printf("\nEnter book author: ");
    fgets(Sbook_author, DIM, stdin);
    Sbook_author[strcspn(Sbook_author, "\n")] = '\0';

    while (fscanf(fp, "%d %39s %39s", &id, tmp_name, tmp_author) == 3) {
        if (strcmp(Sbook_name, tmp_name) == 0 &&
            strcmp(Sbook_author, tmp_author) == 0) {
            flag = 1;
            break;
        }
    }

    if (flag)
        printf("\nBook found!\nBook id = %d\n", id);
    else
        printf("\nBook not found!\n");
}


// op3
FILE *rm_book(FILE *fp)
{
    int id, flag = 0;
    int temp_ID;
    char tmp_name[DIM];
    char tmp_author[DIM];

    rewind(fp);

    printf("\n\n=== Remove Book ===");
    printf("\nEnter book id: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %39s %39s", &temp_ID, tmp_name, tmp_author) == 3) {
        if (temp_ID == id) {
            printf("\n== Book found ==\n");
            printf("\nName: %s", tmp_name);
            printf("\nAuthor: %s\n", tmp_author);

            printf("\nRemoving book...\n");

            //file copy and rm
            FILE *tmp = fopen("tmp.txt","w");
            rewind(fp);
            while(fscanf(fp, "%d %39s %39s", &temp_ID, tmp_name, tmp_author) == 3) {
                if(temp_ID != id) {
                    fprintf(tmp,"%d %s %s\n",temp_ID, tmp_name, tmp_author);
                }
            }
            fclose(fp);
            fclose(tmp);
            remove("library.bd");

            rename("tmp.txt","library.bd");

            flag = 1;
            break;
        }
    }

    if (!flag)
        printf("\nBook not found!\n");
    else  {
        printf("\nBook removed!\n"); }

    return fp; 
}


// op4
LINK new_node()
{
    LINK d = malloc(sizeof(node));

    if (d == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return d;
}


void free_list(LINK *lis)
{
    LINK tmp;

    while (*lis != NULL) {
        tmp = *lis;
        *lis = (*lis)->next;
        free(tmp);
    }
}


void print_database_stats(FILE *fp)
{
    int id, counter = 0;
    char book_name[DIM];
    char book_author[DIM];

    LINK head = NULL;
    LINK tail = NULL;

    rewind(fp);

    while (fscanf(fp, "%d %39s %39s",
                  &id, book_name, book_author) == 3) {

        LINK p = new_node();

        p->next = NULL;
        p->d.id = id;

        strcpy(p->d.book_name, book_name);
        strcpy(p->d.book_author, book_author);

        if (head == NULL) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    LINK tmp = head;

    while (tmp != NULL) {
        counter++;
        tmp = tmp->next;
    }

    printf("\n== Data Base Stats ==\n");
    printf("Total: %d\n", counter);

    printf("\nEnter Author to search: ");
    char tmp_book_author[DIM];
    scanf("%s",tmp_book_author);

    tmp = head;
    counter = 0;
    while (tmp != NULL) {
        if(strcmp(tmp->d.book_author,tmp_book_author) == 0) {
            counter++;
        }
        tmp = tmp->next;
    }
    if(counter == 0) {
        printf("\nAuthor: %s\nNo books have been found!",tmp_book_author); }
    else 
        printf("\nAuthor: %s\n%d books have been found!",tmp_book_author,counter);

    //use the linked list for more statistics
    // e.g. print all books, search, sort, etc.

    free_list(&head);
}
