#ifndef _STUDENTS_H
#define _STUDENTS_H

#include <iostream>
#include <string>

using namespace std;

// An item of records of completed courses and scores
struct COURSE 
{

    std::string name;
    int score;
};

struct STUDENT 
{ 
	// Deep copy
    STUDENT& operator=(const STUDENT& other)
    {
        if (this != &other) // self-assignment check
        { 
            id = other.id;
            name = other.name;
            courseCount = other.courseCount;
            for(int i = 0; i < courseCount; i++)
				{
                courses[i].name = other.courses[i].name;
                courses[i].score = other.courses[i].score;
            }
        }
        return *this;
    }
    std::string id; // Student number, unique for each student
    std::string name;
    COURSE courses[10]; // Records of completed courses and scores
    unsigned int courseCount; // Count of completed courses
};

// An abstract class declared the operations of student management
// Operations relatd to the list of students are virtual, to be implemented by derived classes
// Operations on the courses and scores are same so implemented in the base class
class Students
{
public:
    Students();
    virtual ~Students();

    // Get count of students
    virtual int getStudentCount() const = 0;

    // Get list of all students sorted by given sorting key
    // Return the list as an array in students int
    // count is the actual number of returned students
    virtual bool getStudents(STUDENT* students, int& count, int sorting) const = 0;

    // Get a record of single student
    // Return a pointer to student object, so may modify the record via the pointer
    virtual bool getStudent(STUDENT* student, const std::string& id) const = 0;

    // Set a record of a student, add new if not exist, otherwise update
    virtual bool addStudent(const std::string& id, const std::string& name) = 0;

    // Remove a student
    virtual void removeStudent(const std::string& id) = 0;

    // Set course and score to a student
    // If the course is not exist, add a new record
    bool addCourse(const std::string& id, const std::string& course, int score);

    // Remove a course from a student
    void removeCourse(const std::string& id, const std::string& course);

	virtual bool load() = 0;
    virtual bool save() = 0;
protected:
    virtual STUDENT* getStudent(const std::string& id) = 0;
};

#endif
