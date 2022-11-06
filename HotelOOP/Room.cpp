#include "Room.h"
using namespace std;

Room::Room(const int pricePerNight, const int roomId)
{
    setPricePerNight(pricePerNight);
    setRoomId(roomId);
    setCurrentPersons(0);
    setTotalPricePerNight(0);
    setMaxPersons(DEFAULT_MAX_PERSONS);
}

Room::Room(const int pricePerNight, const int roomId, const int maxPersons)
{
    setPricePerNight(pricePerNight);
    setRoomId(roomId);
    setCurrentPersons(0);
    setTotalPricePerNight(0);
    setMaxPersons(maxPersons);
}

Room::~Room()
{
    removeAllPersonsFromRoom();
}

void Room::setPricePerNight(const int pricePerNight)
{
    mPricePerNight = pricePerNight;
}

void Room::setMaxPersons(const int maxPersons)
{
    if (maxPersons < 0)
    {
        mMaxPersons = DEFAULT_MAX_PERSONS;
    }
    else
    {
        mMaxPersons = maxPersons;
    }
}

int Room::getMaxPersons() const
{
    return mMaxPersons;
}

void Room::setCurrentPersons(const int currentPersons)
{
    mCurrentPersons = currentPersons;
}

int Room::getCurrentPersons() const
{
    return mCurrentPersons;
}

void Room::setRoomId(const int roomId)
{
    mRoomId = roomId;
}

int Room::getRoomId() const
{
    return mRoomId;
}

int Room::getPricePerNight() const
{
    return mPricePerNight;
}

void Room::setTotalPricePerNight(const int totalPricePerNight)
{
    mTotalPricePerNight = totalPricePerNight;
}

int Room::getTotalPricePerNight() const
{
    return mTotalPricePerNight;
}

Person *Room::createDummyPerson()
{
    int id, age;
    string name;
    Person *person = NULL;

    id = 1 + (rand() % 1000);
    age = 17 + (rand() % 90);
    name = "DummyGuest";

    person = new Person(id, name, age);
    if (person == NULL)
    {
        return NULL;
    }
    return person;
}

Person *Room::createPerson()
{
    int id, age;
    string name;
    Person *person = NULL;

    cout << "What is your id:" << endl;
    cin >> id;
    cout << "What is your name:" << endl;
    cin >> name;
    cout << "What is your age:" << endl;
    cin >> age;

    person = new Person(id, name, age);
    if (person == NULL)
    {
        return NULL;
    }
    return person;
}

// Checkout
void Room::removeAllPersonsFromRoom()
{
    Persons *current = head;
    Persons *ptr = current;

    if (head == NULL)
    {
        cout << "Room is already empty" << endl;
    }

    while (current != NULL)
    {
        ptr = current;
        current = current->next;
        delete ptr;
    }

    head = NULL;
    setCurrentPersons(0);
    setTotalPricePerNight(0);
}

// Checkin
void Room::addPersonsToRoom(const int num)
{
    int i;
    if (mCurrentPersons != 0)
    {
        cout << "Room is already occupied" << endl;
        return;
    }
    if (num > mMaxPersons)
    {
        cout << "Number of people exceed the room capacity" << endl;
        return;
    }

    for (i = 0; i < num; i++)
    {
        if (!addPersonToTail())
        {
            // Clean room from people (if any)
            removeAllPersonsFromRoom();
            return;
        }
    }
}

void Room::generateVisitorsToRoom()
{
    int numOfVisitors, i;

    numOfVisitors = 1 + (rand() % mMaxPersons);
    for (i = 0; i < numOfVisitors; i++)
    {
        if (!addDummyPersonToTail())
        {
            // Clean room from people (if any)
            removeAllPersonsFromRoom();
            return;
        }
    }
}

