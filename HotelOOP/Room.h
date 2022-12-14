#ifndef ROOM_H
#define ROOM_H

#include "Person.h"
using namespace std;

const int DEFAULT_MAX_PERSONS = 6;
const int MAX_NIGHTS_STAY = 14;
const int MIN_NIGHTS_STAY = 1;

class Room
{
protected:
    struct Persons
    {
        Person *mPerson;
        struct Persons *next;
    };
    int mCurrentPersons;
    int mMaxPersons;
    struct Persons *head = NULL;
    int mPricePerNight;      // Base price per night
    int mTotalPricePerNight; // Depend on persons count
    int mRoomId;
    
    int mCurrentNight;
    int mNightsStay;

public:
    Room(const int pricePerNight, const int roomId, const int maxPersons);
    Room(const int pricePerNight, const int roomId);
    ~Room();
    void setPricePerNight(const int pricePerNight);
    void setNightsStay(const int nightsStay);
    int getNightsStay() const;
    void setCurrentNight(const int currentNight);
    int getCurrentNight() const;
    int getPricePerNight() const;
    void setMaxPersons(const int maxPersons);
    int getMaxPersons() const;
    void setCurrentPersons(const int currentPersons);
    int getCurrentPersons() const;
    void setRoomId(const int roomId);
    int getRoomId() const;
    void setTotalPricePerNight(const int totalPricePerNight);
    int getTotalPricePerNight() const;
    void addPersonsToRoom(const int num,const int nightStays); // Checkin
    void removeAllPersonsFromRoom();      // Checkout
    void generateVisitorsToRoom();
    virtual void toString() = 0;

private:
    Person *createPerson();
    Person *createDummyPerson();
    bool addDummyPersonToTail();
    bool addPersonToTail();
};

class RegularRoom : public Room
{
private:
    bool mIsBalcony;

public:
    RegularRoom(const int pricePerNight, const int roomId, const bool isBalcony);
    void setIsBalcony(const bool isBalcony);
    bool getIsBalcony();
    void toString();
};

class LuxuryRoom : public Room
{
private:
    bool mIsJacuzzi;

public:
    LuxuryRoom(const int pricePerNight, const int roomId, const bool isJacuzzi);
    void setIsJacuzzi(const bool isJacuzzi);
    bool getIsJacuzzi() const;
    void toString();
};
#endif