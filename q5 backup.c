#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int age;
    char *name;
    char *department;
    char *gender;
    struct node *left;
    struct node *right;
    boolean lthread;
    boolean rthread;
};

int count = 0;

typedef enum
{
    false,
    true
} boolean;

struct node *in_scr(struct node *p); // declaration of all functions beforehand so that it no longer assume variable argument and return as int and avoid warning lol
struct node *in_pred(struct node *p);
struct node *insert(struct node *root, int new_age, char *new_name, char *new_department, char *new_gender);
struct node *del(struct node *root, int farewell_age, char *farewell_name);
struct node *type_a(struct node *root, struct node *par, struct node *ptr);
struct node *type_b(struct node *root, struct node *par, struct node *ptr);
struct node *type_c(struct node *root, struct node *par, struct node *ptr);
void inorder(struct node *root);
void preorder(struct node *root);
void search(struct node *root, char *search_name);

struct node *insert(struct node *root, int new_age, char *new_name, char *new_department, char *new_gender)
{
    struct node *tmp, *par, *ptr;
    int found = 0;
    ptr = root;
    par = NULL;

    while (ptr != NULL)
    {
        if (strcmp(ptr->name, new_name) == 0) // name must be unique
        {
            found = 1;
            break;
        }
        par = ptr;

        if (new_age < ptr->age)
        {
            if (ptr->lthread == false) // left insert
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rthread == false)
                ptr = ptr->right; // right insert
            else
                break;
        }
    }

    if (found)
        printf("\n the name: %[^\n]%*c exists in the database", ptr->name);

    else
    {
        tmp = (struct node *)malloc(sizeof(struct node)); // new node

        tmp->age = new_age; // setting up new data

        tmp->name = malloc(sizeof(char) * 50);
        strcpy(tmp->name, new_name);
        printf("name copied as: %s\n", tmp->name);

        tmp->department = malloc(sizeof(char) * 50);
        strcpy(tmp->department, new_department);

        tmp->gender = malloc(sizeof(char) * 50);
        strcpy(tmp->gender, new_gender);

        tmp->lthread = true; // setting left and right booleans to true
        tmp->rthread = true;

        if (par == NULL) // root
        {
            root = tmp;
            tmp->left = NULL;
            tmp->right = NULL;
        }
        else if (new_age < ptr->age) // insert right
        {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        }
        else
        {
            tmp->left = par; // insert left
            tmp->right = par->right;
            par->rthread = false;
            par->right = tmp;
        }
    }
    return root;
}

struct node *del(struct node *root, int farewell_age, char *farewell_name)
{
    struct node *par, *ptr;
    int found = 0;
    ptr = root;
    par = NULL;
    while (ptr != NULL)
    {
        if ((strcmp(ptr->name, farewell_name) == 0))
        {
            found = 1;
            break;
        }
        par = ptr;

        if (farewell_age < ptr->age)
        {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }
    if (found == 0)
    {
        printf("\n no one by the name:  %[^\n]%*c is present in database", farewell_name);
    }

    else if (ptr->lthread == false && ptr->rthread == false) // there are both left and right child
    {
        root = type_c(root, par, ptr);
    }

    else if (ptr->lthread == false)
    {
        root = type_b(root, par, ptr); // just right child (me)
    }

    else if (ptr->rthread == false)
    {
        root = type_b(root, par, ptr); // just left child
    }

    else
    {
        root = type_a(root, par, ptr); // lol
    }

    return root; // returning results
}

struct node *type_a(struct node *root, struct node *par, struct node *ptr)
{
    if (par == NULL)
        root = NULL;

    else if (ptr == par->left)
    {
        par->lthread = true;
        par->left = ptr->left;
    }
    else
    {
        par->rthread = true;
        par->right = ptr->right;
    }
    free(ptr->name);
    free(ptr->department);
    free(ptr->gender);
    free(ptr);
    return root;
}

struct node *type_b(struct node *root, struct node *par, struct node *ptr) // one child is present (branch)
{
    struct node *child, *s, *p;

    if (ptr->lthread == false)
        child = ptr->left;

    else
        child = ptr->right;

    if (par == NULL)
        root = child;

    else if (ptr == par->left)
        par->left = child;

    else
        par->right = child;
    s = in_scr(ptr);
    p = in_pred(ptr);

    if (ptr->lthread == false)
        p->right = s;

    else
    {
        if (ptr->rthread == false)
            s->left = p;
    }
    free(ptr->name);
    free(ptr->department);
    free(ptr->gender);
    free(ptr);
    return root;
}

struct node *type_c(struct node *root, struct node *par, struct node *ptr)
{
    struct node *scr, *parscr;
    parscr = ptr;
    scr = ptr->right;

