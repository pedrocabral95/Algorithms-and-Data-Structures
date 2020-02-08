#include "List.h"
#include "Hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Pedro Cabral IST 90767 IAED - 2 - Project*/


/* 
	int getHash(char *name, int size) 
	Receive a name and size,
	get HashCode
	return an int with hashcode
*/
int getHash(char *name, int size) {
	int h , a = 31415, b = 27183 ;
	for (h = 0; *name != '\0' ; name++, a = a*b % (size-1)) {
		h = ( a*h + *name) % size;
	}
	return h;
}
/*
	int loadHash(int a, int b)
	Receive a number of elements (a) and hash size(b),
	Calculate the load factor,
	Return 1 - Loaded
	Return 0 - Not Loaded
*/
int loadHash(int a, int b) {
	if ((a/b) >= 0.45) {
		return 1;
	}
	return 0;
}

/* 
	Hashmail *reMail(Hashmail *hash)
	Receive an hashmail,
	Allocate new size for hashmail and copy previous mails
	Return a pointer to hash struture.
*/
Hashmail *reMail(Hashmail *hash) {
	Hashmail *prev,*new;
	int iter, newSize;
	prev = hash;
	newSize = prev->size * 3;
	new = makeMail(newSize);

	for (iter = 0 ; iter < prev->size ; iter++) {
		addMail(new,prev->mail[iter]->mail);
	}
	freeMail(prev);
	return new;
}

/* 
	Hashtable *reTable(Hashtable *hash)
	Receive an hashtable,
	Allocate new size for hashtable and copy previous contacts
	Return a pointer to hash struture.
*/
Hashtable *reTable(Hashtable *hash) {
	Hashtable *prev,*new;
	int iter, newSize;
	prev = hash;
	newSize = prev->size * 3;
	new = makeHash(newSize);
	for (iter = 0 ; iter < prev->size ; iter++) {
		addHash(new,prev->Contacts[iter]);
	}
	freeHash(prev);
	return new;
}

/* 
	Hashtable *makeHash(int k)
	Receive an int k,
	Allocate k contacts and an hashtable,
	Set all contacts to NULL, and number of Elements to 0,
	Return a pointer to hash struture.
*/
Hashtable *makeHash(int k){
	int iter;

	/*Allocates an Hashtable*/
	Hashtable *hash = malloc(sizeof(Hashtable));

	hash->size = k;
	/*Allocates a list inside a hashtable with PRIME - 1 contacts*/
	hash->Contacts = malloc(sizeof(Contact)*hash->size);
		
	for (iter = 0 ; iter < hash->size ; iter++) {
		hash->Contacts[iter] = NULL;
	}
	hash->nEl = 0;
	return hash;
}

/* 
	Hashmail *makeMail(int k)
	Receive an int k,
	Allocate k mails and an hashmail,
	Set all mails to NULL, and number of Elements to 0,
	Return a pointer to hash struture.
*/
Hashmail *makeMail(int k){
	int iter;
	
	/*Allocates an Hashmail*/
	Hashmail *hash = malloc(sizeof(Hashmail));

	hash->size = k;
	/*Allocates a mail list inside a hashmail with PRIME - 1 mails*/
	hash->mail = malloc(sizeof(Mail)*hash->size);

	for (iter = 0 ; iter < hash->size; iter++) {
		hash->mail[iter] = NULL;
	}
	hash->nEl = 0;
	return hash;
}
/* 
	void addHash(Hashtable *hash,Contact *c)
	Receive an hash and a contact,
	Get the hashcode,
	Add contact to hashtable.
	If hashtable is loaded make expand 
*/
void addHash(Hashtable *hash,Contact *c){

	int i = getHash(c->name,hash->size);
	while (hash->Contacts[i] != NULL) {
		i = (i + 1 ) % hash->size;
	}
	hash->Contacts[i] = c;
	hash->nEl++;
	if (loadHash(hash->nEl,hash->size) == 1) {
		hash = reTable(hash);
	}
}

/* 
	void addMail(Hashmail *hash,char *text)
	Receive an hash and a mail,
	Get the hashcode,
	Add mail to hashmail.
	If hashmaild is loaded make expand 
*/
void addMail(Hashmail *hash,char *mail){

	int i = getHash(mail,hash->size);

	Mail *newMail = malloc(sizeof(Mail));
	
	while (hash->mail[i] != NULL) {
		if (strcmp(hash->mail[i]->mail,mail)==0) {
			hash->mail[i]->nOcur++;
			free(newMail);
			return;
		}
		i = (i + 1 ) % hash->size;
	}

	newMail->mail = malloc((strlen(mail)+1) * sizeof(char));
	strcpy(newMail->mail,mail);
	newMail->nOcur = 1;
	hash->mail[i] = newMail;
	hash->nEl++;
	
	if (loadHash(hash->nEl,hash->size) == 1) {
		hash = reMail(hash);
	}	
}

