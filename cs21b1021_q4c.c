#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    int age;
    char *name;
    char *department;
    char *gender;
    struct node *left;
    struct node *right;
};
typedef node node;
int count = 0;

// Create a new Node
struct node *createNode(int new_age, char *new_name, char *new_department, char *new_gender)
{
    struct node *newNode = malloc(sizeof(struct node));

    newNode->age = new_age;

    newNode->name = malloc(sizeof(char) * 50);
    strcpy(newNode->name, new_name);
    printf("name copied as: %s\n", newNode->name);

    newNode->department = malloc(sizeof(char) * 50);
    strcpy(newNode->department, new_department);

    newNode->gender = malloc(sizeof(char) * 50);
    strcpy(newNode->gender, new_gender);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Preorder traversal basically 123456789
void preorderTraversal(struct node *root)
{
    if (root == NULL)
    {
        printf(" \n the tree is empty \n ");
        return;
    }

    printf(" \n%d\n ", root->age);
    printf("%s\n", root->name);
    printf("%s\n", root->department);
    printf("%s\n", root->gender);
    printf("\n");

    preorderTraversal(root->left);
    preorderTraversal(root->right);
}


node *insertroot((int new_age, char *new_name, char *new_department, char *new_gender))
{
    struct node *root = createNode(int new_age, char *new_name, char *new_department, char *new_gender);
    count++;
    return root;
}

node *insert((struct node * root, int new_age, char *new_name, char *new_department, char *new_gender))
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    count++;
    if (root == NULL)
    {
        root = insertroot(int new_age, char *new_name, char *new_department, char *new_gender);
    }

    int result = strcmp(root->name, new_node->name);

    if (result == 1)
    {
        root->right = insert((root->right, new_age, new_name, new_department, new_gender))
    }

    if (result == -1)
    {
        root->left = insert((root->left, new_age, new_name, new_department, new_gender))
    }

    if (result == 0)
    {
        root->left = insert((root->left, new_age, new_name, new_department, new_gender))
            printf("this name already exists \n");
    }
    retun root;
}

void deleteNode(struct node *root, char *farewell_name)
{
    struct Node *temp = *root;
    while (temp != NULL && strcmp(temp->name, farewell_name) != 0)
    {
        temp = temp->right;
        temp = temp->left;
    }

    // the name is not present
    if (temp == NULL)
    {
        printf("\n no matches found\n");
        return;
    }

    free(temp->name);
    free(temp->department);
    free(temp->gender);
    free(temp);
    return;
}

int searchNode(struct node *root, char *farewell_name)
{
    struct Node *current = *root;

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

void printList(struct Node *root)
{
    while (node != NULL)
    {
        printf(" \n%d\n ", node->age);
        printf("%s\n", node->name);
        printf("%s\n", node->department);
        printf("%s\n", node->gender);
        printf("\n");
        node = node->right;
        node = node->left;
    }
}

int main()
{

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

            if (count == 0)
            {
                insertroot((struct node * root, int new_age, char *new_name, char *new_department, char *new_gender));
            }

            else
            {
                insert((struct node * root, int new_age, char *new_name, char *new_department, char *new_gender));
            }

            printf("\n welcome to IIIT Raichur, your entry has been registered ");
            printList(root);
        }

        /*  if (action == 'v'){
              printf("here is list containing all professor_name and professor_department \n");
              printList(root);
         }*/

        if (action == 'r')
        {

            char professor_name[50];

            printf("please insert professor name: ");
            while (getchar() != '\n')
                ;
            scanf("%[^\n]%*c", professor_name);

            count--;
            deleteNode(root, professor_name);
            printf("we are sorry to see you go \n here is list containing all current professor_name and professor_department \n");
            printList(root);
        }

        if (action == 's')
        {

            char search_professor_name[50];

            while (getchar() != '\n')
                ;
            printf("\nplease enter prof name\n");
            scanf("%[^\n]%*c", search_professor_name);

            int result = searchNode(root, search_professor_name);

            if (result)
            {
                printf("found\n");
                printList(root);
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