bool Room::addDummyPersonToTail()
{
    Persons *ptr = head;
    Person *person = NULL;

    person = createDummyPerson();
    if (person == NULL)
    {
        cout << "Cannot create person, insufficient resources" << endl;
        return false;
    }

    if (head == NULL)
    {
        head = new Persons();
        if (head == NULL)
        {
            cout << "Cannot create persons list, insufficient resources" << endl;
            return false;
        }
        head->mPerson = person;
        head->next = NULL;
        setCurrentPersons(mCurrentPersons++);
        setTotalPricePerNight(mTotalPricePerNight + mPricePerNight);
        return true;
    }
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new Persons();
    if (ptr->next == NULL)
    {
        cout << "Cannot create new Persons node, insufficient resources" << endl;
        return false;
    }
    ptr->next->mPerson = person;
    ptr->next->next = NULL;
    setCurrentPersons(mCurrentPersons++);
    setTotalPricePerNight(mTotalPricePerNight + mPricePerNight);
    return true;
}
bool Room::addPersonToTail()
{
    Persons *ptr = head;
    Person *person = NULL;

    person = createPerson();
    if (person == NULL)
    {
        cout << "Cannot create person, insufficient resources" << endl;
        return false;
    }

    if (head == NULL)
    {
        head = new Persons();
        if (head == NULL)
        {
            cout << "Cannot create persons list, insufficient resources" << endl;
            return false;
        }
        head->mPerson = person;
        head->next = NULL;
        setTotalPricePerNight(mTotalPricePerNight + mPricePerNight);
        setCurrentPersons(mCurrentPersons++);
        return true;
    }
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new Persons();
    if (ptr->next == NULL)
    {
        cout << "Cannot create new Persons node, insufficient resources" << endl;
        return false;
    }
    ptr->next->mPerson = person;
    ptr->next->next = NULL;
    setCurrentPersons(mCurrentPersons++);
    setTotalPricePerNight(mTotalPricePerNight + mPricePerNight);
    return true;
}

RegularRoom::RegularRoom(const int pricePerNight, const int roomId, const bool isBalcony) : Room(pricePerNight, roomId)
{
    setIsBalcony(isBalcony);
}
void RegularRoom::setIsBalcony(const bool isBalcony)
{
    mIsBalcony = isBalcony;
}
bool RegularRoom::getIsBalcony()
{
    return mIsBalcony;
}
void RegularRoom::toString()
{
    Persons *ptr = head;
    cout << "  " << mRoomId << ") [ Type: RegularRoom, Price: " << mPricePerNight << ", Balcony?: " << mIsBalcony << ", Total revenue per night: " << mTotalPricePerNight << " ]" << endl;
    if (ptr == NULL)
    {
        cout << "Room has no guests" << endl;
    }
    else
    {
        cout << "Guests:" << endl;
        while (ptr != NULL)
        {
            ptr->mPerson->toString();
            ptr = ptr->next;
        }
    }
    cout << endl;
}

LuxuryRoom::LuxuryRoom(const int pricePerNight, const int roomId, const bool isJacuzzi) : Room(pricePerNight, roomId)
{
    setIsJacuzzi(isJacuzzi);
}
void LuxuryRoom::setIsJacuzzi(const bool isJacuzzi)
{
    mIsJacuzzi = isJacuzzi;
}
bool LuxuryRoom::getIsJacuzzi() const
{
    return mIsJacuzzi;
}
void LuxuryRoom::toString()
{
    Persons *ptr = head;
    cout << "  " << mRoomId << ") [ Type: LuxuryRoom, Price per night: " << mPricePerNight << ", Jacuzzi?: " << mIsJacuzzi << ", Total revenue per night: " << mTotalPricePerNight << " ]" << endl;
    if (ptr == NULL)
    {
        cout << "Room has no guests" << endl;
    }
    else
    {
        cout << "Guests:" << endl;
        while (ptr != NULL)
        {
            ptr->mPerson->toString();
            ptr = ptr->next;
        }
    }
    cout << endl;
}
