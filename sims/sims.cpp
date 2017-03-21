#include "Students.h"
#include "StudentsArray.h"
#include "StudentsList.h"
#include <sstream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
// Global object of Students
Students* theStudents = NULL;

// Print version information on screen
void version()
{
    std::cout << "Student Infomation Management System (SIMS)\n";
    std::cout << "Created by Qin Rui. Version 0.1\n";
}

// Print operation menu on screen
void menu()
{
    std::cout << "\n";
    std::cout << "Please choose an operation:\n";
    std::cout << "[1] List all students\n";
    std::cout << "[2] Display information of a student\n";
    std::cout << "[3] Add a student\n";
    std::cout << "[4] Remove a student\n";
    std::cout << "[5] Add a completed course to a student\n";
    std::cout << "[6] Remove a completed course from a student\n";
    std::cout << "[0] Exit the application\n";
    std::cout << ">>";
}

// List all students
void listStudents()
{
	
    while(true)
    {
        // First inpurt sorting option
        std::cout << "Please choose a sorting option:" << "\n";
        std::cout << "[1] Sorting by student ID\n";
        std::cout << "[2] Sorting by name\n";
        std::cout << "[0] No sorting\n";
        std::cout << ">>";

        std::string option;
        std::cin >> option;
        int sorting = -1;
		std::istringstream iss(option);
	    iss>>sorting;

        if(sorting < 0) // invalid input
        {
            continue;
        }

        // Get students list
        int count = theStudents->getStudentCount();
        if(count > 0)
        {
            STUDENT* students = new STUDENT[count];
            if(theStudents->getStudents(students, count, sorting) && count > 0)
            {
				std::cout << std::setw(8) << "Index" << std::setw(16) << "ID" << std::setw(32) << "Name" << "\n";
                for(int i = 0; i < count; i++)
                {
                    std::cout << std::setw(8) << i + 1 << std::setw(16) << students[i].id 
                            << std::setw(32) << students[i].name << "\n";
                }
            }
        }
        std::cout << count << " students in total.\n";
        break;
    }
}

// Display information of of a student
void displayStudent()
{
	std::string id;
	while(id.empty())
	{
		std::cout<<"Please input student number:";
			std::cin>>id;
	}
	STUDENT student;
	if(!theStudents->getStudent(&student,id))//Faild
	{
		std::cout<<"Not found the student.\n";
	}
	std::cout<<std::setw(8)<<"ID:"<<student.id<<"\n";
	std::cout<<std::setw(8)<<"NAME:"<<student.name<<"\n";
	std::cout<<"Completed courses:"<<student.courseCount<<"\n";
	for(int i=0;i<student.courseCount ;i++)
	{
		std::cout<<student.courses[i].name <<":"<<student.courses [i].score <<"\n";
	}
}

// Add a student
void addStudent()
{
    std::string id;
    std::string name;

    while(id.empty())
    {
        std::cout << "Please input student number:";
        std::cin >> id;
    }

    while(name.empty())
    {
        std::cout << "Please input student name:";
        std::cin >> name;
    }

    theStudents->addStudent(id, name);
}

// Remvoe a student
void removeStudent()
{
    std::string id;
    while(id.empty())
    {
        std::cout << "Please input student ID:";
        std::cin >> id;
    }

    theStudents->removeStudent(id);
}

// Add a course to a student
void addCourse()
{
		std::string id;
    while(id.empty())
    {
        std::cout << "Please input student number:";
        std::cin >> id;
    }

    std::string course;
    while(course.empty())
    {
        std::cout << "Please input course name:";
        std::cin >> course;
		}

    std::string score;
    int iscore = -1;
    while(iscore < 0)
    {
        std::cout << "Please input course score:";
        std::cin >> score;
        std::istringstream iss(score);
        iss >> iscore;
    }

    theStudents->addCourse(id, course, iscore);

}

// Remove a course from a student
void removeCourse()
{
	std::string id; 
    std::string course;

    while(id.empty())
    {
        std::cout << "Please input student number:";
        std::cin >> id;
    }

    while(course.empty())
    {
        std::cout << "Please input course name:";
		std::cin >> course;
    }

    theStudents->removeCourse(id, course);

}



int main(int argc, char* argv[])
{
   version(); // Display software information

    // Init students manager
    if(argc >= 2 && std::string(argv[1]) == "--list")
    {
        theStudents = new StudentsList();
        std::cout << "Program is using List to manage students records.\n\n";
        std::cout << "sims.exe --array will force the program using Array.\n";
    }
    else
    {
        theStudents = new StudentsArray();
        std::cout << "Program is using Array to manage students records.\n\n";
        std::cout << "sims.exe --list will force the program using Array.\n";
    }
    theStudents->load();

    while(true) // Loop to excute user's operations
    {
        menu(); // Display operations menu

        std::string option; // Why use string, rather than char or int ?
        std::cin >> option; // Input an operation 

        // Operations
        if(option == "1") listStudents();
        else if(option == "2") displayStudent();
        else if(option == "3") addStudent();
        else if(option == "4") removeStudent();
        else if(option == "5") addCourse();
        else if(option == "6") removeCourse();
        else if(option == "0") break; // exit
    }

    // Destroy students manager
    theStudents->save();
    delete theStudents;


    return 0;
}
