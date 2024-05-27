#include "functii.h"
//este ok
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
void eliberare_lista(echipa** head)
{
    echipa* nod=*head;
    while(nod!=NULL)
    {
        //free(nod->name_team);
        //free(nod->total_points);
        for(int i=0;i<nod->number_players;i++)
        {
            free(nod->player[i].firstName);
            free(nod->player[i].secondName);
            //free(nod->player[i].points);
        }
        free(nod);

        nod= nod->next;

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
    /*for(int i=lungime-2;i>=0;i--)
    {
        if(linie[i]==' ')
        {
            linie[i]='\0';
        }
        else break;
    }*/
    return linie;
}
//este ok
void omitere_spatiu(FILE* f, long poz) {
    if (fseek(f, poz, SEEK_CUR) != 0) {
        printf("Eroare la deplasare.\n");
    }
}
//?
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
        nume_echipa=sterge_spatiu_final(nume_echipa);
        //printf("%s\n",nume_echipa);
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
        //printf("%d\n",total);
        adauga_la_inceput_lista(&lista_echipa, nume_echipa, nr_jucatori, total, p);
        free(nume_echipa);
        free(p);
    }
    return lista_echipa;
}

void cerinta1(FILE* fis_team, FILE* print) {
    echipa* lista_echipa;
    lista_echipa = creaza_echipa(fis_team);
    echipa* cap_lista = lista_echipa;
    while (cap_lista != NULL) {
        fprintf(print, "%s\r\n", cap_lista->name_team);
        cap_lista = cap_lista->next;
    }
    //free(lista_echipa);
    eliberare_lista(&lista_echipa);
    cap_lista=NULL;
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

    //printf("%d\n", nr);
    eliberare_lista(&lista_echipa);
    free(punctaj_echipe);
}


Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void deleteQueue(Queue* q) {
    Node* aux;
    while (!isEmpty(q)) {
        aux = q->front;
        q->front = q->front->urm;
        free(aux);
    }
    free(q);
}

void enQueue(Queue* q, echipa* echipa1) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei pentru newNode\n");
        exit(EXIT_FAILURE);
    }
    newNode->team1 = echipa1;
    newNode->urm = NULL;
    if (q->rear == NULL) {
        q->rear = newNode;
        q->front = newNode;
    } else {
        q->rear->urm = newNode;
        q->rear = newNode;
    }
}


void deQueue(Queue* q, echipa** t1) {
    if (isEmpty(q)) {
        *t1 = NULL;
        return;
    }

    Node* aux = q->front;
    *t1 = aux->team1;
    q->front = q->front->urm;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(aux);
}


void adauga_spatii(FILE *f, int numar_spatii) {
    for (int i = 0; i < numar_spatii; ++i) {
        fprintf(f, " ");
    }
}

int isEmptystack(node* top) {
    return top == NULL;
}

void deleteStack(node** top) {
    node* temp;
    while (*top != NULL) {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

node_aux* pop(node** top) {
    if (isEmptystack(*top)) {
        return NULL;
    }
    node* temp = *top;
    node_aux* aux = (node_aux*)malloc(sizeof(node_aux));
    if (aux == NULL) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru node_aux\n");
        exit(EXIT_FAILURE);
    }
    aux->t = temp->t;
    *top = (*top)->next;
    free(temp);
    return aux;
}

void push(node** top, echipa* echip) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru node\n");
        exit(EXIT_FAILURE);
    }
    newNode->t = echip;
    newNode->next = *top;
    *top = newNode;
}

node_aux* top(node* top) {
    if (isEmptystack(top)) {
        return NULL;
    }
    node_aux* aux = (node_aux*)malloc(sizeof(node_aux));
    if (aux == NULL) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru node_aux\n");
        exit(EXIT_FAILURE);
    }
    aux->t = top->t;
    return aux;
}



echipa* eliminare_pierzatori(node* stiva_pierzatori, echipa** lista) {
    echipa* list_ramas = NULL;
    echipa* last_ramas = NULL;
    //echipa* l=lista;
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

void creare_coada_runde(echipa* lista, FILE* print, node** stiva_castigatori, node** stiva_pierzatori) {
    echipa* cap_lista = lista;
    Queue* coada = createQueue();
    if (coada == NULL) {
        fprintf(stderr, "Eroare la crearea cozii\n");
        exit(EXIT_FAILURE);
    }
    while (cap_lista != NULL) {
        enQueue(coada, cap_lista);
        cap_lista = cap_lista->next;
    }

    while (!isEmpty(coada)) {
        echipa* t1, * t2;
        deQueue(coada, &t1);
        deQueue(coada,&t2);
        if (t1 != NULL && t2 != NULL) {
            int l1 = strlen(t1->name_team);
            int l2 = strlen(t2->name_team);
            int lungime_ap = 68;
            /*fwrite(t1->name_team,sizeof(t1->name_team[0]),strlen(t1->name_team),print);
            adauga_spatii(print,lungime_ap/2-l1-1);
            fprintf(print,"-");
            adauga_spatii(print,lungime_ap/2-l2-1);
            fwrite(t2->name_team,sizeof(t2->name_team[0]),strlen(t2->name_team),print);
            fprintf(print,"\n");
            */
            fprintf(print,"%-33s-%33s",t1->name_team,t2->name_team);
            //fputc('\r\n',print);
            fprintf(print,"\r\n");
            if ((float)t1->total_points / t1->number_players > (float)t2->total_points / t2->number_players) {
                push(stiva_castigatori, t1);
                push(stiva_pierzatori, t2);
            } else if((float)t1->total_points / t1->number_players <= (float)t2->total_points / t2->number_players){
                push(stiva_castigatori, t2);
                push(stiva_pierzatori, t1);
            }
        }
    }
    deleteQueue(coada);
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
            /*fprintf(print, "%s", castigator->name_team);
            adauga_spatii(print,gaps-8-strlen(castigator->name_team));
            fprintf(print,"%c",'-');
            adauga_spatii(print,ad);*/
            float rez=(float)(castigator->total_points)/(castigator->number_players);
            rez=rez+nr;
            fprintf(print,"%-34s-  %.2f",castigator->name_team,rez);
            //fputc('\r\n',print);
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
        //printf("OK\n");
        //printf("%d\n",calc);
        //printf("%d\n",nr);
        if(calc==8)
        {
            *lista_arbore=lista_castigatori;
            *r=nr;
        }
        nr++;
        //*lista_ramasa=lc;
        *lista_ramasa=ls;
        
    }

}


