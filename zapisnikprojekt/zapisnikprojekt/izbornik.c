#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"
#include "header.h"

static int brojClanova = 0;

int izbornik(const char* const ime) {

	printf("\t\t----------------------------------------\n\n");
	printf("\t\tOdaberite opciju: \n\n");
	printf("\t\t\n\n");

	printf("\t\tOpcija 1: Dodavanje zapisa!\n");
	printf("\t\tOpcija 2: Ispisi podatke o svim zapisma!\n");
	printf("\t\tOpcija 3: Pretrazivanje zapisa po ID-u!\n");
	printf("\t\tOpcija 4: Azuriraj zapis!\n");
	printf("\t\tOpcija 5: Obrisi zapis!\n");
	printf("\t\tOpcija 6: Izlaz iz programa!\n");

	printf("\t\t----------------------------------------\n\n");

	int odgovor = 0;

	static ZAPIS* poljeZapisa = NULL;
	static ZAPIS* pronadeniZapis = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		dodajZapis(ime);
		break;
	case 2:
		if (poljeZapisa != NULL) {
			free(poljeZapisa);
			poljeZapisa = NULL;
		}

		poljeZapisa = (ZAPIS*)ucitajZapise(ime);

		ispisiSve(poljeZapisa);
		break;
	case 3:
		if (poljeZapisa != NULL) {
			free(poljeZapisa);
			poljeZapisa = NULL;
		}

		poljeZapisa = (ZAPIS*)ucitajZapise(ime);

		pronadeniZapis = (ZAPIS*)pretraziZapise(poljeZapisa);

		if (pronadeniZapis != NULL) {
			printf("ID: %d\n", pronadeniZapis->id);
			printf("Ime: %s\n", pronadeniZapis->ime);
			printf("prezime: %s\n", pronadeniZapis->prezime);
			printf("datum: %d.%d.%d. \n", pronadeniZapis->dan, pronadeniZapis->mjesec, pronadeniZapis->godina);
		}
		else {
			printf("Ne postoji zapis s tim ID-em.\n");
		}

		break;
	case 4:
		if (poljeZapisa != NULL) {
			free(poljeZapisa);
			poljeZapisa = NULL;
		}

		poljeZapisa = (ZAPIS*)ucitajZapise(ime);

		azurirajZapis(poljeZapisa, ime);
		break;
	case 5:
		if (poljeZapisa != NULL) {
			free(poljeZapisa);
			poljeZapisa = NULL;
		}

		poljeZapisa = (ZAPIS*)ucitajZapise(ime);

		brisanjeZapisa(poljeZapisa, ime);
		break;
	default:
		free(poljeZapisa);
		poljeZapisa = NULL;
		odgovor = 0;
	}

	return odgovor;
}