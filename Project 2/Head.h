#include "List.h"
#include "Hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Pedro Cabral IST 90767 IAED - 2 - Project*/

/* Main functions declarations */
void add(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail, char *number);
void printAll(List *l); 
void printfOne(Hashtable *table, char *name);
void remuve(Hashtable *table, Hashmail *hmail, List *l, char *name);
void change(Hashtable *table, Hashmail *hmail, List *l, char *name, char *mail);
void printMail(Hashmail *hmail,char *mail);