#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>

#include "../inc/main.h"
#include "../inc/Date.h"
#include "../inc/Employee.h"

using namespace std;

extern int empDBSize;
int totalpopulateEmployee;
string filename;
unordered_set<string> usedFilenames;
set<string> uniqueICs;

int InputData(vector<Employee> &employees) {

	if (empDBSize == MAX_NO_OF_RECORDS)
 	{
 		cout << "Employee Records DB is FULL! Unable to read new data!" ;
 		return 0;
 	}
 	
    // Prompt the user for the path to the file
    cout << "------------------------------------------------------------" << endl;
    cout << "Reading data from file  to populate Employee DB ..." << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
    
    while (true) 
    {
        cout << "Please enter the input (CSV) file's name : ";
        getline(cin, filename);
        cout << endl;

        if (isOnlyWhitespace(filename)) {
            cout << "Error! Please do not leave it blank!" << endl;
            cout << endl;
            continue; // Ask for input again
        }

        // Add path prefix
        filename = "./input-files/" + filename;

        // Check if filename is already used
        if (usedFilenames.find(filename) != usedFilenames.end()) {
            cout << "Error! You cannot read the same file again." << endl;
            cout << endl;
            continue; // Ask for input again
        }

        // If filename is valid, break the loop
        break;
    }
   	
    totalpopulateEmployee = readEmployeesFromCSV(filename, employees, MAX_NO_OF_RECORDS);
    empDBSize = empDBSize + totalpopulateEmployee;
    if (MAX_NO_OF_RECORDS <= empDBSize)
    {
    	cout << "Maxinum number of records reached. Ignoring additional data from file '" << filename << "' !!!" << endl;
    	cout << endl;	
    	empDBSize = MAX_NO_OF_RECORDS;
    }  
	
	if (totalpopulateEmployee > 0)
	{
    cout << "Done! Total no. of records read in and stored in DB : " << totalpopulateEmployee ; 
    }
    return totalpopulateEmployee;
}

int readEmployeesFromCSV(const std::string &filename, std::vector<Employee> &employees, int maxLines) 
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }
    
    for (const Employee &emp : employees) 
    {
    	uniqueICs.insert(emp.getIC());  // Assuming 'ic' is a public field
	}

    usedFilenames.insert(filename);
    std::string line;
    bool isFirstLine = true;
    int count = 0;
    int nameIndex = -1, EmailIndex = -1, ICIndex = -1, PhoneNumIndex = -1, HiredDateIndex = -1, BirthDateIndex = -1;
    
    while (count < maxLines && std::getline(file, line))  
    {
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;
        
        while (std::getline(ss, token, ','))  
        {
            tokens.push_back(token);
        }
		
	if (isFirstLine) 
	{
    	isFirstLine = false;
    	for (size_t i = 0; i < tokens.size(); ++i) 
    	{
		    if (tokens[i] == "Name" || tokens[i] == "Name\r")  // Assuming "Name" is the column header
            {
		        nameIndex = i;
		        std::cout << "Detected Name Column: " << nameIndex << std::endl;
            }
		    else if (tokens[i] == "Email" || tokens[i] == "Email\r") 
		    {
		        EmailIndex = i;
		        std::cout << "Detected Email Column: " << EmailIndex << std::endl;
            }
		    else if (tokens[i] == "IC" || tokens[i] == "IC\r")  
		    {
		        ICIndex = i;
		        std::cout << "Detected IC Column: " << ICIndex << std::endl;
		    } 
		    else if (tokens[i] == "PhoneNum" || tokens[i] == "PhoneNum\r") 
		    {
		        PhoneNumIndex = i;
		        std::cout << "Detected PhoneNum Column: " << PhoneNumIndex << std::endl;
		    } 
		    else if (tokens[i] == "HireDate" || tokens[i] == "HireDate\r")  
		    {
		        HiredDateIndex = i;
		        std::cout << "Detected HiredDate Column: " << HiredDateIndex << std::endl;
		    } 
		    else if (tokens[i] == "BirthDate" || tokens[i] == "BirthDate\r") 
		    {
		        BirthDateIndex = i;
		        std::cout << "Detected BirthDate Column: " << BirthDateIndex << std::endl;
		    }
		}

            // Ensure all necessary columns exist
            if (nameIndex == -1 || EmailIndex == -1 || ICIndex == -1 || PhoneNumIndex == -1 || HiredDateIndex == -1 || BirthDateIndex == -1)  
            {
                std::cerr << "Error: Missing required columns in CSV file!" << std::endl;
                return 0;
            }
            continue; // Move to next line after processing headers
        }

        // Ensure the row has enough data
        if (tokens.size() <= static_cast<size_t>(std::max({static_cast<int>(nameIndex), static_cast<int>(EmailIndex), 
                                                   static_cast<int>(ICIndex), static_cast<int>(PhoneNumIndex), 
                                                   static_cast<int>(HiredDateIndex), static_cast<int>(BirthDateIndex)}))) 
		{
			std::cerr << "Error: Incomplete row, skipping entry!" << std::endl;
			continue;
		}
		
		if (uniqueICs.find(tokens[ICIndex]) != uniqueICs.end()) 
		{
			cout << "Duplicate IC found, skipping: " << tokens[ICIndex] << endl;
			continue;
		}
		uniqueICs.insert(tokens[ICIndex]); 

        // Create and populate an Employee object
        Employee emp(
            tokens[nameIndex],
            tokens[EmailIndex],
            tokens[ICIndex],
            tokens[PhoneNumIndex],
            parseDate(tokens[HiredDateIndex]),  
            parseDate(tokens[BirthDateIndex])
        );

        employees.push_back(emp);
        count++;
    }

    file.close();
    return count;
}

Date parseDate(const std::string &dateStr) {
    // Expected format: "DD/MM/YYYY"
    // We'll split by '/' and convert to integers
    int day = 1, month = 1, year = 2000; // default
    std::stringstream ss(dateStr);
    std::string token;
    std::vector<int> parts;

    while (std::getline(ss, token, '/')) {
        parts.push_back(std::stoi(token));
    }

    if (parts.size() == 3) {
        day   = parts[0];
        month = parts[1];
        year  = parts[2];
    }
    return Date(day, month, year);
}
