#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    int mId;
    string mName;
    int mAge;

public:
    Person(const int id, const string name, const int age);
    void setName(const string name);
    string getName() const;
    void setId(const int id);
    int getId() const;
    void setAge(const int age);
    int getAge() const;
    void toString() const;
};

#endif