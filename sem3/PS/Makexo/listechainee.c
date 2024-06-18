#include "listechainee.h"
#include <stddef.h>
#include <stdlib.h>

/*Déclaration dans le .c pour une
utilisation privée */
typedef struct el {
  struct el *suivant;
  void *contenu;
} element_t;

typedef element_t* listeChainee;

listeChainee initListeChaineeVide() {
  return NULL;
}

void addListe(listeChainee* liste, void* contenu) {
  //Creation d'un element et ajout dans la liste
  element_t *unEl = (element_t*) malloc(sizeof(element_t));
  unEl->contenu = contenu; //(*unEl).contenu se transforme en unEl->contenu
  unEl->suivant = *liste;
  *liste = unEl;
}

void* removeListe(listeChainee *liste) {
  listeChainee tmp;
  void* ret;

  ret = (*liste)->contenu;
  tmp = *liste;
  *liste = tmp->suivant;
  free(tmp); //Libération de la mémoire
  return ret;
}