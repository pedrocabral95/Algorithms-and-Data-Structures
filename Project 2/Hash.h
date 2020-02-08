#ifndef TABLE
#define TABLE
#define PRIME 29009
#include "List.h"
/* Pedro Cabral IST 90767 IAED - 2 - Project*/

/* All Hash struts and functions are defined here*/

/* Structures */

/* Hashtable with contacts associated */ 
typedef struct {
	Contact **Contacts;
	int size;
	int nEl;
} Hashtable;

/* Hashtable with domain of contacts associated */ 
typedef struct {
	Mail **mail;
	int size;
	int nEl;
} Hashmail;

/*Hashtable Functions*/
int getHash(char *name, int size);
int loadHash(int a,int b);

Hashtable *makeHash(int k);
Hashmail *makeMail(int k);

void addMail(Hashmail *hash, char *mail);
void addHash(Hashtable *hash,Contact *c) ;

void removeHash(Hashtable *hash, char *p);
void removeMail(Hashmail *hMail, char *mail);

int mailOcur(Hashmail *hash, char *mail);
Contact *searchName(Hashtable *hash, char *name);

void changeMail(Hashtable *hash,char *name,char *mail);

Hashtable *reTable(Hashtable *hash);
Hashmail *reMail(Hashmail *hash);


void freeHash(Hashtable *hash);
void freeMail(Hashmail *mail);
#endif