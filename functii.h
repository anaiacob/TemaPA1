#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

typedef struct Player jucator;

struct team
{
    char* name_team;
    int number_players;
    jucator* player;
    struct team* next;
    int total_points;
    struct team* prev;
};

typedef struct team echipa;


void deschidere_fisiere(char* ar1, FILE** f1, char* ar2, FILE** f2, char* ar3, FILE** f3);
void citeste_cerinte(FILE* f1, int* cerinte);
void omitere_spatiu(FILE* f, long poz);
char* citire_linie(FILE* f);
char* citire_cuvant(FILE* f);
void citire_jucatori(FILE* f, int nr_jucatori, jucator* p, int* total);
echipa* creaza_echipa(FILE* fis_team);
void cerinta1(FILE* fis_team,FILE* print);
void adauga_la_inceput_lista(echipa** head, char* nume, int nr_jucatori, int total, jucator* p);
void afis_juc(jucator* p,int nr_juc);
void goToNextLine(FILE* file);
long long putere2(int n);
void elimina_nod(echipa** head, echipa* nod);
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
long long putere2(int n);
void eliminare_echipa(int m,int* punctaj_echipe,echipa** head);
void cerinta2(FILE* fis_team, FILE* print);

void eliberare_lista(echipa** head);

