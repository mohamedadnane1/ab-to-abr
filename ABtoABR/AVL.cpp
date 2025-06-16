#include<iostream>
#include <stack>
#include <fstream>
using namespace std;

#include"AVL.h"

noeud::noeud(int n)
{
    cle = n;
    fg = NULL;
    fd = NULL;
    pere = NULL;
    N = 1; 
    h = 0; 
    d = 0; 
}

noeud::~noeud(){
    delete(fg);
    delete(fd);
}
AVL::AVL(noeud* r){
    this->r = r;
}
AVL::~AVL(){
    delete(r);
}

void AVL::prefixe(noeud* x){
    if(x){
        cout<<" clé:"<<x->cle<<"  ( N:"<<x->N<<"   d:"<<x->d<<"   h:"<<x->h<<" )"<<endl;
        if(x->fg){
            cout<<" clé_fg:"<<x->fg->cle<<"    ";
        }
        if(x->fd){
            cout<<" clé_fd:"<<x->fd->cle;
        }
        cout<<endl;
        
        cout<<" ----------------------------- "<<endl;
        prefixe(x->fg);
        prefixe(x->fd);
    } 
}
void AVL::prefixe() {
	prefixe(r);
}


void AVL::inserer_feuille(noeud * x, noeud *b){
    noeud* a = x;
    noeud* pere = NULL;
    if(a == NULL){
        r = b;
        return;
    }
    while(a){
        pere = a;
        if(b->cle <= a->cle){ 

            a = a->fg;
        }
        else{
            a = a->fd;
        }
    }
    b->pere = pere;
    if(b->pere == NULL){
        r = b;
    }
    if(b->cle < pere->cle){
        pere->fg = b;
    }
    else{
        pere->fd = b;
    }
}


void AVL::inserer_racine(noeud * a, noeud *b){

    if(a == NULL){
        r = b;
        return;
    }
    else{
        if(b->cle < a->cle){
            if(a->fg == NULL){
                a->fg = b;
                }
            else{
                inserer_racine(a->fg,b);
            }
            rotationDroite(a);
        }
        else{
            if(a->fd == NULL){
                a->fd = b;
                }
            else{
                inserer_racine(a->fd,b);
            }
            rotationGauche(a);
        }
    }

}
AVL::AVL(char* filename, bool option) {
    this->r = nullptr;

    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    int numIntegers;
    file >> numIntegers;

    for (int i = 0; i < numIntegers; i++) {
        int info;
        file >> info;
        noeud* nouveau = new noeud(info);

        if (option) {
            inserer_feuille(r, nouveau);
        } else {
            inserer_racine(r, nouveau);
        }
    }
    hauteur();
    desequilibres();
    nb_noeuds();
    file.close();
}


void noeud::affiche() {

}
// fonction rotation (vu en TP)
void AVL::rotationDroite(noeud* x) {
    if (x == NULL || x->fg == NULL) {
        return;
    }
    noeud* G = x->fg;
    G->pere = x->pere;
    x->fg = G->fd;
    if (G->fd) {
        G->fd->pere = x;
    }
    G->fd = x;
    if (x->pere) {
        if (x->pere->fg == x) {
            x->pere->fg = G;
        } else {
            x->pere->fd = G;
        }
    } else {
        r = G;
    }
    x->pere = G;
    x->h = hauteur(x);
    G->h = hauteur(G);
}
void AVL::rotationDroite() {
    rotationDroite(r);
}
// fonction rotation (vu en TP)
void AVL::rotationGauche(noeud* x) {
    if (x == NULL || x->fd == NULL) {
        return;
    }
    noeud* G = x->fd;
    G->pere = x->pere;
    x->fd = G->fg;
    if (G->fg) {
        G->fg->pere = x;
    }
    G->fg = x;
    if (x->pere) {
        if (x->pere->fd == x) {
            x->pere->fd = G;
        } else {
            x->pere->fg = G;
        }
    } else {
        r = G;
    }
    x->pere = G;
    x->h = hauteur(x);
    G->h = hauteur(G);
}
void AVL::rotationGauche() {
    rotationGauche(r);
}

// fonction partition (du TD)
noeud* AVL::partition(noeud* x, int k) {
    x->h = hauteur(x);
    desequilibres();
    nb_noeuds();
    if (x == NULL) {
        return NULL;
    }
    noeud* res = NULL;
    int t = 0;
    if (x->fg) {
        t = x->fg->N;
    }
    if (t == k - 1) {
        res = x;
    } else {
        if (t > k - 1) {
            res = partition(x->fg, k);
            rotationDroite(x);
        } else {
            res = partition(x->fd, k-t-1);
            rotationGauche(x);
        }
    }
    x->h = hauteur(x);
    desequilibres();
    nb_noeuds();
    return res;
}
// change la valeur de h de chaque noeud de l'arbre 
int AVL::hauteur(noeud* x) {
    if (x == NULL) {
        return -1; 
    }

    int HGauche = hauteur(x->fg);
    int HDroite = hauteur(x->fd);

    if(HGauche >= HDroite){
        x->h = 1 + HGauche;
        return 1 + HGauche;
    } 
    else{
        x->h = 1 + HDroite;
        return 1 + HDroite; 
    }
}
void AVL::hauteur() {
   hauteur(r);
}


// change la valeur de N de chaque noeud de l'arbre 
int AVL::noeuds(noeud* x) {
    if (x == NULL) {
        return 0;
    }
    int NGauche = noeuds(x->fg);
    int NDroite = noeuds(x->fd);

    x->N = NGauche + NDroite + 1;

    return x->N;
}

void AVL::nb_noeuds() {
   noeuds(r);
}


// change la valeur de d de chaque noeud de l'arbre 
void AVL::desequilibres(noeud* x) {
    if (x == NULL) {
        return;
    }

    int DGauche = hauteur(x->fg);
    int DDroite = hauteur(x->fd);

    x->d = DGauche - DDroite;

    desequilibres(x->fg);
    desequilibres(x->fd);
}
void AVL::desequilibres() {
   desequilibres(r);
}


// équilibre arbre (fonction du TD)
void AVL::equilibre(noeud* x) {
   
    desequilibres();
    nb_noeuds();
    if (x != nullptr && x->N >= 1) {
        int n = x->N;
        int m = (n+1) / 2;
        partition(x, m);
        equilibre(x->fg);
        equilibre(x->fd);
    }
}

//verifier si l'arbre est est desiquilibré
bool AVL::est_desiquilibre(noeud* x){
    if(x){
        x->h = hauteur(x);
        desequilibres();
        if(x->d <=-2 || x->d >=2 ){
            return true;
        }
        est_desiquilibre(x->fg);
        est_desiquilibre(x->fd);
    } 
    return false;
}

// tant que arbre est désiquilibré alors équilibrer
void AVL::equilibre(){
    while(est_desiquilibre(r)){
        equilibre(r);
        equilibre(r);
    }

}