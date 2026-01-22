#include <iostream>
#include <fstream>      
#include <vector>
#include <sstream>
#include <limits>
#include <cctype>  
#include <algorithm>

#include "../inc/main.h"

using namespace std;

int SearchICOptions();

string UserIC = "00";

void SearchIC(vector<Employee> &employees){
	
	int userEnteredNumber;
	int counter;
	
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }
    
    do 
    {
        userEnteredNumber = SearchICOptions();
        cout << endl;
        
        switch (userEnteredNumber) {
            case 1:
                cout << "Please type in IC value to search for ( < 10 chars): ";
    			getline(cin, UserIC);
    			cout << endl;

    			while (UserIC.length() >= 10 || isOnlyWhitespace(UserIC)) 
    			{
    				if (UserIC.length() >= 10)
    				{ 
        				cout << "Input too long. Please enter data again ( < 10 chars ) : ";
        			}       			
        			else if (isOnlyWhitespace(UserIC))
        			{
        				cout << "Error! Do not leave it blank! Please enter data again : ";
        			}
        			getline(cin, UserIC);
        			cout << endl;
   				}
   				
   				
    			break;
            	    
            case 2:
    			counter = 0;

    			// Count exact matches
    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getIC()) == toLowerCase(UserIC))
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with IC: " << UserIC << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with IC EXACTLY matching '" << UserIC << "' " << endl;
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
            		if (toLowerCase(employees[i].getIC()) == toLowerCase(UserIC)) 
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
    					cout << counter<< " records found, with IC EXACTLY matching " << UserIC << "!!";
    					cout << endl;
    			break;

                
			case 3:

                counter = 0;

    			for (size_t i = 0; i < employees.size(); ++i)
    			 {
        			if (toLowerCase(employees[i].getIC()).find(toLowerCase(UserIC)) != string::npos)
        			{  
            			counter++;
        			}
    			}

    			if (counter == 0) 
    			{
        			cout << "\nNo employee found with IC: " << UserIC << endl;
    			} 
    			else 
    			{
        			cout << "\nRecords with IC PARTIALLY matching '" << UserIC << "' " << endl;
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
            		if (toLowerCase(employees[i].getIC()).find(toLowerCase(UserIC)) != string::npos)
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
    					cout << counter<< " records found, with IC PARTIALLY matching " << UserIC << "!!";
    					cout << endl;
    			break;
    			
    			case 4 :
    				break;
    			
    			default :
    				cout << "Invalid! Please try again " << endl ;
            }
   	}while (userEnteredNumber != 4);
}
                
int SearchICOptions() {	
	
    cout << "\n-----------------------------------------------------" << endl;
    cout << "\n 1) Enter an IC     ( current value = '"<< UserIC <<"')" << endl;
    cout << " 2) Search for employee IC	    = '"<< UserIC <<"' (i.e. EXACT MATCH)" << endl;
    cout << " 3) Search for employee IC containing '"<< UserIC <<"' (i.e. PARTIAL MATCH)" << endl;
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
