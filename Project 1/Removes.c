#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "headerproj.h"
#include <string.h>
#include <time.h>

void removeEvent(char *desc) {
	int iroom, ievent, nEvents, can = 0;

	if (!isEvent(desc)) {
		printf("Evento %s inexistente.\n", desc);
		return;
	}

	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
		for ( ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) { /* Compare if the event exists, and remove*/

				while(ievent < nEvents) {
					rooms[iroom].events[ievent] = rooms[iroom].events[ievent+1];
					ievent++;
					can = 1;
				}
				rooms[iroom].numEvents--;
				
			}
		}
	}	
	if (can) {
		removeEventToPrint(desc);
	}	
}

void removeGuest(char *desc, char *guest) {
	int iroom, ievent,nEle, nEvents, imate = 0,can = 0;
	Event ev;
	if (!isEvent(desc)) {
		printf("Evento %s inexistente.\n", desc);
		return;
	}

	for ( iroom = 0 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
	
		for (ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) { /* Compare if the event exists, and remove*/

				nEle =  rooms[iroom].events[ievent].numOfGuests;
				if (nEle == 1 && strcmp(rooms[iroom].events[ievent].guestList[imate].name,guest) == 0) {
					printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", guest, desc);
					return;
				}
				for (imate = 0; imate < nEle; imate++) {
					if (strcmp(rooms[iroom].events[ievent].guestList[imate].name,guest) == 0){
						
						while(imate < nEle) {
							rooms[iroom].events[ievent].guestList[imate] = rooms[iroom].events[ievent].guestList[imate + 1];/*segmentation*/
							
							imate++;
						} 
						rooms[iroom].events[ievent].numOfGuests--;
						can = 1;
						ev = rooms[iroom].events[ievent];
					}
					}
				}
		}
	}
	if (can){
		changeEtp(desc,ev);
	}
	return ;
}

void removeEventToPrint(char *desc){
	unsigned int ievent, nEvents;
	nEvents = events.nEvents;
	for ( ievent = 0 ; ievent < nEvents; ievent++){
		if (strcmp(events.events[ievent].name, desc) == 0) { /* Compare if the event exists, and remove*/
	
			while(ievent < nEvents) {
				events.events[ievent] = events.events[ievent+1];
				ievent++;
				}
				events.nEvents--;
		}
	}
}
