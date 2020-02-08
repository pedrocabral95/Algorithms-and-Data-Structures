#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "headerproj.h"
#include <string.h>
#include <time.h>
/*

	File : shows.c
	Author : Pedro Cabral
	Description: In this file are all functions to show all events and all rooms 

*/

void showAllEvents() {
	int ievent, guest, lim, nEvents;
	toPrinte();
	nEvents = events.nEvents;
	for (ievent = 0 ; ievent < nEvents; ievent++) {
		printf("%s %s %s %s Sala%d %s\n*", events.events[ievent].name,events.events[ievent].date,events.events[ievent].begin,events.events[ievent].duration,events.events[ievent].room,events.events[ievent].coordinator.name);
		guest = 0;
		lim = events.events[ievent].numOfGuests;
		while(guest < lim) {
			printf(" %s",events.events[ievent].guestList[guest].name);
			guest++;
		}
		printf("\n");
	}
}

void showAllRoomEvents(char *info) {
	int lim,guest,room;
	unsigned int nEvents, ievent;
	asort(info);
	room = atoi(info);
	nEvents = rooms[room].numEvents;
	for (ievent = 0 ; ievent < nEvents; ievent++) {
			printf("%s %s %s %s Sala%d %s\n*", rooms[room].events[ievent].name,rooms[room].events[ievent].date,rooms[room].events[ievent].begin,rooms[room].events[ievent].duration,rooms[room].events[ievent].room,rooms[room].events[ievent].coordinator.name);
			guest = 0;
			lim =rooms[room].events[ievent].numOfGuests;
			while(guest < lim) {
				printf(" %s", rooms[room].events[ievent].guestList[guest].name);
				guest++;
			}
			printf("\n");
			}
	return;
}
