#include "functii.h"
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
        if (strcmp(echip->name_team, node->t->name_team) >= 0) {
            node->right = insertAVL(node->right, echip);
        } else {
            node->left = insertAVL(node->left, echip);
        }
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);
//primele 2 strcmp
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

    if(balance>1 && echip->total_points==node->left->t->total_points)
    {
        if(strcmp(echip->name_team,node->left->t->name_team)<0)
            return rotateRight(node);
        else return rotateLeft(node);
    }
    if(balance<-1 && echip->total_points==node->right->t->total_points)
    {
        if(strcmp(echip->name_team,node->right->t->name_team)<0)
            return rotateLeft(node);
        else return rotateRight(node);
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
            fprintf(print,"%s\r\n",root->t->name_team);
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