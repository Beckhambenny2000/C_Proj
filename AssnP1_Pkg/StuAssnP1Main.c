#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "MyMenu.h"

// -------------------------------------------------------------------------------------
// Below preprocessor macros, using #define to specify CONSTANTS
// -------------------------------------------------------------------------------------
#define AREA_OF_RECTANGLE(area) (length*breadth)
#define PERIMETER_OF_RECTANGLE(perimeter) (2*(length+breadth))

#define DEFAULT_PRECISION 8
#define MAX_DEFAULT_PRECISION 15
#define MAX_DRAWABLE_RECT_LENGTH 100
#define MAX_DRAWABLE_RECT_BREADTH 20
#define MIN_DRAWABLE_LENGTH_FOR_RECT_CORNER 5
// -------------------------------------------------------------------------------------
// Global Variables
// -------------------------------------------------------------------------------------
// (Recommended but not compulsory. Delete them if you do not wish to use ...)
// -------------------------------------------------------------------------------------
	bool markRectCenter = false;
    bool markRectCorner = false;
    char charForRectCenter = 'X';
    char charForRectCorner = 'c';
    char charForRectPerimeter = '#';
    
    int field1_width = 15;
    int field2_width = 15;
    int field3_width = 30;
    int field4_width = 15;
    
    int defaultPrecision = DEFAULT_PRECISION; 
    int MaxPrecision = MAX_DEFAULT_PRECISION;
    int MaxLength = MAX_DRAWABLE_RECT_LENGTH;
    int MaxBreadth = MAX_DRAWABLE_RECT_BREADTH;
    int MinCorner = MIN_DRAWABLE_LENGTH_FOR_RECT_CORNER;
// -------------------------------------------------------------------------------------
// Function Prototypes (sample)
// -------------------------------------------------------------------------------------
void printWelcomeMsg ();
void DrawRecSubMenu ();
void PrintNumSubMenu ();
void PrintNumberInfo();
void drawRectangle();
void readIntegerInput(int *number);
void readCharInput(char *inputChar);

// -------------------------------------------------------------------------------------

int main() {

    int userEnteredNumber;

	printWelcomeMsg(); // Print the welcome message
    // Below function is declared in "MyMenu.h", implemented in "MyMenu.c"
    printMainMenuOptions();
    do {
        // Prompt and read the user's choice using the function that validates input
        printf("Please enter your choice (1 - 5) : ");
        readIntegerInput(&userEnteredNumber);

        // Check if the input is within the expected range (1 to 5)
        if (userEnteredNumber < 1 || userEnteredNumber > 5) 
        {
            printf("Invalid choice! Please try again.\n");
            printMainMenuOptions();
        }

        printf("\n");
        switch (userEnteredNumber) 
        {
            case 1:
                DrawRecSubMenu();
                break;

            case 2:
                PrintNumSubMenu();
                break;

            case 3:
                drawRectangle();
                break;

            case 4:
                PrintNumberInfo();
                break;

            default: // Case 5 will break the loop and exit
                break;
        }

    } while (userEnteredNumber != 5);

    // Exit message
    printf("Thank you for using this program, have a nice day!\n");
    printf("\n");

    return 0;
}

void printWelcomeMsg ()
{
    printf("\n");
    printf("------------------------------------------------------ \n");
    printf("- Welcome to My Assn P1 Program! - \n");
    printf("------------------------------------------------------ \n");
    printf("- Student Number : 2400867 \n");
    printf("- Student Name   : BECKHAM BENNY ROSS \n");
    printf("------------------------------------------------------ \n");
    printf("\n");
    
}   // end printWelcomeMsg () ...

