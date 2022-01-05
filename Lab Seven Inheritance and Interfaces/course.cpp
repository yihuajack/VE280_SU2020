//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#include <iostream>
#include "course.h"

typedef struct task{
    std::string type;
    int index; // Task index of type
    int due_month;
    int due_day;
} Task;
/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * due_month and due_day specifies its due date
 */

const int MAXTASKS = 4; // default maximum number of tasks in a course at a time
class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;
public:
    // TODO: implement the constructor
    TechnicalCourse(const std::string &course_code, int size = MAXTASKS): numTasks(0), sizeTasks(size), course_code(course_code) {
        tasks = new Task[size];
    }
    // TODO: declare and implement the destructor
    ~TechnicalCourse() {
        delete[] tasks;
    }
    // TODO: declare updateTask method
    void updateTask(const std::string &type, int index, int due_month, int due_day);
    void finishTask(const std::string &type, int index, int finish_month, int finish_day);
    void print();
};

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its due_month & due_day ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    // TODO: implement this function
    bool flag = false;
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].index == index && tasks[i].type == type) {
            flag = true;
            tasks[i].due_month = due_month;
            tasks[i].due_day = due_day;
            break;
        }
    }
    if (!flag) {
        if (numTasks == sizeTasks)
            throw tooManyTasks();
        else {
            tasks[numTasks].type = type;
            tasks[numTasks].index = index;
            tasks[numTasks].due_month = due_month;
            tasks[numTasks].due_day = due_day;
            if (tasks[numTasks].type == "Lab" || tasks[numTasks].type == "Project")
                std::cout << course_code << " " << tasks[numTasks].type << " " << tasks[numTasks].index << " is released! Submit it via oj!" << std::endl;
            else
                std::cout << course_code << " " << tasks[numTasks].type << " " << tasks[numTasks].index << " is released! Submit it via canvas!" << std::endl;
            numTasks++;
        }
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
// REQUIRES: Task index of type is in tasks. finish_month and finish_day are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // TODO: implement this function
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].type == type && tasks[i].index == index) {
            if (finish_month < tasks[i].due_month || (finish_month == tasks[i].due_month && finish_day <= tasks[i].due_day))
                std::cout << course_code << " " << tasks[i].type << " " << tasks[i].index << " is finished!" << std::endl;
            else
                std::cout << course_code << " " << tasks[i].type << " " << tasks[i].index << " is overdue!" << std::endl;
            for (int j = i; j < numTasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            numTasks--;
            break;
        }
    }
}

void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for(int i = 0; i < numTasks; ++i){
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

class UpperlevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperlevelTechnicalCourse(const std::string &course_code, int size = MAXTASKS): TechnicalCourse(course_code, size) {}
    // TODO: declare and implement the destructor
    ~UpperlevelTechnicalCourse() {}
    void updateTask(const std::string &type, int index, int due_month, int due_day);
};

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    // TODO: implement this function
    bool flag1 = false;
    int i, j, k;
    for (i = 0; i < numTasks; i++) {
        if (tasks[i].index == index && tasks[i].type == type) {
            if (tasks[i].due_month == due_month && tasks[i].due_day == due_day)
                return;
            flag1 = true;
            tasks[i].due_month = due_month;
            tasks[i].due_day = due_day;
            bool flag2 = false;
            Task temptask = tasks[i];
            for (j = 0; j < numTasks; j++) {
                if (j == i)
                    continue;
                if (due_month < tasks[j].due_month || (due_month == tasks[j].due_month && due_day < tasks[j].due_day)) {
                    if (j < i) {
                        for (k = j; k < i - 1; k++) {
                            tasks[k + 1] = tasks[k];
                        }
                    }
                    else if (j > i) {
                        for (k = i; k < j - 1; k++) {
                            tasks[k] = tasks[k + 1];
                        }
                    }
                    flag2 = true;
                    tasks[j] = temptask;
                    break;
                }
            }
            if (!flag2) {
                for (j = i; j < numTasks - 1; j++) {
                    tasks[j] = tasks[j + 1];
                }
                tasks[numTasks - 1] = temptask;
            }
            break;
        }
    }
    if (!flag1) {
        if (numTasks == sizeTasks)
            throw tooManyTasks();
        else {
            for (i = 0; i < numTasks; i++) {
                if (due_month < tasks[i].due_month || (due_month == tasks[i].due_month && due_day < tasks[i].due_day)) {
                    for (j = i; j < numTasks; j++) {
                        tasks[j + 1] = tasks[j];
                    }
                    tasks[i].type = type;
                    tasks[i].index = index;
                    tasks[i].due_month = due_month;
                    tasks[i].due_day = due_day;
                    flag1 = true;
                    break;
                }
            }
            if (!flag1) {
                tasks[numTasks].type = type;
                tasks[numTasks].index = index;
                tasks[numTasks].due_month = due_month;
                tasks[numTasks].due_day = due_day;
            }
            if (type == "Lab" || type == "Project")
                std::cout << course_code << " " << type << " " << index << " is released! Submit it via oj!" << std::endl;
            else if (type == "Team Project")
                std::cout << course_code << " " << type << " " << index << " is released! Submit it via github!" << std::endl;
            else
                std::cout << course_code << " " << type << " " << index << " is released! Submit it via canvas!" << std::endl;
            numTasks++;
        }
    }
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if(class_type == "Technical"){
        if(assign_size){
            return new TechnicalCourse(course_code, tasks_size);
        }
        else{
            return new TechnicalCourse(course_code);
        }
    }
    else if(class_type == "Upper Level Technical"){
        if(assign_size){
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else{
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else{
        return nullptr;
    }
}
