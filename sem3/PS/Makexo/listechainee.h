#ifndef _LISTECHAINEE_H
#define _LISTECHAINEE_H

// Anciennement typedef element_t* listeChainee;
typedef struct el* listeChainee;

listeChainee initListeChaineeVide();
void addListe(listeChainee* liste, void* contenu);
void* removeListe(listeChainee *liste);

#endif