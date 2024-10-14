
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Create a node
struct Node
{
    int age;
    char *name;
    char *department;
    char *gender;
    struct Node *next;
    struct Node *prev;
};

int count = 0;

// Insert
void insert(struct Node **head_ref, int new_age, char *new_name, char *new_department, char *new_gender)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;

    new_node->age = new_age;

    new_node->name = malloc(sizeof(char) * 50);
    strcpy(new_node->name, new_name);
    printf("name copied as: %s\n", new_node->name);

    new_node->department = malloc(sizeof(char) * 50);
    strcpy(new_node->department, new_department);

    new_node->gender = malloc(sizeof(char) * 50);
    strcpy(new_node->gender, new_gender);

    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;

    return;
}

// to Remove professor_name and professor_department
void deleteNode(struct Node **head_ref, char *farewell_name)
{
    struct Node *temp = *head_ref, *last, *ahead;
    last = ahead = NULL;

    // Find the name to be deleted
    while (temp != NULL && strcmp(temp->name, farewell_name) != 0)
    {
        last = temp;
        temp = temp->next;
        ahead = temp->next;
    }

    // the name is not present
    if (temp == NULL)
    {
        printf("\n no matches found\n");
        return;
    }

    // Remove the node with the name
    if (last != NULL)
    {
        last->next = temp->next;
    }

    if (ahead != NULL)
    {
        ahead->prev = temp->prev;
    }

    temp->next = NULL;
    temp->prev = NULL;

    free(temp->name);
    free(temp->department);
    free(temp->gender);
    free(temp);
    return;
}

// Search to Find professor_name and professor_department
int searchNode(struct Node **head_ref, char *farewell_name)
{
    struct Node *current = *head_ref;

    while (current != NULL)
    {

        if (strcmp(current->name, farewell_name) == 0)
        {
            return 1;
        }
        else
        {
            current = current->next;
        }
    }
    return 0;
}

// view to see professor_name and professor_department
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" \n%d\n ", node->age);
        printf("%s\n", node->name);
        printf("%s\n", node->department);
        printf("%s\n", node->gender);
        printf("\n");
        node = node->next;
    }

}

/*void getcount (){
    printf("no. of professors are %d",count);
}*/

int main()
{

    struct Node *head = NULL;

    char action;

    printf(" please type i to insert professor_name and professor_department \n");
    /* printf(" please type v to see professor_name, professor_age,professor_gender and professor_department \n"); */
    printf(" please type r to remove his/her professor_name  \n");
    printf(" please type s to find by his/her professor_name  \n");
    printf(" please type x to leave this program \n");
    /*  printf(" please type n to know the number of professsors \n");*/

    do
    {
        scanf("%c", &action);

        printf("working.......\n");

        if (action == 'i')
        {
            count++;
            int professor_age;
            char professor_name[50], professor_department[50], professor_gender[50];

            printf(" please insert professor data:\nage: ");
            scanf("%d", &professor_age);
            printf("name: ");
            while (getchar() != '\n')
                ;

            scanf("%[^\n]%*c", professor_name);
            printf("dept: ");
            scanf("%[^\n]%*c", professor_department);
            printf("gender: ");
            scanf("%[^\n]%*c", professor_gender);

            insert(&head, professor_age, professor_name, professor_department, professor_gender);

            printf("\n welcome to IIIT Raichur, your entry has been registered ");
            printList(head);
        }

        /*  if (action == 'v'){
              printf("here is list containing all professor_name and professor_department \n");
              printList(head);
         }*/

        if (action == 'r')
        {

            char professor_name[50];

            printf("please insert professor name: ");
            while (getchar() != '\n')
                ;
            scanf("%[^\n]%*c", professor_name);

            count--;
            deleteNode(&head, professor_name);
            printf("we are sorry to see you go \n here is list containing all current professor_name and professor_department \n");
            printList(head);
        }

        if (action == 's')
        {

            char search_professor_name[50];

            while (getchar() != '\n')
                ;
            printf("\nplease enter prof name\n");
            scanf("%[^\n]%*c", search_professor_name);

            int result = searchNode(&head, search_professor_name);

            if (result)
            {
                printf("found\n");
                printList(head);
            }

            else
            {
                printf("no results found\n");
            }
        }

        /* if (action == 'n'){
             getcount();
         }*/

    } while (action != 'x');
    return 0;
}