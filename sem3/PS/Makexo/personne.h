#ifndef _PERSONNE_H
#define _PERSONNE_H

//Déclaration de la structure
struct personne {
  char* nom;
  char* prenom;
  int age;
};

struct personne createPersonne(const char* nom, const char* prenom, int age);

void affichePersonne(struct personne pers);

#endif