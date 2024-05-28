#include "functii.h"

void eliberare_lista(echipa** head)
{
    echipa* nod=*head;
    while(nod!=NULL)
    {
        for(int i=0;i<nod->number_players;i++)
        {
            free(nod->player[i].firstName);
            free(nod->player[i].secondName);
        }
        free(nod);
        nod= nod->next;
    }
}

void citire_jucatori(FILE* f, int nr_jucatori, jucator* p, int* total) {
    for (int i = 0; i < nr_jucatori; i++) {
        p[i].firstName = citire_cuvant(f);
        p[i].secondName = citire_cuvant(f);
        if (fscanf(f, " %d", &p[i].points) != 1) {
            printf("Eroare la citirea punctajului jucatorului.");
            return;
        }
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
    newNod->number_players = nr_jucatori;
    newNod->total_points = total;
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
        nume_echipa=sterge_spatiu_final(nume_echipa);
        if (!nume_echipa) {
            printf("Eroare la citirea numelui echipei %d.\n", i + 1);
            exit(1);
        }
        int i=0;
        jucator* p = (jucator*)malloc((nr_jucatori+1) * sizeof(jucator));
        if (p == NULL) {
            free(nume_echipa);
            printf("Eroare la alocarea memoriei pentru jucatori pentru echipa %d.\n", i + 1);
            exit(1);
        }
        int total = 0;
        citire_jucatori(fis_team, nr_jucatori, p, &total);
        adauga_la_inceput_lista(&lista_echipa, nume_echipa, nr_jucatori, total, p);
        free(nume_echipa);
        free(p);
    }
    return lista_echipa;
}

void elimina_nod(echipa** head, echipa* nod) {
    if (nod == NULL) {
        return;
    }
    if (*head == nod) {
        *head = nod->next;
    }
    if (nod->prev != NULL) {
        nod->prev->next = nod->next;
    }
    if (nod->next != NULL) {
        nod->next->prev = nod->prev;
    }
    free(nod->name_team);
    for (int i = 0; i < nod->number_players; i++) {
        free(nod->player[i].firstName);
        free(nod->player[i].secondName);
    }
    free(nod->player);
    free(nod);
}


void adauga_la_sfarsit(echipa** cap, echipa* val) {
    if (*cap == NULL) {
        *cap = val;
        val->next = NULL;
        val->prev = NULL;
    } else {
        echipa* temp = *cap;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = val;
        val->prev = temp;
        val->next = NULL;
    }
}

echipa* eliminare_pierzatori(node* stiva_pierzatori, echipa** lista) {
    echipa* list_ramas = NULL;
    echipa* last_ramas = NULL;
    while (!isEmptystack(stiva_pierzatori)) {
        node_aux* pierzator_aux = top(stiva_pierzatori);
        if (pierzator_aux == NULL) {
            printf("Eroare la obținerea pierzatorului\n");
            return NULL;
        }
        echipa* pierzator = pierzator_aux->t;
        echipa* cap_lista = *lista;
        echipa* prev_lista = NULL;
        int found = 0;
        while (cap_lista != NULL) {
            if (cap_lista->name_team == NULL) {
                printf("Eroare: name_team este NULL\n");
                return NULL;
            }
            if (strcmp(cap_lista->name_team, pierzator->name_team) == 0) {
                if (prev_lista == NULL) {
                    *lista = cap_lista->next;
                } else {
                    prev_lista->next = cap_lista->next;
                }

                echipa* de_eliminat = cap_lista;
                cap_lista = cap_lista->next;
                free(de_eliminat);
                found = 1;
                break;
            } else {
                prev_lista = cap_lista;
                cap_lista = cap_lista->next;
            }
        }

        if (!found) {
            printf("Echipa pierzatoare nu a fost gasita in lista: %s\n", pierzator->name_team);
        }

        pop(&stiva_pierzatori);
        free(pierzator_aux);
    }

    echipa* cap_lista = *lista;
    while (cap_lista != NULL) {
        if (list_ramas == NULL) {
            list_ramas = cap_lista;
            last_ramas = list_ramas;
        } else {
            last_ramas->next = cap_lista;
            last_ramas = last_ramas->next;
        }
        cap_lista = cap_lista->next;
    }

    if (last_ramas != NULL) {
        last_ramas->next = NULL;
    }

    return list_ramas;
}
