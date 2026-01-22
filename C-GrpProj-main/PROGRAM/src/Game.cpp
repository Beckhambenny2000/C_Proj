#include <iostream>
#include <cstdlib>
#include <vector>

//#include <sstream>

#include "../inc/Main.h"
#include "../inc/SatComRelay.h"
#include "../inc/VehData.h"

#include <unistd.h> // For sleep()

using namespace std;

extern string scr_filename;				//Autopilotsettings.cpp
extern bool scr_encrypted;				//Autopilotsettings.cpp
extern bool rdm_pos;					//Autopilotsettings.cpp
extern int mission_type;				//Autopilotsettings.cpp
extern string rpt_filename;				//Autopilotsettings.cpp
extern string scr_filename_dir;			//Autopilotsettings.cpp

//Mapping.cpp
extern vector<vector<char>> matrix;

VehData Vehicle_Data;
SatComRelay Vehicle_Relay;

void Scan_North();
void Scan_NorthEast();
void Scan_East();
void Scan_SouthEast();
void Scan_South();
void Scan_SouthWest();
void Scan_West();
void Scan_NorthWest();

void Scan_surround();
void Scan_surround2();

void Move_North();
void Move_East();
void Move_South();
void Move_West();

bool Start = 0;

char result;
int x_curr;
int y_curr;
int x_max = 3;
int y_max = 3;


void Game()
{
	float delay = 0.0;
	
	long Bef_Energ;
	long Bef_S_Energ;
	long Aft_Energ;
	long Aft_S_Energ;
	Start = 0;
	result = ' ';
	x_curr = 0;
    y_curr = 0;
	x_max = 3;
	y_max = 3;
	Vehicle_Data = VehData();        // Resets all fields to default
	Vehicle_Relay = SatComRelay();   // Same
	matrix.clear();
	

	Vehicle_Data = Vehicle_Relay.initializeVehicle(scr_filename_dir, scr_encrypted, rdm_pos, mission_type);		//init vechicle at satcomrelay.h
	cout <<"\n";
	
	Vehicle_Relay.allocateEnergyToShield(1000000);
	
	do							//move vehicle to the bottom of the map
	{	
		Move_South();	
		Scan_South();	
		
	}while (result != '#');
	cout <<"Here 1 \n";
	
	do							//move vehicle to the right of the map
	{
		Move_East();		
		Scan_East();	
	}while (result != '#');
	cout <<"Here 2 \n";
	
	do							//move vehicle to the top of the map and count number of step and to into variable y_max
	{
		Move_North();	
		cout <<"Here 1 \n";	
		Scan_North();
		cout <<"Here 1 \n";	
		y_max += 1;	
		cout <<"Here 1 \n";	
	}while (result != '#');
	cout <<"Y Max = "<<y_max<<"\n";
	
	do							//move vehicle to the left of the map and count number of step and to into variable x_max
	{	
		Move_West();
		Scan_West();
		x_max += 1;	
	}while (result != '#');
	cout <<"X Max = "<<x_max<<"\n";
	x_curr = 1;					//store position as 1,1 as (0,0), (0,1) and (1,0) is wall
	y_curr = 1;
	
	initializeMatrix();			//set the matrix size
	
	//cout <<"start scanning\n\n";		//Start scanning
	Start = 1;
	
	do
	{
		do
		{
			cout <<"X Curr = "<<x_curr<<"\n";					//display current position
			cout <<"Y Curr = "<<y_curr<<"\n";
			Scan_surround();
			printMatrix();
			Bef_Energ = Vehicle_Data.getCurrentEnergy();
			Bef_S_Energ = Vehicle_Data.getCurrentShieldEnergy();
			sleep(delay);
			Move_East();
			Aft_Energ = Vehicle_Data.getCurrentEnergy();
			Aft_S_Energ = Vehicle_Data.getCurrentShieldEnergy();
			updateEnergy(result, Bef_Energ - Aft_Energ, Bef_S_Energ-Aft_S_Energ);
			Scan_surround();
			printMatrix();
		}while (x_curr != x_max-2);
		
		for (int j=0;j<3;j++)
		{
			if (y_max-2 == y_curr)
			{
				break;
			}
			else
			{
				Scan_South();
				Move_South();
				sleep(delay);
				printMatrix();
			}
		}
		do
		{	
			Scan_surround2();
			sleep(delay);
			if (x_curr != 1)
			{
				Bef_Energ = Vehicle_Data.getCurrentEnergy();
				Bef_S_Energ = Vehicle_Data.getCurrentShieldEnergy();
				Move_West();
				Aft_Energ = Vehicle_Data.getCurrentEnergy();
				Aft_S_Energ = Vehicle_Data.getCurrentShieldEnergy();
				updateEnergy(result, Bef_Energ - Aft_Energ, Bef_S_Energ-Aft_S_Energ);
				Scan_surround2();
			}
			printMatrix();
		}while (x_curr != 1);
		result = 'A';
		
		for (int j=0;j<3;j++)
		{
			if (y_max-2 == y_curr)
			{
				break;
			}
			else
			{
				Scan_South();
				Move_South();
				sleep(delay);
			}
			printMatrix();
		}	
		
	}while (matrix[y_max-1][x_max-1] != '#');
	cout.clear(); 
	
}

