#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../inc/SatComRelay.h"                                                  // Link header file to souce file

VehDataType My_vehicle;	    													// Link Header file "VehDataType" to current program "My_vehicle"

#define ROWS 31
#define COLS 61   

//Pre-game to Post Game
char user_input_c, extra_character, scanresult;                                 // Create 2 Character for Global variable  
bool Error;                                                                     // Create 1 boolean for Global variable
int result, user_input;                                                         // Create 2 integer for Global variable 

//Post Game
int scanned, movement;
long before_energy,before_shield;                          						// Create 2 long variable
bool File_Print;
FILE *file;

//Post Game dictionary
typedef struct {
    char character;
    int count;
} Scanned_Counter;

typedef struct {
    char character;
    int count;
    int energy;  
    int shield;	 // travelled counter
} CharCounter2;

// Matrix Game
char S_matrix[ROWS][COLS];
char T_matrix[ROWS][COLS];
int midRow = ROWS / 2; // Calculate the middle row index
int midCol = COLS / 2; // Calculate the middle column index

Scanned_Counter S_1_terrain[] = {{'#', 0}, {' ', 0}, {'j', 0}, {'M', 0}, {'~', 0}, {'X', 0}, {'S', 0}, {'E', 0}, {'?', 0}, {'f', 0}, {'h', 0}, {'w', 0}};
Scanned_Counter S_2_terrain[] = {{'#', 0}, {' ', 0}, {'j', 0}, {'M', 0}, {'~', 0}, {'X', 0}, {'S', 0}, {'E', 0}, {'?', 0}, {'f', 0}, {'h', 0}, {'w', 0}};
CharCounter2 T_terrain[] = {{'#', 0, 0, 0}, {' ', 0, 0, 0}, {'j', 0, 0, 0}, {'M', 0, 0, 0}, {'~', 0, 0, 0}, {'X', 0, 0, 0}, {'S', 0, 0, 0}, {'E', 0, 0, 0}, {'f', 0, 0, 0}, {'h', 0, 0, 0}, {'w', 0, 0, 0}};



void char_checker();                                                            // Check Character
void int_checker();                                                             // Check integer
void Pre_game();                                                                // Run Pre game
void Game();																	// Run Game
void Game_Usage_instruction();													// Run Game Info
void Info_vehicle_status();														// Run Info on vehicle status
void Vehicle_Movement();
void Vehicle_Scan(int radius);
void F_Scanned_Map();
void Post_Game();

void Scanned_Update(Scanned_Counter counters[], int size, char input);
void Scanned_Print(const Scanned_Counter counters[], int size, const char *setName);
void T_counter(CharCounter2 counters[], int size, char input, int energyUsed, int shieldUsed);
void printT_counter(const CharCounter2 counters[], int size, const char *setName);

//Matrix
void printscanMatrix() ;
void printtravelMatrix(); 

int main()
{
	
    Pre_game();
    Game();
    Post_Game();

    return 0;
}

void char_checker()
{
	Error = 0;
	scanf("%c%c", &user_input_c, &extra_character);                    // Input from keyboard store to user_input_c and extra_character, result store in result variable
	if (extra_character != '\n')				                                // Check if extra_character is not empty and result is not equal to 2
	{
		printf("Input is not char. \n\n");                                      // Print error message if condition is met
		while (getchar() != '\n');                                              // Clear buffer
		Error = 1;                                                              // Error = TRUE if condition is met
	}
	user_input_c = tolower(user_input_c);										// Lower case user input
}

void int_checker()
{
	Error = 0;
	result = scanf("%d%c", &user_input, &extra_character);                      // Input from keyboard store to user_input_c and extra_character, result store in result variable
	printf("result = %d \n",result);
	if (extra_character != '\n' || result != 2)                                 // Check if extra_character is not empty and result is not equal to 2
	{
		printf("Input is not integer. ");                                       // Print error message if condition is met
		while (getchar() != '\n');                                              // Clear buffer
		Error = 1;                                                              // Error = TRUE if condition is met
	}
}

