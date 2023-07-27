#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[50];  
    int days; 
    float rent;        
    int data;          
    struct node *prev;
    struct node *next;
};

struct node *hc = NULL, *newnode, *tc = NULL;
struct node *ha = NULL, *ta = NULL;
struct node *hs;

void mainmenu()
{
    printf("\n\t\t\t**************************************************************************\n");
    printf("\t\t\t                       WELCOME TO CAR RENTAL SERVICE                             ");
    printf("\n\t\t\t**************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t1. ADMIN SECTION\n");
    printf("\t\t\t\t\t\t2. CUSTOMER SECTION\n");
    printf("\t\t\t\t\t\t3. EXIT\n\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
}

void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t Select from the choices given below:");
    printf("\n\n\t\t\t\t\t\t\t 1. View total sales.");
    printf("\n\t\t\t\t\t\t\t 2. Add new cars models to the lot.");
    printf("\n\t\t\t\t\t\t\t 3. Delete car models from the lot.");
    printf("\n\t\t\t\t\t\t\t 4. Display all cars.");
    printf("\n\t\t\t\t\t\t\t 5. Back to main menu.");
    printf("\n\n\t\t\t\t\t\t\t Enter your choice:");
}

void customermenu()
{
    printf("\n\t\t\t\t\t\t\t Select from the choices given below:");
    printf("\n\n\t\t\t\t\t\t\t1. Select a car of your liking.");
    printf("\n\t\t\t\t\t\t\t2. View the list of rented car.");
    printf("\n\t\t\t\t\t\t\t3. Cancel your ride.");
    printf("\n\t\t\t\t\t\t\t4. Display final bill.");
    printf("\n\t\t\t\t\t\t\t5. Back to main menu.");
    printf("\n\n\t\t\t\t\t\t\t Enter your choice: ");
}


struct node *createadmin(struct node *head, int data, char carname[25], float rent)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->rent = rent;
    newnode->days = 0;
    strcpy(newnode->name, carname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;
    if (temp == NULL)
        ha = ta = newnode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = ta;
        ta = newnode;
    }
    return ha;
}

struct node *createcustomer(struct node *head, int data, int ndays)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    struct node *temp1 = ha;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newnode->data = data;
        newnode->rent = ndays*(temp1->rent);
        newnode->days = ndays;
        strcpy(newnode->name, temp1->name);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if (temp == NULL)
            hc = tc = newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tc;
            tc = newnode;
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis car model is not present in the lot!\n");
    }
    return hc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if (temp1 == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!\n\n");
    }
    else
    {
        printf("\n");
        while (temp1 != NULL)
        {
            if (temp1->days == 0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n", temp1->data, temp1->name, temp1->rent);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n", temp1->data, temp1->name, temp1->days, temp1->rent);
            }
            temp1=temp1->next;
        }
        printf("\n");
    }
}

struct node *totalsales(int data, int ndays)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = ha;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->rent = ndays*(temp1->rent);
    newnode->days = ndays;
    strcpy(newnode->name, temp1->name);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = hs;

    if (temp == NULL)
        hs = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if (flag == 1)
        {
            temp->days += newnode->days;
            temp->rent += newnode->rent;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return hs;
}

void calculatetotsales()
{
    struct node *temp = hc;
    while (temp != NULL)
    {
        hs = totalsales(temp->data, temp->days);
        temp = temp->next;
    }
}

