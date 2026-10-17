#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

// Represents a university member (Student or Faculty)
class Student {
private:
    string studentID;     // NED Roll Number or Faculty ID (e.g., CS-024)
    string studentName;   // Full name
    string department;    // Department (e.g., Computer Science)
    string email;         // University email address
    string phoneNumber;   // Contact phone number
    string role;          // "Student" or "Faculty"

public:
    // Default constructor
    Student();

    // Parameterized constructor
    Student(string id, string name, string dept, string mail, string phone, string userRole);

    // Getters
    string getStudentID() const;
    string getStudentName() const;
    string getDepartment() const;
    string getEmail() const;
    string getPhoneNumber() const;
    string getRole() const;

    // Display student details
    void displayStudent() const;
};

#endif
