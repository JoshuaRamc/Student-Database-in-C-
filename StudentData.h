#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class Student
{
private:
    unsigned int id;
    std::string name;
    unsigned short age;
public:
    Student(unsigned int student_id, std::string student_name, unsigned short student_age);
    //Getters  
    unsigned int GetStudentID() const;
    std::string GetStudentName() const;
    unsigned short GetStudentAge() const;
};

class MyParser
{
private:
    std::vector<char> separators = { ' ', '\t', '>', '<','=' };

public:
    MyParser();
    std::vector<std::string> operator()(std::string& s);
    //static void Parsed_string(std::string s, std::vector<std::string>& v);
    void DetermineCommand(std::vector<std::string> v);

};



class MyManager
{
private:
    bool running{ true };
    std::vector<Student*> student_tracker;

public:

    MyManager();
    void setVector(std::vector<Student*> fromFile);
    MyManager(std::vector<std::string> v);
    std::vector<Student*> GetPreviousVector();
    bool process(std::vector<std::string> v);
    bool AddErrorCheck(std::vector<std::string> v);
    bool FindErrorCheck(std::vector<std::string> v);
    bool RemoveErrorCheck(std::vector<std::string> v);
    void ADD(unsigned int student_ID, std::string name, unsigned short age);
    void REMOVE(std::string parameter_specify, std::string relationship_operator, std::string name, int value);
    void FIND(std::string parameter_specify, std::string relationship_operator, std::string name, int value);
    void STOP();
    ~MyManager();
};



class DiskManager : public MyManager
{
protected:
    std::string filename;
    std::vector<Student*> listStudents;
public:
    DiskManager();
    void write_file(std::vector<Student*> write);
    //std::vector<Student*> read_file(std::vector<Student*> temp);
    std::vector<std::string> read_file();
    //void read_file();
    ~DiskManager();
};