void Pre_game()
{
	char filename[15], file_directory[30];							   			// Create 2 string variable with 15 spaces (Increase the value is user enter more character)
    bool scr_name_bl, random_start_pos_bl;                                      // Create 2 boolean variable
    int mission;										             	        // Create 1 integer variable
	
	do
	{
		printf("\nPlease enter the scenario file's name        : ");
		scanf("%s",filename);                                                   // User to enter file name in string Ex. Scenario05.dat
		while (getchar() != '\n');												// Clear buffer
		snprintf(file_directory, sizeof(file_directory), "./%s", filename);		// Empty the string before combining both string, creating path file for directory Ex. ./Scenario05.dat									
    	printf("Checking path: %s. \n", file_directory);
    	if(access(file_directory,F_OK) == -1)									// Checking file exist, F_OK is a flag that check file exist, if exist will return 0 else -1
    	{										
    		printf("File does not exist. \n");
    	}
    	else
    	{
    		printf("File Exist. \n");
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

void Game()
{
	int radius = 1;
	long energyToAllocate;

    for (int i = 0; i < ROWS; i++)												// Set size for scan matrix 
    {
        for (int j = 0; j < COLS; j++) 
        {
            S_matrix[i][j] = ' ';
        }
    }
    for (int i = 0; i < ROWS; i++) 												// Set size for travel
    {
        for (int j = 0; j < COLS; j++) 
        {
            T_matrix[i][j] = ' ';
        }
    }
	
	Game_Usage_instruction();
	do
	{
		printf("Enter your command (q to quit) : ");
		char_checker();
		printf("\n");
		
		if (Error == 0)
		{
			switch(user_input_c)
			{
				case 'q': 
					break;
					
				case 'v': 
					Game_Usage_instruction();
					break;
					
				case 'w':		
				case 'a':
				case 's': 
				case 'd': 
					Vehicle_Movement();
					break;
					
				case '1':
				case '2':
				case '3':
				case '4':
				case '6':
				case '7':
				case '8':
				case '9':
					Vehicle_Scan(radius);
					break;
					
				case 't': 
					radius = (radius == 1) ? 2 : 1;
        			printf("Toggle Scan Radius => now set to %d terrain units! \n",radius);
					break;
					
				case 'i':
					printf("Enter amt. of energy to increase / allocate to shields (1 - 100000) : ");
					scanf(" %ld",&energyToAllocate);                                    // Enter amount of energy to allocate
					while (getchar() != '\n'); 
        			My_vehicle = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);    // Send out energy to allocate to header file and gets output
        			printf("\n");
					break;
					
				case 'z':
					printf("Vehicle Status / Statistics : \n\n");
        			Info_vehicle_status(); 												//Print status of vehicle 
					break;
					
				case 'x':
					printf("Currently Explored Terrain Layout : \n");
					printtravelMatrix(T_matrix, midRow, midCol);
					break;
					
				case 'c':
					//printf("Currently Scanned Terrain Layout : \n");
					printscanMatrix(S_matrix, midRow, midCol);
					break;
					
				default:
					printf("Invalid Command : '%c', please try again!\n",user_input_c);
					break;
			}
		}
		printf("\n");
	}
	while(user_input_c != 'q');													// Check 'y' key enter if not loop
}
void Game_Usage_instruction()
{
    printf("\n\n");
    printf("********************************************* \n");
    printf("*** Welcome to Team 1 Vehicle Simulator ! *** \n");
    printf("********************************************* \n\n\n");
    printf("[ Usage Instructions ] \n\n");
    printf("------------------------------------------------------------------------------------ \n\n");
    printf("Enter 'q' to Quit\n\n");
    printf("Enter 'v' to show this Usage Instruction (again ..) \n\n");
    printf("'w', 's', 'a', 'd' keys to MOVE vehicle North South, West & East \n\n");
    printf("Enable 'Numlock', (right key pad), keys 1-9 (except 5) to SCAN terrain : \n");
    printf("SW (1), S(2), SE (3), W (4), E (6), NW (7), N(8), NE (9) respectively \n\n");
    printf("'t' Key = Toggle Scan Radius (betw. 1-2) \n\n");
    printf("'i' Key = increase / divert energy to shield \n\n");
    printf("'z' Key = Info on Vehicle Status \n");
    printf("'x' Key = Map of terrain scanned by vehicle \n");
    printf("'c' Key = Map of terrain travelled by vehicle \n\n");
    printf("Note : In map display, ' ' underline indicates curr. veh. location!\n\n");
    printf("------------------------------------------------------------------------------------ \n\n"); 

    do                                                       				 
    {
    	printf("press'y' key and hit Enter to continue: ");
    	char_checker();
    	printf("\n");
	}
	while(user_input_c != 'y');													// Check 'y' key enter if not loop
}

void Info_vehicle_status()
{
	My_vehicle.totEnergyUsed = My_vehicle.totEnergyUsed - (movement*90);
	My_vehicle.currEnergy = My_vehicle.currEnergy + (movement*90);
	printf("Initial Enrg : %1ld, Tot Enrg Use : %1ld, Tot Shld Enrg Use : % 1ld, Engy Left : %1ld, Shld Enrg Left : %1ld \n\n", My_vehicle.initialEnergy, My_vehicle.totEnergyUsed, My_vehicle.totShieldEnergyUsed, My_vehicle.currEnergy, My_vehicle.currShieldEnergy);
}

void printscanMatrix() 
{
	printf("Currently Scanned Terrain Layout : \n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (i == midRow && j == midCol) 
            {
                printf("\033[4m"); // Start underlining
            }

            char currentChar = S_matrix[i][j];

            switch (currentChar) 
            {
                case '#': 
                case 'X':
                    printf("\033[31m%c\033[0m", currentChar);  // Red
                    break;
                    
                case '-':
                	printf("\033[34m%c\033[0m", currentChar);  // Blue
                    break;
                    
                case 'M':
                    printf("\033[35m%c\033[0m", currentChar);  // Purple
                    break;
                
                case 'E':
                	printf("\033[37m%c\033[0m", currentChar);  // White
                    break;
                    
                case 'h':
                case 'f':
                    printf("\033[32m%c\033[0m", currentChar);  // Green
                    break;
                case 'w':
                    printf("\033[33m%c\033[0m", currentChar);  // yellow
                    break;
                case '~':
                    printf("\033[36m%c\33[0m", currentChar);  // Cyan
                    break;
                    
                default:
                    printf("%c", currentChar);  // Default formatting for other characters
                    break;
            }
            if (i == midRow && j == midCol) 
            {
                printf("\033[0m "); // Stop underlining and reset formatting
            }
            else 
            {
                printf(" "); // Ensure spacing is consistent
            }
        }
        printf("\n");
    }
}

void printtravelMatrix() 
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (i == midRow && j == midCol) 
            {
                printf("\033[4m"); // Start underlining
            }
            
            char currentChar = T_matrix[i][j];
            
            switch (currentChar) 
            {
                case 'X':
                    printf("\033[31m%c\033[0m", currentChar);  // Red
                    break;
                case 'M':
                    printf("\033[35m%c\033[0m", currentChar);  // Purple
                    break;
                case 'h':
                case 'f':
                case 'j':
                    printf("\033[32m%c\033[0m", currentChar);  // Green
                    break;
                case 'w':
                    printf("\033[33m%c\033[0m", currentChar);  // yellow
                    break;
                case '~':
                    printf("\033[36m%c\33[0m", currentChar);  // cyan
                    break;
                case 'E':
                    printf("\033[37m%c\33[0m", currentChar);  // white
                    break;
                case '_':
                	if (i == midRow && j == midCol) 
                	{
                		printf("_");
                		
                	}
                	else
                	{
                		printf("\033[47;37m%c\33[0m", currentChar); // White background with white word
                	}
                	break;
                default:
                    printf("%c", currentChar);  // Default formatting for other characters
                    break;
            }
  

            if (i == midRow && j == midCol) 
            {
                printf("\033[0m "); // Stop underlining and reset formatting
            }
            else 
            {
                printf(" "); // Ensure spacing is consistent
            }
        }
        printf("\n");
    }
}

