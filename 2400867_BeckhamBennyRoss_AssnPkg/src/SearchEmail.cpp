#include <iostream>
#include <fstream>      
#include <vector>
#include <sstream>
#include <cctype>  
#include <algorithm>

#include "../inc/main.h"

using namespace std;

int SearchEmailOptions();

string UserEmail = "SAMPLE EMAIL";

string toLowerCase(const string &str) 
{
	string lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

string toUpperCase(const string &str) 
{
	string upperStr = str;
	transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
	return upperStr;
}

void SearchEmail(vector<Employee> &employees){
	
	int userEnteredNumber;
	int counter;
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }

    do 
    {
        userEnteredNumber = SearchEmailOptions();
        cout << endl;
        
        switch (userEnteredNumber) {
            case 1:
                cout << "Please type in Email value to search for ( < 35 chars): ";
    			getline(cin, UserEmail);
    			cout << endl;

    			while (UserEmail.length() >= 35 || isOnlyWhitespace(UserEmail)) 
    			{
    				if (UserEmail.length() >= 35)
    				{
        				cout << "Input too long. Please enter data again ( < 35 chars ) : ";
        			}
        			else if (isOnlyWhitespace(UserEmail))
        			{
        				cout << "Error! Do not leave it blank! Please enter data again : ";
        			}
        			getline(cin, UserEmail);
        			cout << endl;
   				}

    			break;
                
            case 2:
    			counter = 0;

    			// Count exact matches
    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getEmail()) == toLowerCase(UserEmail))
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with email: " << UserEmail << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with Email EXACTLY matching '" << UserEmail << "' " << endl;
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
            		if (toLowerCase(employees[i].getEmail()) == toLowerCase(UserEmail)) 
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
    					cout << counter<< " records found, with Email EXACTLY matching " << UserEmail << " !!";
    					cout << endl;
    			break;

                
			case 3:

                counter = 0;

    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getEmail()).find(toLowerCase(UserEmail)) != string::npos)
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with email: " << UserEmail << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with Email PARTIALLY matching '" << UserEmail << "' " << endl;
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
            		if (toLowerCase(employees[i].getEmail()).find(toLowerCase(UserEmail)) != string::npos)
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
    					cout << counter<< " records found, with Email PARTIALLY matching " << UserEmail << "!!";
    					cout << endl;
    			break;
    			
    			case 4 :
    				break;
    			
    			default :
    				cout << "Invalid! Please try again " << endl ;
            }
   	}while (userEnteredNumber != 4);
}
                
int SearchEmailOptions() {	
	
    cout << "\n-----------------------------------------------------" << endl;
    cout << "\n 1) Enter an email     ( current value = '"<< UserEmail <<"')" << endl;
    cout << " 2) Search for employee email	       = '"<< UserEmail <<"' (i.e. EXACT MATCH)" << endl;
    cout << " 3) Search for employee email containing '"<< UserEmail <<"' (i.e. PARTIAL MATCH)" << endl;
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
