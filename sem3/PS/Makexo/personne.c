#include "personne.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


struct personne createPersonne(const char* nom, const char* prenom, int age) {
  int length;
  struct personne pers;

  length = strlen(nom) + 1; //+1 pour '\0'
  pers.nom = calloc(length, sizeof(char));
  pers.prenom = calloc(strlen(prenom) + 1, sizeof(char));
  if((pers.nom == NULL) || (pers.prenom == NULL)) {
    printf("Erreur allocation mémoire\n");
    exit(1);
  }
  strcpy(pers.nom, nom);
  strcpy(pers.prenom, prenom);
  pers.age = age;
  return pers;
}

void affichePersonne(struct personne pers) {
  printf("Nom: %s, Prenom: %s, Age: %d\n", pers.nom, pers.prenom, pers.age);
}