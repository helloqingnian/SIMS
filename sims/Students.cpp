#include "Students.h"

Students::Students()
{

}

Students::~Students()
{

}

// Set course and score to a student
// If the course is not exist, add a new record
bool Students::addCourse(const std::string& id, const std::string& course, int score)
{
	// Find the student
    STUDENT* p = getStudent(id);
    if(p == NULL) // not Found
    {
        return false;
    }

    // Find the course
    int i = 0;
    while(i < p->courseCount)
    {
        if(p->courses[i].name == course) // Found, update score
        {
            p->courses[i].score = score;
            break;
        }
        i++;
    }

    if(i == p->courseCount) // Not found the course, add
    {

        if(p->courseCount == 10) // Has been the max count 
        {
            return false;
        }
        p->courses[p->courseCount].name = course;
        p->courses[p->courseCount].score = score;
        p->courseCount++;
    }

    return true;
}

// Remove a course from a student
void Students::removeCourse(const std::string& id, const std::string& course)
{
    // Find the student
    STUDENT* p = getStudent(id);
    if(p != NULL) // Found
    {
        // Find the position of course
        for(int i = 0; i < p->courseCount; i++)
        {
            if(p->courses[i].name == course) // Found
            {
                // Move forward all following courses
                for(int j = i; j < p->courseCount - 1; j++)
                {
                    p->courses[j].name = p->courses[j+1].name;
                    p->courses[j].score = p->courses[j+1].score;
                }
                p->courseCount--;
                break;
            }
        }
    }
}
