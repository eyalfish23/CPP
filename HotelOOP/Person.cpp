#include "Person.h"

using namespace std;

Person::Person(const int id, const string name, const int age)
{
    setId(id);
    setName(name);
    setAge(age);
}

void Person::setName(const string name)
{
    mName = name;
}

string Person::getName() const
{
    return mName;
}

void Person::setId(const int id)
{
    mId = id;
}

int Person::getId() const
{
    return mId;
}

void Person::setAge(const int age)
{
    mAge = age;
}

int Person::getAge() const
{
    return mAge;
}

void Person::toString() const
{
    cout << "  Id: " << mId << ", Name: " << mName << ", Age: " << mAge << endl;
}