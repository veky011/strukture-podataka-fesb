#define _CRT_SECURE_NO_WARNINGS // iznad svih includeova!
#define N 50
#include <stdio.h>
#include <stdlib.h>

typedef struct _student {
	char ime[N];
	char prezime[N];
	int punti;
} student;

int maxPunti(student* students, int r) {
	int p;
	p = students[0].punti;
	for (int i = 0; i < r; i++) {
		if (students[i].punti > p) {
			p = students[i].punti;
		}
	}
	return p;
}

float relPunti(student* students, int punti, int r) {
	return (float)punti / maxPunti(students, r) * 100;
}

void output(student* students, int r) {
	for (int i = 0; i < r; i++) {
		printf("%s %s: %.3f\n", students[i].prezime, students[i].ime,
			relPunti(students, students[i].punti, r)
		);
	}
}

int main() {
	FILE* fptr = fopen("popis.txt", "r");
	if (!fptr) return -1;

	char buffer[N] = { 0 };
	int r = 0;

	while (!feof(fptr)) {
		fgets(buffer, N, fptr);
		r++;
	}
	rewind(fptr);
	// student* students = NULL;
	student* students = (student*)malloc(r * sizeof(student));

	int i = 0;
	while (!feof(fptr)) {
		fscanf(fptr, "%s %s %d", students[i].ime, students[i].prezime,
			&students[i].punti
		);
		++i;
	}

	output(students, r);

	fclose(fptr); // UVIJEK NAKON KRAJA RADA S FILEOM!!
	free(students);
	return 0;
}