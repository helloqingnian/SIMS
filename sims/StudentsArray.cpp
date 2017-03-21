#include "StudentsArray.h"
#include <fstream>
#include <sstream>
StudentsArray::StudentsArray()
{
	_studentCount=0;
	for(int i=0;i<10;i++)
	{
		_students[i].courseCount=0;
	}


}

StudentsArray::~StudentsArray()
{

}
bool StudentsArray::load()
{
    std::ifstream f("sims.txt");
    std::string line;
    while(std::getline(f, line))
    {
        STUDENT* p = &(_students[_studentCount++]);
        std::stringstream ss(line);
        std::getline(ss, p->id, ',');
        std::getline(ss, p->name, ',');
        
        std::string course;
        std::string score;
        while(std::getline(ss, course, ',') && std::getline(ss, score, ','))
        {
            p->courses[p->courseCount].name = course;
            std::istringstream iss(score);
            iss >> p->courses[p->courseCount].score;
            p->courseCount++;
        }
    }
    return true;
}

bool StudentsArray::save()
{
    std::ofstream f("sims.txt", std::ios::trunc); // Open and clean file
    for(int i = 0; i < _studentCount; i++)
    {
        f << _students[i].id << ',' << _students[i].name << ',';
        for(int j = 0; j < _students[i].courseCount; j++)
        {
            f << _students[i].courses[j].name << ',' << _students[i].courses[j].score << ',';
        }
        f << "\n";
    }
    f.close();
    return true;
}

STUDENT* StudentsArray::getStudent(const std::string& id) 

{
    STUDENT* p = NULL;
    for(int i = 0; i < _studentCount; i++)
    {
        if(_students[i].id == id) // Found the student
        {
            return &(_students[i]);
        }
    }
    return NULL;
}

// Get Count of students
int StudentsArray::getStudentCount() const
{
    return _studentCount;
}

// Get list of all students sorted by given sorting key
// Return the list as an array in students 
// count is the actual number of returned students
bool StudentsArray::getStudents(STUDENT* students, int& count, int sorting) const
{
    if(students==NULL)
	{
		count= _studentCount;
		return false;
	}
	if(count< _studentCount)
	{
		return false;
	}
	count = _studentCount;
    for(int i = 0; i < _studentCount; i++)
    {
        int j = i-1;
        for(; j >= 0; j--)
			{
            if(((sorting == 1) && (students[j].id < _students[i].id)) || 
               ((sorting == 2) && (students[j].name < _students[i].name)))
            {
                break;
            }
			students[j+1] = students[j];
        }
        students[j+1] = _students[i];
    }
	return true;
		    // Copy student records into array students
    // Here we know we need a operator overloading of = for STUDENT
}

// Get a record of single student
// Return a pointer to student object, so may modify the record via the pointer
bool StudentsArray::getStudent(STUDENT* student, const std::string& id) const
{
    for(int i = 0; i < _studentCount; i++)
    {
        if(_students[i].id == id) // Found the student
        {
            *student = _students[i];
            return true;
        }
    }

    return false;
}

// Set a record of a student, add new if not exist, otherwise update
// If the student is not exist, add a new record
bool StudentsArray::addStudent(const std::string& id, const std::string& name)
{
    STUDENT* p = getStudent(id);
    if(p != NULL) // exist, update
    {
        p->name = name;
    }
    else // not exist, add new one
    {
        if(_studentCount == 10)
        {
            return false;
        }
        _students[_studentCount].id = id;
        _students[_studentCount].name = name;
       _studentCount++;
    }
    return true;
}

// Remove a student
void StudentsArray::removeStudent(const std::string& id)
{
    // Find the position of student
    for(int i = 0; i < _studentCount; i++)
    {
        if(_students[i].id == id) // Found
        {
            // Move forward all following courses
            for(int j = i; j < _studentCount - 1; j++)
            {
                _students[j] = _students[j+1]; // Need operator overloading for deep copy
            }
            _studentCount--;
            break;
        }
    }
}

