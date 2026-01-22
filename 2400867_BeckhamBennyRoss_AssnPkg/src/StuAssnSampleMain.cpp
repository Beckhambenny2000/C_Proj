#include <iostream>
#include <limits>

#include "../inc/main.h"
#include "../inc/Employee.h"


// Global variables

Employee EmployeeRecordsDB [MAX_NO_OF_RECORDS];

/* Keeps track of the actual number of records
   empDBSize's value MUST BE UPDATED WHENEVER an employee record is : 
   - inserted into EmployeeRecordsDB  OR 
   - deleted from EmployeeRecordsDB
*/
int empDBSize = 0; 

// Function prototypes
void printWelcomeMsg();
int printMainMenuOptions();
int queryCurrentNoOfEmpRecs();

using namespace std;

int main() 
{
    printWelcomeMsg();
	
	vector<Employee> employees;
    int userEnteredNumber;

    do 
    {
        userEnteredNumber = printMainMenuOptions();
        cout << endl;

        switch (userEnteredNumber) {
            case 1:
            	cout << "-----------------------------------------------------" << endl;
            	cout << "Get current no. of records in Empolyee Database" << endl;
            	cout << "-----------------------------------------------------" << endl;
                cout << "Current no. of Employee Records in Database : " << queryCurrentNoOfEmpRecs() << endl;
                break;

            case 2:
				InputData(employees);
                break;

            case 3:
                DisplayRecords(employees);
                break;

            case 4:
                SearchIC(employees);
                break;

            case 5:
                SearchName(employees);
                break;

            case 6:
                SearchEmail(employees);
                break;

            case 7:
                SearchNumber(employees);
                break;

            case 8:
                InsertNew(employees);
                break;

            case 9:
                UpdateRecord(employees);
                break;

            case 10:
                Delete(employees);
                break;

            case 11:
                WriteData(employees);
                break;

            case 12:
                break;

            default:
                cout << endl << "Invalid Choice => " << userEnteredNumber << ", please try again!" << endl;
                break;        
        }

        cout << endl;

    } while (userEnteredNumber != 12);

    cout << "\nThank you for using this program, have a nice day!" << endl;

    return 0;
}

// Function to print the welcome message
void printWelcomeMsg() {
    cout << "\n------------------------------------------------------" << endl;
    cout << "- Welcome to My Assn P2 Program! -" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "- Student Number : < 2400867 > " << endl;
    cout << "- Student Number : < Beckham Benny Ross > " << endl;
    cout << endl;
}

// Function to print the main menu and get user input
int printMainMenuOptions() {
    cout << "-----------------------------------------------------" << endl;
    cout << " \n 1) Get current no. of records in Employee Database" << endl;
    cout << " 2) Read Data From File and Populate Employee DB" << endl;
    cout << " 3) Display All Records" << endl;
    cout << " 4) Search for records by IC" << endl;
    cout << " 5) Search for records by Name" << endl;
    cout << " 6) Search for records by Email" << endl;
    cout << " 7) Search for records by Phone Number" << endl;
    cout << " 8) INSERT New Employee Record" << endl;
    cout << " 9) Search (by ic) & UPDATE Existing Employee Record" << endl;
    cout << "10) Search (by ic) & DELETE Existing Employee Record" << endl;
    cout << "11) Write Data From Employee DB To File" << endl;
    cout << "12) Quit" << endl;
    cout << "\n-----------------------------------------------------" << endl;
    cout << endl;

    int userEnteredNumber;
    cout << "Please enter your choice (1 - 12): ";
    cin >> userEnteredNumber;
    
    if (cin.fail() || cin.peek() != '\n')
    {
    	cin.clear();
    	userEnteredNumber = 0;
    }  
    cin.ignore(100, '\n');

    return (userEnteredNumber);
}

int queryCurrentNoOfEmpRecs () 
{
  return (empDBSize);

}   // end queryCurrentNoOfEmpRecs () ...