void Vehicle_Movement()
{
	movement++;
    before_shield = My_vehicle.totShieldEnergyUsed;
	switch(user_input_c)
	{
		case 'w':
			scanresult = SCRelay_Signal_Veh_ScanNorth(&My_vehicle);		//Move Up
			before_energy = My_vehicle.totEnergyUsed;
			My_vehicle = SCRelay_Signal_Veh_MoveUpNorth();	
			if (scanresult != '?' && scanresult != '#')
			{
				midRow -= 1;
				T_matrix[midRow][midCol] = scanresult;
			}
			break;
			
		case 'a':
			scanresult = SCRelay_Signal_Veh_ScanWest(&My_vehicle);		// Move Left
			before_energy = My_vehicle.totEnergyUsed;
			My_vehicle = SCRelay_Signal_Veh_MoveLeftWest();
			if (scanresult != '?' && scanresult != '#')
			{
				midCol -= 1;
				T_matrix[midRow][midCol] = scanresult;
			}
			break;
					
		case 's': 
			scanresult = SCRelay_Signal_Veh_ScanSouth(&My_vehicle);		//Move Down
			before_energy = My_vehicle.totEnergyUsed;
			My_vehicle = SCRelay_Signal_Veh_MoveDownSouth(); 
			if (scanresult != '?' && scanresult != '#')
			{
				midRow += 1;
				T_matrix[midRow][midCol] = scanresult;
			}
			break;
					
		case 'd': 
			scanresult = SCRelay_Signal_Veh_ScanEast(&My_vehicle);		//Move Right
			before_energy = My_vehicle.totEnergyUsed;
			My_vehicle = SCRelay_Signal_Veh_MoveRightEast(); 
			if (scanresult != '?' && scanresult != '#')
			{
				midCol += 1;
				T_matrix[midRow][midCol] = scanresult;
			}
			break;
	}
	if(scanresult == ' ')
    {
        T_matrix[midRow][midCol] = '_';
    }
    T_counter(T_terrain, sizeof(T_terrain) / sizeof(T_terrain[0]), scanresult, My_vehicle.totEnergyUsed - before_energy, My_vehicle.totShieldEnergyUsed - before_shield);
	Info_vehicle_status();
	printtravelMatrix(T_matrix, midRow, midCol);
}
void Vehicle_Scan(int radius)
{
	scanned++;                                                   	     	  // increase counter by 1 if above condition is met
    before_energy = My_vehicle.totEnergyUsed;                            	  // store before energy before scanning
	if(radius == 1)
	{
		switch (user_input_c)													
		{
			case '1':															// South West
				scanresult = SCRelay_Signal_Veh_ScanSouthWest (&My_vehicle);    // Scan South West 1 and store result into scanresult
				S_matrix[midRow+1][midCol-1] = scanresult;						// Put result into South West 1
				printf("SW 1 \n");
				break;
				
			case '2':														   // South
				scanresult = SCRelay_Signal_Veh_ScanSouth (&My_vehicle);       // Scan South 1 and store result into scanresult
				S_matrix[midRow+1][midCol] = scanresult;					   // Put result into South 1
				printf("S 1 \n");
				break;
				
			case '3':														   // South South East
				scanresult = SCRelay_Signal_Veh_ScanSouthEast (&My_vehicle);   // Scan South East 1 and store result into scanresult
				S_matrix[midRow+1][midCol+1] = scanresult;					   // Put result into South East 1
				printf("SE 1 \n");
				break;
						
			case '4':														   // Scan West
				scanresult = SCRelay_Signal_Veh_ScanWest (&My_vehicle);        // Scan West 1 and store result into scanresult
				S_matrix[midRow][midCol-1] = scanresult;					   // Put result into West 1
				printf("W 1 \n");
				break;
						
			case '6':														   // Scan East
				scanresult = SCRelay_Signal_Veh_ScanEast (&My_vehicle);        // Scan East 1 and store result into scanresult
				S_matrix[midRow][midCol+1] = scanresult;					   // Put result into East 1
				printf("E 1 \n");
				break;
						
			case '7':														   // San North West
				scanresult = SCRelay_Signal_Veh_ScanNorthWest (&My_vehicle);   // San North West 1 and store result into scanresult
				S_matrix[midRow-1][midCol-1] = scanresult;					   // Put result into North West 1
				printf("NW 1 \n");
				break;
						
			case '8':														   // Scan North
				scanresult = SCRelay_Signal_Veh_ScanNorth (&My_vehicle);       // Scan North 1 and store result into scanresult
				S_matrix[midRow-1][midCol] = scanresult;					   // Put result into North 1
				printf("N 1 \n");
				break;
						
			case '9':														   // Scan North East
				scanresult = SCRelay_Signal_Veh_ScanNorthEast (&My_vehicle);   // Scan North East 1 and store result into scanresult
				S_matrix[midRow-1][midCol+1] = scanresult;					   // Put result into East 1
				printf("NE 1 \n");
				break;
						
		}
		Scanned_Update(S_1_terrain, sizeof(S_1_terrain) / sizeof(S_1_terrain[0]), scanresult);
	}	
	else if (radius == 2)
	{
		switch (user_input_c)													
		{
			case '1':															// South West
				scanresult = SCRelay_Signal_Veh_ScanSouthWest2 (&My_vehicle);    // Scan South West 2 and store result into scanresult
				S_matrix[midRow+2][midCol-2] = scanresult;						// Put result into South West 2
				printf("SW 2 \n");
				break;
				
			case '2':														   // South
				scanresult = SCRelay_Signal_Veh_ScanSouth2 (&My_vehicle);       // Scan South 2 and store result into scanresult
				S_matrix[midRow+2][midCol] = scanresult;					   // Put result into South 2
				printf("S 2 \n");
				break;
				
			case '3':														   // South South East
				scanresult = SCRelay_Signal_Veh_ScanSouthEast2 (&My_vehicle);   // Scan South East 2 and store result into scanresult
				S_matrix[midRow+2][midCol+2] = scanresult;					   // Put result into South East 2
				printf("SE 2 \n");
				break;
						
			case '4':														   // Scan West
				scanresult = SCRelay_Signal_Veh_ScanWest2 (&My_vehicle);        // Scan West 2 and store result into scanresult
				S_matrix[midRow][midCol-2] = scanresult;					   // Put result into West 2
				printf("W 2 \n");
				break;
						
			case '6':														   // Scan East
				scanresult = SCRelay_Signal_Veh_ScanEast2 (&My_vehicle);        // Scan East 2 and store result into scanresult
				S_matrix[midRow][midCol+2] = scanresult;					   // Put result into East 2
				printf("E 2 \n");
				break;
						
			case '7':														   // San North West
				scanresult = SCRelay_Signal_Veh_ScanNorthWest2 (&My_vehicle);   // San North West 2 and store result into scanresult
				S_matrix[midRow-2][midCol-2] = scanresult;					   // Put result into North West 2
				printf("NW 2 \n");
				break;
						
			case '8':														   // Scan North
				scanresult = SCRelay_Signal_Veh_ScanNorth2 (&My_vehicle);       // Scan North 2 and store result into scanresult
				S_matrix[midRow-2][midCol] = scanresult;					   // Put result into North 2
				printf("N 2 \n");
				break;
						
			case '9':														   // Scan North East
				scanresult = SCRelay_Signal_Veh_ScanNorthEast2 (&My_vehicle);   // Scan North East 2 and store result into scanresult
				S_matrix[midRow-2][midCol+2] = scanresult;					   // Put result into East 2
				printf("NE 2 \n");
				break;
			}
			Scanned_Update(S_2_terrain, sizeof(S_2_terrain) / sizeof(S_2_terrain[0]), scanresult);
		}
		printf("Returned (scanned) terrain symbol is '%c'. Energy used '%ld'. \n\n",scanresult,My_vehicle.totEnergyUsed - before_energy);  // Print out symbol scanned
		Info_vehicle_status();
		printscanMatrix(S_matrix, midRow, midCol);

}

