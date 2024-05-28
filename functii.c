#include "functii.h"

void deschidere_fisiere(char* ar1, FILE** f1, char* ar2, FILE** f2, char* ar3, FILE** f3)
{
    *f1=fopen(ar1,"rt");
    if(f1==NULL)
    {
        printf("Nu s-a putut deschide.\n");
        exit(1);
    }
    *f2=fopen(ar2,"rt");
    if(f2==NULL)
    {
        printf("Nu s-a putut deschide.\n");
        exit(1);
    }
    *f3=fopen(ar3,"wt");
    if(f3==NULL)
    {
        printf("Nu s-a putut deschide.\n");
        exit(1);
    }
}

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

void goToNextLine(FILE* file) {
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {}

    if (c != EOF) {
        fseek(file, 1, SEEK_CUR);
    }
}

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

void omitere_spatiu(FILE* f, long poz) {
    if (fseek(f, poz, SEEK_CUR) != 0) {
        printf("Eroare la deplasare.\n");
    }
}

char* sterge_spatiu_final(char* name) {
    char* sir = name;
    int lungime_sir = strlen(sir);
    while (lungime_sir > 0 && isspace((unsigned char)sir[lungime_sir - 1])) {
        lungime_sir--;
    }
    char* copie_sir = (char*)malloc((lungime_sir + 1) * sizeof(char));
    if (copie_sir == NULL) {
        printf("EROARE\n");
        exit(1);
    }
    strncpy(copie_sir, sir, lungime_sir);
    copie_sir[lungime_sir] = '\0';

    return copie_sir;
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
    if (lungime == 0 && cuv == EOF) {
        free(cuvant);
        return NULL;
    }
    return cuvant;
}

