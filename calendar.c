#include <stdio.h>

// Function to find the day of the week
int dayOfWeek(int day, int month, int year) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

// Function to print the calendar
void printCalendar(int year, int month) {
    int days, currentDay, i;

    // Array to store the number of days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    // Find the day of the week for the 1st day of the given month
    currentDay = dayOfWeek(1, month, year);

    // Print the calendar header
    printf("\n---------------------------");
    printf("\n     %02d/%04d", month, year);
    printf("\n---------------------------");
    printf("\n Sun Mon Tue Wed Thu Fri Sat\n");

    // Print blank spaces for the days before the 1st day
    for (i = 0; i < currentDay; i++)
        printf("    ");

    // Print the days of the month
    for (i = 1; i <= daysInMonth[month - 1]; i++) {
        printf("%4d", i);

        // Move to the next line after Saturday
        if (++currentDay > 6) {
            currentDay = 0;
            printf("\n");
        }
    }

    printf("\n---------------------------\n");
}

int main() {
    int year, month;

    // Get the year from the user
    printf("Enter the year: ");
    scanf("%d", &year);

    // Get the month from the user with validation
    do {
        printf("Enter the month (1-12): ");
        scanf("%d", &month);
        if (month < 1 || month > 12) {
            printf("Invalid month. Please enter a value between 1 and 12.\n");
        }
    } while (month < 1 || month > 12);

    // Print the calendar for the specified month and year
    printCalendar(year, month);

    return 0;
}
