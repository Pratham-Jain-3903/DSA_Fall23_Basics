#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum nodeColor
{
    RED,
    BLACK
};
int count = 0;
int result = 0; 

typedef struct Node
{
    int age, color; // each node has color parent(except root) and left(&|)right child
    struct Node *link[2];
}Node;

struct Node *root = NULL;

struct Node *createNode(int age)
{
    struct Node *newnode;

    newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->age = age;
    newnode->color = RED;                       // default as red nodes don't violate depth rule but change it back to black because can't attach red to red node
    newnode->link[0] = newnode->link[1] = NULL; // no children yet

    return newnode;
}

void insert(int age)
{

    struct Node *stack[98], *ptr, *newnode, *ptrx, *ptry;
    int dir[256], height = 0, index;

    ptr = root;

    if (!root) // insert root
    {
        root = createNode(age);
        return;
    }

    stack[height] = root;
    dir[height++] = 0; // just root then setting height as 0

    while (ptr != NULL)
    {
        if (ptr->age == age)
        {
            printf("this entry already exist \n");
            return;
        }

        index = (age - ptr->age) > 0 ? 1 : 0;
        stack[height] = ptr;
        ptr = ptr->link[index];
        dir[height++] = index;
    }

    stack[height - 1]->link[index] = newnode = createNode(age);

    while ((height >= 3) && (stack[height - 1]->color == RED))
    {
        if (dir[height - 2] == 0)
        {
            ptry = stack[height - 2]->link[1];
            if (ptry != NULL && ptry->color == RED)
            {
                stack[height - 2]->color = RED;
                stack[height - 1]->color = ptry->color = BLACK; // correcting color
                height = height - 2;
            }
            else
            {
                if (dir[height - 1] == 0)
                {
                    ptry = stack[height - 1];
                }
                else
                {
                    ptrx = stack[height - 1];
                    ptry = ptrx->link[1];
                    ptrx->link[1] = ptry->link[0];
                    ptry->link[0] = ptrx;
                    stack[height - 2]->link[0] = ptry;
                }

                ptrx = stack[height - 2];
                ptrx->color = RED;
                ptry->color = BLACK;
                ptrx->link[0] = ptry->link[1];
                ptry->link[1] = ptrx;

                if (ptrx == root)
                {
                    root = ptry;
                }

                else
                {
                    stack[height - 3]->link[dir[height - 3]] = ptry;
                }
                break;
            }
        }

        else
        {
            ptry = stack[height - 2]->link[0];

            if ((ptry != NULL) && (ptry->color == RED))
            {
                stack[height - 2]->color = RED;
                stack[height - 1]->color = ptry->color = BLACK;
                height = height - 2;
            }

            else
            {
                if (dir[height - 1] == 1)
                {
                    ptry = stack[height - 1];
                }

                else
                {
                    ptrx = stack[height - 1];
                    ptry = ptrx->link[0];
                    ptrx->link[0] = ptry->link[1];
                    ptry->link[1] = ptrx;
                    stack[height - 2]->link[1] = ptry;
                }

                ptrx = stack[height - 2];
                ptry->color = BLACK;
                ptrx->color = RED;
                ptrx->link[1] = ptry->link[0];
                ptry->link[0] = ptrx;

                if (ptrx == root)
                {
                    root = ptry;
                }

                else
                {
                    stack[height - 3]->link[dir[height - 3]] = ptry;
                }

                break;
            }
        }
    }
    root->color = BLACK; // maintaining color
}

