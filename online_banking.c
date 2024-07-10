#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
}

struct user
{
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

// Function to check if an account with the given account number already exists
int accountExists(const char *accountNumber)
{
    FILE *fp;
    char filename[50];
    strcpy(filename, accountNumber);
    strcat(filename, ".txt");
    fp = fopen(filename, "r");
    if (fp != NULL)
    {
        fclose(fp);
        return 1; // Account already exists
    }
    return 0; // Account does not exist
}

//  function to register an account
void registerAccount()
{
    struct user usr;
    FILE *fp;
    char filename[50];
    printf("Enter your account number:\t");
    scanf("%s", usr.ac);

    // Check if the account already exists
    if (accountExists(usr.ac))
    {
        printf("\nAn account with the provided account number already exists.");
    }
    else
    {
        printf("Enter your phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);
        usr.balance = 0;
        strcpy(filename, usr.ac);
        strcat(filename, ".txt"); // Use ".txt" extension for text file
        fp = fopen(filename, "w");

        if (fp != NULL)
        {
            fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr.ac, usr.phone, usr.password, usr.balance);
            fclose(fp);
            printf("\n\nAccount successfully registered");
        }
        else
        {
            printf("\n\nSomething went wrong, please try again");
        }
    }
}

// Function for account login and operations
void accountLogin()
{
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int choice;
    char cont = 'y';
    float amount;

    printf("\nPhone number:\t");
    scanf("%s", phone);
    printf("Password:\t");
    scanf("%s", pword);
    strcpy(filename, phone);
    strcat(filename, ".txt"); // Use ".txt" extension for text file
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\nAccount number not registered");
    }
    else
    {
        fscanf(fp, "Account number: %s\nPhone number: %s\nPassword: %s\nBalance: %f", usr.ac, usr.phone, usr.password, &usr.balance);
        fclose(fp);

        if (strcmp(pword, usr.password) != 0)
        {
            printf("\nIncorrect password");
        }
        else
        {

            while (cont == 'y')
            {
                system("cls");
                printf("\n\t\tWelcome!\n");
                divider();
                printf("\n\nPress 1 for balance inquiry");
                printf("\nPress 2 for depositing cash");
                printf("\nPress 3 for cash withdrawal");
                printf("\nPress 4 for online transfer");
                printf("\nPress 5 for password change");
                printf("\n\nYour choice:\t");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("\nYour current balance is Rs. %.2f", usr.balance);
                    break;
                case 2:
                    printf("\nEnter the amount:\t");
                    scanf("%f", &amount);
                    usr.balance += amount;
                    fp = fopen(filename, "w");
                    fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr.ac, usr.phone, usr.password, usr.balance);
                    fclose(fp);
                    printf("\nSuccessfully deposited.");
                    break;
                case 3:
                    printf("\nEnter the amount:\t");
                    scanf("%f", &amount);
                    if (amount > usr.balance)
                    {
                        printf("\nInsufficient balance");
                    }
                    else
                    {
                        usr.balance -= amount;
                        fp = fopen(filename, "w");
                        fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr.ac, usr.phone, usr.password, usr.balance);
                        fclose(fp);
                        printf("\nYou have withdrawn Rs. %.2f", amount);
                    }
                    break;
                case 4:
                    printf("\nPlease enter the phone number to transfer the balance:\t");
                    scanf("%s", phone);
                    printf("\nPlease enter the amount to transfer:\t");
                    scanf("%f", &amount);
                    strcpy(filename, phone);
                    strcat(filename, ".txt"); // Use ".txt" extension for text file
                    fp = fopen(filename, "r");

                    if (fp == NULL)
                    {
                        printf("\nAccount number not registered");
                    }
                    else
                    {
                        fscanf(fp, "Account number: %s\nPhone number: %s\nPassword: %s\nBalance: %f", usr1.ac, usr1.phone, usr1.password, &usr1.balance);
                        fclose(fp);

                        if (amount > usr.balance)
                        {
                            printf("\nInsufficient balance");
                        }
                        else
                        {
                            usr.balance -= amount;
                            fp = fopen(filename, "w");
                            usr1.balance += amount;
                            fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr1.ac, usr1.phone, usr1.password, usr1.balance);
                            fclose(fp);
                            printf("\nYou have successfully transferred Rs. %.2f to %s", amount, phone);

                            strcpy(filename, usr.phone);
                            strcat(filename, ".txt"); // Use ".txt" extension for text file
                            fp = fopen(filename, "w");
                            fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr.ac, usr.phone, usr.password, usr.balance);
                            fclose(fp);
                        }
                    }
                    break;
                case 5:
                    printf("\nPlease enter your new password:\t");
                    scanf("%s", pword);
                    fp = fopen(filename, "w");
                    strcpy(usr.password, pword);
                    fprintf(fp, "Account number:  %s\nPhone number:   %s\nPassword:   %s\nBalance:    %.2f\n", usr.ac, usr.phone, usr.password, usr.balance);
                    fclose(fp);
                    printf("\nPassword successfully changed");
                    break;
                default:
                    printf("\nInvalid option");
                }

                printf("\nDo you want to continue the transaction [y/n]\t");
                scanf(" %c", &cont);
            }
        }
    }
}

int main()
{
    int opt;
    char log = 'y';
    while (log == 'y')
    {
        printf("\n");
        divider();
        printf("\nWhat do you want to do?");
        printf("\n\n1. Register an account");
        printf("\n2. Login to an account");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);

        if (opt == 1)
        {
            system("cls");
            registerAccount();
        }
        else if (opt == 2)
        {
            system("cls");
            accountLogin();
        }
        else
        {
            divider();
            printf("\nInvalid input!");
        }
        printf("\nPress 'y' to go to home\nPress'x' to exit\n");
        scanf(" %c", &log);
    }
    if (log == 'x')
    {
        printf("----Thank you for using our service!----");
        exit(0);
    }
    return 0;
}