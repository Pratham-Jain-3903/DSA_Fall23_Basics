#include <stdio.h>

#define max 3

int q[max]; // queue = queu = que = qu = q
int front = -1;
int rear = -1; // intial condn
int count = 0;

void vu()
{

    int i = front;

    if (front == -1 && rear == -1)
    {
        printf("\n underflow\n");
    }

    else
    {
        while (1)
        {
            printf("%d ", q[i]);

            if (i == rear)
            {
                break;
            }

            i = (i + 1) % max;
        }
    }
    printf("\n");
}

void nq()
{
    count++;

    int age;
    scanf("%d", &age);

    if (front == -1 && rear == -1) // first element
    {
        front = 0;
        rear = 0;
        q[rear] = age;

        vu();
    }

    else if ((rear + 1) % max == front) // overflow just like bengaluru
    {
        printf("\n overflow \n");
    }

    else // rest of the nq-ing is done this way
    {
        rear = (rear + 1) % max;
        q[rear] = age;

        vu();
    }
}

void dq()
{
    count--;

    if (front == -1 && rear == -1) // no element
    {
        printf("\n underflow\n");
    }

    else if (front == rear) // one element
    {
        printf("\n %d successfully dequeued\n", q[front]);

        front = -1;
        rear = -1;
    }

    else // rest of the dq-ing is done this way
    {
        printf("\n %d successfully dequeued\n", q[front]);
        front = (front + 1) % max;

        vu();
    }
}

/*void getcount()
{
    printf("\nthere are %d entries\n", count);
}*/

int main()
{
    int choice = 1, data; // variables declaration

    while (choice < 5 && choice != 0)
    {
        printf("\n Press 1: Insert");
        printf("\n Press 2: Delete\n");
        // printf("\nPress 3: view");
        // printf("\nPress 4: count");

        printf("\nEnter your choice\n");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:

            printf("\n Enter the element which is to be inserted\n");
            nq();
            break;

        case 2:

            dq();
            break;
        
            /* case 3:
                 vu();
                 break;
        
             case 4:
                 getcount();
                 break;*/

        default:

          printf("\n Please press 1 or 2 \n");
          printf("\n Hasta-la-vista \n");
       
        }
    }
    return 0;
}