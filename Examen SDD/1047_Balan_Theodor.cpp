#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STRUCTURI
struct Angajat
{
	unsigned int cod_departament;
	char* nume;
	float salariu;
	int vechime;
	int varsta;
	int proiecte;
};

struct nodSublista {
	Angajat info;
	nodSublista* next;
};

struct nodLista {
	nodSublista* info;
	nodLista* next;
};


struct nodCoada {
	Angajat info;
	nodCoada* nextCoada;
};

//HEADERE
void pop(nodCoada*& first, nodCoada*& last);

void push(nodCoada*& first, nodCoada*& last, Angajat info);

void afisCoada(nodCoada* first);

void coadaSublista(nodSublista* cap, nodCoada** first, nodCoada** last);

void coadaLista(nodLista* cap, nodCoada** first, nodCoada** last, int cod);

nodSublista* inserareSublista(nodSublista* cap, Angajat p);

nodLista* inserareLista(nodLista* capLista, nodSublista* capLS);

void afisareSublista(nodSublista* cap);

void afisareLista(nodLista* cap);

void alocareVectorSublista(nodSublista* cap, float salariu, Angajat* angajati, int& ii);

void alocareVectorLista(nodLista* cap, float salariu, Angajat* angajati, int& ii);

void dezalocareSublista(nodSublista* cap);

void dezalocareLista(nodLista* cap);

void dezalocareVector(Angajat* angajati);

void dezalocareCoada(nodCoada* first, nodCoada* last);

//MAIN
void main()
{
	FILE* file = fopen("1047_balan_Theodor.txt", "r");
	char buff[128];
	char* bucata;
	char split[] = { "," };

	int nr = 0;
	int i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	nodLista* capLista = NULL;
	nodSublista* capSubLista1 = NULL;
	nodSublista* capSubLista2 = NULL;
	nodSublista* capSubLista3 = NULL;

	while (fgets(buff, 128, file)) {
		Angajat a;
		bucata = strtok(buff, split);
		a.cod_departament = atoi(bucata);

		bucata = strtok(NULL, split);
		a.nume = (char*)malloc(sizeof(char) * (strlen(bucata)+1));
		strcpy(a.nume, bucata);

		bucata = strtok(NULL, split);
		a.salariu = atof(bucata);

		bucata = strtok(NULL, split);
		a.vechime = atoi(bucata);

		bucata = strtok(NULL, split);
		a.varsta = atoi(bucata);

		bucata = strtok(NULL, split);
		a.proiecte = atoi(bucata);
		if (a.cod_departament == 1) {
			capSubLista1 = inserareSublista(capSubLista1, a);
		}
		else if (a.cod_departament == 2) {
			capSubLista2 = inserareSublista(capSubLista2, a);
		}
		else {
			capSubLista3 = inserareSublista(capSubLista3, a);
		}
		
		
	}
	capLista = inserareLista(capLista, capSubLista1);
	capLista = inserareLista(capLista, capSubLista2);
	capLista = inserareLista(capLista, capSubLista3);
	printf("\n\nLISTA DE LISTE\n\n");
	afisareLista(capLista);

	Angajat* angajati = (Angajat*)malloc(sizeof(Angajat) * nr);
	int ii = 0;
	float salariu = 2300;
	alocareVectorLista(capLista, salariu, angajati, ii);

	printf("\n\nVECTOR\n\n");
	for (int k = 0; k < ii; k++) {
		printf("\ncod_departament: %u; nume: %s; salariu: %5.2f; vechime: %d; varsta: %d; proiecte %d;", angajati[k].cod_departament, angajati[k].nume,
			angajati[k].salariu, angajati[k].vechime, angajati[k].varsta, angajati[k].proiecte);
	}

	nodCoada* first = NULL;
	nodCoada* last = NULL;
	unsigned int cod=2;
	coadaLista(capLista, &first, &last, cod);
	printf("\n\nCOADA\n\n");
	afisCoada(first);

	dezalocareCoada(first,last);
	dezalocareLista(capLista);
	dezalocareVector(angajati);
}

//FUNCTII

void dezalocareCoada(nodCoada* first, nodCoada* last)
{
	while (last) {
		pop(first, last);
	}
	printf("\nCoada Dezalocata\n");
}

