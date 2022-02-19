/*Name: Rittika Deb
Registration Number: 20BEC0257
*/

#include <stdio.h>
# define SIZE 100
int inp_arr[SIZE];
int rear = - 1;
int front = - 1;
void enqueue();
void dequeue();
void show();

int main()
{
    int choice;
    while (1)
    {
        printf("1.Enqueue Operation\n");
        printf("2.Dequeue Operation\n");
        printf("3.Display the Queue\n");
        printf("4.End\n");
        printf("Enter your choice of operations : ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            enqueue();
            break;
            case 2:
            dequeue();
            break;
            case 3:
            show();
            break;
            case 4:
            exit(0);
            default:
            printf("Incorrect choice \n");
        } 
    } 
} 
  
void enqueue()
{
    int insert_item;
    if (rear == SIZE - 1)
       printf("Overflow \n");
    else
    {
        if (front == - 1)
        front = 0;
        printf("Element to be inserted in the Queue\n : ");
        scanf("%d", &insert_item);
        rear = rear + 1;
        inp_arr[rear] = insert_item;
    }
} 
  
void dequeue()
{
    if (front==- 1||front>rear)
    {
        printf("Underflow \n");
        return ;
    }
    else
    {
        printf("Element deleted from the Queue: %d\n", inp_arr[front]);
        front = front + 1;
    }
} 
  
void show()
{ 
    if (front == - 1)
        printf("Empty Queue \n");
    else
    {
        printf("Queue: \n");
        for (int i = front; i <= rear; i++)
            printf("%d ", inp_arr[i]);
        printf("\n");
    }
} 