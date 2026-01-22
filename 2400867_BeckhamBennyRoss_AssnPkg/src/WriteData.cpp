#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>

#include "../inc/main.h"

extern int empDBSize;

void WriteData(vector<Employee> &employees)
{
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }
    
	string filename;
	cout << "-----------------------------------------------------" << endl;
    cout << "Writing data from Employee DB to an output file ..." << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << endl;
    
    cout << "Please enter the output (CSV) file name : ";
    getline(cin, filename);
    cout << endl;  
        
    if (filename.length() <= 4 || filename.substr(filename.length() - 4) != ".csv")
	{
		cout << "Error writing data from employee DB to file! Please make sure filename end with (.csv) ";
	}
    else
    {
    ofstream OutputFile(filename);
    OutputFile << "Idx,Name,Email,IC,PhoneNum,Hired Date,Birth Date\n";
         
    for (size_t i = 0; i < employees.size(); ++i) 
    {
    OutputFile << i + 1 << "," 
    			<< employees[i].getName() << ","
                << employees[i].getEmail() << ","
                << employees[i].getIC() << ","
                << employees[i].getPhoneNum() << ","
                << employees[i].getHiredDate().toString() << ","
                << employees[i].getBirthDate().toString() << endl;
    }
    
    cout << "Done! Total no. of records wrtten to output file '"<< filename <<"' = " << empDBSize << endl;
    }
}
