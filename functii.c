#include "functii.h"
//este ok
void citeste_cerinte(FILE* f1, int* cerinte) {
    char c;
    int i = 0;
    while ((c = getc(f1)) != EOF) {
        if (c == '1' || c == '0') {
            cerinte[i] = (int)(c - '0');
            i++;
        }
    }
}
//este ok
void goToNextLine(FILE* file) {
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {}

    if (c != EOF) {
        fseek(file, 1, SEEK_CUR);
    }
}
//este ok
char* citire_linie(FILE* f) {
    long long dimensiune_linie = 100, lungime = 0;
    char* linie = (char*)malloc(dimensiune_linie * sizeof(char));
    if (!linie) {
        printf("Eroare la alocare memorie pentru linie.\n");
        exit(1);
    }
    while (fgets(linie + lungime, dimensiune_linie - lungime, f)) {
        lungime = strlen(linie);
        if (linie[lungime - 1] == '\n') {
            linie[lungime - 1] = '\0';
            break;
        }
        dimensiune_linie *= 2;
        char* new_line = (char*)realloc(linie, dimensiune_linie);
        if (new_line == NULL) {
            free(linie);
            printf("Nu s-a putut realoca.\n");
            exit(1);
        }
        linie = new_line;
    }
    if (lungime == 0 && feof(f)) {
        free(linie);
        return NULL;
    }
    return linie;
}
//este ok
void omitere_spatiu(FILE* f, long poz) {
    if (fseek(f, poz, SEEK_CUR) != 0) {
        printf("Eroare la deplasare.\n");
    }
}
//este ok
char* citire_cuvant(FILE* f) {
    int dimensiune_cuvant = 100, lungime = 0;
    char* cuvant = (char*)malloc(dimensiune_cuvant * sizeof(char));
    if (cuvant == NULL) {
        printf("Nu s-a putut citi cuvantul.\n");
        exit(1);
    }
    char cuv;
    while ((cuv = fgetc(f)) != EOF && cuv != ' ' && cuv != '\n') {
        if (lungime + 1 >= dimensiune_cuvant) {
            dimensiune_cuvant *= 2;
            char* newcuv = (char*)realloc(cuvant, dimensiune_cuvant);
            if (newcuv == NULL) {
                free(cuvant);
                printf("Nu s-a putut realoca.\n");
                exit(1);
            }
            cuvant = newcuv;
        }
        cuvant[lungime++] = cuv;
    }
    cuvant[lungime] = '\0';
    //printf("%s\n",cuvant);
    if (lungime == 0 && cuv == EOF) {
        free(cuvant);
        return NULL;
    }
    return cuvant;
}

void citire_jucatori(FILE* f, int nr_jucatori, jucator* p, int* total) {
    for (int i = 0; i < nr_jucatori; i++) {
        p[i].firstName = citire_cuvant(f);
        //printf("%s\n", p[i].firstName);

        p[i].secondName = citire_cuvant(f);
        //printf("%s\n", p[i].secondName);

        if (fscanf(f, " %d", &p[i].points) != 1) {
            printf("Eroare la citirea punctajului jucatorului.");
            return;
        }
        //printf("%d\n", p[i].points);

        fscanf(f, " ");
        *total+=p[i].points;
    }
}


void adauga_la_inceput_lista(echipa** head, char* nume, int nr_jucatori, int total, jucator* p) {
    echipa* newNod = (echipa*)malloc(sizeof(echipa));
    if (newNod == NULL) {
        printf("Nu s-a putut aloca memoria pentru echipa.\n");
        exit(1);
    }

    newNod->name_team = (char*)malloc((strlen(nume) + 1) * sizeof(char));
    if (newNod->name_team == NULL) {
        free(newNod);
        printf("Nu s-a putut aloca memoria pentru numele echipei.\n");
        exit(1);
    }
    strcpy(newNod->name_team, nume);

    //printf("%s\n", newNod->name_team);

    newNod->number_players = nr_jucatori;
    //printf("%d\n", newNod->number_players);

    newNod->total_points = total;
    //printf("%d\n", newNod->total_points);

    newNod->player = (jucator*)malloc(nr_jucatori * sizeof(jucator));
    if (newNod->player == NULL) {
        free(newNod->name_team);
        free(newNod);
        printf("Nu s-a putut aloca memoria pentru jucatori.\n");
        exit(1);
    }

    for (int i = 0; i < nr_jucatori; i++) {
        newNod->player[i].firstName = (char*)malloc((strlen(p[i].firstName) + 1) * sizeof(char));
        newNod->player[i].secondName = (char*)malloc((strlen(p[i].secondName) + 1) * sizeof(char));

        if (newNod->player[i].firstName == NULL || newNod->player[i].secondName == NULL) {
            printf("Nu s-a putut aloca memoria pentru numele jucatorilor.\n");
            for (int j = 0; j <= i; j++) {
                free(newNod->player[j].firstName);
                free(newNod->player[j].secondName);
            }
            free(newNod->player);
            free(newNod->name_team);
            free(newNod);
            exit(1);
        }

        strcpy(newNod->player[i].firstName, p[i].firstName);
        strcpy(newNod->player[i].secondName, p[i].secondName);
        newNod->player[i].points = p[i].points;

        //printf("%s\n", newNod->player[i].firstName);
        //printf("%s\n", newNod->player[i].secondName);
        //printf("%d\n", newNod->player[i].points);
    }

    newNod->next = *head;
    newNod->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNod;
    }

    *head = newNod;
}
echipa* creaza_echipa(FILE* fis_team) {
    int nr_echipe;
    if (fscanf(fis_team, "%d", &nr_echipe) != 1) {
        printf("Eroare la citirea numarului de echipe.\n");
        exit(1);
    }

    echipa* lista_echipa = NULL;
    for (int i = 0; i < nr_echipe; i++) {
        int nr_jucatori;
        if (fscanf(fis_team, "%d", &nr_jucatori) != 1) {
            printf("Eroare la citirea numarului de jucatori pentru echipa %d.\n", i + 1);
            exit(1);
        }
        omitere_spatiu(fis_team, 1);
        char* nume_echipa = citire_linie(fis_team);
        if (!nume_echipa) {
            printf("Eroare la citirea numelui echipei %d.\n", i + 1);
            exit(1);
        }
        jucator* p = (jucator*)malloc((nr_jucatori+1) * sizeof(jucator));
        if (p == NULL) {
            free(nume_echipa);
            printf("Eroare la alocarea memoriei pentru jucatori pentru echipa %d.\n", i + 1);
            exit(1);
        }

        int total = 0;
        citire_jucatori(fis_team, nr_jucatori, p, &total);
        //printf("%d\n",total);
        adauga_la_inceput_lista(&lista_echipa, nume_echipa, nr_jucatori, total, p);
        free(nume_echipa);
        free(p);
    }
    return lista_echipa;
}

void cerinta1(FILE* fis_team, echipa** lista_echipa, FILE* print) {
    *lista_echipa = creaza_echipa(fis_team);
    echipa* cap_lista = *lista_echipa;
    while (cap_lista != NULL) {
        fprintf(print, "%s\n", cap_lista->name_team);
        cap_lista = cap_lista->next;
    }
}
