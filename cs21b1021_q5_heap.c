#include <stdio.h>

int size = 0;
int count = 0;
int array[1024];
int minimum;

void change(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapify(int array[], int size, int i)
{
    if (size == 1)
    {
        printf("there is only  one entry in database");
    }
    else
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && array[l] > array[largest])
            largest = l;
        if (r < size && array[r] > array[largest])
            largest = r;
        if (largest != i)
        {
            change(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}

void insert(int array[], int newNum)
{
    if (size == 0)
    {
        array[0] = newNum;
        size += 1;
    }
    else
    {
        array[size] = newNum;
        size += 1;
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(array, size, i);
        }
    }
}

void deletemin(int array[], int num)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (num == array[i])
            break;
    }

    change(&array[i], &array[size - 1]);
    size -= 1;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

int search(int array[], int n)
{
    minimum = array[0];

    for (int i = 1; i < n; ++i)

        if (minimum > array[i])
        {
            minimum = array[i];
        }

    return minimum;
}

int main()
{

    int choice, num;
    struct node *root = NULL;
    while (1)
    {

        printf("\n Kindly give integer input for following operations \n");
        printf("1.Insert\n");
        printf("2.Delete minimum value\n");
        printf("3.Find minimum value\n");
        printf("4.Quit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        printf("\nworking.......\n");

        switch (choice)
        {
        case 1:;
            int professor_age;

            printf(" please insert professor data:\nage: ");
            scanf("%d", &professor_age);

            count++;

            insert(array, professor_age);
            printArray(array, size);
            break;

        case 2:;

            int farewell_age;
            farewell_age = search(array, size);

                        if (count != 0)
            {
                deletemin(array, farewell_age);
                printf("\n deleted \n these are the remaining professor entries \n");
                printArray(array, size);
                count--;
                break;
            }
            else
            {
                printf("\n the database is empty\n ");
                break;
            }
            break;

        case 3:;

            int search_age;
            search_age = search(array, size);
            printf("\nthe minimum value is : %d \n", search_age);
            break;

        case 4:
            exit(1);

        default:
            printf("\n Please enter valid input\n");
        }
    }
    return 0;
}
