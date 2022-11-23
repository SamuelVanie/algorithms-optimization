#include <math.h>
#define TAILLE 100

int main(){

    int tab[100] = {0};

    int somme = 0;
    int somme_carres=0;
    for(int i=0; i<sizeof(tab)/sizeof(int); i++){
        somme += tab[i];
    }

    for(int i=0; i<sizeof(tab)/sizeof(int); i++){
        somme_carres += pow(tab[i], 2);
    }
}
