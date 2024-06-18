## Dans l'exemple ci-dessous, déterminez pourquoi l'utilisation de l'opérateur *instanceof* au lieu de la méthode *getClass* est problématique. Pour vois aider, imaginez un cas ou la propriété symétrique de la relation n'est pas respectée

```java
class Person{
    protected int id;
    protected String name;
    public Person(int id, String name){
        this.id = id; this.name = name;
    }
    @Override public String toString(){
        return "Person("+this.id+", "+this.name+")";
    }
    @Override public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || !(o instanceof Person)){
            return false;
        }
        Person p = (Person o);
        return p.id == this.id && p.name.equals(this.name);
    }
}

class Patient extends Person{
    private String room;
    public Patient(int id, String name, String room){
        super(id, room);
        this.room = room;
    }
    @Override public String toString(){
        return "Patient("+this.id+", " this.name + ", " + room + ")";
    }
    @Override public boolean equals(Object o){
        if(this == o)return true;
        if(o == null || !(o instanceof Patient)){
            return false;
        }
        Patient p = (Patient)o;
        return p.id == this.id && p.name.equals(this.name) && this.room.equals(p.room);
    }
}
```

l'utilisation de *instanceof* pose problème car si on a :
```java
Person p = new Patient(0, "Toto", "Cuisine");
Patient p2 = new Patient(0, "Toto", "Cuisine");
```

p.equals(p2) va retourner false. car p n'est pas une instance de p2. C'est p2 qui est une instance de p. Alors que la méthode getClass retourne la class de l'objet pointé tandis que instanceof retourne true si la class de la référence dépend d'une classe au-dessus.