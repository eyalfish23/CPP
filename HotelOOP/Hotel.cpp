#include "./Hotel.h"
using namespace std;

Hotel::Hotel(const string name, const int stars, const int maxRooms)
{
    setName(name);
    setStars(stars);
    currentRooms = 0;
    setMaxRooms(maxRooms);
    setRegularRoomBasePricePerNight(DEFAULT_REGULAR_ROOM_BASE_PRICE_PER_NIGHT);
    setLuxuryRoomBasePricePerNight(DEFAULT_LUXURY_ROOM_BASE_PRICE_PER_NIGHT);
}

Hotel::Hotel(const string name, const int stars)
{
    setName(name);
    setStars(stars);
    currentRooms = 0;
    setMaxRooms(DEFAULT_MAX_ROOMS);
    setRegularRoomBasePricePerNight(DEFAULT_REGULAR_ROOM_BASE_PRICE_PER_NIGHT);
    setLuxuryRoomBasePricePerNight(DEFAULT_LUXURY_ROOM_BASE_PRICE_PER_NIGHT);
}

Hotel::Hotel(const string name, const int stars, const int maxRooms, const int regularRoomBasePricePerNight, const int luxuryRoomBasePricePerNight)
{
    setName(name);
    setStars(stars);
    currentRooms = 0;
    setMaxRooms(maxRooms);
    setRegularRoomBasePricePerNight(regularRoomBasePricePerNight);
    setLuxuryRoomBasePricePerNight(luxuryRoomBasePricePerNight);
}

Hotel::~Hotel()
{
    struct Rooms *current = head;
    struct Rooms *ptr = current;

    while (current != NULL)
    {
        ptr = current;
        current = current->next;
        delete ptr->mRoom;
        delete ptr;
    }

    head = NULL;
    currentRooms = 0;
    cout << "~Hotel()" << endl;
}

void Hotel::setName(const string name)
{
    mName = name;
}

string Hotel::getName() const
{
    return mName;
}

void Hotel::setStars(const int stars)
{
    if (stars < MIN_STARS)
    {
        mStars = MIN_STARS;
    }
    else if (stars > MAX_STARS)
    {
        mStars = MAX_STARS;
    }
    else
    {
        mStars = stars;
    }
}

int Hotel::getStars() const
{
    return mStars;
}

void Hotel::setMaxRooms(const int maxRooms)
{
    if (maxRooms < 0)
    {
        mMaxRooms = DEFAULT_MAX_ROOMS;
    }
    else
    {
        mMaxRooms = maxRooms;
    }
}

int Hotel::getMaxRooms() const
{
    return mMaxRooms;
}

void Hotel::toString()
{
    Rooms *ptr = head;
    cout << "\nHotel: " << mName << endl;
    cout << "Rating: " << mStars << endl;
    if (ptr != NULL)
    {
        cout << "Rooms:" << endl;
        while (ptr != NULL)
        {
            ptr->mRoom->toString();
            ptr = ptr->next;
        }
    }
    else
    {
        cout << "This hotel does not have any rooms" << endl;
    }
    cout << "----------------------------------------------------------------------" << endl;
    cout << endl;
}

void Hotel::setRegularRoomBasePricePerNight(const int regularRoomBasePricePerNight)
{
    mRegularRoomBasePricePerNight = regularRoomBasePricePerNight;
}

int Hotel::getRegularRoomBasePricePerNight() const
{
    return mRegularRoomBasePricePerNight;
}

void Hotel::setLuxuryRoomBasePricePerNight(const int luxuryRoomBasePricePerNight)
{
    mLuxuryRoomBasePricePerNight = luxuryRoomBasePricePerNight;
}

int Hotel::getLuxuryRoomBasePricePerNight() const
{
    return mLuxuryRoomBasePricePerNight;
}

Room *Hotel::makeRegularRoom(const int pricePerNight, const bool isBalcony, const int roomId)
{
    Room *room = NULL;
    room = new RegularRoom(pricePerNight, roomId, isBalcony);
    return room;
}

Room *Hotel::makeLuxuryRoom(const int pricePerNight, const bool isJacuzzi, const int roomId)
{
    Room *room = NULL;
    room = new LuxuryRoom(pricePerNight, roomId, isJacuzzi);
    return room;
}

