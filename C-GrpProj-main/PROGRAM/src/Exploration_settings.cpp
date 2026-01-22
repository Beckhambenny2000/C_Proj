#include <iostream>
#include "../inc/Main.h"
#include <filesystem>	//to check file

using namespace std;
namespace fs = std::filesystem;

extern string input;	//From Main.cpp

string map_rpt_filename = "map-rpt.txt";
string route_rpt_filename = "route-rpt.txt";
string IdealRoute = "minimized total energy expenditure";
string VehicleType = "HighLander";

void Exploration_settings()
{	
    //char vehchoice, choice;
    string user_input;
    
	do
	{
		cout << "	[ Configure Terrain Exploration Simulator settings ] \n\n";
    	cout << "	a) Specify INPUT map details filename (current: " << map_rpt_filename << ")\n";
    	cout << "	b) Specify OUTPUT route report filename (current: " << route_rpt_filename << ") \n";
    	cout << "	c) Specify ideal route criteria (current: " << IdealRoute << ")\n";
    	cout << "	d) Specify vehicle type (current: " << VehicleType << ")\n";
    	cout << "	e) Back to main menu\n\n";
    	cout << "	Please enter your choice (a – e): ";
    	getline(cin,input);
		cout <<"\n";
		if (input.length() == 1)
		{
			input[0] = tolower(input[0]);								//lower first char of the input
			switch (input[0])
			{
				case 'a':
        			do
					{
						cout << "	Please enter INPUT map details filename (current: " << map_rpt_filename << "): ";
						getline(cin,map_rpt_filename);
        				if (map_rpt_filename.length() <= 4 || map_rpt_filename.substr(map_rpt_filename.length() - 4) != ".txt")		//check if '.txt' fil extension
        				{
        					cout << "	Please enter INPUT scenario filename with '.txt'. \n\n";
        				}
        			}while(map_rpt_filename.length() <= 4 || map_rpt_filename.substr(map_rpt_filename.length() - 4) != ".txt");
					break;
					
				case 'b':
					do
					{
						do
						{
							cout << "	Please enter OUTPUT route report filename (current: " << route_rpt_filename << "): ";
							getline(cin,route_rpt_filename);
        					if (route_rpt_filename.length() <= 4 || route_rpt_filename.substr(route_rpt_filename.length() - 4) != ".txt")		//check if '.txt' fil extension
        					{
        						cout << "	Please enter OUTPUT scenario filename with '.txt'. \n\n";
        					}
        				}while(route_rpt_filename.length() <= 4 || route_rpt_filename.substr(route_rpt_filename.length() - 4) != ".txt");
        				
        				if  (!fs::exists(route_rpt_filename))							// check if file has been created before
        				{
        					cout <<"\n";
        					cout << "	File available to use: "<<route_rpt_filename<<"\n";
        					cout << "	OUTPUT map report filename successfully set to '" << route_rpt_filename << "'!\n";
        				}
        				else
        				{
        					cout << "	Duplicate file. \n";
        					do
 							{
 								cout << "	Do you wish to use the same file? (y/n) : ";
								getline(cin,user_input);
								user_input[0] = tolower(user_input[0]);								//lower first char of the input
								if (user_input != "y" && user_input != "n")
								{
									cout << "	Wrong input. Please enter (y/n).\n\n";
								}
							}while(user_input != "y" && user_input != "n");
							cout <<"\n";
        				}
					}while(fs::exists(route_rpt_filename) && user_input != "y");
					break;
					
				case 'c':
					do
					{
						cout << "	[ Specify Ideal Route Criteria (current: " << IdealRoute << ") ]\n\n"; 
						cout << "	a) minimized total energy expenditure\n";
        				cout << "	b) shortest distance from Start to End locations\n";
        				cout << "	c) go back to sub menu\n\n";
        				cout << "	Please enter your choice (a - c): ";
        				getline(cin,input);
        				cout <<"\n";
        				if (input.length() == 1)
						{
							input[0] = tolower(input[0]);								//lower first char of the input
        					switch (input[0]) 
        					{
								case 'a':
									IdealRoute = "minimized total energy expenditure";
                					break;
								case 'b':
									IdealRoute = "shortest distance from Start to End locations";
									break;
								case 'c':
									cout << "	Going back to sub Menu ...\n";
									break;
								default:
									cout <<"	Please enter your choice a to c. \n\n";
									break;
							}
							cout << "	Ideal Route Criteria successfully set to '" << IdealRoute << "'!\n\n";
						}
						else
						{
							cout <<"	Please enter your choice a to c. \n\n";	
						}
					}while(input != "c");
					cout << "\n";
					break;
				case 'd':
					do
					{
						cout << "	[ Specify Vehicle Type (current: " << VehicleType << ") ]\n\n";
		    			cout << "	a) HighLander (Hill h, Mountain M)\n";
		    			cout << "	b) DragonFly (Swamp W, Watery ~)\n";
		    			cout << "	c) ShieldHero (Danger area X)\n";
		    			cout << "	d) go back to sub menu\n\n";
		    			cout << "	Please enter your choice (a - d): ";
		    			getline(cin,input);
        				cout <<"\n";
        				if (input.length() == 1)
						{
							input[0] = tolower(input[0]);								//lower first char of the input
		    				switch(input[0])
		    				{
        						case 'a':
									VehicleType = "HighLander";
									break;
								case 'b':
									VehicleType = "DragonFly";
									break;
								case 'c':
									VehicleType = "ShieldHero";
									break;	
								case 'd':
									cout << "	Going back to sub Menu ...\n";
									break;
								default:
									cout <<"	Please enter your choice a to d. \n\n";	
									break;
        					}
        					cout << "	Vehicle Type successfully set to '" << VehicleType << "'!\n\n";
        				}
        				else
						{
							cout <<"	Please enter your choice a to d. \n\n";	
						}
        			}while(input!= "d");
        			cout << "\n";
        			break;
        		case 'e':
        			break;
        		default :
        			cout <<"	Please enter your choice a to e. \n\n";
        			break;
				cout <<"\n";
			}
		}
		else
		{
			cout <<"	Please enter your choice a to e. \n\n";
		}
	}while(input[0] != 'e');
}
