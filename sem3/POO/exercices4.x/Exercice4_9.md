## Soient le code ci-dessous:
```java
Person p1 = new Person(1, "Joel");
Person p2 = new Person(1, "Joel");
// Un ensemble ne peut contenir qu'un élément unique
// il ne peut pas y avoir d'éléments dupliqués
Set<Person> persons = new HashSet<Person>();
persons.add(p1);
persons.add(p2);
System.out.println("Size = " + persons.size());
```
## Si l’affichage est “Size = 2” au lieu de “Size = 1”, quel est le symptôme (répondez par vrai ou faux):
* La classe Person ne surcharge pas la méthode equals(Object o) ? Faux
* La classe Person ne redéfinit pas la méthode equals(Object o) ? Vrai
* La classe Person ne surcharge pas la méthode hashCode() ? Faux
* La classe Person ne redéfinit pas la méthode hashCode() ? Vrai
* La classe Person ne surcharge pas la méthode toString() ? Faux
* La classe Person ne redéfinit pas la méthode toString() ? Faux
