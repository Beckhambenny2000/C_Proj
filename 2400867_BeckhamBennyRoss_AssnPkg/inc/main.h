#include <vector>
#include <string>

#include "../inc/Employee.h"

using namespace std;

#ifndef MAIN_H
#define MAIN_H

#define MAX_NO_OF_RECORDS 60

int InputData(vector<Employee> &employees); 	  // 2
void DisplayRecords(vector<Employee> &employees); // 3
void SearchIC(vector<Employee> &employees);  	  // 4
void SearchName(vector<Employee> &employees);     // 5
void SearchEmail(vector<Employee> &employees);    // 6
void SearchNumber(vector<Employee> &employees);   // 7
void InsertNew(vector<Employee> &employees);      // 8
void UpdateRecord(vector<Employee> &employees);   // 9
void Delete(vector<Employee> &employees);         // 10
void WriteData(vector<Employee> &employees);      // 11

string toLowerCase(const string &str);
string toUpperCase(const string &str);
bool isLeapYear(int year);
bool isValidDate(const string& date);
bool isValidString(const string& input);
bool isValidInteger(const string& input);
bool ValidConfirmation(string input);
int readEmployeesFromCSV(const std::string &filename, std::vector<Employee> &employees, int maxLines);
Date parseDate(const std::string &dateStr);
std::vector<Employee> readCSV(const std::string& filename);
bool isOnlyWhitespace(const string& str);
bool isAtLeast18YearsOld(const Date& birthDate, const Date& hireDate) ;
bool isValidEmail(const string& email);

#endif