void cerinta1(FILE* fis_team, FILE* print) {
    echipa* lista_echipa;
    lista_echipa = creaza_echipa(fis_team);
    echipa* cap_lista = lista_echipa;
    while (cap_lista != NULL) {
        fprintf(print, "%s\r\n", cap_lista->name_team);
        cap_lista = cap_lista->next;
    }
    eliberare_lista(&lista_echipa);
    cap_lista=NULL;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

long long putere2(int n) {
    int m = 1;
    while (m <= n)
        m *= 2;
    m /= 2;
    return m;
}

void eliminare_echipa(int m, int* punctaj_echipe, echipa** head) {
    int i = 0;
    while (m > 0 && *head != NULL) {
        echipa* capat = *head;
        while (capat != NULL && m > 0) {
            if (capat->total_points == punctaj_echipe[i]) {
                echipa* urm = capat->next;
                elimina_nod(head, capat);
                capat = urm;
                m--;
            } else {
                capat = capat->next;
            }
        }
        i++;
    }
}

void cerinta2(FILE* fis_team, FILE* print, echipa** lista_ramasa, int* nr_echipe_ramase) {
    int nrechipe;
    if (fscanf(fis_team, "%d", &nrechipe) != 1) {
        printf("Eroare la citirea numarului de echipe.\n");
        exit(EXIT_FAILURE);
    }

    long long m = putere2(nrechipe);
    fseek(fis_team, 0, SEEK_SET);
    *nr_echipe_ramase = m;
    echipa* lista_echipa = creaza_echipa(fis_team);
    if (lista_echipa == NULL) {
        printf("Eroare: Lista de echipe este goala.\n");
        exit(EXIT_FAILURE);
    }

    echipa* cap_lista = lista_echipa;
    echipa* current_lista_ramasa = NULL;
    *lista_ramasa = NULL;
    int* punctaj_echipe = (int*)malloc(nrechipe * sizeof(int));
    if (punctaj_echipe == NULL) {
        printf("Eroare la alocarea memoriei pentru punctajele echipelor.\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (cap_lista != NULL) {
        punctaj_echipe[i] = cap_lista->total_points;
        cap_lista = cap_lista->next;
        i++;
    }

    quickSort(punctaj_echipe, 0, nrechipe - 1);
    eliminare_echipa(nrechipe - m, punctaj_echipe, &lista_echipa);

    int nr = 0;
    cap_lista = lista_echipa;
    while (cap_lista != NULL) {
        fprintf(print, "%s\r\n", cap_lista->name_team);
        if (*lista_ramasa == NULL) {
            *lista_ramasa = (echipa*)malloc(sizeof(echipa));
            if (*lista_ramasa == NULL) {
                printf("Eroare la alocarea memoriei pentru lista de echipe ramase.\n");
                exit(EXIT_FAILURE);
            }
            **lista_ramasa = *cap_lista;
            (*lista_ramasa)->next = NULL;
            current_lista_ramasa = *lista_ramasa;
        } else {
            current_lista_ramasa->next = (echipa*)malloc(sizeof(echipa));
            if (current_lista_ramasa->next == NULL) {
                printf("Eroare la alocarea memoriei pentru lista de echipe ramase.\n");
                exit(EXIT_FAILURE);
            }
            *(current_lista_ramasa->next) = *cap_lista;
            current_lista_ramasa = current_lista_ramasa->next;
            current_lista_ramasa->next = NULL;
        }
        cap_lista = cap_lista->next;
        nr++;
    }
    eliberare_lista(&lista_echipa);
    free(punctaj_echipe);
}

void adauga_spatii(FILE *f, int numar_spatii) {
    for (int i = 0; i < numar_spatii; ++i) {
        fprintf(f, " ");
    }
}

echipa* echipe_castigatoare_print(FILE* print, node* stiva_castigatori,int nr,int* calc,int* ok)
{
    echipa* lista=NULL;
    int gaps=42, ad=2;
    while(!isEmptystack(stiva_castigatori))
    {
            node_aux* castigator_aux = top(stiva_castigatori);
            if (castigator_aux == NULL) {
                printf("Eroare la obtinerea castigatorului\n");
                return NULL;
            }
            echipa* castigator = castigator_aux->t;
            float rez=(float)(castigator->total_points)/(castigator->number_players);
            rez=rez+nr;
            fprintf(print,"%-34s-  %.2f",castigator->name_team,rez);
            if(*ok==0)
                fprintf(print,"\r\n");
            echipa* copie_echipa = (echipa*)malloc(sizeof(echipa));
            if (copie_echipa == NULL) {
                printf("Eroare la alocarea memoriei pentru echipa.\n");
                exit(1);
            }
            copie_echipa->name_team = strdup(castigator->name_team);
            copie_echipa->number_players = castigator->number_players;
            copie_echipa->total_points = castigator->total_points;
            copie_echipa->player = (jucator*)malloc(castigator->number_players * sizeof(jucator));
            for (int i = 0; i < castigator->number_players; i++) {
                copie_echipa->player[i].firstName = strdup(castigator->player[i].firstName);
                copie_echipa->player[i].secondName = strdup(castigator->player[i].secondName);
                copie_echipa->player[i].points = castigator->player[i].points;
            }
            adauga_la_sfarsit(&lista, copie_echipa);
            *calc=*calc+1;
            pop(&stiva_castigatori);
            free(castigator_aux);
    }
    return lista;
}



void cerinta3(FILE* fis_team, FILE* print, echipa** lista_ramasa, int* nr_echipe,echipa** lista_arbore,int* r) {
    int nr = 1,ok=0;
    for (int i = 1; i < *nr_echipe; i = i * 2) {
        if(i==*nr_echipe/2) ok=1;
        node* stiva_castigatori = NULL;
        node* stiva_pierzatori = NULL;
        fprintf(print, "--- ROUND NO:%d\r\n", nr);
        echipa* copie1 = *lista_ramasa;
        creare_coada_runde(copie1, print, &stiva_castigatori, &stiva_pierzatori);
        echipa* copie = *lista_ramasa;
        echipa* lista_castigatori = eliminare_pierzatori(stiva_pierzatori, &copie);
        fprintf(print, "\r\n");
        
        fprintf(print, "WINNERS OF ROUND NO:%d\r\n", nr);
        int calc=0;
        echipa* ls=echipe_castigatoare_print(print, stiva_castigatori, nr,&calc,&ok);
        fprintf(print,"\r\n"); 
        if(calc==8)
        {
            *lista_arbore=lista_castigatori;
            *r=nr;
        }
        nr++;
        *lista_ramasa=ls;
    }
}

void cerinta4(FILE* print,echipa** lista_arbore,int* nr_echipe,int nr,echipa** lista_avl)
{
    fprintf(print,"\r\n");
    fprintf(print,"TOP 8 TEAMS:\r\n");
    BSTNode *root = NULL;
    echipa* cap=*lista_arbore;
    while(cap!=NULL) {
        root = insertBST(root, cap);
        cap=cap->next;
    }
    printBSTDesc(root, print,nr,lista_avl);
}

void cerinta5(FILE* print, echipa** lista_avl, int* nr_echipe) {
    AVLNode *root = NULL;
    echipa* cap=*lista_avl;
    while(cap!=NULL) {
        root = insertAVL(root, cap);
        cap=cap->next;
    }
    fprintf(print,"\n");
    fprintf(print, "THE LEVEL 2 TEAMS ARE: \n");
    printAVLDesc(root,0,print);
    freeAVL(root);
}
