#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Student
{
public:
    string name;
    int roll_number;

    Student(string n, int roll) : name(n), roll_number(roll) {}
};

void addStudent(fstream &file)
{
    string name;
    int roll_number;

    cout << "Enter student name: ";
    cin >> name;

    cout << "Enter roll number: ";
    cin >> roll_number;

    file.seekg(0, ios_base::beg);

    string line;
    bool rollNumberExists = false;

    while (getline(file, line))
    {
        istringstream iss(line);
        string current_name;
        int current_roll_number;

        iss >> current_name >> current_roll_number;

        if (current_roll_number == roll_number)
        {
            rollNumberExists = true;
            break;
        }
    }

    if (!rollNumberExists)
    {
        file.clear();
        file.seekp(0, ios_base::end);
        file << name << " " << roll_number << endl;
        cout << "Student added successfully!" << endl;
    }
    else
    {
        cout << "Student with the same roll number already exists. Not added." << endl;
    }
}

void deleteStudent(fstream &file)
{
    int roll_number;

    cout << "Enter the roll number to delete: ";
    cin >> roll_number;

    file.seekg(0, ios_base::beg);
    file.seekp(0, ios_base::beg);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        istringstream iss(line);
        string name;
        int current_roll_number;

        iss >> name >> current_roll_number;

        if (current_roll_number != roll_number)
        {
            file << name << " " << current_roll_number << endl;
        }
        else
        {
            found = true;
        }
    }

    if (found)
    {
        cout << "Student deleted successfully!" << endl;
    }
    else
    {
        cout << "Student with roll number " << roll_number << " not found." << endl;
    }
}

void modifyStudent(fstream &file)
{
    int roll_number;

    cout << "Enter the roll number to modify: ";
    cin >> roll_number;

    file.seekg(0, ios_base::beg);
    file.seekp(0, ios_base::beg);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        istringstream iss(line);
        string name;
        int current_roll_number;

        iss >> name >> current_roll_number;

        if (current_roll_number == roll_number)
        {
            string new_name;
            cout << "Enter the new name: ";
            cin >> new_name;

            file.seekp(file.tellg());
            file << new_name << " " << current_roll_number << endl;
            found = true;
        }
    }

    if (found)
    {
        cout << "Student modified successfully!" << endl;
    }
    else
    {
        cout << "Student with roll number " << roll_number << " not found." << endl;
    }
}

void displayStudents(fstream &file)
{
    vector<Student> students;

    file.seekg(0, ios_base::beg);

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string name;
        int roll_number;

        iss >> name >> roll_number;
        students.push_back(Student(name, roll_number));
    }

    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.roll_number < b.roll_number; });

    cout << "Student Records:" << endl;
    for (const auto &student : students)
    {
        cout << "Name: " << student.name << ", Roll Number: " << student.roll_number << endl;
    }
}

int main()
{
    fstream file("student_records.txt", ios_base::in | ios_base::out | ios_base::app);

    char choice;

    while (true)
    {
        cout << "\n1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Modify Student" << endl;
        cout << "4. Display Students" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            addStudent(file);
            break;
        case '2':
            deleteStudent(file);
            break;
        case '3':
            modifyStudent(file);
            break;
        case '4':
            displayStudents(file);
            break;
        case '5':
            cout << "Exited program" << endl;
            file.close();
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        file.clear();
        file.seekg(0, ios_base::beg);
        file.seekp(0, ios_base::beg);
    }
}
