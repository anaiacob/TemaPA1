#include "functii.h"

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
            fprintf(print,"%-33s-%33s",t1->name_team,t2->name_team);
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