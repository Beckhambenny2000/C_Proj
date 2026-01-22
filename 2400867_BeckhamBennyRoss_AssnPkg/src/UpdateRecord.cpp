#include <iostream>
#include <fstream>  
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <regex>

#include "../inc/main.h"

using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to check if the entered day, month, and year are valid
bool isValidDate(const string& date) {
    // Regular expression for date format dd-mm-yyyy
    regex datePattern(R"(^\d{2}-\d{2}-\d{4}$)");

    // Check if the date matches the pattern
    if (!regex_match(date, datePattern)) {
        return false;  // Invalid format
    }

    // Extract the day, month, and year from the date string
    int day, month, year;
    char dash1, dash2;
    stringstream ss(date);
    ss >> day >> dash1 >> month >> dash2 >> year;

    if (ss.fail() || dash1 != '-' || dash2 != '-') {
        return false;  // Parsing failed
    }

    // Check if the month is valid
    if (month < 1 || month > 12) {
        return false;
    }

    // Check if the day is valid for the given month and year
    if (month == 2) {
        // February has 28 or 29 days depending on leap year
        if (isLeapYear(year)) {
            if (day < 1 || day > 29) {
            cout << "Day value > 29 for month = 2 in leap year! (Expected range is 1-29)" << endl ;
            cout << endl ;
                return false;
            }
        } else {
            if (day < 1 || day > 28) {
                return false;
            }
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        // April, June, September, November have 30 days
        if (day < 1 || day > 30) {
            return false;
        }
    } else {
        // All other months have 31 days
        if (day < 1 || day > 31) {
            return false;
        }
    }

    return true;
}

bool isAtLeast18YearsOld(const Date& birthDate, const Date& hireDate) {  
    // Ensure birthdate is not after hire date  
    if (birthDate.year > hireDate.year ||  
        (birthDate.year == hireDate.year && birthDate.month > hireDate.month) ||  
        (birthDate.year == hireDate.year && birthDate.month == hireDate.month && birthDate.day > hireDate.day)) {  
        return false; // Birthdate cannot be after hire date  
    }  

    // Calculate age difference  
    int age = hireDate.year - birthDate.year;

    if (age > 18) return true;  // Older than 18, valid
    if (age < 18) return false; // Younger than 18, invalid

    // If exactly 18 years old, check if hire date is on or after birth date  
    if (hireDate.month > birthDate.month) return true;  
    if (hireDate.month == birthDate.month && hireDate.day >= birthDate.day) return true;  

    return false; // If month/day condition fails
}

void UpdateRecord(vector<Employee> &employees)
{
	int counter = 0;
	int position = 0;
	string UserIC, NewIC, NewEmail, NewName, NewNumber, NewBirth, NewHire, Input;
	
	if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
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
			return;
		  }
            
            cout << endl;
    		cout << counter << " records found, with IC EXACTLY matching '" << UserIC << "' !!" << endl ;
    		
    		int UserInput;
			do
    		{
    			cout << endl;
				cout << "++++++++++++++++++++++++++++++" << endl ;
				cout << "+++ Item to be updated ... +++" << endl ;
				cout << "++++++++++++++++++++++++++++++" << endl ;
				cout << "1) Update IC		(curr. value = '" << employees[position].getIC() << "')" << endl ;
    			cout << "2) Update Email		(curr. value = '" << employees[position].getEmail() << "')" << endl ;
    			cout << "3) Update Name		(curr. value = '" << employees[position].getName() << "')" << endl ;
    			cout << "4) Update Phone Number	(curr. value = '" << employees[position].getPhoneNum() << "')" << endl ;
    			cout << "5) Update Birth Date	(curr. value = '" << employees[position].getBirthDate().toString() << "')" << endl ;
    			cout << "6) Update Hired Date	(curr. value = '" << employees[position].getHiredDate().toString() << "')" << endl ;
    			cout << "7) Done with updates" << endl ;
    			cout << "++++++++++++++++++++++++++++++" << endl ;
    			cout << "Please enter your choice (1-7) : " ;
    			cin >> UserInput;
    			if (cin.fail() || cin.peek() != '\n')
    			{	
    				cin.clear();
    				UserInput = 0;
    			} 
    			cin.ignore(100, '\n');
    			cout << endl;
    		
    		switch (UserInput)
    		{
    			case 1:
    				cout << "Please type in employee's IC ( < 10 chars ) : " ;
					getline(cin, NewIC);
					cout << endl;
					
						while (NewIC.length() >= 10 || isOnlyWhitespace(NewIC))
						{
							if(NewIC.length() >= 10)
							{
								cout << "Input too long. Please enter data again ( < 10 chars ) : " ;
							}
							else if (isOnlyWhitespace(NewIC))
							{
								cout << "Error! Do not leave it blank! Please enter data again : ";
							}
							getline(cin, NewIC);
							cout << endl;
						}
					
					for (size_t i = 0; i < employees.size(); ++i) 
					{
						if (toLowerCase(employees[i].getIC()) == toLowerCase(NewIC))
						{
							cout << "Error! IC No. '" << NewIC << "' already exist in employee records DB, please try again! " << endl;
							cout << "\nPlease type in employee's IC ( < 10 chars ) : " ;
							getline(cin, NewIC);
							cout << endl;
							
							while (NewIC.length() >= 10 || isOnlyWhitespace(NewIC))
							{
								if(NewIC.length() >= 10)
								{	
									cout << "Input too long. Please enter data again ( < 10 chars ) : " ;
								}
								else if (isOnlyWhitespace(NewIC))
								{
									cout << "Error! Do not leave it blank! Please enter data again : ";
								}
								getline(cin, NewIC);
								cout << endl;
							}
						}
					}
					employees[position].setIC(NewIC);
					break;
					
				case 2:
    				cout << "Please type in employee's email ( < 35 chars ) : " ;
					getline(cin, NewEmail);
					cout << endl; 

						while (NewEmail.length() >= 35 || isOnlyWhitespace(NewEmail) || !isValidEmail(NewEmail))
						{
							if (NewEmail.length() >= 35)
							{
								cout << "Input too long. Please enter data again ( < 35 chars ) : " ;
							}
							else if (isOnlyWhitespace(NewEmail))
							{
								cout << "Error! Do not leave it blank! Please enter data again : ";
							}
							else if (!isValidEmail(NewEmail))
							{
								cout << "Invalid email format! Please enter data again: ";
							}
							getline(cin, NewEmail);
							cout << endl;
						}
						
					for (size_t i = 0; i < employees.size(); ++i)
					{
						if (toLowerCase(employees[i].getEmail()) == toLowerCase(NewEmail))
						{
							cout << "Error! Email '" << NewEmail << "' already exist in employee records DB, please try again! " << endl;
							cout << "\nPlease type in employee's Email ( < 35 chars ) : " ;
							getline(cin, NewEmail);
							cout << endl;
							
							while (NewEmail.length() >= 35 || isOnlyWhitespace(NewEmail) || !isValidEmail(NewEmail))
							{
								if (NewEmail.length() >= 35)
								{
									cout << "Input too long. Please enter data again ( < 35 chars ) : " ;
								}
								else if (isOnlyWhitespace(NewEmail))
								{
									cout << "Error! Do not leave it blank! Please enter data again : ";
								}
								else if (!isValidEmail(NewEmail))
								{
									cout << "Invalid email format! Please enter data again: ";
								}
								getline(cin, NewEmail);
								cout << endl;
							}
						}
					}
					employees[position].setEmail(NewEmail);
					break;
				
				case 3:
					insertName:
    				cout << "Please type in employee's name ( < 35 chars ) : " ;
					getline(cin, NewName);
					cout << endl;
					
					while (NewName.length() >= 35 || !isValidString(NewName) || isOnlyWhitespace(NewName)) 
					{
        
        				if (NewName.length() >= 35)
        				{
            				cout << "Input too long. Please enter data again ( < 35 chars ): ";
        				}
        
        				else if (!isValidString(NewName) || isOnlyWhitespace(NewName)) 
        				{
            				cout << "Error: Input must contain only letters. Try again: ";
        				}

        				getline(cin, NewName);
        				cout << endl;
    				}
						
					for (size_t i = 0; i < employees.size(); ++i) 
					{
						if (toLowerCase(employees[i].getName()) == toLowerCase(NewName))
						{
							cout << "Error! Name '" << NewName << "' already exist in employee records DB, do you INSIST this is correct? (y/n) : ";
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
								cout << "Alright, you insisted! Strong (duplicate) Name '" << NewName << "' under this Employee Record in DB ..." << endl;
								cout << endl;
								break;
							}
							else
							{
								goto insertName;
							}	
						}
					}
					employees[position].setName(NewName);
					break;
				
				case 4:
					insertNumber:
    				cout << "Please type in employee's phone num ( < 15 chars ) : " ;
					getline(cin, NewNumber);
					cout << endl;
					
					while (NewNumber.length() >= 15 || !isValidInteger(NewNumber) || isOnlyWhitespace(NewNumber)) 
					{
    					if (NewNumber.length() >= 15) 
    					{
        					cout << "Input too long. Please enter data again ( < 15 chars ): ";
        				} 
        				else if (!isValidInteger(NewNumber) || isOnlyWhitespace(NewNumber)) 
        				{
            				cout << "Error: Input must contain only numbers. Try again: ";
        				}
        				getline(cin, NewNumber);
        				cout << endl;
    				}
						
					for (size_t i = 0; i < employees.size(); ++i) 
					{
						if (toLowerCase(employees[i].getPhoneNum()) == toLowerCase(NewNumber))
						{
							cout << "Error! Phone Num '" << NewNumber << "' already exist in employee records DB, do you INSIST this is correct? (y/n) : ";
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
							cout << "Alright, you insisted! Strong (duplicate) phone num '" << NewNumber << "' under this Employee Record in DB ..." << endl;
							cout << endl;
							break;
						}
						else
						{
							goto insertNumber;
						}
						}	
					}
					employees[position].setPhoneNum(NewNumber);
					break;
					
				case 5:
				{
					cout << "To enter employee's date of birth, please adhere to the format shown in prompt below ..." << endl;
					cout << "\nEnter a date (dd-mm-yyyy): ";
					getline(cin, NewBirth);
					cout << endl;

					while (!isValidDate(NewBirth) || isOnlyWhitespace(NewBirth))  // Keep asking until a valid date is entered
					{
    					cout << "Invalid date format or values. Please try again: ";
    					getline(cin, NewBirth);
    					cout << endl;
					}
					
					replace(NewBirth.begin(), NewBirth.end(), '-', '/');
					
					Date Birth_Date = parseDate(NewBirth);
					Date Hired_Date = employees[position].getHiredDate();
					
					while (!isAtLeast18YearsOld(Birth_Date, Hired_Date)) 
					{
						cout << "Employee must be at least 18 years old differnet. Please enter a valid date: ";
						getline(cin, NewBirth);
						cout << endl;
						replace(NewBirth.begin(), NewBirth.end(), '-', '/');
						Birth_Date = parseDate(NewBirth);
					}
					
					employees[position].setBirthDate(Birth_Date);
					break;
				}
					
				case 6:
				{
					cout << "To enter employee's date of hire, please adhere to the format shown in prompt below ..." << endl;
					cout << "\nEnter a date (dd-mm-yyyy): ";
					getline(cin, NewHire);
					cout << endl;
					
					Date Birth_Date = employees[position].getBirthDate(); // Retrieve stored birthdate
					Date Hire_Date;
	
					while (1)
					{
						if (!isValidDate(NewHire))
						{
								
							do
							{
								cout << "Invalid date format or values. Please try again: ";
								getline(cin, NewHire);
								cout << endl ;
							}while(!isValidDate(NewHire));
						}
						replace(NewHire.begin(), NewHire.end(), '-', '/');
						Hire_Date = parseDate(NewHire);
						if (!isAtLeast18YearsOld(Birth_Date, Hire_Date)) 
						{
							cout << "Employee must be at least 18 years old different. Please enter a valid date: ";
						}
						else
						{
							break;
						}
						getline(cin, NewHire);
						cout << endl;
					}
										
					employees[position].setHiredDate(Hire_Date);
					break;
				}
				
				case 7:
					break;
					
				default:
					cout << "Invalid! Please try again " << endl ;
					
			}
		}while (UserInput != 7);
		}
