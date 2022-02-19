/*Name: Rittika Deb
Registration Number: 20BEC0257
*/

#include<stdio.h>   
#include<stdlib.h>  
struct node   
{  
    int data;   
    struct node *next;  
};  

struct node *front;  
struct node *rear;   
void insert();  
void delete();  
void display();  
void main ()  
{  
    int choice;   
    while(choice != 4)   
    {     
        printf("\n20BEC0257:RITTIKA DEB");
        printf("\n--------------");  
        printf("\n1.Enqueue\n2.Dequeue\n3.Display the queue\n4.Exit\n");  
        printf("\nEnter your choice: ");  
        scanf("%d",& choice);  
        switch(choice)  
        {  
            case 1:  
            insert();  
            break;  
            case 2:  
            delete();  
            break;  
            case 3:  
            display();  
            break;  
            case 4: 
            printf("****Exit****"); 
            exit(0);  
            break;  
            default:   
            printf("\nInvalid choice\n");  
        }  
    }  
}  
void insert()  
{  
    struct node *ptr;  
    int item;   
      
    ptr = (struct node *) malloc (sizeof(struct node));  
    if(ptr == NULL)  
    {  
        printf("\nOVERFLOW\n");  
        return;  
    }  
    else  
    {   
        printf("\nEnter element to be inserted\n");  
        scanf("%d",&item);  
        ptr -> data = item;  
        if(front == NULL)  
        {  
            front = ptr;  
            rear = ptr;   
            front -> next = NULL;  
            rear -> next = NULL;  
        }  
        else   
        {  
            rear -> next = ptr;  
            rear = ptr;  
            rear->next = NULL;  
        }  
    }  
}     
void delete ()  
{  
    struct node *ptr;  
    if(front == NULL)  
    {  
        printf("\nUNDERFLOW\n");  
        return;  
    }  
    else   
    {  
        ptr = front;  
        front = front -> next;  
        free(ptr); 
        printf("Element popped"); 
    }  
}  
void display()  
{  
    struct node *ptr;  
    ptr = front;      
    if(front == NULL)  
    {  
        printf("\nEmpty queue\n");  
    }  
    else  
    {     
        while(ptr != NULL)   
        {  
            printf("\n%d\n",ptr -> data);  
            ptr = ptr -> next;  
        }  
    }  
}  