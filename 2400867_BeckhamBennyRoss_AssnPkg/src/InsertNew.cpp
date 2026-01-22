#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "../inc/main.h"

using namespace std;

extern int empDBSize;

bool ValidConfirmation(string input) 
{
    return (input == "y" || input == "Y" || input == "n" || input == "N");
}

bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    return (atPos != string::npos && atPos > 0 &&
            dotPos != string::npos && dotPos > atPos + 1 && 
            dotPos < email.length() - 1); 
}

void InsertNew(vector<Employee> &employees)
{
	string UserName, UserIC, UserEmail, UserNumber, UserBirth, UserHire, Input;
 	
 	if (empDBSize == MAX_NO_OF_RECORDS)
 	{
 		cout << "Employee Records DB is FULL! Unable to add new record!" ;
 		return;
 	}

	insertName:
	cout << "Please type in existing employee's name ( < 35 chars ) : " ;
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
       			
    for (size_t i = 0; i < employees.size(); ++i) 
{
    if (toLowerCase(employees[i].getName()) == toLowerCase(UserName)) 
    {
        cout << "Error! Name '" << UserName << "' already exists in employee records DB, do you INSIST this is correct? (y/n) : ";
        getline(cin, Input);
        cout << endl;
        
        while (!ValidConfirmation(Input) || isOnlyWhitespace(Input)) 
        {
                cout << "Invalid! Please enter 'y' or 'n'. Try again. : ";
                getline(cin, Input);
                cout << endl;
        }
            
        if (Input == "y" || Input == "Y") 
        {
        	cout << "Alright, you insisted! Strong (duplicate) Name '" << UserName << "' under this Employee Record in DB ..." << endl;
           	cout << endl;
            break;
        }
        else
        {
            goto insertName;
        }
     }
}
	
	cout << "Please type in employee's IC ( < 10 chars ) : " ;
	getline(cin, UserIC);
	cout << endl;
	
	while (UserIC.length() >= 10 || isOnlyWhitespace(UserIC))
	{
		if(UserIC.length() >= 10)
		{	
			cout << "Input too long. Please enter data again ( < 10 chars ) : " ;
		}
		else if (isOnlyWhitespace(UserIC))
		{
			cout << "Error! Do not leave it blank! Please enter data again : ";
		}	
		getline(cin, UserIC);
		cout << endl;
	}
		
	for (size_t i = 0; i < employees.size(); ++i) 
	{
		while (toLowerCase(employees[i].getIC()) == toLowerCase(UserIC))
		{
			cout << "Error! IC No. '" << UserIC << "' already exist in employee records DB, please try again! " << endl;
			cout << "\nPlease type in employee's IC ( < 10 chars ) : " ;
			getline(cin, UserIC);
			cout << endl;
		}
	}
	
	cout << "Please type in employee's email ( < 35 chars ) : " ;
	getline(cin, UserEmail);
	cout << endl;
	
	while (UserEmail.length() >= 35 || isOnlyWhitespace(UserEmail) || !isValidEmail(UserEmail))
	{
		if (UserEmail.length() >= 35)
		{
			cout << "Input too long. Please enter data again ( < 35 chars ) : " ;
		}
		else if (isOnlyWhitespace(UserEmail))
		{
			cout << "Error! Do not leave it blank! Please enter data again : ";
		}
		else if (!isValidEmail(UserEmail))
        {
        	cout << "Invalid email format! Please enter data again: ";
        }
		getline(cin, UserEmail);
		cout << endl;
	}
		
	for (size_t i = 0; i < employees.size(); ++i)
	{
		while (toLowerCase(employees[i].getEmail()) == toLowerCase(UserEmail))
		{
			cout << "Error! Email '" << UserEmail << "' already exist in employee records DB, please try again! " << endl;
			cout << "\nPlease type in employee's email ( < 35 chars ) : " ;
			getline(cin, UserEmail);
			cout << endl;
		}
	}
	
	insertNumber:
	cout << "Please type in employee's phone num ( < 15 chars ) : " ;
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
	
	for (size_t i = 0; i < employees.size(); ++i) 
	{
		if (toLowerCase(employees[i].getPhoneNum()) == toLowerCase(UserNumber))
		{
			cout << "Error! Phone Num '" << UserNumber << "' already exist in employee records DB, do you INSIST this is correct? (y/n) : ";
			getline(cin, Input);
			cout << endl;
			
			while (!ValidConfirmation(Input) || isOnlyWhitespace(Input)) 
        	{
                cout << "Invalid! Please enter 'y' or 'n'. Try again. : ";
                getline(cin, Input);
                cout << endl;
       		}
		
			if (Input == "y" || Input == "Y")
			{
				cout << "Alright, you insisted! Strong (duplicate) phone num '" << UserNumber << "' under this Employee Record in DB ..." << endl;
				cout << endl;
				break;
			}
			else
			{
				goto insertNumber;
			}
		}	
	}
	
	cout << "To enter employee's date of birth, please adhere to the format shown in prompt below ..." << endl;
	cout << "\nEnter a data (dd-mm-yyyy) : ";
	getline(cin, UserBirth);
	cout << endl;
	
	while (!isValidDate(UserBirth))  // Keep asking until a valid date is entered
	{
    	cout << "Invalid date format or values. Please try again: ";
    	getline(cin, UserBirth);
    	cout << endl;
	}
					
	replace(UserBirth.begin(), UserHire.end(), '-', '/');
	Date Birth_Date = parseDate(UserBirth);
	
	cout << "To enter employee's date of hire, please adhere to the format shown in prompt below ..." << endl;
	cout << "\nEnter a data (dd-mm-yyyy) : ";
	getline(cin, UserHire);
	cout << endl;
	
	Date Hire_Date;
	
	while (1)
	{
		if (!isValidDate(UserHire))
		{
    			
    		do
    		{
    			cout << "Invalid date format or values. Please try again: ";
    			getline(cin, UserHire);
    			cout << endl;
    		}while(!isValidDate(UserHire));
    	}
    	replace(UserHire.begin(), UserHire.end(), '-', '/');
		Hire_Date = parseDate(UserHire);
    	if (!isAtLeast18YearsOld(Birth_Date, Hire_Date)) 
		{
			cout << "Employee must be at least 18 years old different. Please enter a valid date: ";
		}
		else
		{
			break;
		}
		getline(cin, UserHire);
    	cout << endl;
	}
	
	employees.push_back(Employee(UserName, UserEmail, toUpperCase(UserIC), UserNumber, Hire_Date, Birth_Date));
	empDBSize = empDBSize + 1;

	cout << "\nDone! Going back to main menu ..." << endl;
}
		
	
