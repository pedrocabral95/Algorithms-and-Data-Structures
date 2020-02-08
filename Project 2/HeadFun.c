#include "List.h"
#include "Hash.h"
#include "Head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Pedro Cabral IST 90767 IAED - 2 - Project*/

/* All main functions are defined here*/


/* 
	void add(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail, char *number)
	Receive hashmail, hashtable, name , number and  mail,
	Check if name exists on hash table,
	Add contacto to a double linked list.
	Add contact to hashtable
	Add mail to hashmail.
*/
void add(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail, char *number) {
	Contact *c;
	if (searchName(table,name)){
		printf("Nome existente.\n");
		return;
	}
	c = addContact(l,name,mail,number,getMail(mail));
	addHash(table,c);
	addMail(hmail,c->domain);
	return;
}
/* 
	void printAll(List *l)
	Receive a list,
	Print all contact in list.
*/
void printAll(List *l) {
	printList(l);
}

/* 
	void printfOne(Hashtable *table,char *name)
	Receive an hash and a name
	Print contact with a given name,
	Error if contact is not in hashtable.
*/
void printfOne(Hashtable *table,char *name) {
	Contact *c = searchName(table,name);
	if ( c == NULL){
		printf("Nome inexistente.\n");
		return;
	}
	else {
		printContact(c);
		return;
	}
}

/* 
	void remuve(Hashtable *table, Hashmail *hmail, List *l, char *name) {
	Receive an hashtable,a hashmail,a list  and a name
	Remove contact and mail from hashtable, hashmail and list with a given name,
	Error if contact is not in hashtable.
*/
void remuve(Hashtable *table, Hashmail *hmail, List *l, char *name) {
	Contact *c = searchName(table,name);
	if (c == NULL){
		printf("Nome inexistente.\n");
		return;
	}
	removeMail(hmail,c->domain);
	removeHash(table,name);
	removeContact(l,c);
	return;
}

/* 
	void remuve(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail) {
	Receive an hashtable,a hashmail,a list, mail  and a name
	Change contact and mail from hashtable, hashmail and list with a given name,
	Error if contact is not in hashtable.
*/
void change(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail) {
	Contact *c = searchName(table,name);
	if (c == NULL){
		printf("Nome inexistente.\n");
		return;
	}
	removeMail(hmail,c->domain);
	changeContact(l,name,mail);
	changeMail(table,name,mail);
	addMail(hmail,getMail(mail));
	return;
}

/* 
	void printMail(Hashmail *hmail,char *mail)
	Receive an hashmail and a mail
	Print a given mail frequency on hashmail.
*/
void printMail(Hashmail *hmail,char *mail){
	printf("%s:%d\n",mail,mailOcur(hmail,mail));
}