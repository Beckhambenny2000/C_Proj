#include <iostream>
#include <fstream>      
#include <vector>
#include <sstream>
#include <cctype>  
#include <algorithm>

#include "../inc/main.h"

using namespace std;

int SearchNumberOptions();

string UserNumber = "(00)-00000000";

bool isValidInteger(const string& input) 
{
    if (input.empty()) return false; 

    size_t start = 0;

    for (size_t i = start; i < input.length(); i++) 
    {
        if (!isdigit(input[i]) && (input[i] != '-') && (input[i] != '(') && (input[i] != ')')) 
        {  
            return false;
        }
    }
    return true;
}



void SearchNumber(vector<Employee> &employees){
	
	int userEnteredNumber;
	int counter;
	
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }

    do 
    {
        userEnteredNumber = SearchNumberOptions();
        cout << endl;

        switch (userEnteredNumber) {
            case 1:
                cout << "Please type in phone number value to search for ( < 15 chars): "; 
    			getline(cin, UserNumber);
    			cout << endl;

    			while (UserNumber.length() >= 15 || !isValidInteger(UserNumber) || isOnlyWhitespace(UserNumber)) 
				{
    				if (UserNumber.length() >= 15) 
    				{
        				cout << "Input too long. Please enter data again ( < 15 chars ): ";
        			} 
        			else if (!isValidInteger(UserNumber) || isOnlyWhitespace(UserNumber)) 
        			{
            			cout << "Error: Input must contain only numbers. Try again: ";
        			}
        			getline(cin, UserNumber);
        			cout << endl;
    			}
    			
    			break;
            	    
            case 2:
    			counter = 0;

    			// Count exact matches
    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getPhoneNum()) == toLowerCase(UserNumber))
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with Number: " << UserNumber << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with phone number EXACTLY matching '" << UserNumber << "' " << endl;
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
            		if (toLowerCase(employees[i].getPhoneNum()) == toLowerCase(UserNumber)) 
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
    					cout << counter<< " records found, with phone number EXACTLY matching " << UserNumber << "!!";
    					cout << endl;
    			break;

                
			case 3:

                counter = 0;

    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getPhoneNum()).find(toLowerCase(UserNumber)) != string::npos)
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with phone number: " << UserNumber << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with phone number PARTIALLY matching '" << UserNumber << "' " << endl;
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
            		if (toLowerCase(employees[i].getPhoneNum()).find(toLowerCase(UserNumber)) != string::npos)
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
    					cout << counter<< " records found, with phone number PARTIALLY matching " << UserNumber << "!!";
    					cout << endl;
    			break;
    			
    			case 4 :
    				break;
    			
    			default :
    				cout << "Invalid! Please try again " << endl ;
            }
   	}while (userEnteredNumber != 4);
}
                
int SearchNumberOptions() {	
	
    cout << "\n-----------------------------------------------------" << endl;
    cout << "\n 1) Enter an phone number     ( current value = '"<< UserNumber <<"')" << endl;
    cout << " 2) Search for employee phone number	      = '"<< UserNumber <<"' (i.e. EXACT MATCH)" << endl;
    cout << " 3) Search for employee phone number containing '"<< UserNumber <<"' (i.e. PARTIAL MATCH)" << endl;
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