/*void delete (int age)
{
    struct Node *stack[98], *ptr, *ptrx, *ptry;
    struct Node *pPtr, *qPtr, *rPtr;
    int dir[98], height = 0, diff, i;
    enum nodeColor color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    while (ptr != NULL)
    {
        if ((age - ptr -> age) == 0)
            break;
        diff = (age - ptr -> age) > 0 ? 1 : 0;
        stack[height] = ptr;
        dir[height++] = diff;
        ptr = ptr -> link[diff];
    }

    if (ptr -> link[1] == NULL)
    {
        if ((ptr == root) && (ptr -> link[0] == NULL))
        {
            free(ptr);
            root = NULL;
        }
        else if (ptr == root)
        {
            root = ptr -> link[0];
            free(ptr);
        }
        else
        {
            stack[height - 1] -> link[dir[height - 1]] = ptr -> link[0];
        }
    }
    else
    {
        ptrx = ptr -> link[1];
        if (ptrx -> link[0] == NULL)
        {
            ptrx -> link[0] = ptr -> link[0];
            color = ptrx -> color;
            ptrx -> color = ptr -> color;
            ptr -> color = color;

            if (ptr == root)
            {
                root = ptrx;
            }
            else
            {
                stack[height - 1] -> link[dir[height - 1]] = ptrx;
            }

            dir[height] = 1;
            stack[height++] = ptrx;
        }
        else
        {
            i = height++;
            while (1)
            {
                dir[height] = 0;
                stack[height++] = ptrx;
                ptry = ptrx -> link[0];
                if (!ptry -> link[0])
                    break;
                ptrx = ptry;
            }

            dir[i] = 1;
            stack[i] = ptry;
            if (i > 0)
                stack[i - 1] -> link[dir[i - 1]] = ptry;

            ptry -> link[0] = ptr -> link[0];

            ptrx -> link[0] = ptry -> link[1];
            ptry -> link[1] = ptr -> link[1];

            if (ptr == root)
            {
                root = ptry;
            }

            color = ptry -> color;
            ptry -> color = ptr -> color;
            ptr -> color = color;
        }
    }

    if (height < 1)
        return;

    if (ptr -> color == BLACK)
    {
        while (1)
        {
            pPtr = stack[height - 1] -> link[dir[height - 1]];
            if (pPtr && pPtr -> color == RED)
            {
                pPtr -> color = BLACK;
                break;
            }

            if (height < 2)
                break;

            if (dir[height - 2] == 0)
            {
                rPtr = stack[height - 1] -> link[1];

                if (!rPtr)
                    break;

                if (rPtr -> color == RED)
                {
                    stack[height - 1] -> color = RED;
                    rPtr -> color = BLACK;
                    stack[height - 1] -> link[1] = rPtr -> link[0];
                    rPtr -> link[0] = stack[height - 1];

                    if (stack[height - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[height - 2] -> link[dir[height - 2]] = rPtr;
                    }
                    dir[height] = 0;
                    stack[height] = stack[height - 1];
                    stack[height - 1] = rPtr;
                    height++;

                    rPtr = stack[height - 1] -> link[1];
                }

                if ((!rPtr -> link[0] || rPtr -> link[0] -> color == BLACK) &&
                    (!rPtr -> link[1] || rPtr -> link[1] -> color == BLACK))
                {
                    rPtr -> color = RED;
                }
                else
                {
                    if (!rPtr -> link[1] || rPtr -> link[1] -> color == BLACK)
                    {
                        qPtr = rPtr -> link[0];
                        rPtr -> color = RED;
                        qPtr -> color = BLACK;
                        rPtr -> link[0] = qPtr -> link[1];
                        qPtr -> link[1] = rPtr;
                        rPtr = stack[height - 1] -> link[1] = qPtr;
                    }
                    rPtr -> color = stack[height - 1] -> color;
                    stack[height - 1] -> color = BLACK;
                    rPtr -> link[1] -> color = BLACK;
                    stack[height - 1] -> link[1] = rPtr -> link[0];
                    rPtr -> link[0] = stack[height - 1];
                    if (stack[height - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[height - 2] -> link[dir[height - 2]] = rPtr;
                    }
                    break;
                }
            }
            else
            {
                rPtr = stack[height - 1] -> link[0];
                if (!rPtr)
                    break;

                if (rPtr -> color == RED)
                {
                    stack[height - 1] -> color = RED;
                    rPtr -> color = BLACK;
                    stack[height - 1] -> link[0] = rPtr -> link[1];
                    rPtr -> link[1] = stack[height - 1];

                    if (stack[height - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[height - 2] -> link[dir[height - 2]] = rPtr;
                    }
                    dir[height] = 1;
                    stack[height] = stack[height - 1];
                    stack[height - 1] = rPtr;
                    height++;

                    rPtr = stack[height - 1] -> link[0];
                }
                if ((!rPtr -> link[0] || rPtr -> link[0] -> color == BLACK) &&
                    (!rPtr -> link[1] || rPtr -> link[1] -> color == BLACK))
                {
                    rPtr -> color = RED;
                }
                else
                {
                    if (!rPtr -> link[0] || rPtr -> link[0] -> color == BLACK)
                    {
                        qPtr = rPtr -> link[1];
                        rPtr -> color = RED;
                        qPtr -> color = BLACK;
                        rPtr -> link[1] = qPtr -> link[0];
                        qPtr -> link[0] = rPtr;
                        rPtr = stack[height - 1] -> link[0] = qPtr;
                    }
                    rPtr -> color = stack[height - 1] -> color;
                    stack[height - 1] -> color = BLACK;
                    rPtr -> link[0] -> color = BLACK;
                    stack[height - 1] -> link[0] = rPtr -> link[1];
                    rPtr -> link[1] = stack[height - 1];
                    if (stack[height - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[height - 2] -> link[dir[height - 2]] = rPtr;
                    }
                    break;
                }
            }
            height--;
        }
    }
}*/

void search(int search_age)
{

    struct Node *stack[98], *ptr, *newnode, *ptrx, *ptry;
    int dir[256], height = 0, index;

    ptr = root;

   /* if (!root) // insert root
    {
        root = createNode(age);
        return;
    }*/

    stack[height] = root;
    dir[height++] = 0; // just root then setting height as 0

    while (ptr != NULL)
    {
        if (ptr->age == search_age)
        {
            printf("\n entry found %d \n", ptr->age);
            result = 1;
            return;
        }

        index = (search_age - ptr->age) > 0 ? 1 : 0;
        stack[height] = ptr;
        ptr = ptr->link[index];
        dir[height++] = index;
    }

}


/*void search2(struct Node *node, int search_age)
{
    struct Node *sptr;

    if (node)
    {
        search(node->link[0],node->age);

        if (sptr->age == search_age)
        {
            printf("professor entry found \n professor age: %d\n ", sptr->age);
            result =1;
            return;
        }

        search(node->link[1],node->age);
    }
    return;
}*/

void inorder(Node *node)
{
    if (node)
    {
        inorder(node->link[0]);
        printf("%d  ", node->age);
        inorder(node->link[1]);
    }
    return;
}

int main()
{
    int choice, num;
    struct node *root = NULL;

    printf("1.Insert professor age in database\n");
    printf("2.search by age\n");
    printf("3.exit");

    
    

    while (1)
    {
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            printf("\n enter professor age :\n");

            int professor_age;
            scanf("%d", &professor_age);
            count++;
            insert(professor_age);
            inorder(root);

            break;

        case 2:

            printf("\n enter professor age to search :\n");

            int search_age;
            scanf("%d", &search_age);
            search(search_age);

           
           

            break;

            /*case 3:

             printf("\n enter professor age to delete :\n");

            int delete_age;
            scanf("%d", &delete_age);
            search(root,delete_age);


            break;*/

        case 3:
            exit(0); // or ctrl c
         

        default:

            printf("only 1,2 and 3 are valid choices \n");

            break;
        }
    }
    return 0;
}