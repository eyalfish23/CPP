#include "Hotel.h"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    // Initial data
    int i;
    Hotel *hotel = NULL;
    hotel = new Hotel("Meridian", 4, 20);
    for (i = 0; i < 6; i++)
    {
        Room *room = hotel->generateRoom();
        if (room != NULL)
        {
            room->generateVisitorsToRoom();
        }
    }
    hotel->toString();
    hotel->removeRoomById(2);
    hotel->removeRoomById(1);
    hotel->toString();
    delete hotel;
    return 0;
}