void Scan_surround()
{
	Scan_SouthEast();
	Scan_South();
	Scan_SouthWest();
	Scan_West();
	Scan_NorthWest();
	Scan_North();
	Scan_NorthEast();
	Scan_East();
}

void Scan_surround2()
{
	Scan_NorthWest();
	Scan_North();
	Scan_NorthEast();
	Scan_East();
	Scan_SouthEast();
	Scan_South();
	Scan_SouthWest();
	Scan_West();
}

void Move_North()
{
	Vehicle_Data = Vehicle_Relay.moveUpNorth();
	y_curr -= 1;
}

void Move_East()
{
	Vehicle_Data = Vehicle_Relay.moveRightEast();
	x_curr += 1;
}

void Move_South()
{
	Vehicle_Data = Vehicle_Relay.moveDownSouth();
	y_curr += 1;
}


void Move_West()
{
	Vehicle_Data = Vehicle_Relay.moveLeftWest();
	x_curr -= 1;
}

void Scan_North()
{
	result = Vehicle_Relay.scanNorth(Vehicle_Data);
	cout <<"N Char out: " << result <<"\n\n";
	if (Start == 1)
	{
		matrix[y_curr-1][x_curr] = result;
	}
}

void Scan_NorthEast()
{
	result = Vehicle_Relay.scanNorthEast(Vehicle_Data);
	cout <<"NE Char out: " << result <<"\n\n";
	matrix[y_curr-1][x_curr+1] = result;
}

void Scan_East()
{
	result = Vehicle_Relay.scanEast(Vehicle_Data);
	cout <<"E Char out: " << result <<"\n\n";
	if (Start == 1)
	{
		matrix[y_curr][x_curr+1] = result;
	}
}

void Scan_SouthEast()
{
	result = Vehicle_Relay.scanSouthEast(Vehicle_Data);
	cout <<"SE Char out: " << result <<"\n\n";
	matrix[y_curr+1][x_curr+1] = result;
}

void Scan_South()
{
	result = Vehicle_Relay.scanSouth(Vehicle_Data);
	cout <<"S Char out: " << result <<"\n\n";
	if (Start == 1)
	{
		matrix[y_curr+1][x_curr] = result;
	}
}

void Scan_SouthWest()
{
	result = Vehicle_Relay.scanSouthWest(Vehicle_Data);
	cout <<"SW Char out: " << result <<"\n\n";
	matrix[y_curr+1][x_curr-1] = result;
}

void Scan_West()
{
	result = Vehicle_Relay.scanWest(Vehicle_Data);
	cout <<"W Char out: " << result <<"\n\n";
	if (Start == 1)
	{
		matrix[y_curr][x_curr-1] = result;
	}
}

void Scan_NorthWest()
{
	result = Vehicle_Relay.scanNorthWest(Vehicle_Data);
	cout <<"NW Char out: " << result <<"\n\n";
	matrix[y_curr-1][x_curr-1] = result;
}
