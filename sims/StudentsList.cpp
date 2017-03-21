#include "StudentsList.h"
#include <fstream>
#include <sstream>
StudentsList::StudentsList()
{
    _head = NULL;
    _tail = NULL;
}

StudentsList::~StudentsList()
{
    STUDENT_NODE* d = NULL;
    STUDENT_NODE* p = _head;
    while(p != NULL)
    {
        d = p;
        p = p->next;
        delete d;
    }
}
bool StudentsList::load()
{
    std::ifstream f("sims.txt");
    std::string line;
    while(std::getline(f, line))
    {
        STUDENT_NODE* p = new STUDENT_NODE;
        p->next = NULL;
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

        if(_head == NULL)
        {
            _head = p;
            _tail = p;
        }
        else
        {
            _tail->next = p;
            _tail = p;
        }
    }
    return true;
}

bool StudentsList::save()
{
    std::ofstream f("sims.txt", std::ios::trunc); // Open and clean file
    for(STUDENT_NODE* p = _head; p != NULL; p = p->next)
    {
        f << p->id << ',' << p->name << ',';
        for(int j = 0; j < p->courseCount; j++)
        {
            f << p->courses[j].name << ',' << p->courses[j].score << ',';
        }
        f << "\n";
    }
    f.close();
    return true;
}
// Get a record of single student
// Return a pointer to student object, so may modify the record via the pointer
STUDENT* StudentsList::getStudent(const std::string& id)
{
    STUDENT_NODE* p = _head;
    while(p != NULL && p->id != id)
    {
         p = p->next;
    }
    return p;
}

// Get count of students
int StudentsList::getStudentCount() const

{
    int count = 0;
    for(STUDENT_NODE* p = _head; p != NULL; p = p->next)
    {
        count++;
    }
    return count;
}

// Get list of all students sorted by given sorting key
// Return the list as an array in students 
// count is the actual number of returned students
bool StudentsList::getStudents(STUDENT* students, int& count, int sorting) const
{
    if(students == NULL)
    {
        count = getStudentCount();
        return false;
    }

    if(count < getStudentCount())
    {
        return false;
    }

    count = 0;
    for(STUDENT_NODE* p = _head; p != NULL; p = p->next)
    {
        students[count++] = *(STUDENT*)p;
    }
    return true;
}

bool StudentsList::getStudent(STUDENT* student, const std::string& id) const
{
    STUDENT_NODE* p = _head;
    while(p != NULL)
    {
        if(p->id == id)
        {
            *student = *(STUDENT*)p;
            return true;
        }
        p = p->next;
    }
    return NULL;
}

// Set a record of a student, add new if not exist, otherwise update
// If the student is not exist, add a new record
bool StudentsList::addStudent(const std::string& id, const std::string& name)
{
    STUDENT* p = getStudent(id);
    if(p != NULL) // exist, update
    {
        p->name = name;
    }
    else // not exist, add new one
    {
        STUDENT_NODE* p = new STUDENT_NODE();
        p->id = id;
		p->courseCount =0;
        p->name = name;
        p->next = NULL;
        if(_tail == NULL)
        {
            _head = _tail = p;
        }
        else
        {
            _tail->next = p;
            _tail = p;
        }
    }
	return true;
}

// Remove a student
void StudentsList::removeStudent(const std::string& id)
{
    //Empty
	if(_head== NULL)return;
	//Headis target
	if(_head->id ==id)
	{
		if(_head->next ==NULL)//Only one
		{
			delete _head;
			_head=NULL;
			_tail=NULL;
		}
		else
		{
			STUDENT_NODE* d=_head;
			_head=_head->next ;
			delete d;
		}
		return;
	}
	//next onee is target
	STUDENT_NODE*pre=_head;
	for(STUDENT_NODE*d=_head->next ;d!=NULL;pre=d,d=d->next)
	{
		if(d->id==id)//found
		{
			if(d->next==NULL)//last one
			{
				_tail=pre;
			}
			else
			{
				pre->next=d->next;

			}
			delete d;
		}
	}
}





