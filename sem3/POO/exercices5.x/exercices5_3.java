//realiser avec Thibault Chatillon
class exercices5_3{

}
interface Transport {
    /**
    * Prend un conteneur du transport
    * @return le prochain conteneur. Retourne une exception s'il n'y
    * a plus de conteneur
    */
    public Container takeNext();
}

interface Article {
    /**
    * Calcul le prix de l'article
    * @return le prix de l'article
    */
    public double price();
}

class Car implements Article {
    private String brand;
    private double price;
    
    public Car(String brand, double price) {
        this.brand = brand;
        this.price = price;
    }
    // A compléter
    @Override 
    public double price(){
        return this.price;
    }
}

class Container {
    private Article[] articles;
    public Container(Article[] articles){
    // A compléter
        this.articles = articles;
    }
    public double totalPrice() {
    // A compléter
        double res=0;
        for( Article a : this.articles){
            res += a.price();
        }
        return res;
    }
}
class Boat implements Transport {
    private Container[] containers;
    private String name;
    private int i=0;
    public Boat(String name, Container[] containers) {
    // A compléter
        this.name = name;
        this.containers = containers;
    }
    // A compléter
    @Override
    public Container takeNext(){
        if(i>this.containers.length-1){
            throw new RuntimeException("Il n'y a plus de Conteneur.");
        }
        return this.containers[i++];
    }
}