/* 
	Contact *searchName(Hashtable *hash, char *name)
	Receive an hash and a name,
	Get the hashcode,
	return pointer to a contact if is on hashtable.
	else  return NULL pointer
*/
Contact *searchName(Hashtable *hash, char *name) {

	int i = getHash(name,hash->size);
	while (hash->Contacts[i] != NULL) {
		if (strcmp(hash->Contacts[i]->name,name)==0)
			return hash->Contacts[i];
		else
			i = (i + 1 ) % hash->size;
	}
	return NULL;
}

/* 
	void changeMail(Hashtable *hash,char *name,char *mail)
	Receive an hash,a name and a mail,
	Get the hashcode,
	Change mail contact on hashtable.
*/
void changeMail(Hashtable *hash,char *name,char *mail){
	int i = getHash(name,hash->size);
	while (hash->Contacts[i] != NULL) {
		if (strcmp(hash->Contacts[i]->name,name) == 0){
		
			free(hash->Contacts[i]->mail);
			free(hash->Contacts[i]->domain);

			hash->Contacts[i]->mail = malloc(sizeof(char)*(strlen(mail)+1));
			hash->Contacts[i]->domain = malloc(sizeof(char)*(strlen(getMail(mail))+1));

			strcpy(hash->Contacts[i]->mail,mail);
			strcpy(hash->Contacts[i]->domain,getMail(mail));
			return;
		}
		else
			i = (i + 1 ) % hash->size;
	}
	return;
}


/* 
	int mailOcur(Hashmail *hash, char *mail) 
	Receive an hash and a mail,
	Get the hashcode,
	return mail frequency at hashmail 
*/
int mailOcur(Hashmail *hash, char *mail) {

	int i = getHash(mail,hash->size);
	while (hash->mail[i] != NULL) {
		if (strcmp(hash->mail[i]->mail,mail) == 0)
			return hash->mail[i]->nOcur;
		else
			i = (i + 1) % hash->size;
	}
	return 0;
}

/* 
  void removeHash(Hashtable *hash, char *name)
	Receive an hash and a name,
	Get the hashcode,
	Remove from hashtable.
*/
void removeHash(Hashtable *hash, char *name) {
	int j, i = getHash(name,hash->size);
	Contact *c;
	while(hash->Contacts[i]!= NULL) {
		c = hash->Contacts[i];
		if (strcmp(c->name,name) == 0) {
			break;
		}
		else {
			i = (i + 1 ) % hash->size;
		}
	}
	if (hash->Contacts[i] == NULL)
		return;
	hash->Contacts[i] = NULL;
	for( j = (i) % hash->size ; hash->Contacts[j] != NULL; j = (i+1) % hash->size ) {
		c =  hash->Contacts[j];
		hash->Contacts[j] = NULL;
		addHash(hash,c);
	}
	hash->nEl--;

	if (loadHash(hash->nEl,hash->size) == 1) {
		hash = reTable(hash);
	}
}

/* 
  void removeMail(Hashmail *hash, char *name)
	Receive an hash and a name,
	Get the hashcode,
	Remove from hashtable.
*/
void removeMail(Hashmail *hash, char *mail) {
	int j, i = getHash(mail,hash->size);
	Mail *m;

	/*finding mail ocurrence  */
	while(hash->mail[i] != NULL) {
		if (strcmp(hash->mail[i]->mail,mail)==0) 
			break;
		else
			i = (i + 1 ) % hash->size;
	}
	if (hash->mail[i] == NULL)
		return;
	if (hash->mail[i]->nOcur == 1) {
		free(hash->mail[i]->mail);
		free(hash->mail[i]);
		hash->mail[i] = NULL;
		for( j = (i+1) % hash->size ; hash->mail[j] != NULL; j = (i+1) % hash->size ) {
			m =  hash->mail[j];
		 	hash->mail[j] = NULL;
		 	addMail(hash,m->mail);
		}
		return;
	}
	if (hash->mail[i]->nOcur > 1)
		hash->mail[i]->nOcur--;
	if (loadHash(hash->nEl,hash->size) == 1) {
		hash = reMail(hash);
	}
	return;

}


/* 
  void freeHash(Hashtable *hash)
	Receive an hash,
	Free the Contact list and the hash.
*/
void freeHash(Hashtable *hash) {
	free(hash->Contacts);
	free(hash);
}

/* 
  void freeMail(Hashmail *hash)
	Receive an hash,
	Free the mail list and the hash.
*/
void freeMail(Hashmail *hash){
	int iter;

	for (iter = 0 ; iter < hash->size ; iter++) {
		Mail *freed = hash->mail[iter];
		if (freed) {
			free(freed->mail);
			free(freed);
		}
	} 
	free(hash->mail);
	free(hash);
}
