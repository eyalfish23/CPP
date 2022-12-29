#ifndef HOTEL_H
#define HOTEL_H
#include "./Room.h"
#include <cstdlib>
using namespace std;

const int MIN_STARS = 3;
const int MAX_STARS = 5;
const int DEFAULT_REGULAR_ROOM_BASE_PRICE_PER_NIGHT = 100;
const int DEFAULT_LUXURY_ROOM_BASE_PRICE_PER_NIGHT = 160;
const int DEFAULT_MAX_ROOMS = 20;

class Hotel
{
private:
    struct Rooms
    {
        Room *mRoom;
        struct Rooms *next;
    };
    string mName;
    int mStars;
    int currentRooms;
    int mMaxRooms;
    int mRegularRoomBasePricePerNight;
    int mLuxuryRoomBasePricePerNight;
    struct Rooms *head = NULL;

public:
    Hotel(const string name, const int stars);
    Hotel(const string name, const int stars, const int maxRooms);
    Hotel(const string name, const int stars, const int maxRooms, const int regularRoomBasePricePerNight, const int luxuryRoomBasePricePerNight);
    ~Hotel();
    void setName(const string name);
    string getName() const;
    void setStars(const int stars);
    int getStars() const;
    void setMaxRooms(const int maxRooms);
    int getMaxRooms() const;
    void toString();
    Room *generateRoom();
    void addRoom();
    void setRegularRoomBasePricePerNight(const int regularRoomBasePricePerNight);
    int getRegularRoomBasePricePerNight() const;
    void setLuxuryRoomBasePricePerNight(const int luxuryRoomBasePricePerNight);
    int getLuxuryRoomBasePricePerNight() const;
    void removeRoomById(const int id);
    Room *getEmptyRoom();

private:
    Room *makeRegularRoom(const int pricePerNight, const bool isBalcony, const int roomId);
    Room *makeLuxuryRoom(const int pricePerNight, const bool isJacuzzi, const int roomId);
    void addNodeToTail(Room *room);
    bool isRoomLeft() const;
};

#endif