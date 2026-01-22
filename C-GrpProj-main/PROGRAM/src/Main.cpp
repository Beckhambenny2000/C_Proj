#include <iostream>
#include <string>			// For String
#include <string>			// For isdigit
#include "../inc/Main.h"	// For extern header file

using namespace std;
string input;

void Main_Menu();

int main()
{
	cout <<"Team Number      : 3 \n";
	cout <<"Team Leader Name : Beckham Benny Ross \n";
	cout <<"------------------------------------- \n\n";
	Main_Menu();
	return 0;
}

void Main_Menu()
{
	//int choice;
	do
	{
		cout <<"Welcome to Team 3 Group Project \n\n";
		cout <<"1) Configure Autopilot Mapping Exploration settings \n";
		cout <<"2) Configure Terrain Exploration Simulator settings \n";
		cout <<"3) Start Autopilot Mapping \n";
		cout <<"4) Start Simulation \n";
		cout <<"5) End \n\n";
		cout <<"Please enter your choice: ";
		getline(cin,input);
		cout <<"\n";
		if (input.length() == 1 && isdigit(input[0]))		//check if length is 1 and input[0] is digit
		{
			switch (input[0])
			{
				case '1': 
					Autopilot_settings();					//Autopilotsetting.cpp
					break;
				case '2':
					Exploration_settings();					//Explorationsetting.cpp
					break;
				case '3':
					Autopilot_mapping();					//Autopilotmapping.cpp
					break;
				case '4':
					SimulationRun();						//SimulationRun.cpp
					break;
				case '5':
					cout <<"Thank You for using this program. \n";
					break;
				default:
					cout <<"Please enter your choice 1 to 5. \n\n";
					break;
		}
		}
		else
		{
			cout <<"Please enter your choice 1 to 5. \n\n";
		}
	}
	while(input[0] != '5');
}
