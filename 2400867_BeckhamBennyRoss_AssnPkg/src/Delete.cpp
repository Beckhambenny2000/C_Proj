#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#include "../inc/main.h"

using namespace std;

extern int empDBSize;

void Delete(vector<Employee> &employees)
{
	int position = 0;
	int counter = 0;
	string UserIC, Input;
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }

	cout << "Please type in employee's IC ( < 10 chars ) : " ;
	getline(cin, UserIC);
	cout << endl ;
	
	while (UserIC.length() >= 10 || isOnlyWhitespace(UserIC))
	{
		if (UserIC.length() >= 10)
		{
			cout << "Input too long. Please enter data again ( < 10 chars ) : " ;
		}
		else if (isOnlyWhitespace(UserIC))
		{
			cout << "Error! Do not leave it blank! Please enter data again : ";
		}
		getline(cin, UserIC);
		cout << endl ;
	}
	
	for (size_t i = 0; i < employees.size(); ++i) 
	{
        if (toLowerCase(employees[i].getIC()) == toLowerCase(UserIC))
        {  
            counter++;
            position = i ;

			cout << "\nRecords with IC EXACTLY matching '" << UserIC << "' : " << endl;
        			cout << "\n==========================================================================================================" << endl;
        			cout << left << setw(EMP_IC_LENGTH)    << "IC"
             			 << setw(EMP_NAME_LENGTH)  << "Name"
             			 << setw(EMP_TEL_LENGTH)   << "Phone"
             			 << setw(EMP_DATE_LENGTH)  << "Birth Date"
             			 << setw(EMP_DATE_LENGTH)  << "Hired Date"
             			 << setw(EMP_EMAIL_LENGTH) << "Email" << endl;
        			cout << "==========================================================================================================" << endl;

            		
                		cout << left << setw(EMP_IC_LENGTH) << employees[i].getIC()
                    		 << setw(EMP_NAME_LENGTH) << employees[i].getName()
                    		 << setw(EMP_TEL_LENGTH) << employees[i].getPhoneNum()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getBirthDate().toString()
                    		 << setw(EMP_DATE_LENGTH) << employees[i].getHiredDate().toString()
                    		 << setw(EMP_EMAIL_LENGTH) << employees[i].getEmail() << endl;

                		cout << "==========================================================================================================" << endl;
        }
    }
        if (counter == 0)
		{
			cout << "\nError! IC No. '" << UserIC << "' DOES NOT exist in employee records DB! ";
		}
		else
		{
            cout << endl;
    		cout << counter << " records found, with IC EXACTLY matching '" << UserIC << "' !!" << endl ;
    		
    		cout << "\nConfirm deletion of the record? (y/n) : ";
    		getline(cin, Input);
            cout << endl ;
    		
    		while (!ValidConfirmation(Input) || isOnlyWhitespace(Input)) 
       		{
                cout << "Invalid! Please enter 'y' or 'n'. Try again. : ";
                getline(cin, Input);
                cout << endl ;
        	}
        
    		if (Input == "y" || Input == "Y")
			{
				employees.erase(employees.begin() + position);
				empDBSize--;
				cout << "\nDone! Going back to main menu ...";
			}
		}
}
