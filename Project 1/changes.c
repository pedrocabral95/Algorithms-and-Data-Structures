#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "headerproj.h"
#include <string.h>
#include <math.h>
#include <time.h>
/* 

	File : gets.c
	Author : Pedro Cabral
	Description: In this file are all necessaire function to change any paramtres 

*/

/* Change the begin Hour given event
*	Input: i Reuniao dos Pedros:0930
* Output : None 
*	Previous: Reuniao dos Pedros:0945
* Now: Reuniao dos Pedros:0930
*/
void changeTime(char *desc, char *time, int n) {
	int iroom, ievent, imate ,nEvents, nGuests ,iter, room = 0, iGuest ,ret = 0;
	Inp dados[10];
	Data newDate, eDay;


	if (!isEvent(desc)){
		printf("Evento %s inexistente.\n", desc);
		return;
	}
	/*Recolha de dados*/
	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
		for (ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) {
				ret = 1;
				room = iroom;
				
				strcpy(dados[1].dados,rooms[iroom].events[ievent].name);
				strcpy(dados[2].dados,rooms[iroom].events[ievent].date);
				strcpy(dados[5].dados,rooms[iroom].events[nEvents].cRoom);
				strcpy(dados[6].dados,rooms[iroom].events[ievent].coordinator.name);
				iter = 0;
				iGuest = rooms[iroom].events[ievent].numOfGuests;
				while ( iter < iGuest) {
					strcpy(dados[7 + iter].dados,rooms[iroom].events[ievent].guestList[iter].name);
					iter++;
				}

				if (n == 1) {
					newDate = addDate(newDate,rooms[iroom].events[ievent].date,time,rooms[iroom].events[ievent].duration);
					strcpy(dados[3].dados,time);
					strcpy(dados[4].dados,rooms[iroom].events[ievent].duration);

					break;
				}
				if (n == 2) {
					newDate = addDate(newDate,rooms[iroom].events[ievent].date,rooms[iroom].events[ievent].begin,time);
					strcpy(dados[3].dados,rooms[iroom].events[ievent].begin);
					strcpy(dados[4].dados,time);
					break;
				}		
			}
		}
	}

	nEvents = rooms[room].numEvents;
	for (ievent = 0 ; ievent < nEvents ; ievent++) {
		if (strcmp(rooms[room].events[ievent].name, desc)) {
			eDay = rooms[room].events[ievent].day;
			if (compareDate(newDate,eDay)) {
				printf("Impossivel agendar evento %s. Sala%d ocupada.\n", desc, room);
				return;
			}
		}
	}	

	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		
		nEvents = rooms[iroom].numEvents;

		for (ievent = 0 ; ievent < nEvents; ievent++) {

			if (strcmp(rooms[iroom].events[ievent].name, desc)){

				nGuests =  rooms[iroom].events[ievent].numOfGuests;
				eDay = rooms[iroom].events[ievent].day;

				for (iGuest = 0 ; iGuest < 3 ; iGuest++) {
					for (imate = 0 ; imate < nGuests ; imate++) {
						if (compareDate(newDate,eDay) && (strcmp(rooms[iroom].events[ievent].guestList[imate].name,dados[iGuest].dados) == 0 || strcmp(rooms[iroom].events[ievent].coordinator.name,dados[iGuest].dados) == 0 )) {
								printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", desc, dados[iGuest].dados);
								ret = 0;
								break;
						}
					}
				}
			}
		}
	}
	if (ret){

		removeEvent(desc);
		addEvent(dados);					
	}
	return;
}

void changeRoom(char *desc, char *room) {
	int iroom, ievent,nEvents,iter, roome,iGuest,can = 0;
	Inp dados[10];
	Data newDate;

	if (!isEvent(desc)){
		printf("Evento %s inexistente.\n", desc);
		return;
	}
	/*Recolha de dados*/
	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
		for (ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) {
				strcpy(dados[1].dados,rooms[iroom].events[ievent].name);
				strcpy(dados[2].dados,rooms[iroom].events[ievent].date);
				strcpy(dados[3].dados,rooms[iroom].events[ievent].begin);
				strcpy(dados[4].dados,rooms[iroom].events[ievent].duration);
				strcpy(dados[5].dados,room);
				strcpy(dados[6].dados,rooms[iroom].events[ievent].coordinator.name);
				iter = 0;
				iGuest = rooms[iroom].events[ievent].numOfGuests;
				while ( iter < iGuest) {
					strcpy(dados[7 + iter].dados,rooms[iroom].events[ievent].guestList[iter].name);
					iter++;
				}
				can = 1;
				break;
			}
			
		}
	}

	/*Create a Date */
	newDate = addDate(newDate,dados[2].dados,dados[3].dados,dados[4].dados);
	roome = atoi(room);
	if (isRoomOcupped(rooms[roome],newDate)) {
		printf("Impossivel agendar evento %s. Sala%d ocupada.\n",dados[1].dados, roome);
		return;
	} 
	if (can) {
		removeEvent(desc);
		addEvent(dados);
	}
	return;
}

void changeEtp(char *desc, Event event) {
	unsigned int nEvents,ievent;

	nEvents = events.nEvents;

	for (ievent = 0 ; ievent < nEvents ; ievent++) {
		if (strcmp(events.events[ievent].name,desc) ==0) {
			events.events[ievent] = event;
		}
	}
	return;
}