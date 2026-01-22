#include <iostream>
#include <iomanip>
#include <map>				// For storing of dictionary values	

#include "../inc/Main.h"
#include "../inc/SatComRelay.h"
#include "../inc/VehData.h"

using namespace std;

extern VehData Vehicle_Data;
extern SatComRelay Vehicle_Relay;

std::map<char, std::pair<int,int>> terrainEnergy = {
	{' ', {0,0}},
	{'f', {0,0}},
	{'j', {0,0}},
	{'h', {0,0}},
	{'M', {0,0}},
	{'~', {0,0}},
	{'w', {0,0}},
	{'X', {0,0}},
	};
	
void updateEnergy(char symbol, int newMovtEnergy, int newShldEnergy) {
    if (terrainEnergy.find(symbol) != terrainEnergy.end()) {
        //terrainEnergy[symbol] = {newMovtEnergy, newShldEnergy};
        std::cout << "Updated '" << symbol << "' to ("
                  << terrainEnergy[symbol].first << ", "
                  << terrainEnergy[symbol].second << ")\n";
    } else {
        std::cout << "Symbol '" << symbol << "' not found!\n";
    }
    terrainEnergy[symbol] = {newMovtEnergy, newShldEnergy};
}

void Vehicle_Status()
{
	cout <<"Initial Enrg: " << Vehicle_Data.getInitialEnergy() << ", ";
	cout <<"Curr Enrg: " << Vehicle_Data.getCurrentEnergy() << ", ";
	cout <<"Curr Shield Enrg: " << Vehicle_Data.getCurrentShieldEnergy() << ", ";
	cout <<"Total Enrg Used: " << Vehicle_Data.getTotalEnergyUsed() << ", ";
	cout <<"TOtal Shield Enrg used: " << Vehicle_Data.getTotalShieldEnergyUsed() << ".\n\n";
}

void Print_Energy()
{
	cout << left << setw(15) << "Terrain" 
				 << setw(15) << "Movt Enrg" 
				 << setw(15) << "Shld Enrg" << endl;
				 
    cout << left << setw(15) << "Symbol" 
    			 << setw(15) << "Reqd:" 
    			 << setw(15) << "Reqd:" << endl;
    
    for (const auto& entry : terrainEnergy) {
       // char terrainType = entry.first;
        int value1 = entry.second.first;
        int value2 = entry.second.second;

        if (value1 == 0 && value2 == 0) 
        {
            cout << setw(15) << (string("'") + entry.first + "'") 
            	 << setw(15) << "N.A" 
            	 << setw(15) << "N.A" << "\n";
        } 
        else 
        {
           cout << setw(15) << (string("'") + entry.first + "'") 
           		<< setw(15) << entry.second.first 
           		<< setw(15) << entry.second.second << "\n";
        }
      }
    cout <<"\n";
}

