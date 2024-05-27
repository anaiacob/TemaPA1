#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

struct Node
{
    //echipa* team1;
    echipa* team1;
    struct Node* urm;
};
typedef struct Node Node;
struct Queue
{
    Node* front,*rear;
};
typedef struct Queue Queue;

struct node
{
    echipa* t;
    struct node* next;
};
typedef struct node node;
struct Node_aux
{
    echipa* t;
};
typedef struct Node_aux node_aux;
struct BSTNode {
    echipa* t;
    struct BSTNode *left;
    struct BSTNode *right;
};
typedef struct BSTNode BSTNode;
struct AVLNode {
    echipa* t;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};
typedef struct AVLNode AVLNode;
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
void cerinta2(FILE* fis_team, FILE* print,echipa** lista_ramasa,int* nr_echipe_ramase);
void eliberare_lista(echipa** head);
void cerinta3(FILE* fis_team, FILE* print, echipa** lista_ramasa,int* nr_echipe,echipa** lista_arbore,int* r);
Queue* createQueue();
int isEmpty(Queue*q);
void deleteQueue(Queue*q);
void enQueue(Queue*q, echipa* echipa1);
void deQueue(Queue*q,echipa** t1);
void creare_coada_runde(echipa* lista,FILE* print,node** stiva_castigatori,node** stiva_pierzatori);
void adauga_spatii(FILE *f, int numar_spatii);
int isEmptystack(node*top);
void deleteStack(node**top);
node_aux* pop(node**top);
void push(node**top, echipa* echip);
node_aux* top(node *top);
echipa* eliminare_pierzatori(node* stiva_pierzatori, echipa** lista);
echipa* echipe_castigatoare_print(FILE* print, node* stiva_castigatori,int nr,int* calc,int* ok);
//void inversare_lista(echipa* cap_initial,echipa** cap_inversat);
void adauga_la_sfarsit(echipa** cap, echipa* val);
char* sterge_spatiu_final(char* name);
BSTNode* createNode(echipa* echip);
BSTNode* insertBST(BSTNode *root, echipa* echip);
void printBSTDesc(BSTNode *root, FILE *print,int r);
void cerinta4(FILE* print,echipa** lista_arbore,int* nr_echipe,int r);
AVLNode* createNodeAVL(echipa* echip);
int getHeight(AVLNode *node);
int getBalance(AVLNode *node);
AVLNode* rotateRight(AVLNode *y);
AVLNode* rotateLeft(AVLNode *x);
AVLNode* insertAVL(AVLNode *node, echipa* echip);
void printLevel2(AVLNode *root, int level, FILE *print);
void freeAVL(AVLNode *root);
void printAVLDesc(AVLNode *root,int level, FILE *print);
void cerinta5(FILE* print, echipa** lista_arbore, int* nr_echipe);
