#define GNUSOURCE

#include <stdio.h>
#include <stdlib.h>
#include "headerproj.h"
#include <string.h>
#include <time.h>

/* 

	File : gets.c
	Author : Pedro Cabral
	Description: In this file are all necessaire function to change any paramtres 

*/

/* Add a given event to a room!
*	Input: a Reuniao dos Pedros:09022019:1000:30:2:Jaime: Jaime Gama: Jaima Nao Gama: Jaime foi dentro
* Output : None 
*/
void addEvent(Inp info[10]) {
	int imate,nEvents,iter, room,ret = 1,len;
	Data newDate;
	/* serve para ver se na sala x existe algum evento aquela hora e dia*/
	room = atoi(info[5].dados); 
	
	/*Create a Date */
	newDate = addDate(newDate,info[2].dados,info[3].dados,info[4].dados);

	nEvents = rooms[room].numEvents;
	if ( nEvents == MAXEVENTS)
		return;
	if (isRoomOcupped(rooms[room],newDate)) {
		printf("Impossivel agendar evento %s. Sala%d ocupada.\n", info[1].dados, room);
		ret = 0;
	} 
	for (imate = 6 ; imate < 10 ; imate++) {
		if (isGuestOcupped(info[imate].dados,newDate)){
			printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", info[1].dados, info[imate].dados);
			ret = 0;
		}								
	}
	
	if (ret) {
		
		nEvents = rooms[room].numEvents;

		strcpy(rooms[room].events[nEvents].name, info[1].dados);	
		strcpy(rooms[room].events[nEvents].date, info[2].dados);
		strcpy(rooms[room].events[nEvents].begin, info[3].dados);
		strcpy(rooms[room].events[nEvents].duration, info[4].dados);
		strcpy(rooms[room].events[nEvents].cRoom, info[5].dados);
		rooms[room].events[nEvents].day = newDate;
		rooms[room].events[nEvents].day.order += room;
		rooms[room].events[nEvents].room = room;
		strcpy(rooms[room].events[nEvents].coordinator.name, info[6].dados);

		/* Adicionar participantes*/
		iter = 0;		
		len = strlen(info[7+iter].dados);
		while (strcmp(info[7+iter].dados,"\0") && strcmp(info[7+iter].dados," ") && strcmp(info[7+iter].dados,"\n") && len > 1 &&  iter < 3){
			strcpy(rooms[room].events[nEvents].guestList[iter].name, info[7+iter].dados);
			iter++;
		}
		rooms[room].events[nEvents].numOfGuests = iter;
		rooms[room].numEvents = nEvents + 1;
		iter = events.nEvents;
		events.events[iter++] = rooms[room].events[nEvents];
		return;	
	}
return;
}

/* Add a guest to a given event!
*	Input: A Reuniao dos Pedros:Jaime Gamou
* Output : None 
* Errors : 
*/
void addGuest(char *desc, char *guest) {
	int iroom, ievent, nEvents,nGuests;
	Data day;
	/* Ver se o evento existe*/
	if (!isEvent(desc)){
		printf("Evento %s inexistente.\n", desc);
		return;
	}

	/* se existir sacar o dia, horas*/
	
	for ( iroom = 1 ; iroom < MAXROOM ; iroom++ ) {
		nEvents = rooms[iroom].numEvents;
		for (ievent = 0 ; ievent < nEvents; ievent++){
			if (strcmp(rooms[iroom].events[ievent].name, desc) == 0) {
				nGuests = rooms[iroom].events[ievent].numOfGuests;

				if (AmIHere(desc,guest)) {
					/*Ignore*/
					return;
				}
				
				day = rooms[iroom].events[ievent].day;
				if (isGuestOcupped(guest,day)) {
					printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", desc, guest);
					break;
				}
				if (nGuests == 3) {
					printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n", desc);
					break;
				}
				else {
					/*add*/
					strcpy(rooms[iroom].events[nEvents].guestList[nGuests].name, guest);
					rooms[iroom].events[ievent].numOfGuests++;
					changeEtp(desc,rooms[iroom].events[ievent]);
				}
			}
		}
	}
	return;
}

void toPrinte(){
	int aux;
	unsigned int ievent, nEvents;
	Event key;
	Data day;

	nEvents = events.nEvents;
	for (ievent = 1 ; ievent < nEvents ; ievent++) {
		key = events.events[ievent];
		day = events.events[ievent].day;
		aux = ievent-1;			
		while (compare(day,events.events[aux].day) && aux >= 0){
			events.events[aux +1] = events.events[aux];
			aux--;
		}
		events.events[aux +1] = key;
	}
}

void asort(char *info){
	int aux,room;
	unsigned int ievent, nEvents;
	Event key;
	Data day;
	room = atoi(info);
	nEvents = rooms[room].numEvents;
	for (ievent = 1 ; ievent < nEvents ; ievent++) {
		key = rooms[room].events[ievent];
		day = rooms[room].events[ievent].day;
		aux = ievent-1;			
		while (compare(day,rooms[room].events[aux].day) && aux >= 0){
			rooms[room].events[aux +1] = rooms[room].events[aux];
			aux--;
		}
		rooms[room].events[aux +1] = key;
	}

}

