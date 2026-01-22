#include <iostream>
#include <string>			//for std:String
#include <ctime>			// for time
#include <unistd.h> 		// For sleep()
#include <filesystem>		//to check file
#include <fstream>			//to create file
#include <vector>			//to store map
#include <map>				// For storing of dictionary values	
#include <set>

#include "../inc/Main.h"

using namespace std;
namespace fs = std::filesystem;

extern string scr_filename;				//Autopilotsettings.cpp
extern bool scr_encrypted;				//Autopilotsettings.cpp
extern bool rdm_pos;					//Autopilotsettings.cpp
extern int mission_type;				//Autopilotsettings.cpp
extern string rpt_filename;				//Autopilotsettings.cpp
extern string scr_filename_dir;			//Autopilotsettings.cpp

extern string input;

//Mapping.cpp
extern vector<vector<char>> matrix;

extern int width; //Game.cpp
extern int x_max;	//Game.cpp
extern int y_max;	//Game.cpp

extern std::map<char, std::pair<int, int>> terrainEnergy;

string Display_Map;
set<std::string> used_scenarios;


void Autopilot_mapping()			//Autopilotmapping.cpp
{
	
  	char start_time[50];
  	char stop_time[50];
  	struct tm * datetime;
  	
  	time_t start;
  	time_t end;
  	
  	ofstream null_stream("/dev/null");         				// remove cout from printing
    streambuf* original_buf = std::cout.rdbuf(); 			// save original cout

	cout << "	[Start Autopilot Mapping]\n\n";
	cout << "	INPUT scenario file name  = "<< scr_filename << "\n";
	cout << "	INPUT scenario file encrypted  = " <<(scr_encrypted?'Y':'N')<< "\n";
	cout << "	OUTPUT map report filename = "<< rpt_filename <<"\n\n";
	
	if (used_scenarios.count(scr_filename) > 0)
	{
		cout << "\n	Scenario file '" << scr_filename << "' has already been used. Please choose a different file.\n\n";
		return;
	}
	
	if  (!fs::exists(scr_filename_dir))						//check if scenario file can be open, if cant open, user to re enter output file in option 2
	{
		cout << "	Scenario file name("<< scr_filename << ") not found. \n\n";	
		return;
	}
	ofstream file(rpt_filename);							//create and open output file
	if  (fs::exists(rpt_filename) && !file.is_open())		//open file
    {
    	cout << "	Unable to create"<< rpt_filename << "\n\n";
    	return;
    }
    
    if (fs::exists(scr_filename_dir)&&fs::exists(rpt_filename))	//check if both file can be open
    {
	    do
	    {
	    	cout << "	When mapping ends, do you wish to display map report on ubuntu terminal? (Y/N) : ";
			getline(cin,Display_Map);							//user to enter y or n
			Display_Map[0] = toupper(Display_Map[0]);
	    }while(Display_Map != "Y"&&Display_Map != "N");
	    
	    
	    cout <<"\n";
	    
	   do
 	   {
 		   	cout << "	BEGIN NOW? (Y): ";
			getline(cin,input);										//user to enter y or n
			input[0] = toupper(input[0]);
		}while(input != "Y");
		cout <<"\n";
		time(&start);
  		datetime = localtime(&start);								//store current time
		strftime(start_time, 50, "%d/%m/%y, %H:%M:%S", datetime);	//display current time
		cout << "	Autopilot Mapping STARTED!	Start datetime stamp = " << start_time << "\n\n";
    
		cout <<"\n\n";
	
		cout << "		MAPPING IN PROGRESS..PLEASE DO NOT END PROGRAM !";
		cout <<"\n\n";
		
		if (Display_Map == "N" )								// if display map is N, cout will be masked off and nothing will be printed.
	    {
   		 	cout.rdbuf(null_stream.rdbuf());
	    }
	    
		Game();													//Start of game
		
		cout.rdbuf(original_buf); 								//put cout to normal
		
		cout <<"\n";
		time(&end);												//store end time
  		datetime = localtime(&end);
		strftime(stop_time, 50, "%d/%m/%y, %H:%M:%S", datetime);
    	cout << "	Autopilot Mapping ENDED!	End datetime stamp = " << stop_time << "\n\n";		//display end time
		int Mapping_Dur = difftime(end, start);
		cout << "\n	Total Mapping Duration: "<<Mapping_Dur/3600 <<"hr "<<(Mapping_Dur%3600)/60 <<"min " <<(Mapping_Dur%3600)%60 <<"sec \n\n";
		
		//start print to file
		file << "INPUT scenario file name           = "<<scr_filename<< "\n";					//Print to file
    	file << "INPUT scenario file name encrypted = "<<(scr_encrypted?'Y':'N')<<"\n";			//Print to file
    	file << "OUTPUT map report filename         = "<<rpt_filename<<"\n\n";					//Print to file
    	
    	file << "Start datetime stamp    = " << start_time << "\n";								//Print to file
    	file << "End datetime stamp      = " << stop_time << "\n\n";							//Print to file
    	file << "Total Mapping Duration: "<<Mapping_Dur/3600 <<"hr "<<(Mapping_Dur%3600)/60 <<"min " <<(Mapping_Dur%3600)%60 <<"sec \n\n";

		
		file << setw(width) << " ";							//store map to file
    	for (int j = 0; j < x_max; j++) 
    	{
        	file << setw(width) << j;
   		}
    	file << "\n";

    	for (int i = 0; i < y_max; i++) {
        	file << setw(width) << i;
        	for (int j = 0; j < x_max; j++) 
        	{
            	file << setw(width) << matrix[i][j];
        	}
        	file << "\n";
    	}
    	file <<"\n\n";
    	
    	file << left << setw(15) << "Terrain" 				//store energy to file
					 << setw(15) << "Movt Enrg" 
					 << setw(15) << "Shld Enrg" << endl;
				  
		file << left << setw(15) << "Symbol" 
    				 << setw(15) << "Reqd:" 
    				 << setw(15) << "Reqd:" << endl;

   	 	for (const auto& entry : terrainEnergy) 
   	 	{
        	//char terrainType = entry.first;
       		int value1 = entry.second.first;
        	int value2 = entry.second.second;

        	if (value1 == 0 && value2 == 0) 
        	{
           		file << setw(15) << (string("'") + entry.first + "'") 
           			 << setw(15) << "N.A" 
           		 	 << setw(15) << "N.A" << "\n";
        	} 
        	else 
        	{
           		file << setw(15) << (string("'") + entry.first + "'") 
           			 << setw(15) << entry.second.first 
           		     << setw(15) << entry.second.second << "\n";
        	}
      	}
    	file <<"\n";

    	file.close();							//close file
		
		cout << "	Map report saved to: "<< rpt_filename <<"\n\n";
		if (Display_Map == "Y")												//display map on ubuntu if user enter Y
		{
			cout << "	Displaying contents of : "<< rpt_filename <<" on ubuntu terminal \n\n";
			printMatrix();
			cout <<"\n";
			Print_Energy();
		}
	}
	do
	{
		cout << "	Press <Enter> to go back to main menu ... ";
		getline(cin,input);
	}while(!input.empty());
	cout << "\n\tGoing back to main menu ... \n\n";
	used_scenarios.insert(scr_filename);
}
