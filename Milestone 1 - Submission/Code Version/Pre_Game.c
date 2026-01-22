#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include <time.h>
//#include <stdbool.h>
#include <ctype.h>
#include "SatComRelay.h"                                                        // Link header file to souce file

VehDataType My_vehicle;	    													// Link Header file "VehDataType" to current program "My_vehicle"

char user_input_c, extra_character;                                             // Create 2 Character for Global variable  
bool Error;                                                                     // Create 1 boolean for Global variable
int result, user_input;                                                         // Create 2 integer for Global variable 

void char_checker();                                                            // Check Character
void int_checker();                                                             // Check integer
void Pre_game();                                                                // Run Pre game

int main()
{
    Pre_game();

    return 0;
}

void char_checker()
{
	result = scanf("%c%c", &user_input_c, &extra_character);                    // Input from keyboard store to user_input_c and extra_character, result store in result variable
	if (extra_character != '\n' || result != 2)                                 // Check if extra_character is not empty and result is not equal to 2
	{
		printf("Input is not char. \n\n");                                      // Print error message if condition is met
		while (getchar() != '\n');                                              // Clear buffer
		Error = 1;                                                              // Error = TRUE if condition is met
	}
	else
	{
		Error = 0;                                                              // Error = False if condition is not met
	}
	user_input_c = tolower(user_input_c);										// Lower case user input
}

void int_checker()
{
	result = scanf("%d%c", &user_input, &extra_character);                      // Input from keyboard store to user_input_c and extra_character, result store in result variable
	if (extra_character != '\n' || result != 2)                                 // Check if extra_character is not empty and result is not equal to 2
	{
		printf("Input is not integer. ");                                       // Print error message if condition is met
		while (getchar() != '\n');                                              // Clear buffer
		Error = 1;                                                              // Error = TRUE if condition is met
	}
	else
	{
		Error = 0;                                                              // Error = False if condition is not met
	}
}

void Pre_game()
{
	char filename[15],file_directory[20];							   			// Create 2 string variable with 15 spaces (Increase the value is user enter more character)
    bool scr_name_bl, random_start_pos_bl;                                      // Create 2 boolean variable
    int mission;										             	        // Create 1 integer variable
	
	do
	{
		printf("\nPlease enter the scenario file's name        : ");
		scanf("%s",filename);                                                   // User to enter file name in string
		while (getchar() != '\n');												// Clear buffer
		snprintf(file_directory, sizeof(file_directory), "./%s", filename);		// Empty the string before combining both string, creating path file for directory Ex. ./Scenario05.dat									
    	printf("Checking path: %s\n", file_directory);
    	if(access(file_directory,F_OK) == -1)									// Checking file exist, F_OK is a flag that check file exist, if exist will return 0 else -1
    	{										
    		printf("File does not exist \n");
    	}
    }
    while(access(file_directory,F_OK) == -1);
    printf("\n");																// Print new line

    do                       
    {
    	printf("Is the scenario name encrypted          (y/n): ");
    	char_checker();															// Run char_checker Loop	
    	if(Error == 1 || (user_input_c != 'y' && user_input_c != 'n'))          // Check if variable is y or n or is there error from char_checker
    	{
      		printf("Invalid character. Please enter 'y' or 'n'.\n");          	// Print out error message if condition is met
    	}
   		else                                                                    
    	{
        	scr_name_bl = user_input_c == 'y'? 1 : 0;                           // If condition is met, scr_name_bl will store 1 if input is y, else 0
    	}
    	printf("\n");
    }
    while(Error == 1 || (user_input_c != 'y' && user_input_c != 'n'));          // If user did not met if condition, do loop will repeat until condition is not met.

    do
    {
    	printf("Do you wish to randomize start position (y/n): ");
    	char_checker();															// Run char_checker Loop
    	if(Error == 1 || (user_input_c != 'y' && user_input_c != 'n'))          // Check if variable is y or n or is there error from char_checker
    	{
    		printf("Invalid character. Please enter 'y' or 'n'.\n");            // Print out error message if condition is met

    	}
   		else                                                                    
    	{
        	random_start_pos_bl = user_input_c == 'y'? 1 : 0;                   // If condition is met, random_start_pos_bl will store 1 if input is y, else 0
    	}
    	printf("\n");
	}
	while(Error == 1 || (user_input_c != 'y' && user_input_c != 'n'));          // If user did not met if condition, do loop will repeat until condition is not met.

    printf("Please select mission type below\n\n");
    printf(" 1) Casual Explore\n");
    printf(" 2) Find  1   End Point\n");
    printf(" 3) Reach 1   End Point \n");
    printf(" 4) Find  ALL End Point \n");
    printf(" 5) Reach ALL End Point \n");
    printf(" 6) Reach ALL Danger Point \n");
    printf(" 7) Find Map Boundaries \n");
    printf(" 8) Explore Everything \n\n");

    do
    {
    	printf("Enter your choice (1-8) : ");                                   
    	int_checker();                                                          // Run int_checker Loop 
    	if(Error == 1 || user_input <= 0 || user_input > 8 )                    // Check if variable is between 1 to 8 or is there error from int_checker
    	{
    		printf("Please enter 1 - 8. \n\n");                					// Print out error message if condition is met
    	}          
    }
    while(Error == 1 || user_input <= 0 || user_input > 8) ;                    // If user did not met if condition, do loop will repeat until condition is not met.
    mission = user_input;                                                       // Store mission number from user_input
    printf("\n");
    printf("filename : %s, is FileEncrypted : %d, randomizeStartposition : %d \n",filename,scr_name_bl,random_start_pos_bl); // print string file name and both boolean 
    My_vehicle = SCRelay_Signal_Veh_Init(filename,&scr_name_bl,&random_start_pos_bl,mission); // Sent out data to header file and gets and output
}
