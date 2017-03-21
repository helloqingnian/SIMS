#ifndef _STUDENTS_ARRAY_H
#define _STUDENTS_ARRAY_H

#include "Students.h"

// Implementation of Students 
// Using a plain array to manage the records of students
// The advantage is simple
// The disadvantage is the size of array is fixed, can not increasing for more students
class StudentsArray : public Students
{
public:
    StudentsArray();
    virtual ~StudentsArray();

    // Get count of students
    virtual int getStudentCount() const;

    // Get list of all students sorted by given sorting key
    // Return the list as an array in students 
    // count is the actual number of returned students
    virtual bool getStudents(STUDENT* students, int& count, int sorting) const;

    // Get a record of single student
    // Return a pointer to student object, so may modify the record via the pointer
    virtual bool getStudent(STUDENT* student, const std::string& id) const;

    // Set a record of a student, add new if not exist, otherwise update
    virtual bool addStudent(const std::string& id, const std::string& name);

    // Remove a student
    virtual void removeStudent(const std::string& id);

	virtual bool load();
    virtual bool save();
protected:
    virtual STUDENT* getStudent(const std::string& id);
    
private:
    STUDENT _students[10]; // Array of students
    unsigned int _studentCount; // Current count of students
};

#endif
