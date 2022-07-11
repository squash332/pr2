#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "datatype.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajZapis(const char* const);
void* ucitajZapise(const char* const);
void ispisiSve(const ZAPIS*);
void* pretraziZapise(ZAPIS* const);
void azurirajZapis(ZAPIS*, const char* const);
void brisanjeZapisa(ZAPIS* const, const char* const);

#endif