void Hotel::addNodeToTail(Room *room)
{
    Rooms *ptr = head;
    if (head == NULL)
    {
        head = new Rooms();
        if (head == NULL)
        {
            cout << "Cannot create head, insufficient resources" << endl;
            return;
        }
        head->mRoom = room;
        head->next = NULL;
        return;
    }

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new Rooms();
    if (ptr->next == NULL)
    {
        cout << "Cannot create new Rooms node, insufficient resources" << endl;
        return;
    }
    ptr->next->mRoom = room;
    ptr->next->next = NULL;
}

bool Hotel::isRoomLeft() const
{
    if (currentRooms <= mMaxRooms)
    {
        return true;
    }
    return false;
}

Room *Hotel::generateRoom()
{
    int roomType, isBalcony, isJacuzzi;
    Room *room = NULL;
    roomType = rand() % 2;

    if (!isRoomLeft())
    {
        cout << "No available room" << endl;
        return NULL;
    }

    if (roomType == 0)
    {
        isBalcony = rand() % 2;
        if (isBalcony == 0)
        {
            room = makeRegularRoom(mRegularRoomBasePricePerNight, false, (currentRooms + 1));
        }
        else
        {
            room = makeRegularRoom(mRegularRoomBasePricePerNight + 50, true, (currentRooms + 1));
        }
    }
    else
    {
        isJacuzzi = rand() % 2;
        if (isJacuzzi == 0)
        {
            room = makeLuxuryRoom(mLuxuryRoomBasePricePerNight, false, (currentRooms + 1));
        }
        else
        {
            room = makeLuxuryRoom(mLuxuryRoomBasePricePerNight + 60, true, (currentRooms + 1));
        }
    }
    if (room == NULL)
    {
        cout << "Cannot create room. Insufficient resources" << endl;
        return NULL;
    }
    currentRooms++;
    addNodeToTail(room);
    return room;
}
void Hotel::addRoom()
{
    int roomType;
    Room *room = NULL;

    if (!isRoomLeft())
    {
        cout << "No available room" << endl;
        return;
    }

    cout << "Choose room type" << endl;
    cout << "0)Regular room" << endl;
    cout << "1)Luxury room" << endl;
    cin >> roomType;

    if ((roomType != 0) && (roomType != 1))
    {
        cout << "Invalid option, " << roomType << endl;
    }
    else
    {
        if (roomType == 0)
        {
            char isBalcony;
            cout << "Do you want a room with a balcony? (Y/N)" << endl;
            cin >> isBalcony;
            if (isBalcony == 'y' || isBalcony == 'Y')
            {
                room = makeRegularRoom(mRegularRoomBasePricePerNight + 50, true, (currentRooms + 1));
            }
            else
            {
                room = makeRegularRoom(mRegularRoomBasePricePerNight, false, (currentRooms + 1));
            }
        }
        else
        {
            char isJacuzzi;
            cout << "Do you want a room with a jacuzzi? (Y/N)" << endl;
            cin >> isJacuzzi;
            if (isJacuzzi == 'y' || isJacuzzi == 'Y')
            {
                room = makeLuxuryRoom(mLuxuryRoomBasePricePerNight + 60, true, (currentRooms + 1));
            }
            else
            {
                room = makeLuxuryRoom(mLuxuryRoomBasePricePerNight, false, (currentRooms + 1));
            }
        }
        if (room == NULL)
        {
            cout << "Cannot create room. Insufficient resources" << endl;
            return;
        }
        currentRooms++;
        addNodeToTail(room);
    }
}

void Hotel::removeRoomById(const int id)
{
    Rooms *ptr = head;
    Rooms *current = ptr->next;
    if (head == NULL)
    {
        cout << "Hotel has currently no rooms" << endl;
        return;
    }

    if (head->mRoom->getRoomId() == id)
    {
        head = current;
        delete ptr->mRoom;
        delete ptr;
        cout << "Room number: " << id << " successfully deleted from head" << endl;
        currentRooms--;
        return;
    }

    while (current != NULL)
    {
        if (current->mRoom->getRoomId() == id)
        {
            ptr->next = current->next;
            delete current->mRoom;
            delete current;
            cout << "Room number: " << id << " successfully deleted" << endl;
            currentRooms--;
            return;
        }
        current = current->next;
        ptr = ptr->next;
    }
    cout << "Room number: " << id << " has not been found" << endl;
}

Room *Hotel::getEmptyRoom()
{
    Rooms *ptr = head;

    if (!isRoomLeft())
    {
        //Not available room
        return NULL;
    }

    while(ptr!=NULL)
    {
        if(ptr->mRoom->getCurrentPersons()==0)
        {
            return ptr->mRoom;
        }
        ptr=ptr->next;
    }

    //All rooms are occupied
    return NULL;
}