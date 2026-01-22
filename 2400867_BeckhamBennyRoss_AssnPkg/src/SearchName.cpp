#include <iostream>
#include <fstream>      
#include <vector>
#include <sstream>
#include <cctype>  
#include <algorithm>

#include "../inc/main.h"

using namespace std;

int SearchNameOptions();

string UserName = "SAMPLE NAME";

bool isOnlyWhitespace(const string& str) {
    return str.find_first_not_of(" \t\n\r\f\v") == string::npos;
}

bool isValidString(const string& input) {
    for (char ch : input) {
        if (!isalpha(ch) && ch != ' ') {  // Check if character is not a letter
            return false;
        }
    }
    return true;
}

void SearchName(vector<Employee> &employees){
	
	int userEnteredNumber;
	int counter;
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }
    
    do 
    {
        userEnteredNumber = SearchNameOptions();
        cout << endl;

        switch (userEnteredNumber) {
            case 1:
                cout << "Please type in name value to search for ( < 35 chars): ";
    			getline(cin, UserName);
    			cout << endl;

    			while (UserName.length() >= 35 || !isValidString(UserName) || isOnlyWhitespace(UserName)) 
    			{
					if (UserName.length() >= 35) 
					{
            			cout << "Input too long. Please enter data again ( < 35 chars ): ";
        			}
        			else if (!isValidString(UserName) || isOnlyWhitespace(UserName)) 
        			{
            			cout << "Error: Input must contain only letters. Try again: ";
        			}
					getline(cin, UserName);
        			cout << endl;
    			}

    			break;
            	    
            case 2:
    			counter = 0;

    			// Count exact matches
    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getName()) == toLowerCase(UserName))
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with Name: " << UserName << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with Name EXACTLY matching '" << UserName << "' " << endl;
        			cout << "==========================================================================================================" << endl;
        			cout << left << setw(EMP_IC_LENGTH)    << "IC"
             			 << setw(EMP_NAME_LENGTH)  << "Name"
             			 << setw(EMP_TEL_LENGTH)   << "Phone"
             			 << setw(EMP_DATE_LENGTH)  << "Birth Date"
             			 << setw(EMP_DATE_LENGTH)  << "Hired Date"
             			 << setw(EMP_EMAIL_LENGTH) << "Email" << endl;
        			cout << "==========================================================================================================" << endl;

        // Display matching records
        	  for (size_t i = 0; i < employees.size(); ++i) 
        	  	{
            		if (toLowerCase(employees[i].getName()) == toLowerCase(UserName)) 
            		{ 
                		cout << left << setw(EMP_IC_LENGTH) << employees[i].getIC()
                    		 << setw(EMP_NAME_LENGTH) << employees[i].getName()
                    		 << setw(EMP_TEL_LENGTH) << employees[i].getPhoneNum()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getBirthDate().toString()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getHiredDate().toString()
                    		 << setw(EMP_EMAIL_LENGTH) << employees[i].getEmail() << endl;
            		}
        		}
        				cout << "==========================================================================================================" << endl;
    			}
    					cout << endl;
    					cout << counter<< " records found, with Name EXACTLY matching " << UserName << "!!";
    					cout << endl;
    			break;

                
			case 3:

                counter = 0;

    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getName()).find(toLowerCase(UserName)) != string::npos)
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with Name: " << UserName << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with Name PARTIALLY matching '" << UserName << "' " << endl;
        			cout << "==========================================================================================================" << endl;
        			cout << left << setw(EMP_IC_LENGTH)    << "IC"
             			 << setw(EMP_NAME_LENGTH)  << "Name"
             			 << setw(EMP_TEL_LENGTH)   << "Phone"
             			 << setw(EMP_DATE_LENGTH)  << "Birth Date"
             			 << setw(EMP_DATE_LENGTH)  << "Hired Date"
             			 << setw(EMP_EMAIL_LENGTH) << "Email" << endl;
        			cout << "==========================================================================================================" << endl;

        	  for (size_t i = 0; i < employees.size(); ++i) 
        	  	{
            		if (toLowerCase(employees[i].getName()).find(toLowerCase(UserName)) != string::npos)
            		{ 
                		cout << left << setw(EMP_IC_LENGTH) << employees[i].getIC()
                    		 << setw(EMP_NAME_LENGTH) << employees[i].getName()
                    		 << setw(EMP_TEL_LENGTH) << employees[i].getPhoneNum()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getBirthDate().toString()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getHiredDate().toString()
                    		 << setw(EMP_EMAIL_LENGTH) << employees[i].getEmail() << endl;

                		
        			}
        		}
        				cout << "==========================================================================================================" << endl;   		
    			}
    					cout << endl;
    					cout << counter<< " records found, with Name PARTIALLY matching " << UserName << "!!";
    					cout << endl;
    			break;
    			
    			case 4 :
    				break;
    			
    			default :
    				cout << "Invalid! Please try again " << endl ;
            }
   	}while (userEnteredNumber != 4);
}
                
int SearchNameOptions() {	
	
    cout << "\n-----------------------------------------------------" << endl;
    cout << "\n 1) Enter an Name     ( current value = '"<< UserName <<"')" << endl;
    cout << " 2) Search for employee Name	      = '"<< UserName <<"' (i.e. EXACT MATCH)" << endl;
    cout << " 3) Search for employee Name containing '"<< UserName <<"' (i.e. PARTIAL MATCH)" << endl;
    cout << " 4) Back to main menu ..." << endl;
    cout << "\n-----------------------------------------------------" << endl;
    cout << endl;

    int userEnteredNumber;
    cout << "Please enter your choice (1 - 4): ";
    cin >> userEnteredNumber;
    
    if (cin.fail() || cin.peek() != '\n')
    {
    	cin.clear();
    	userEnteredNumber = 0;
    } 
    cin.ignore(100, '\n');

    return (userEnteredNumber);
}               
