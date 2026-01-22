#include <iostream>
#include <limits> 																//for clearing buffer
#include <filesystem>															//to check file
#include <cstring>
#include "../inc/Main.h"

using namespace std;
namespace fs = std::filesystem;

extern string input;															//From Main.cpp

string scr_filename = "default.dat";
bool scr_encrypted = 1;
bool rdm_pos = 0;
int mission_type = 20;
string rpt_filename = "map-rpt.txt";
string scr_filename_dir;

void Autopilot_settings()
{	
	string user_input;
	do
	{
		cout << "	[ Configure Autopilot Mapping Exploration settings ] \n\n";
    	cout << "	a) Specify INPUT scenario filename (current: " << scr_filename << ")\n";
    	cout << "	b) Specify INPUT scenario file encrypted (current: " << (scr_encrypted?'Y':'N') << ") \n";
    	cout << "	c) Specify OUTPUT map report filename (current: " << rpt_filename << ")\n";
    	cout << "	d) Back to main menu\n\n";
    	cout << "	Please enter your choice (a – d): ";
    	getline(cin,input);														//get input from user
		cout <<"\n";
		if (input.length() == 1)												//check for one char
		{
			input[0] = tolower(input[0]);										//lower first char of the input
			switch (input[0])
			{
				case 'a':														//if user enter a
					do
					{
						do
						{
							cout << "	Please enter INPUT scenario filename (current: " << scr_filename << "): ";
							getline(cin,user_input);																		// user to enter filename
        					if (user_input.length() <= 4 || user_input.substr(user_input.length() - 4) != ".dat")			//check if '.txt' file extension
        					{
        						cout << "	Please enter INPUT scenario filename with '.dat'. \n\n";
        					}
        				}while(user_input.length() <= 4 || user_input.substr(user_input.length() - 4) != ".dat");
        				scr_filename_dir= "./input-files/" + user_input;													// add file directory ex: ./input-file/default.dat
        				if  (fs::exists(scr_filename_dir))																	// check file exist from scr_filename_dir
        				{
        					cout <<"\n";
							cout << "	INPUT scenario filename successfully set to '" << user_input << "'!\n";
						}
						else
						{
							cout << "	File does not Exist. \n\n";
						}
					}while(!fs::exists(scr_filename_dir));						// repeat until scenario file is found
					scr_filename = user_input;
					break;
					
				case 'b':
					scr_encrypted = !scr_encrypted;								// toggle scr_encrypted example 1 to 0
					break;
					
				case 'c':
					do
					{
						do
						{
							//rpt_filename = "map-rpt.txt";
							cout << "	Please enter OUTPUT map report filename (current: " << rpt_filename << "): ";
							getline(cin,user_input);
        					if (user_input.length() <= 4 || user_input.substr(user_input.length() - 4) != ".txt")		//check if '.txt' fil extension
        					{
        						cout << "	Please enter OUTPUT scenario filename with '.txt'. \n\n";
        					}
        				}while(user_input.length() <= 4 || user_input.substr(user_input.length() - 4) != ".txt");
        				rpt_filename = user_input;
        				if  (!fs::exists(rpt_filename))																	// check if file has been created before
        				{
        					cout <<"\n";
        					cout << "	File available to use: "<<rpt_filename<<"\n";
        					cout << "	OUTPUT map report filename successfully set to '" << rpt_filename << "'!\n";
        				}
        				else
        				{
        					cout << "	Duplicate file. \n";													//if duplicate, prompt user to overite file or input new filename
        					do
 							{
 								cout << "	Do you wish to use the same file? (y/n) : ";
								getline(cin,user_input);
								user_input[0] = tolower(user_input[0]);											//lower first char of the input
								if (user_input != "y" && user_input != "n")
								{
									cout << "	Wrong input. Please enter (y/n).\n\n";
								}
							}while(user_input != "y" && user_input != "n");
							cout <<"\n";
        				}
					}while(fs::exists(rpt_filename) && user_input != "y");										//if user enter y or the file has not be used, continue program
					break;
				case 'd':
					break;
				default:
					cout <<"	Please enter your choice a to d. \n\n";
					break;
			}
			cout <<"\n";
		}
		else
		{
			cout <<"	Please enter your choice a to d. \n\n";
		}
	}while(input[0] != 'd');
}