void dezalocareVector(Angajat* angajati)
{
	free(angajati);

	printf("\nVector Dezalocat\n");
}
void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		dezalocareSublista(temp->info);
		free(temp);
		temp = temp2;
	}

	printf("\nLista Dezalocata\n");
}
void dezalocareSublista(nodSublista* cap)
{
	nodSublista* temp = cap;
	while (temp)
	{
		nodSublista* temp2 = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = temp2;
	}

	printf("\nSublista Dezalocata\n");
}
void alocareVectorLista(nodLista* cap, float salariu, Angajat* angajati, int& ii)
{
	nodLista* temp = cap;
	while (temp != NULL)
	{
		alocareVectorSublista(temp->info, salariu, angajati, ii);
		temp = temp->next;
	}
}
void alocareVectorSublista(nodSublista* cap, float salariu, Angajat* angajati, int& ii)
{
	nodSublista* temp = cap;
	while (temp != NULL)
	{
		if (temp->info.salariu > salariu) {
			angajati[ii].cod_departament = temp->info.cod_departament;
			angajati[ii].salariu = temp->info.salariu;
			angajati[ii].varsta = temp->info.varsta;
			angajati[ii].proiecte = temp->info.proiecte;
			angajati[ii].vechime = temp->info.vechime;
			angajati[ii].nume = (char*)malloc(sizeof(char) * strlen(temp->info.nume));
			strcpy(angajati[ii].nume, temp->info.nume);
			ii++;
		}
		temp = temp->next;
	}
}
void afisareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp != NULL)
	{
		printf("Sublista\n");
		afisareSublista(temp->info);
		temp = temp->next;
	}
}
void afisareSublista(nodSublista* cap)
{
	nodSublista* temp = cap;
	while (temp != NULL)
	{
		printf("cod_departament: %u; nume: %s; salariu: %5.2f; vechime: %d; varsta: %d; proiecte %d;\n", temp->info.cod_departament, temp->info.nume,
			temp->info.salariu, temp->info.vechime, temp->info.varsta, temp->info.proiecte);
		temp = temp->next;
	}
}
void coadaLista(nodLista* cap, nodCoada** first, nodCoada** last, int cod)
{
	nodLista* temp = cap;
	while (temp != NULL)
	{
		if (temp->info->info.cod_departament == cod) {
			coadaSublista(temp->info, first, last);
		}
		temp = temp->next;
	}
}
void coadaSublista(nodSublista* cap, nodCoada** first, nodCoada** last)
{
	nodSublista* temp = cap;
	while (temp != NULL)
	{
		push(*first, *last, temp->info);
		temp = temp->next;
	}
}
void afisCoada(nodCoada* first) {
	nodCoada* cursor = first;
	while (cursor) {
		printf("cod_departament: %u; nume: %s; salariu: %5.2f; vechime: %d; varsta: %d; proiecte %d;\n", cursor->info.cod_departament, cursor->info.nume,
			cursor->info.salariu, cursor->info.vechime, cursor->info.varsta, cursor->info.proiecte);
		cursor = cursor->nextCoada;
	}
}
void push(nodCoada*& first, nodCoada*& last, Angajat info) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->info = info;
	nou->nextCoada = NULL;
	if (first == NULL && last == NULL) {
		first = nou;
		last = nou;
	}
	else {
		last->nextCoada = nou;
		last = nou;
	}
}
void pop(nodCoada*& first, nodCoada*& last) {
	if (first) {
		nodCoada* eliminat = first;
		first = first->nextCoada;
		if (first == NULL) {
			last = NULL;
		}
		free(eliminat);
	}
}
nodLista* inserareLista(nodLista* capLista, nodSublista* capLS)
{
	nodLista* nou = new nodLista;
	nou->info = capLS;
	nou->next = NULL;
	if (capLista == NULL)
		capLista = nou;
	else
	{
		nodLista* temp = capLista;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return capLista;
}
nodSublista* inserareSublista(nodSublista* cap, Angajat p)
{
	nodSublista* nou = new nodSublista;
	nou->info = p;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodSublista* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;

}