// Function to display and handle the sub menu with toggling options
void DrawRecSubMenu() { //Option 1
    
    int choice;

    do {
    	
        // Display the menu
        printf("---------------------------------------------------- \n");
        printf("------Configure Draw Rectangle Options Sub Menu-----\n");
        printf("---------------------------------------------------- \n");
        printf("\n");
        printf("0) Back to Main Menu \n");
        printf("1) Toggle marking of rectangle center\t\t(currently: '%s') \n", markRectCenter ? "ON" : "OFF");
        printf("2) Toggle marking of rectangle corner\t\t(currently: '%s') \n", markRectCorner ? "ON" : "OFF");
        printf("3) Change char for rectangle center\t\t(currently: '%c') \n", charForRectCenter);
        printf("4) Change char for rectangle corner \t\t(currently: '%c') \n", charForRectCorner);
        printf("5) Change char for rectangle perimeter \t\t(currently: '%c')\n", charForRectPerimeter);
        printf("\n");
        printf("---------------------------------------------------- \n");
        printf("\n");

        // Ask for user input
        printf("Please enter your choice (0 - 5): ");
        
        readIntegerInput(&choice);
    	/*if (choice < 0 || choice > 5) 
        {
            printf("Invalid choice! Please try again.\n");
        }*/

        // Handle user input
        switch (choice) {
            case 0:
                printMainMenuOptions();
                break;
            case 1:
                // Toggle marking of rectangle center
                markRectCenter = !markRectCenter;
                printf("\nDone! Marking of rectangle center switch to : '%s'\n", markRectCenter ? "ON" : "OFF");
                break;
            case 2:
                // Toggle marking of rectangle corner
                markRectCorner = !markRectCorner;
                printf("\nDone! Marking of rectangle corner switch to : '%s'\n", markRectCorner ? "ON" : "OFF");
                break;
            case 3:
                // Change character for rectangle center
                printf("Enter new char for rectangle center: ");
                readCharInput(&charForRectCenter);
                printf("Char for rectangle center now set to '%c'\n", charForRectCenter);
                break;
            case 4:
                // Change character for rectangle corner
                printf("Enter new char for rectangle corner: ");
                readCharInput(&charForRectCorner);
                printf("Char for rectangle corner now set to '%c'\n", charForRectCorner);
                break;
            case 5:
                // Change character for rectangle perimeter
                printf("Enter new char for rectangle perimeter: ");
                readCharInput(&charForRectPerimeter);
                printf("Char for rectangle perimeter now set to '%c'\n", charForRectPerimeter);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }

    } while (choice != 0);  // Loop until the user chooses to go back to the main menu

}

void PrintNumSubMenu() { //option 2
    
    int choice;

    do {
        // Display the menu
        printf("---------------------------------------------------- \n");
        printf("------Configure Print Number Options Sub Menu-------\n");
        printf("---------------------------------------------------- \n");
        printf("\n");
        printf("0) Back to Main Menu \n");
        printf("1) Adjust width of field 1\t\t\t(Current: %d spacing-allocated)\n", field1_width);
        printf("2) Adjust width of field 2\t\t\t(Current: %d spacing-allocated)\n", field2_width);
        printf("3) Adjust width of field 3\t\t\t(Current: %d spacing-allocated)\n", field3_width);
        printf("4) Adjust width of field 4\t\t\t(Current: %d spacing-allocated)\n", field4_width);
        printf("5) Adjust floating point number precision\t(Current: %d decimal places)\n", defaultPrecision);
        printf("\n");
        printf("---------------------------------------------------- \n");
        printf("\n");

        // Ask for user input
        printf("Please enter your choice (0 - 5): ");
        
        readIntegerInput(&choice);
    	if (choice < 0 || choice > 5) 
        {
            printf("Invalid choice! Please try again.\n");
        }

        // Handle user input
        switch (choice) {
            case 0:
                // Exit the sub-menu and return to the main menu
                printf("Back to main menu...\n");
                printMainMenuOptions ();
                break;
            case 1:
                do {
        				printf("Enter new (whole number) value for width of field 1 (between 8 and 15): ");
        				readIntegerInput(&field1_width);

        				// Check if the input is within the valid range
        				if (field1_width < 8 || field1_width > 15) 
        				{
            				printf("Invalid field width! The width must be between 8 and 15. Please try again.\n");
        				}
    				} while (field1_width < 8 || field1_width > 15); // Repeat until the input is valid

    				printf("New value for width of field 1 = %d\n", field1_width);
    				break;
            case 2:
                do {
        				printf("Enter new (whole number) value for width of field 2 (between 8 and 15): ");
        				readIntegerInput(&field2_width);

        				// Check if the input is within the valid range
        				if (field2_width < 8 || field2_width > 15) 
        				{
            				printf("Invalid field width! The width must be between 8 and 15. Please try again.\n");
        				}
    				} while (field2_width < 8 || field2_width > 15); // Repeat until the input is valid

    				printf("New value for width of field 2 = %d\n", field2_width);
    				break;
            case 3:
                do {
        				printf("Enter new (whole number) value for width of field 3 (between 15 and 60): ");
        				readIntegerInput(&field3_width);

        				// Check if the input is within the valid range
        				if (field3_width < 15 || field3_width > 60) 
        				{
            				printf("Invalid field width! The width must be between 15 and 60. Please try again.\n");
        				}
    				} while (field3_width < 15 || field3_width > 60); // Repeat until the input is valid

    				printf("New value for width of field 3 = %d\n", field3_width);
    				break;
            case 4:
                do {
        				printf("Enter new (whole number) value for width of field 4 (between 8 and 15): ");
        				readIntegerInput(&field4_width);

        				// Check if the input is within the valid range
        				if (field4_width < 8 || field4_width > 15) 
        				{
            				printf("Invalid field width! The width must be between 8 and 15. Please try again.\n");
        				}
    				} while (field4_width < 8 || field4_width > 15); // Repeat until the input is valid

    				printf("New value for width of field 4 = %d\n", field4_width);
    				break;
            case 5:
                // Adjust floating point number precision
                do {
       				 printf("Enter new (whole number) value for precision : (between >=0 and <=15)");
        			 readIntegerInput(&defaultPrecision);
       				 printf("\n");
        
        			if (defaultPrecision > MAX_DEFAULT_PRECISION || defaultPrecision <= 0) 
        			{
         			   printf("Error! Please enter a value greater than 0 and less than or equal to 15.\n");
        			} 
        			else
        			{
            			printf("New value for number precision = %d\n", defaultPrecision);
          				printf("\n");
        			}
    				} while (defaultPrecision > MAX_DEFAULT_PRECISION || defaultPrecision <= 0);
    				
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }

    } while (choice != 0);  // Loop until the user chooses to go back to the main menu
}

