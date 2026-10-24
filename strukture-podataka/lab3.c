#define N 50
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

int insertBegin(Position p, char* name, char* lname, int y) {
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

int insertEnd(Position p, char* name, char* lname, int y) {
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

int insertAfter(Position p, char* lname_rel, char* name,
	char* lname, int y) {
	while (p != NULL && strcmp(lname_rel, p->lname) != 0) {
		p = p->Next;
	}
	if (p == NULL)
		return -1;

	Position newPerson = (Position)malloc(sizeof(Person));
	newPerson->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	newPerson->lname = (char*)malloc((strlen(lname) + 1) * sizeof(char));
	strcpy(newPerson->name, name);
	strcpy(newPerson->lname, lname);
	newPerson->year = y;
	newPerson->Next = p->Next;
	p->Next = newPerson;

	return 0;
}
int insertBefore(Position p, char* lname_rel, char* name,
	char* lname, int y) {
	while (p != NULL && strcmp(lname_rel, p->Next->lname) != 0) {
		p = p->Next;
	}
	if (p == NULL)
		return -1;

	Position newPerson = (Position)malloc(sizeof(Person));
	newPerson->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	newPerson->lname = (char*)malloc((strlen(lname) + 1) * sizeof(char));
	strcpy(newPerson->name, name);
	strcpy(newPerson->lname, lname);
	newPerson->year = y;
	newPerson->Next = p->Next;
	p->Next = newPerson;

	return 0;
}

int insertSorted(Position p, char* name, char* lname, int y) {
	while (p->Next != NULL && strcmp(p->Next->lname, lname) < 0) {
		p = p->Next;
	}
	if (p != NULL) {
		insertAfter(p, p->lname, name, lname, y);
		return 0;
	}
	return -1;
}

int len(Position p) {
	int i = 0;
	while (p != NULL) {
		p = p->Next;
		++i;
	}
	return i;
}
int output(Position p) {
	// p = HEAD.Next
	printf("------------------\n");
	int i = 0;
	while (p != NULL) {
		printf("#%d: %s %s, %d\n", i, p->lname, p->name, p->year);
		p = p->Next;
		++i;
	}
	printf("------------------\n");

	return 0;
}
int foutput(FILE* fptr, Position p) {
	// p = HEAD.Next
	int i = 0;
	while (p != NULL) {
		fprintf(fptr, "#%d: %s %s %d\n", i, p->lname, p->name, p->year);
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

int delAll(Position p) {
	Position temp = NULL;
	while (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}
	return 0;
}

int readFromFile(FILE* fptr, Position p) {
	char name[50];
	char lname[50];
	int year;
	while (!feof(fptr)) {
		fscanf(fptr, "%s %s %d", name, lname, &year);
		insertEnd(p, name, lname, year);
		p = p->Next;
	}
}

int main() {
	Person HEAD;
	HEAD.name = "";
	HEAD.lname = "";
	HEAD.year = -1;
	HEAD.Next = NULL;

	FILE* fptr1, * fptr2;
	fptr1 = fopen("popis.txt", "r");
	fptr2 = fopen("output.txt", "w");

	insertBegin(&HEAD, "Andrija", "Matkovic", 25);
	insertBegin(&HEAD, "Marko", "Ivic", 49);
	insertEnd(&HEAD, "Ante", "Antic", 19);
	output(HEAD.Next);
	printf("Karlovic na: %d\n", find(HEAD.Next, "Karlovic")); // Nema Karlovic, vraca -1
	printf("Antic na: %d\n", find(HEAD.Next, "Antic")); // 2
	insertEnd(&HEAD, "Duje", "Simic", 53);
	del(HEAD.Next, "Matkovic");
	insertBegin(&HEAD, "Ivan", "Peric", 18);
	del(HEAD.Next, "Jovic"); // Nema Jovic, ne radi nista
	insertAfter(&HEAD, "Antic", "Marko", "Livaja", 10);
	insertBefore(&HEAD, "Livaja", "Michele", "Sego", 69);
	insertBefore(&HEAD, "Peric", "Michael", "Jackson", 69);
	foutput(fptr2, HEAD.Next);
	output(HEAD.Next);

	delAll(&HEAD);

	insertSorted(&HEAD, "Jakov", "Jozinovic", 22);
	insertSorted(&HEAD, "Marin", "Ancic", 33);
	insertSorted(&HEAD, "Oliver", "Dragojevic", 83);
	output(HEAD.Next);

	delAll(&HEAD);

	readFromFile(fptr1, &HEAD);
	output(HEAD.Next);

	return 0;
}