void Scanned_Update(Scanned_Counter counters[], int size, char input)//, int energyUsed) 
{
    for (int i = 0; i < size; i++) 
    {
        if (counters[i].character == input) {
            counters[i].count++;
        }
    }
}

void T_counter(CharCounter2 counters[], int size, char input, int energyUsed, int shieldUsed) 
{
    for (int i = 0; i < size; i++) {
        if (counters[i].character == input) {
            counters[i].count++;
            counters[i].energy = energyUsed;
            counters[i].shield = shieldUsed;
        }
    }
}

void Scanned_Print(const Scanned_Counter counters[], int size, const char *setName) 
{
    printf("%s \n", setName);
    for (int i = 0; i < size; i++) {
        printf("Type '%c' : %d \n", counters[i].character, counters[i].count);
    }
}

void printT_counter(const CharCounter2 counters[], int size, const char *setName) 
{
    printf("%s:\n", setName);
    for (int i = 0; i < size; i++) {
        printf("Type '%c' : %d time, %d energy, %d shield energy. \n",
               counters[i].character, counters[i].count, counters[i].energy, counters[i].shield);
    }
}

void F_Scanned_Map()
{
    fprintf(file, "Currently Scanned Terrain Layout : \n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) 
        {
        	char currentChar = S_matrix[i][j];
            if (i == midRow && j == midCol) 
            {
                fprintf(file, "_ ");
            }
            else
            {
            	fprintf(file, "%c ", currentChar);
            }
        }
       	fprintf(file, "\n");
     }
}