void drawRectangle() { //option 3

 	int length, breadth;
    
    // Input the rectangle dimensions	
    printf("Please enter the length of the rectangle (>= 3 or <= 100 units): ");
    
    readIntegerInput(&length);
    if (length > MaxLength)
    {
    	printf("Invalid dimensions. Width must be >= 3 or <= 100 units.\n");
    	printMainMenuOptions ();
    	return;
    }

    printf("Please enter the breadth of the rectangle (>= 3 or <=20 units): ");
    readIntegerInput(&breadth);

    if (breadth > MaxBreadth)
    {
        printf("Invalid dimensions. and height must be >= 3 or <=20 units.\n");
        printMainMenuOptions ();
        return;
    }
    printf("\n");

     for (int i = 0; i < breadth; i++) {
        for (int j = 0; j < length; j++) {
            // Check if the current position is a perimeter character
            if (i == 0 || i == breadth - 1 || j == 0 ||j == length - 1) {
                // Print perimeter character
                printf("%c", charForRectPerimeter);
            }// Handle center cases
            else if (markRectCenter == 1) {
            
                if ((breadth && length % 2 == 1) && i == breadth / 2 && j == length / 2) 
                {
                    // Case 1: Odd height and odd width (1 center)
                    printf("%c", charForRectCenter);
                } 
                
                else if (breadth % 2 == 0 && length % 2 == 0 && (i == breadth / 2 || i == breadth / 2 - 1) && (j == length / 2 || j == length / 2 - 1))
                {
                    // Case 2: Even height and even width (4 centers)
                    printf("%c", charForRectCenter);
                }
                
                else if (breadth % 2 == 1 && length % 2 == 0 && i == breadth / 2 && (j == length / 2 || j == length / 2 - 1)) 
                {
                    // Case 3: Odd height and even width (2 horizontal centers)
                    printf("%c", charForRectCenter);
                } 
                else if (breadth % 2 == 0 && length % 2 == 1 && (i == breadth / 2 || i == breadth / 2 - 1) && j == length / 2) 
                {
                    // Case 4: Even height and odd width (2 vertical centers)
                    printf("%c", charForRectCenter);
                } 
            // Check if the current position is an inner corner
            else if (markRectCorner == 1 && 
            ((i == 1 && j == 1) ||                     // Top-left inner corner
             (i == 1 && j == length - 2) ||             // Top-right inner corner
             (i == breadth - 2 && j == 1) ||            // Bottom-left inner corner
             (i == breadth - 2 && j == length - 2)))     // Bottom-right inner corner
            {               
                printf("%c", charForRectCorner);           // Print inner corner character               
            }
                else 
                {
                    printf(" ");  // Print space if not a center
                }
            }
            // Print spaces inside the rectangle
            else {
                printf(" ");                               // Print space inside the rectangle
            }
        }
        printf("\n");  // Move to the next row
    }
    
    printf("\nPerimeter of rectangle : %d units\n",PERIMETER_OF_RECTANGLE(perimeter));
   	printf("Area of rectangle : %d units square\n",AREA_OF_RECTANGLE(area));
   	printMainMenuOptions ();
}

