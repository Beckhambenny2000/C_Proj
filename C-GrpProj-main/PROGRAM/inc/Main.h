#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <utility>
#include <map>
#include <set>
#include <string>

using namespace std;

std::vector<std::pair<int,int>> findShortestPathWithWT(
    const std::vector<std::vector<char>>& terrainMap,
    std::pair<int,int> start,
    std::pair<int,int> end
);

void Autopilot_settings();			//Autopilotsettings.cpp
void Exploration_settings();
void Autopilot_mapping();			//Autopilotmapping.cpp

void Vehicle_Status(); 				//VehicleEnergy.cpp

void Game();						//Game.cpp

void printMatrix();				    //Mapping.cpp
void initializeMatrix();			//Mapping.cpp

void Print_Energy();
void updateEnergy(char symbol, int newMovtEnergy, int newShldEnergy);

void SimulationRun();				//simulationRun.cpp
bool isPreferred(char t);
void printRouteEnergySummary(
    const vector<pair<int, int>>& pathCoordinates,
    const vector<vector<char>>& fullTerrainMap,
    const map<char, pair<int, int>>& energyMap,
    const set<char>& preferredTerrain,
    int routeNumber = 2
);

std::string trim(const std::string& str);

#endif
