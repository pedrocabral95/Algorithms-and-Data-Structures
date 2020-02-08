#ifndef CONTACT
#define CONTACT
#define MAXSIZE 1024


/* Pedro Cabral IST 90767 IAED - 2 - Project*/
/* All List struts and functions are declared here*/

/* Structures */

/* Contact */ 
typedef struct contact {
	char *name;
	char *mail;
	char *number;
	char *domain;
	struct contact *prev;
	struct contact *next;
} Contact;

/* Mail */
typedef struct mail{
	int nOcur;
	char *mail;
} Mail;

/* Struct contains pointer to head and the last element! */
typedef struct {
	Contact *head;
	Contact *last;
} List;

/*List Functions*/

List *makeList();
void freeContact(Contact *c);
void freeList(List *l);
void printList(List *l);
void printContact(Contact *c);
void removeContact(List *l, Contact *c);
Contact *addContact(List *l,char *name,char *mail,char *number,char *doamin);
void changeContact(List *l, char *name,char *mail);
char *getMail(char *name);
#endif