void PrintNumberInfo() {

	long double num;
	char extraChar;
	
	printf("Please enter a number: ");
    while (1) {
        // Infinite loop to keep asking until a valid number is entered
        if (scanf("%Lf%c", &num, &extraChar) == 2 && (extraChar == '\n')) {
            break; // Exit the loop when valid input is entered
        } else {
            // Failed to read a valid number or found trailing characters
            scanf("%*[^\n]"); // Discard invalid input up to newline
            getchar(); // Consume the newline character left in the buffer
            printf("Invalid input! Please enter a valid number.\n");
        }
    }
    
    printf("------------------------------------------------------\n");
    printf("Infomation on your number : %Lf\n",num);
    printf("------------------------------------------------------\n");
    printf("\n");

    // Print each value aligned with field width and precision settings
    printf("%*s( %-*.*Lf )%*s %-*.*Lf\n", field1_width, "abs ", field2_width, defaultPrecision, num, field3_width, "is : ", field4_width, defaultPrecision, fabsl(num));
    printf("%*s( %-*.*Lf )%*s %-*.*Lf\n", field1_width, "ceil ", field2_width, defaultPrecision, num, field3_width, "is : ", field4_width, defaultPrecision, ceil(num));
    printf("%*s( %-*.*Lf )%*s %-*.*Lf\n", field1_width, "floor ", field2_width, defaultPrecision, num, field3_width, "is : ", field4_width, defaultPrecision, floor(num));
    printf("%*s( %-*.*Lf )%*s %-*.*Lf\n", field1_width, "round ", field2_width, defaultPrecision, num, field3_width, "is : ", field4_width, defaultPrecision, round(num));

    // Scientific notation
    printf("%*s  %-*.*Lf %*s %-*.*Le\n", field1_width, "", field2_width, defaultPrecision, num, field3_width, "in scientific notation : ", field4_width, defaultPrecision, num);

    // Rounding to decimal places
    printf("%*s  %-*.*Lf %*s %-*.*Lf\n", field1_width, "", field2_width, defaultPrecision, num, field3_width, "to 1 dec place : ", field4_width, 1, num);
    printf("%*s  %-*.*Lf %*s %-*.*Lf\n", field1_width, "", field2_width, defaultPrecision, num, field3_width, "to 2 dec place : ", field4_width, 2, num);
    printf("%*s  %-*.*Lf %*s %-*.*Lf\n", field1_width, "", field2_width, defaultPrecision, num, field3_width, "to 3 dec place : ", field4_width, 3, num);

    // Casting to other types
    printf("%*s  %-*.*Lf %*s %-*.*Lf\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to int : ", field4_width, 0, nearbyint(num));
    printf("%*s  %-*.*Lf %*s %-*.*ld\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to long : ", field4_width, 0, lrint(num));
    printf("%*s  %-*.*Lf %*s %-*.*lld\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to long int : ", field4_width, 0, llrint(num));
    printf("%*s  %-*.*Lf %*s %-*.*f\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to float : ", field4_width, defaultPrecision, float(num));
    printf("%*s  %-*.*Lf %*s %-*.*f\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to double : ", field4_width, defaultPrecision, double(num));
    printf("%*s  %-*.*Lf %*s %-*.*Lf\n", field1_width, "casting ", field2_width, defaultPrecision, num, field3_width, "to long double : ", field4_width, defaultPrecision,num);
	
	printf("\n"); 
    printMainMenuOptions ();
}

void readIntegerInput(int *number) {
    char extraChar;
    while (1) 
    { // Infinite loop to keep asking until a valid integer is entered
        if (scanf("%d%c", number, &extraChar) == 2 && (extraChar == '\n')) 
        { // Successfully read an integer with no trailing characters
            return; // Exit the function when valid input is entered
        } 
        else 
        {
            // Failed to read an integer or found trailing characters
            scanf("%*[^\n]"); // Discard invalid input up to newline
            getchar(); // Consume the newline character left in the buffer
            printf("Invalid input! Please enter a valid input.\n");
        }
    }
}

void readCharInput(char *inputChar) {
    char extraChar;
    while (1) {
        if (scanf(" %c%c", inputChar, &extraChar) == 2 && (extraChar == '\n')) {
            // Successfully read a character with no trailing characters
            return; // Exit the function when valid input is entered
        } else {
            // Failed to read a valid single character or found trailing characters
            scanf("%*[^\n]"); // Discard invalid input up to newline
            getchar(); // Consume the newline character left in the buffer
            printf("Invalid input! Please enter a valid single character.\n");
        }
    }
}