struct node *delete (int data, struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    printf("\n\t\t\t\t\tEnter the serial number of car model to be deleted: ");
    int n;
    scanf("%d", &n);

    struct node *temp = ha;
    while (temp != NULL)
    {
        if (temp->data == n)
        {
            ha = delete (n, ha, ta);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter the serial number of car model to be canceled: ");
    int n;
    scanf("%d", &n);

    struct node *temp = hc;
    while (temp != NULL)
    {
        if (temp->data == n)
        {
            hc = delete (n, hc, tc);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(hc);
    struct node *temp = hc;
    float trent = 0;
    while (temp != NULL)
    {
        trent += temp->rent;
        temp = temp->next;
    }
    printf("\t\t\t\t\t\t###########################################\n");
    printf("\t\t\t\t\t\t\t\tTotal rent: %0.02f\n", trent);
}

struct node *deleteList(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    printf("\n\t\t\t\t\t         ----------------------------------------------\n");
    printf("\t\t\t\t\t\t                 ADMIN SECTION                      ");
    printf("\n\t\t\t\t\t         ----------------------------------------------\n");
    while (1)
    {
     
        adminmenu();
        int c;
        scanf("%d", &c);

        if (c == 5)
            break;

        switch (c)
        {
        case 1:
            printf("\n\t\t\t\t\t\t\t###   Total sales   ###\n");
            printf("\n\t\t\t\t\t\t##########################################");
            printf("\n\t\t\t\t\t\t#   Sr No.  #   Name   #  Price          #");
            printf("\n\t\t\t\t\t\t##########################################\n");
            displayList(hs);
            printf("\t\t\t\t\t\t##########################################\n");
            break;

        case 2:
            printf("\n\t\t\t\t\t\t\tEnter the serial number of car model: ");
            int num, flag = 0;
            char na[50];
            float rent;
            scanf("%d", &num);

            struct node *temp = ha;

            while (temp != NULL)
            {
                if (temp->data == num)
                {
                    printf("\n\t\t\t\t\t\tCar model with entered serial number already exists!\n\n");
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if (flag == 1)
                break;

            printf("\t\t\t\t\t\t\tEnter car model name: ");
            scanf("%s", na);
            printf("\t\t\t\t\t\t\tEnter rent: ");
            scanf("%f", &rent);
            ha = createadmin(ha, num, na, rent);
            printf("\n\t\t\t\t\t\t\tNew car model added to the list!\n\n");
            break;

        case 3:
            if (deleteadmin())
            {
                printf("\n\t\t\t\t\t\t###   Updated list of car models   ###\n");
                printf("\n\t\t\t\t\t\t##########################################");
                printf("\n\t\t\t\t\t\t#   Sr No.  #   Name   #  Price          #");
                printf("\n\t\t\t\t\t\t##########################################\n");
                displayList(ha);
                printf("\t\t\t\t\t\t##########################################\n");
            }
            else
                printf("\n\t\t\t\t\t\tCar model with entered serial number doesn't exist!\n\n");
            break;

        case 4:
            printf("\n\t\t\t\t\t\t\t   ###   Car list   ###\n");
            printf("\n\t\t\t\t\t\t##########################################");
            printf("\n\t\t\t\t\t\t#   Sr No.  #   Name   #  Price          #");
            printf("\n\t\t\t\t\t\t##########################################\n");
            displayList(ha);
            printf("\t\t\t\t\t\t##########################################\n");
            break;

        default:
            printf("\n\t\t\t\t\t\tInvalid choice! PLease choose valid option.\n");
            break;
        }
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch;
    printf("\n\t\t\t\t\t         ----------------------------------------------\n");
    printf("\t\t\t\t\t\t                 CUSTOMER SECTION                      ");
    printf("\n\t\t\t\t\t         ----------------------------------------------\n");
    while (1)
    {
      
        customermenu();

        int c;

        scanf("%d", &c);

        if (c == 5)
            break;
        switch (c)
        {
        case 1:
            printf("\n\t\t\t\t\t\t\t   ###   Car list   ###\n");
            printf("\n\t\t\t\t\t\t##########################################");
            printf("\n\t\t\t\t\t\t#   Sr No.  #   Name   #  Price          #");
            printf("\n\t\t\t\t\t\t##########################################\n");
            displayList(ha);
            printf("\t\t\t\t\t\t##########################################\n");
            printf("\n\t\t\t\t\t\tEnter the number corresponding to car you want to rent: ");
            int n;
            scanf("%d", &n);
            printf("\t\t\t\t\t\tEnter number of days: ");
            int numbersofdays;
            scanf("%d", &numbersofdays);
            hc = createcustomer(hc, n, numbersofdays);
            break;

        case 2:
            printf("\n\t\t\t\t\t\t\t  ### List of car rented ###\n");
            printf("\n\t\t\t\t\t\t###########################################");
            printf("\n\t\t\t\t\t\t#   Sr No.  #   Name  #  Days  #  Total   #");
            printf("\n\t\t\t\t\t\t###########################################\n");
            displayList(hc);
            printf("\t\t\t\t\t\t###########################################\n");
            break;

        case 3:
            if (deletecustomer())
            {
                printf("\n\t\t\t\t\t\t### Updated list of your car models ###\n");
                printf("\n\t\t\t\t\t\t###########################################");
                printf("\n\t\t\t\t\t\t#   Sr No.  #   Name  #  Days  #  Total   #");
                printf("\n\t\t\t\t\t\t###########################################\n");
                displayList(hc);
                printf("\t\t\t\t\t\t###########################################\n");
            }
            else
                printf("\n\t\t\t\t\t\tCar model with entered serial number doesn't exist!\n\n");
            break;

        case 4:
            calculatetotsales();
            printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
            printf("\n\t\t\t\t\t\t###########################################");
            printf("\n\t\t\t\t\t\t#   Sr No.  #   Name  #  Days  #  Total   #");
            printf("\n\t\t\t\t\t\t###########################################\n");
            displaybill();
            printf("\t\t\t\t\t\t###########################################\n");
            hc = deleteList(hc);
            printf("\n\t\t\t\t\t\t   Press any key to return to main menu.");
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;

        default:
            printf("\n\t\t\t\t\t\tInvalid choice! PLease choose valid option.\n");
            break;
        }
        if (flag == 1)
            break;
    }
}
int main()
{

    ha = createadmin(ha, 1, "TESLA", 700);
    ha = createadmin(ha, 2, "BMW", 1000);
    ha = createadmin(ha, 3, "PORCHE", 3000);
    ha = createadmin(ha, 4, "TATA", 300);
    ha = createadmin(ha, 5, "MERCEDES", 2000);

    while (1)
    {
        mainmenu();
        int c;
        scanf("%d", &c);
        if (c == 3)
        {
            printf("\n\n\t\t\t****************************** Thank you!!! ******************************\n");
            break;
        }
        switch (c)
        {
        case 1:
            admin();
            break;

        case 2:
            customer();
            break;

        case 3:
            break;

        default:
            printf("\n\t\t\t\t\t\tInvalid choice! PLease choose valid option.\n");
            break;
        }
    }
}
