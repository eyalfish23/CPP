#include "Hotel.h"
#include <unistd.h> /* Symbolic Constants (fork,sleep)*/ 

using namespace std;

const int SLEEP_TIME_INTERVAL=6;

void *registraion_simulation(void *unused);
Hotel *init_params(int numOfRooms,string hotelName,int stars,int maxRooms);
void menu();

/*************  Globals   *****************/
Hotel *hotel = NULL;
bool isExit=false;
pthread_mutex_t mutex;

int main()
{
    srand((unsigned)time(NULL));
    pthread_t thread_id;

    hotel=init_params(3,"Meridian",4,20);
    if(hotel==NULL)
    {
      return -1;
    }
    
    //Init mutex for protecting race conditions, and sync data between all threads
    if(pthread_mutex_init(&mutex,NULL)!=0)
    {
      cout<<"Mutex initialization err"<<endl;
      delete hotel;
      return -1;
    }

    if(pthread_create(&thread_id,NULL,&registraion_simulation,NULL)!=0)
    {
        cout<<"registraion_simulation thread err"<<endl;
        delete hotel;
        return -1;
    }

    menu();
    //Wait for threads to finish before closing program and release resources
    pthread_join(thread_id,NULL);

    //Resources release
    delete hotel;
    
    return 0;
}

Hotel *init_params(int numOfRooms,string hotelName,int stars,int maxRooms)
{
    int i;
    Hotel *hotel = NULL;

    hotel = new Hotel(hotelName, stars, maxRooms);
    for (i = 0; i < numOfRooms; i++)
    {
        Room *room = hotel->generateRoom();
    }

    return hotel;
}

void menu()
{
  int res;
  do
  {
    cout<<"---------- Menu ----------"<<endl;
    cout<<"Type 1: Show all rooms"<<endl;
    cout<<"Type 0: Exit"<<endl;

    cin>>res;
    pthread_mutex_lock(&mutex);
    if(res==0)
    {
      isExit=true;
    }else if(res==1)
    {
      hotel->toString();
    }
    pthread_mutex_unlock(&mutex);
  } while (!isExit);
  cout<<"Exit menu"<<endl;
  
}

void *registraion_simulation(void *unused)
{
    Room *room=NULL;
    
    while(!isExit)
    {
      pthread_mutex_lock(&mutex);
      room=NULL;
      room=hotel->getEmptyRoom();
      if(room!=NULL)
      {
        room->generateVisitorsToRoom();
      }
      pthread_mutex_unlock(&mutex);

      sleep(SLEEP_TIME_INTERVAL);
    }

    cout<<"Exit registraion_simulation"<<endl;
    return NULL;
}
