#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Item {
    char name[40];
    float rating;
    float price;
    int food_ID_No;
    struct Item *next;
    struct Item *prev;
};

int cust_id = 1;
struct Item *head;
struct Item *last;
int Today_customer = 0;
float total_income;

struct order_hist {
    int customer_ID;
    int items[10][2];
    float amount;
    char date[11];
    struct order_hist *next;
    struct order_hist *prev;
};

struct order_hist *head1;
struct order_hist *last1;

struct Item *getnewNode(char a[], float p, int fin) {
    struct Item *temp = (struct Item *)malloc(sizeof(struct Item));
    temp->food_ID_No = fin;
    strcpy(temp->name, a);
    temp->rating = 4.0;
    temp->price = p;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

int insert(char n[], float p, int fin) {
    struct Item *temp1 = getnewNode(n, p, fin);
    if (head == NULL) {
        head = temp1;
        last = temp1;
    } else {
        temp1->prev = last;
        last->next = temp1;
        last = temp1;
    }
}

int display() {
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------- MENU ------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-10s\n", "INDEX", "ITEM NAME", "PRICE", "RATINGS");  // Header with fixed width
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    struct Item *temp = head;
    if (head == NULL) {
        printf("Menu is empty\n");
    }

    while (temp != NULL) {
        printf("%-10d %-20s %-10.2f %-10.1f\n", temp->food_ID_No, temp->name, temp->price, temp->rating);  // Data with fixed width
        temp = temp->next;
    }

    printf("-------------------------------------------------------------------------------------------------------------------------\n");
}


int login() {
    char username[30];
    char userpwd[20];
    int i;
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    for (i = 0; i < 10; i++) {
        userpwd[i] = getch();
        printf("*");
    }
    userpwd[i] = '\0';
    if (strcmp(username, "admin") == 0 && strcmp(userpwd, "haritha123") == 0) {
        printf("\n\nLogged in successfully\n");
        return 1;
    } else {
        printf("\nIncorrect username or password\n");
        return 0;
    }
}

void order() {
    int a[10][2];
    int n, j = 0, i = 0;
    do {
        printf("Please enter the food ID number and its quantity: ");
        for (i = 0; i < 2; i++) {
            scanf("%d", &a[j][i]);
        }
        j++;
        printf("Do you want to order more items?\n1. Yes\n2. No\n");
        scanf("%d", &n);
    } while (n == 1);

    float total_amount = 0.0;
    char name[25];
    char Date[11];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%s", Date);
    int k = 0;

    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                       BILL                                                              \n");
    printf("Name: %s\n", name);
    printf("Date: %s\n", Date);
    for (k = 0; k < j; k++) {
        struct Item *temp = head;
        while (temp != NULL && temp->food_ID_No != a[k][0]) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Item with food ID %d not found!\n", a[k][0]);
        } else {
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            printf("%d\t%s\t%d\t%.2f\n", temp->food_ID_No, temp->name, a[k][1], (a[k][1] * temp->price));
            total_amount += (a[k][1] * temp->price);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nTotal payable amount: %.2f\n", total_amount);
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    struct order_hist *temp2 = (struct order_hist *)malloc(sizeof(struct order_hist));
    temp2->amount = total_amount;
    temp2->customer_ID = cust_id++;

    int p, s;
    for (p = 0; p < j; p++) {
        for (s = 0; s < 2; s++) {
            temp2->items[p][s] = a[p][s];
        }
    }

    if (head1 == NULL) {
        head1 = last1 = temp2;
    } else {
        last1->next = temp2;
        temp2->prev = last1;
        last1 = temp2;
    }
    strcpy(temp2->date, Date);
    Today_customer++;
    total_income += total_amount;
}

void display_rd_hist() {
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                               ORDER HISTORY                                                             \n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("SR_NO       DATE         TOTAL AMOUNT \n");

    struct order_hist *temp = head1;
    if (head1 == NULL) {
        printf("Order history is empty\n");
    }

    while (temp != NULL) {
        printf("%d\t%s\t%.2f\n", temp->customer_ID, temp->date, temp->amount);
        temp = temp->next;
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
}

int main() {
    head = NULL;
    last = NULL;

    insert("Burger\t",70.23 , 1);
    insert("Pizza\t",235.67, 6);
    insert("Hot Cake\t",750.63, 10);
    insert("Coffee\t",70.24, 2);
    insert("Ice-cream\t",70.23, 3);
    insert("Sandwich\t",60.23, 4);
    insert("Grill\t",52.29, 7);
    insert("Nun-Bread\t",35.13, 8);
    insert("Cold Drinks\t",20.13, 9);

    int choice;

    do {
        printf("\n-------------------------------------------------------------------------------------------------------------------\n");
        printf("1. FOOD PART\n");
        printf("2. ADMIN PANEL\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int ex;
            do {
                printf("1. FOOD LIST\n2. ORDER\n");
                int n;
                scanf("%d", &n);

                switch (n) {
                case 1:
                    display();
                    break;
                case 2:
                    order();
                    break;
                }

                printf("1. FOOD PART\n2. MAIN MENU\n");
                scanf("%d", &ex);
            } while (ex == 1);
            break;
        }
        case 2: {
            int k = login();
            if (k == 1) {
                int e;
                do {
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    printf("1. ADD NEW DISH\n");
                    printf("2. TODAYS TOTAL INCOME\n");
                    printf("3. TODAY'S TOTAL NUMBER OF CUSTOMERS\n");
                    printf("4. ORDER HISTORY\n");
                    printf("5. LIST OF ITEMS\n");
                    printf("6. EXIT ADMIN PANEL\n");
                    printf("---------------------------------------------------------------------------------------------------------\n");

                    int ch;
                    scanf("%d", &ch);
                    switch (ch) {
                    case 1: {
                        char n[50];
                        float p;
                        int fin;

                        printf("Enter the name of the item: ");
                        scanf("%s", n);
                        printf("Enter the price of the item: ");
                        scanf("%f", &p);
                        printf("Enter the food ID number of the item: ");
                        scanf("%d", &fin);

                        insert(n, p, fin);
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        printf("                      NEW DISH ADDED SUCCESSFULLY\n");
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        break;
                    }
                    case 2:
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        printf("                      TODAYS TOTAL INCOME: %.2f\n", total_income);
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        break;
                    case 3:
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        printf("                      TODAYS TOTAL NUMBER OF CUSTOMERS: %d\n", Today_customer);
                        printf("-----------------------------------------------------------------------------------------------------\n");
                        break;
                    case 4:
                        display_rd_hist();
                        break;
                    case 5:
                        display();
                        break;
                    case 6:
                        printf("Exiting Admin Panel...\n");
                        break;
                    }
                } while (e == 1);
            }
            break;
        }
        case 3:
            printf("Exiting...\n");
            return 0;
        }
    } while (1);

    return 0;
}
