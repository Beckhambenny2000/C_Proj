#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>

#include "../inc/main.h"

extern int empDBSize;

using namespace std;

string input;

void DisplayRecords(vector<Employee> &employees) {
    
    if (employees.empty())
	{
        cout << "No employee records found." << endl;
        return;
    }
    
    cout << "Show array index? (y/n): ";
    getline(cin, input);
    cout << endl ;
    
    while (!ValidConfirmation(input) || isOnlyWhitespace(input)) 
    {
        cout << "Invalid input! Please enter 'y' or 'n'. Try again: ";
        getline(cin, input);
        cout << endl ;
    }
    
    bool showIndex = (input == "y" || input == "Y");

	cout << "\t\t\t\t\tAll Employee Records (Total = " << empDBSize <<") ..." << endl;
    cout << "===========================================================================================================================" << endl;

    // Header
    if (showIndex) cout << left << setw(EMP_IDX_LENGTH) << "Idx";
    cout << left << setw(EMP_IC_LENGTH) << "IC"
         << setw(EMP_NAME_LENGTH) << "Name"
         << setw(EMP_TEL_LENGTH) << "Phone"
         << setw(EMP_DATE_LENGTH) << "Birth Date"
         << setw(EMP_DATE_LENGTH) << "Hired Date"
         << setw(EMP_EMAIL_LENGTH) << "Email" << endl;

    cout << "===========================================================================================================================" << endl;

    // Data Rows
    for (size_t i = 0; i < employees.size(); ++i) {
        if (i == MAX_NO_OF_RECORDS) {
            break;
        }

        if (showIndex) cout << left << setw(EMP_IDX_LENGTH) << i;
        cout << left << setw(EMP_IC_LENGTH) << employees[i].getIC()
             << setw(EMP_NAME_LENGTH) << employees[i].getName()
             << setw(EMP_TEL_LENGTH) << employees[i].getPhoneNum()
             << setw(EMP_DATE_LENGTH) << employees[i].getBirthDate().toString()
             << setw(EMP_DATE_LENGTH) << employees[i].getHiredDate().toString()
             << setw(EMP_EMAIL_LENGTH) << employees[i].getEmail() << endl;
    }

    cout << "===========================================================================================================================" << endl;
}

vector<Employee> readCSV(const string& file_name) {
    vector<Employee> employees;
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return employees;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string idx, name, email, ic, phoneNum, hireDateStr, birthDateStr;

        getline(ss, idx, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, ic, ',');
        getline(ss, phoneNum, ',');
        getline(ss, hireDateStr, ',');
        getline(ss, birthDateStr, ',');

        // Parse hire date
        int hDay, hMonth, hYear;
        sscanf(hireDateStr.c_str(), "%d/%d/%d", &hDay, &hMonth, &hYear);
        Date hireDate(hDay, hMonth, hYear);

        // Parse birth date
        int bDay, bMonth, bYear;
        sscanf(birthDateStr.c_str(), "%d/%d/%d", &bDay, &bMonth, &bYear);
        Date birthDate(bDay, bMonth, bYear);

        // Create Employee object and add to vector
        employees.emplace_back(name, email, ic, phoneNum, hireDate, birthDate);
    }

    file.close();
    return employees;
}
