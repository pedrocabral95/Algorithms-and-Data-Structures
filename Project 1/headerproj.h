#define _GNU_SOURCE
#ifndef headerproj
#define MAXNAME 640
#define	MAXGUESTS 192
#define MAXROOM 11
#define MAXEVENTS 100
#define MAXINPUT 4500
#define MAXE 1001


typedef struct Inp {
	char dados[MAXNAME];
} Inp;

typedef struct Data {
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int begin;
	unsigned int end;
	unsigned int order;
} Data;
typedef struct Guest {
	char name[MAXNAME];
} Guest;

typedef struct Event {
	char name[MAXNAME];
	Data day;
	char date[MAXINPUT];
	char begin[MAXINPUT];
	int room;
	char cRoom[4];
	char duration[MAXINPUT];
	Guest coordinator;
	Guest guestList[3];
	unsigned int numOfGuests;
} Event;

typedef struct toPrint {
	Event events[MAXE];
	unsigned int nEvents;
} toPrint;

typedef struct Room {
	Event events[MAXEVENTS];
	unsigned int numEvents;
} Room;

#endif

Room rooms[MAXROOM];
toPrint events;

void cmds();
void addEvent(Inp strings[10]);
void showAllEvents(); 
void showAllRoomEvents(char *info);
void removeEvent(char *info);
void changeTime(char *info, char *time, int n);
void changeRoom(char *desc, char *room);
void addGuest(char *desc, char *guest);
void removeGuest(char *info, char *info1);

/* Auxiliar funtions */
int calculateDuration(char *start);
int power(int x, int y);
Data addDate(Data day, char *date, char *incio, char *duration);
int isRoomOcupped(Room room,Data d1);
int compareDate(Data d2,Data d1);
int isEvent(char *desc);
int isGuestOcupped(char *guest, Data day);
void addList(char *guest, Data day);
int AmIHere(char *desc, char *guest);
void removeDate(Room room , Data date);
int isEqual(Data d1, Data d2);
void changeEtp(char *desc, Event event);
void toPrinte();
void removeEventToPrint(char *desc);
int compare(Data d1, Data d2);
void asort(char *info);

