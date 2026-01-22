#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "../inc/Main.h"

using namespace std;

extern int x_curr;
extern int y_curr;
extern int x_max;
extern int y_max;

int width = 3;

extern string Display_Map; //Autopilotmapping.cpp
extern string rpt_filename;				//Autopilotsettings.cpp

vector<vector<char>> matrix;

//char matrix[31][31];


void initializeMatrix() {
	matrix.clear();
    matrix.resize(y_max, vector<char>(x_max, ' ')); // Resize global matrix

    // Fill the matrix with random values
    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            matrix[i][j] = ' ';
        }
    }
}

void printMatrix() {
	cout << std::setw(width) << " ";
	for (int j = 0; j < x_max; j++) {
		cout << setw(width)<< j;
		
	}
	cout<<"\n";
    for (int i = 0; i < y_max; i++) {
    	cout << std::setw(width) << i;
        for (int j = 0; j < x_max; j++) {
			cout<< std::setw(width)<< matrix[i][j];      
        }
        cout << endl;
    }
}