    while (scr->left != NULL)
    {
        parscr = scr;
        scr = scr->left;
    }
    ptr->age = scr->age; // setting up new data

    ptr->name = scr->name;
    ptr->department = scr->department;
    ptr->gender = scr->gender;

    if (scr->lthread == true && scr->rthread == true)
        root = type_a(root, parscr, scr); // now it's type a

    else
        root = type_b(root, parscr, scr);

    return root;
}

struct node *in_scr(struct node *ptr)
{
    if (ptr->rthread == true)
        return ptr->right;

    else
    {
        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;
        return ptr;
    }
}

struct node *in_pred(struct node *ptr)
{
    if (ptr->lthread == true)
    {
        return ptr->left;
    }

    else
    {
        ptr = ptr->left;
        while (ptr->rthread == false)
        {
            ptr = ptr->right;
        }
        return ptr;
    }
}

void inorder(struct node *root)
{
    struct node *ptr;
    if (root == NULL)
    {
        printf("no one works at this college");
        return;
    }
    ptr = root;

    while (ptr->lthread == false) // going to leftmost leaf
    {
        ptr = ptr->left;
    }

    while (ptr != NULL)
    {
        printf(" \n%d\n ", ptr->age);
        printf("%s\n", ptr->name);
        printf("%s\n", ptr->department);
        printf("%s\n", ptr->gender);
        printf("\n");

        ptr = in_scr(ptr); // recursion
    }
}

void preorder(struct node *root)
{
    struct node *ptr;

    if (root == NULL)
    {
        printf("no one works at this college");
        return;
    }
    ptr = root;

    while (ptr != NULL)
    {
        printf(" \n%d\n ", ptr->age);
        printf("%s\n", ptr->name);
        printf("%s\n", ptr->department);
        printf("%s\n", ptr->gender);
        printf("\n");

        if (ptr->lthread == false)
        {
            ptr = ptr->left;
        }
        else if (ptr->rthread == false)
        {
            ptr = ptr->right;
        }
        else
        {
            while (ptr != NULL && ptr->rthread == true)
            {
                ptr = ptr->right;
            }
            if (ptr != NULL)
            {
                ptr = ptr->right;
            }
        }
    }
}

void search(struct node *root, char *search_name)
{
    struct node *ptr;
    if (root == NULL)
    {
        printf("no one works at this college");
        return;
    }
    ptr = root;

    while (ptr->lthread == false) // going to leftmost leaf
    {
        ptr = ptr->left;
    }

    while (ptr != NULL)
    {
        if (strcmp(ptr->name, search_name) == 0)
        {
            printf("\nwe found the following details\n");
            printf(" \n%d\n ", ptr->age);
            printf("%s\n", ptr->name);
            printf("%s\n", ptr->department);
            printf("%s\n", ptr->gender);
            printf("\n");
        }
        ptr = in_scr(ptr); // recursion
    }
}

int main()
{
    int choice, num;
    struct node *root = NULL;
    while (1)
    {

        printf("\n Kindly give integer input for following operations \n");
        printf("1.Insert\n");
        printf("2.Delete\n");
        printf("3.Search by name\n");
        printf("4.Inorder Traversal\n");
        printf("5.Quit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        printf("\nworking.......\n");

        switch (choice)
        {
        case 1:
            int professor_age;
            char professor_name[50], professor_department[50], professor_gender[50];

            printf(" please insert professor data:\nage: ");
            scanf("%d", &professor_age);
            printf("name: ");
            while (getchar() != '\n');

            scanf("%[^\n]%*c", professor_name);
            printf("dept: ");
            scanf("%[^\n]%*c", professor_department);
            printf("gender: ");
            scanf("%[^\n]%*c", professor_gender);

            count++;

            root = insert(root, professor_age, professor_name, professor_department, professor_gender);
            break;

        case 2:

            char professor_name[50];

            printf("please insert professor name: ");
            while (getchar() != '\n')
                ;
            scanf("%[^\n]%*c", professor_name);

            count--;

            printf("we are sorry to see you go \n these are the remaining professors \n");
            preorder(root);

            root = del(root, professor_age, professor_name);
            break;

        case 3:
            char search_name[50];

            printf("please insert professor name: ");
            while (getchar() != '\n')
                ;
            scanf("%[^\n]%*c", search_name);

            search(root, search_name);
            break;

        case 4:

            inorder(root);
            break;

        case 5:
            exit(1);

        default:
            printf("\n Please enter valid input\n");
        }
    }
    return 0;
}