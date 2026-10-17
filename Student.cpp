#include "Student.h"

// Default constructor
Student::Student() {
    studentID = "";
    studentName = "";
    department = "";
    email = "";
    phoneNumber = "";
    role = "Student";
}

// Parameterized constructor
Student::Student(string id, string name, string dept, string mail, string phone, string userRole) {
    studentID = id;
    studentName = name;
    department = dept;
    email = mail;
    phoneNumber = phone;
    role = userRole;
}

// Getters
string Student::getStudentID() const {
    return studentID;
}

string Student::getStudentName() const {
    return studentName;
}

string Student::getDepartment() const {
    return department;
}

string Student::getEmail() const {
    return email;
}

string Student::getPhoneNumber() const {
    return phoneNumber;
}

string Student::getRole() const {
    return role;
}

// Display profile in readable format
void Student::displayStudent() const {
    cout << "  --------------------------------------------------\n";
    cout << "  ID / Roll No : " << studentID << " (" << role << ")\n";
    cout << "  Name         : " << studentName << "\n";
    cout << "  Department   : " << department << "\n";
    cout << "  Email        : " << email << "\n";
    cout << "  Phone        : " << phoneNumber << "\n";
    cout << "  --------------------------------------------------\n";
}
