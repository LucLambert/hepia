#include "listechainee.h"
#include "personne.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    struct personne *ptPersonne;
    listeChainee maListe = initListeChaineeVide();

    //Une première personne ajoutée
    struct personne unePersonne = createPersonne("Rodepeter", "Jessica", 36);
    affichePersonne(unePersonne);
    addListe(&maListe, &unePersonne);

    //Une seconde personne ajoutée
    if((ptPersonne = malloc(sizeof(struct personne))) == NULL)
    {
        printf("Erreur mémoire\n");
        return 1;
    }
    *ptPersonne = createPersonne("Page", "Marc", 8);
    affichePersonne(*ptPersonne);
    addListe(&maListe, ptPersonne);

    //Recupère le contenu de la liste
    affichePersonne(*( (struct personne*) removeListe(&maListe)));
    affichePersonne(*( (struct personne*) removeListe(&maListe)));
    free(ptPersonne);

    return 0;
}