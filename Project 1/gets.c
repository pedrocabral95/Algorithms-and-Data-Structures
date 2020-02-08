#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "headerproj.h"
#include <string.h>
#include <time.h>

void cmds() {
	int iter, _input,len;
	Inp strings[10];
	char *input,*nC;

	/* Alloced memory for input*/
	input = (char*)malloc(sizeof(char)*4000000000);

	do {
		for (iter = 0 ; iter < 10 ; iter++) {
			strcpy(strings[iter].dados,"\0");

		}
		fgets(input,MAXINPUT,stdin);

		iter = 0;

		nC = strtok(input," :");
		len = (int)strlen(nC);

		while (nC != NULL && len > 0 ) {
				if (nC[0] == '\0')
					break;
			strcpy(strings[iter++].dados,nC);
			nC = strtok(NULL,":\n");
		}

		_input = (int) strings[0].dados[0];
		switch(_input) {
			case 'a':addEvent(strings);break;
			case 'l':showAllEvents();break;
			case 's':showAllRoomEvents(strings[1].dados);	break;
			case 'r':removeEvent(strings[1].dados);break;
			case 'i':changeTime(strings[1].dados,strings[2].dados,1);break;
			case 't':changeTime(strings[1].dados,strings[2].dados,2);break;
			case 'm':changeRoom(strings[1].dados,strings[2].dados);break;
			case 'A':addGuest(strings[1].dados,strings[2].dados);break;
			case 'R':removeGuest(strings[1].dados,strings[2].dados);break;
			case 'x':return;
		}
	} while (_input != EOF);
	
	free(input);
	return;
	
}

int power(int a, int b) {
		int result = 1;
    while (b != 0){
      result *= a;
      --b;
    }
    return result;
}
int calculateDuration(char *start) {
	int sum = 0, h = 0, m = 0, iter, lim;
	iter = 0;
	lim = 2;
	while ( iter < lim) {
		h += (start[iter] - '0') * power(10, lim - iter-1);
		iter++;
	}
	lim =4;
	while(iter < lim ) {
		m += (start[iter] - '0') * power(10, lim - iter-1);
		iter++;
	}
	sum = (h *60) + m; 
	
	return sum;
}

Data addDate(Data day, char *date, char *inicio, char *duration) {
	struct tm tm;
	unsigned int toOrder = 0;
	strptime(date,"%d%m%Y", &tm);
	strptime(inicio,"%H%M", &tm);

	day.year = (unsigned int) tm.tm_year;
	day.month = (unsigned int) tm.tm_mon;
	day.day = (unsigned int) tm.tm_mday;
	
	day.begin = (int) calculateDuration(inicio);
	day.end = (int) (day.begin + atoi(duration));
	toOrder = day.year + day.month + day.day + day.begin;
	day.order = (unsigned int) toOrder;

	return day;

}

/* Output 1 - Livre
	Output 0 - Ocupado
	d2 - a inserir
	d1 - ja la esta
	*/


int compareDate(Data d1,Data d2) {
	if (isEqual(d1,d2) && d1.begin < d2.end && d2.begin < d1.end) {
		return 1;
	}
	return 0;
}

int compare(Data d1,Data d2) { 
   
    if (d1.year < d2.year) 
      return 1; 
    if (d1.year == d2.year && d1.month < d2.month) 
      return 1; 
    if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day) 
      return 1; 
    if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.begin < d2.begin)
     	return 1;
    return 0; 
} 
/* Room ocupped = 1 */
int isRoomOcupped(Room room,Data d2) { 
	int ievent;
	int nEvents;
	
		nEvents = room.numEvents;
		for (ievent = 0 ; ievent < nEvents ; ievent++) {
			if (compareDate(room.events[ievent].day,d2))
				return 1;
		}
	return 0;
}
/* Event exists = 1 */
int isEvent(char *desc) {

	int iroom, ievent, nEvents;

	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
		for (ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name,desc) == 0) { /* Compare if the event exist */
				return 1;
			}
		}
	}
	return 0;
}

/* Guest Ocupped = 1 */
int isGuestOcupped(char *guest, Data day) {	
	int iroom,ievent,imate ,nEvents, nEle;
	Data eDay;

	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		
		nEvents = rooms[iroom].numEvents;

		for (ievent = 0 ; ievent < nEvents; ievent++){
			nEle =  rooms[iroom].events[ievent].numOfGuests;
			eDay = rooms[iroom].events[ievent].day;
			if (strcmp(rooms[iroom].events[ievent].coordinator.name,guest) == 0){
					if (compareDate(eDay,day))
						return 1;
					return 0;
				}
			for (imate = 0 ; imate < nEle ; imate++) {
				if (strcmp(rooms[iroom].events[ievent].guestList[imate].name,guest) == 0) {
					if (compareDate(eDay,day))
						return 1;
					return 0;
				}
			}
		}
	}
	return 0;
}

/* AmITher if guest belong at event desc = 1*/

int AmIHere(char *desc, char *guest) {
	int iroom, ievent,nEle, nEvents, imate;

	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		
		nEvents = rooms[iroom].numEvents;

		for (ievent = 0 ; ievent < nEvents; ievent++){
		
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) {
			
				nEle =  rooms[iroom].events[ievent].numOfGuests;

				if (strcmp(rooms[iroom].events[ievent].coordinator.name,guest) == 0)
					return 1;
				
				for (imate = 0 ; imate < nEle ; imate++) {

					if (strcmp(rooms[iroom].events[ievent].guestList[imate].name,guest) == 0)
						return 1;
				}
			}
		}
	}
	return 0;
}

int isEqual(Data d1, Data d2) {
	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year )
		return 1;
	return 0;
}

