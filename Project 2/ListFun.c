#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Pedro Cabral IST 90767 IAED - 2 - Project*/
/* All List functions are defined here*/

/*
	List *makeList()
	Allocate memory to a list and set his atributtes to NULL.
	Return a pointer to a list struture
*/ 
List *makeList(){
	List *l = malloc(sizeof(List));
	l->head = NULL;
	l->last = NULL;
	return l;
}

/*
	void freeContact(Contact *c)
	Receive a contact,
	Free all atributtes of a contact and itself.
*/ 
void freeContact(Contact *c) {
	free(c->name);
	free(c->number);
	free(c->mail);
	free(c->domain);
	free(c);
}

/*
	void freeList(List *l)
	Receive a list,
	Use freeContact(...) function and Free all contacts on list..
	Free a list.
*/ 
void freeList(List *l) {
	while(l->head) {
		Contact *aux = l->head->next;
		freeContact(l->head);
		l->head = aux;
	}
	free(l);
}

/*
	void printList(List *l)
	Receive a list,
	Print all contacts in list using a function printContact(....).
*/
void printList(List *l) {
	Contact *p;
	for(p = l->head; p ; p = p->next) 
		printContact(p);
}

/*
	void printContact(Contact *c)
	Receive a contact,
	Print a given contact.
	Ex:
	Jaqueline jaquelina@tatataata.bala 45-52
*/
void printContact(Contact *c) {
	printf("%s %s %s\n", c->name, c->mail, c->number);
}

/*
	void removeContact(Contact *c)
	Receive a contact,
	Remove a given contact.
*/
void removeContact(List *l, Contact *c) {
	if (!c -> prev){
		l -> head = c -> next;
	}
	else {
		c -> prev -> next = c -> next;
	}
	if (!c -> next) {
		l -> last = c -> prev;
	}
	else {
		c -> next -> prev = c -> prev;
	}
	freeContact(c);
}

/*
	Contact *addContact(List *l, char *name, char *mail, char *number, char *domain)
	Receive a list, name , mail number and domain(cut from mail),
	Add to a given list.
	Return a pointer to a contact.
*/
Contact *addContact(List *l, char *name, char *mail, char *number, char *domain) {
	
	Contact *newContact = malloc(sizeof(Contact));
	/*Alocating memory for name, mail, domain and number*/
	newContact->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(newContact->name, name);
	newContact->mail = malloc(sizeof(char)*(strlen(mail)+1));
	strcpy(newContact->mail, mail);
	newContact->domain = malloc(sizeof(char)*(strlen(domain)+1));
	strcpy(newContact->domain,domain);
	newContact->number = malloc(sizeof(char)*(strlen(number)+1));	
	strcpy(newContact->number, number);

	/* If list has contacts add to the end*/
	if (l->last) {
		l-> last->next = newContact;
		newContact->prev = l->last;
		l->last = newContact;
		newContact->next = NULL;
	}
	/*if list is empty add to head*/
	if (!l->head) {
		l->head = newContact;
		l->last = newContact;
		newContact -> prev = NULL;
		newContact -> next = NULL;
	}
	return newContact;
}
/*
	void changeContact(List *l, char *name,char *text)
	Receive a list, name , mail,
	Change a given contact in list.
*/
void changeContact(List *l, char *name,char *text) {
	Contact *p = l -> head;
	for (p = l -> head; p; p = p -> next) {
		if (strcmp(p -> name,name) == 0) {
			free(p -> mail);
			free(p -> domain);
			p -> mail = malloc(sizeof(char)*(strlen(text)+1));
			p -> domain = malloc(sizeof(char)*(strlen(getMail(text))+1));
			strcpy(p -> mail, text);
			strcpy(p -> domain, getMail(text));
			return;
		}
	}
	return;
}

/*
	AUXILIAR FUNTION

	char *getMail(char *mail)
	Receive a mail,
	get domain from mail.
	Ex
			Mail  							 ->		Domain
	jaqueline@tatatatat.bala -> tatatatat.bala
*/
char *getMail(char *mail) {
	for (;*mail != '\0';mail++){
		if (*mail == 64) {
			mail++;
			break;
		}
	}
	return mail;
}


