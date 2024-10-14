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

void heapSort(int array[], int size)
{

    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    // Heap sort
    for (int i = size - 1; i >= 0; i--)
    {
        change(&array[0], &array[i]);
        heapify(array, i, 0);
    }

    printArray(array, size);
}

int main()
{
    int choice, num;
    struct node *root = NULL;

    printf("1.Insert element in array\n");
    printf("2.Print sorted element\n");

    printf("\nEnter your choice : ");
       scanf("%d", &choice);

 
    while (1)
    {
        switch (choice)
        {
        case 1:;

            printf("\n number of elements in array \n");
            scanf("%d", &num);
            for (int i = 0; i < num; ++i)
            {
                int professor_age;
                scanf("%d", &professor_age);
                count++;
                insert(array, professor_age);
            }
            break;

        case 2:;

            printf("\n sorted \n these are the %d sorted professor entries \n",count);
            printArray(array, size);
            break;
        }
    }
    return 0;
}
