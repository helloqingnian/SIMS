#ifndef _STUDENTS_LIST_H
#define _STUDENTS_LIST_H

#include "Students.h"

// A node of sigle direction list of students
struct STUDENT_NODE : public STUDENT
{
    STUDENT_NODE* next;
};

// Implementation of Students 
// Using a single direction list to manage the records of students
// The advantage is allocating memory with the increasing of student count 
class StudentsList : public Students
{
public:
    StudentsList();
    virtual ~StudentsList();

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
    // If the student is not exist, add a new record
    virtual bool addStudent(const std::string& id, const std::string& name);

    // Remove a student
    virtual void removeStudent(const std::string& id);

	bool load();
	bool save();
protected:
    virtual STUDENT* getStudent(const std::string& id);

private:
    STUDENT_NODE* _head;
    STUDENT_NODE* _tail;
};

#endif
