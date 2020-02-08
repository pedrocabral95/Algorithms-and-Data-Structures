#include "List.h"
#include "Hash.h"
#include "Head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Pedro Cabral IST 90767 IAED - 2 - Project*/

/* Main function 

main function has three essencial atritutes,
	an hash table who saves contacts
	an hash table who saves domain of mail contacts
	an doubly linked list who saves order of contacts insertion 

	scans name mail and number depends on a given char!
*/
int main() {
	char name[MAXSIZE], mail[513], number[64];
	int ch;
	List *l= makeList();
	Hashtable *hash= makeHash(PRIME);
	Hashmail *hmail= makeMail(PRIME);	
	while ((ch = getchar()) != EOF)
		switch (ch) {
			case 'a': 
			scanf("%s %s %s", name, mail, number);
			add(hash,hmail,l,name,mail,number);
			break;

			case 'l': 
			printAll(l);
			break;

			case 'p':
			scanf("%s",name); 
			printfOne(hash,name);
			break;

			case 'r':
			scanf("%s", name);  
			remuve(hash,hmail,l,name);
			break;

			case 'e': 
			scanf("%s%s",name,mail); 
			change(hash,hmail,l,name,mail);
			break;

			case 'c':
			scanf("%s", mail);
			printMail(hmail,mail);
			break;

			/*Free all memory in hashtable hashmail and list!*/
			case 'x':
			freeList(l);
			freeHash(hash);
			freeMail(hmail);
			return 0;

			default:
			break;
		}
	return 0;
}