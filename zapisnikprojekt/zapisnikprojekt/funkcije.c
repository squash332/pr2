/*  složeni podaci - strukture, pokazivaèi
	funkcije- argumenti trebaju biti složeni podaci
			  strukture, pokaivaèi na strukture	
	datoteka - tekst ili binarna, èitanje ako je potrebno
	dinamièka alokacija memorije - potpuno rukovanje memorijom
	algoritmi sortiranja - algoritam sortiranja i pretrazivanja
	organizacija koda - razdvajanje programa u više datoteka

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

static int brojZapisa = 0;
static int i, j = 0;
static int br = 0;

int izbornik() {

	int opcija = 0;
	static zapis* polje = NULL;

	printf("----------------------------------------------------------------------------------\n");
	printf("Dobrodošli!\nOdaberite jednu od slijedeæih opcija:\n");
	printf(" 1 - Dodaj zapis\n");
	printf(" 2 - Uredi postojani zapis\n");
	printf(" 3 - Ispis zapisa\n");
	printf(" 4 - Tražilica zapisa\n");
	printf(" 6 - Brisanje zapisa\n");
	printf(" 7 - Izlaz\n");
	*/
	
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"
#include "header.h"

static int brojZapisa = 1;
//funckije za zauzimanje memorije, za pisanje i ucitavanje datoteke
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojZapisa, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}

}

void dodajZapis(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje zapisa u datoteku zapis.bin");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojZapisa
	fread(&brojZapisa, sizeof(int), 1, fp);
	printf("Broj zapisa: %d\n\n", brojZapisa);

	ZAPIS temp = { 0 };
	temp.id = brojZapisa + 1;
	getchar();

	printf("Unesite ime korisnika: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime korisnika: ");
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite datum: ");
	scanf("%d", &temp.dan);
	scanf("%d", &temp.mjesec);
	scanf("%d", &temp.godina);

	//pomicemo se na kraj datoteke i zapisujemo nov zapis tamo
	fseek(fp, sizeof(ZAPIS) * brojZapisa, SEEK_CUR);
	fwrite(&temp, sizeof(ZAPIS), 1, fp);
	printf("Novi zapis dodan.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojZapisa++;

	// zapis novog broja zapisa
	fwrite(&brojZapisa, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajZapise(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje korisnika iz zapis.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojZapisa, sizeof(int), 1, fp);
	printf("Broj zapisa: %d\n", brojZapisa);

	ZAPIS* poljeZapisa = (ZAPIS*)calloc(brojZapisa, sizeof(ZAPIS));

	if (poljeZapisa == NULL) {
		perror("Zauzimanje memorije za zapise");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeZapisa, sizeof(ZAPIS), brojZapisa, fp);

	printf("Svi zapisi uspjesno ucitani.\n\n");

	return poljeZapisa;
}

void ispisiSve(const ZAPIS* polje) {

	if (brojZapisa == 0) {
		printf("Polje zapisa prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojZapisa; i++) {
		printf("zapis broj %d\nID: %d\nIme: %s\nprezime: %s \ndatum: %d.%d.%d. \n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->dan,
			(polje + i)->mjesec,
			(polje + i)->godina);
	}
}

void* pretraziZapise(ZAPIS* const polje) {

	if (brojZapisa == 0) {
		printf("Polje zapisa prazno\n");
		return;
	}

	int i;

	int trazeniId;

	printf("Unesite ID zapisa koju trazite: \n");
	scanf("%d", &trazeniId);

	// ako nademo clana vracamo cijeli element polja s trazenim id-em
	for (i = 0; i < brojZapisa; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("zapis pronadena.\n");

			return(polje + i);
		}
	}

	// vracamo NULL u slucaju da ne nademo nijednu pusku s tim id
	return NULL;
}


void azurirajZapis(ZAPIS* polje, const char* const dat) {

	if (brojZapisa == 0) {
		printf("Polje zapisa prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje zapisa");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID zapisa koju zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojZapisa) {
			printf("Zapis s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojZapisa);

	ZAPIS temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime korisnika (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf("%24[^\n]", temp.ime);

	getchar();
	printf("Unesite prezime  korisnika (trenutno: %s): ", (polje + trazeniId - 1)->prezime);
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite dan (trenutno: %d:) ", (polje + trazeniId - 1)->dan);
	scanf("%d[^\n]", &temp.dan);
	printf("Unesite mjesec (trenutno: %d:) ", (polje + trazeniId - 1)->mjesec);
	scanf("%d[^\n]", &temp.mjesec);
	printf("Unesite godinu (trenutno: %d:) ", (polje + trazeniId - 1)->godina);
	scanf("%d[^\n]", &temp.godina);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(ZAPIS) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(ZAPIS), 1, fp);

	printf("Zapis uspjesno azuriran.\n");

	fclose(fp);
}

void brisanjeZapisa(ZAPIS* const polje, const char* const dat) {

	if (brojZapisa == 0) {
		printf("Polje zapisa prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje zapisa");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID zapisa kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojZapisa) {
			printf("zapis s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojZapisa);

	ZAPIS* pomocnoPolje = (ZAPIS*)calloc(brojZapisa - 1, sizeof(ZAPIS));

	if (pomocnoPolje == NULL) {
		perror("Zauzimanje memorije za pomocno polje.");
		return NULL;
		exit(EXIT_FAILURE);
	}

	int counter = 0;

	for (i = 0; i < brojZapisa; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(ZAPIS), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Zapis je uspjesno obrisan.\n");
}