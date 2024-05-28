#include "functii.h"
BSTNode* createNodeBST(echipa* echip) {
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->t = echip;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insertBST(BSTNode *root, echipa* echip) {
    if (root == NULL) {
        return createNodeBST(echip);
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

void printBSTDesc(BSTNode *root, FILE *print,int nr,echipa** lista_avl) {
    if (root == NULL) {
        return;
    }

    printBSTDesc(root->right, print,nr,lista_avl);
    int gaps=42,add=2;
    float rez=(float)root->t->total_points/root->t->number_players+nr;
    fwrite(root->t->name_team,sizeof(root->t->name_team[0]),strlen(root->t->name_team),print);
    adauga_spatii(print,gaps-7-strlen(root->t->name_team)-1);
    fprintf(print,"-");
    adauga_spatii(print,add);
    fprintf(print,"%.2f\r\n",rez);
    echipa* castigator=root->t;
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
    adauga_la_sfarsit(lista_avl, copie_echipa);
    //fprintf(print, "%s %.2f\n", root->t->name_team, (float)root->t->total_points/root->t->number_players+nr);
    printBSTDesc(root->left, print,nr,lista_avl);
}