BSTNode* createNode(echipa* echip) {
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->t = echip;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insertBST(BSTNode *root, echipa* echip) {
    if (root == NULL) {
        return createNode(echip);
    }

    if (echip->total_points > (root->t)->total_points) {
        root->right = insertBST(root->right, echip);
    } else if (echip->total_points < (root->t)->total_points) {
        root->left = insertBST(root->left, echip);
    } else {
        if (strcmp(echip->name_team, (root->t)->name_team) > 0) {
            root->right = insertBST(root->right, echip);
        } else {
            root->left = insertBST(root->left, echip);
        }
    }

    return root;
}

void printBSTDesc(BSTNode *root, FILE *print,int nr) {
    if (root == NULL) {
        return;
    }

    printBSTDesc(root->right, print,nr);
    int gaps=42,add=2;
    float rez=(float)root->t->total_points/root->t->number_players+nr;
    fwrite(root->t->name_team,sizeof(root->t->name_team[0]),strlen(root->t->name_team),print);
    adauga_spatii(print,gaps-7-strlen(root->t->name_team)-1);
    fprintf(print,"-");
    adauga_spatii(print,add);
    fprintf(print,"%.2f\r\n",rez);
    //fprintf(print, "%s %.2f\n", root->t->name_team, (float)root->t->total_points/root->t->number_players+nr);
    printBSTDesc(root->left, print,nr);
}

void cerinta4(FILE* print,echipa** lista_arbore,int* nr_echipe,int nr)
{
    fprintf(print,"\r\n");
    fprintf(print,"TOP 8 TEAMS:\r\n");
    BSTNode *root = NULL;
    echipa* cap=*lista_arbore;
    while(cap!=NULL) {
        root = insertBST(root, cap);
        cap=cap->next;
        //lista_arbore=lista_arbore->next;
    }

    printBSTDesc(root, print,nr);
}


AVLNode* createNodeAVL(echipa* echip) {
    AVLNode *newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->t = echip;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

AVLNode* rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

AVLNode* insertAVL(AVLNode *node, echipa* echip) {
    if (node == NULL) {
        return createNodeAVL(echip);
    }

    if (echip->total_points > node->t->total_points) {
        node->right = insertAVL(node->right, echip);
    } else if (echip->total_points < node->t->total_points) {
        node->left = insertAVL(node->left, echip);
    } else {
        if (strcmp(echip->name_team, node->t->name_team) > 0) {
            node->right = insertAVL(node->right, echip);
        } else {
            node->left = insertAVL(node->left, echip);
        }
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && echip->total_points < node->left->t->total_points) {
        return rotateRight(node);
    }

    if (balance < -1 && echip->total_points > node->right->t->total_points) {
        return rotateLeft(node);
    }

    if (balance > 1 && echip->total_points > node->left->t->total_points) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && echip->total_points < node->right->t->total_points) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void printLevel2(AVLNode *root, int level, FILE *print) {
    if (root == NULL) {
        return;
    }
    //printf("%s  %d\n",root->t->name_team,level);
    if (level == 2) {
        //fprintf(print, "%s %.2f\n", root->t->name_team, root->echipa.punctaj);
        fprintf(print,"%s\n",root->t->name_team);
    } else { //<
        printLevel2(root->left, level + 1, print);
        printLevel2(root->right, level + 1, print);
    }
    //printf("%s  %d\n",root->t->name_team,level);
}
void printAVLDesc(AVLNode *root,int level, FILE *print) {
    if (root != NULL) {
            //printf("%s  %d\n",root->t->name_team,level);
        if(level==2)
        {
            fprintf(print,"%s\n",root->t->name_team);
        }
        printAVLDesc(root->right,level+1, print);
        //fprintf(outFile, "%s %.2f\n", root->echipa.nume, root->echipa.punctaj);
        printAVLDesc(root->left,level+1, print);
    }
}
void freeAVL(AVLNode *root) {
    if (root == NULL) {
        return;
    }

    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
}

void cerinta5(FILE* print, echipa** lista_arbore, int* nr_echipe) {
    AVLNode *root = NULL;

    echipa* cap=*lista_arbore;
    while(cap!=NULL) {
        root = insertAVL(root, cap);
        //printf("%s\n",cap->name_team);
        cap=cap->next;
        //lista_arbore=lista_arbore->next;
    }
    fprintf(print,"\n");
    fprintf(print, "THE LEVEL 2 TEAMS ARE: \n");
    //printLevel2(root, 0, print);
    printAVLDesc(root,0,print);
    freeAVL(root);
}