void Post_Game()
{
    char filename[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    File_Print = 1;	
    
    strftime(filename, sizeof(filename), "./logs/output_Scan_Map_%Y%m%d_%H%M%S.txt", t); //Create new file and name
    file = fopen(filename, "w");												// Open File
    if (file == NULL) 															//Check file can be open
    {
        printf("Error opening file!\n");
    }
	
	printf("---------------------------------- \n");
    printf("--- Team 1 Exploration Report! --- \n");
    printf("---------------------------------- \n\n\n");
    printf("Total no. of scans             taken: %d \n", scanned);
    printf("Total no. of movements (steps) taken: %d \n\n",movement);
    printf("[Energy Report] \n\n");
    printf("Initial Energy           : % 1ld \n", My_vehicle.initialEnergy);
    printf("Total Energy Used        : % 1ld \n", My_vehicle.totEnergyUsed);
    printf("Total Shield Energy Used : % 1ld \n", My_vehicle.totShieldEnergyUsed);
    printf("Energy Left              : % 1ld \n", My_vehicle.currEnergy);
    printf("Shield Energy Left       : % 1ld \n\n", My_vehicle.currShieldEnergy);
    printf("[Terrain type Scanned] \n\n");
    Scanned_Print(S_1_terrain, sizeof(S_1_terrain) / sizeof(S_1_terrain[0]), "[1 terrain units]");
    printf("\n");
    Scanned_Print(S_2_terrain, sizeof(S_2_terrain) / sizeof(S_2_terrain[0]), "[2 terrain units]");
    printf("\n");
    printT_counter(T_terrain, sizeof(T_terrain) / sizeof(T_terrain[0]), "[Terrain type Explored]");
    F_Scanned_Map();
	SCRelay_Signal_Veh_Close ();
    
    fclose(file);
}
