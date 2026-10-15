#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Person* Position;
typedef struct _Person {
	char* name;
	char* lname;
	int year;
	Position Next;
} Person;

int insertBegin(Position p, const char* name, const char* lname, int y) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		return -1;
	}

	newPerson->name = (char*)malloc(strlen(name) + 1);
	newPerson->lname = (char*)malloc(strlen(lname) + 1);
	if (newPerson->name == NULL || newPerson->lname == NULL) {
		free(newPerson->name);
		free(newPerson->lname);
		free(newPerson);
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lname, lname);
	newPerson->year = y;

	newPerson->Next = p->Next;
	p->Next = newPerson;

	return 0;
}

int insertEnd(Position p, const char* name, const char* lname, int y) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		return -1;
	}

	newPerson->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	newPerson->lname = (char*)malloc((strlen(lname) + 1) * sizeof(char));
	if (newPerson->name == NULL || newPerson->lname == NULL) {
		free(newPerson->name);
		free(newPerson->lname);
		free(newPerson);
		return -1;
	}

	newPerson->Next = NULL;
	while (p->Next != NULL) {
		p = p->Next;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lname, lname);
	newPerson->year = y;

	newPerson->Next = p->Next;
	p->Next = newPerson;

	return 0;
}

int output(Position p) {
	// p = HEAD.Next
	int i = 0;
	while (p != NULL) {
		printf("#%d: %s %s, %d\n", i, p->lname, p->name, p->year);
		p = p->Next;
		++i;
	}

	return 0;
}

int find(Position p, char* lname) {
	// Vraca poziciju u listi, pocevsi od 0
	int i = 0;
	
	while (p != NULL) {
		if (!strcmp(lname, p->lname)) {
			return i;
		}
		p = p->Next;
		++i;
	}

	return -1;
}

int del(Position p, char* lname) {
	// p = HEAD.Next
	int pos = find(p, lname);
	if (pos == -1)
		return -1;


	for (int i = 0; i < pos - 1; i++) {
		p = p->Next;
	}
	Position curr = p->Next;
	p->Next = curr->Next;
	free(curr);

	return pos;
}

int main() {
	Person HEAD;
	HEAD.name = "";
	HEAD.lname = "";
	HEAD.year = -1;
	HEAD.Next = NULL;

	insertBegin(&HEAD, "Andrija", "Matkovic", 25);
	insertBegin(&HEAD, "Marko", "Ivic", 49);
	insertEnd(&HEAD, "Ante", "Antic", 19);
	output(HEAD.Next);
	printf("------------------\n");
	printf("Karlovic na: %d\n", find(HEAD.Next, "Karlovic")); // Nema Karlovic, vraca -1
	printf("Antic na: %d\n", find(HEAD.Next, "Antic")); // 2
	insertEnd(&HEAD, "Duje", "Simic", 53);
	del(HEAD.Next, "Matkovic");
	insertBegin(&HEAD, "Ivan", "Peric", 18);
	del(HEAD.Next, "Jovic"); // Nema Jovic, ne radi nista
	output(HEAD.Next);
	return 0;
}