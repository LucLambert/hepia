public class Exercice4_4{
    enum Boisson{
        BiereB("Bière Blanche", 4.5, 4.0),
        BiereA("Bière ambrée", 5.2, 5.0),
        Sauda("Sauda Cola", 0, 3.5),
        Whisky("Bière Blanche", 57.0, 9.0);
        
        private final String name;
        private final double alcohol;
        private final double price;
        
        private Boisson(String name, double alcohol, double price){
            this.name = name;
            this.alcohol = alcohol;
            this.price = price;
        }

        public boolean isAlcoholic(){
            return this.alcohol != 0;
        }
        public double alcoholLevel(){
            return this.alcohol;
        }
        public double price(){
            return this.price;
        }
        public static void display(Boisson b){
            if(b.isAlcoholic()){
                System.out.println("Contrôle d'âge nécessaire.");
                if(b.alcoholLevel() < 6.0){
                    System.out.println("La personne doit avoir 16 ans révolus.");
                }
                else{
                    System.out.println("La personne doit avoir 18 ans révolus.");
                }
            }else{
                System.out.println("Bravo !");
            }
            System.out.println(b.name + " : " + b.price + "$");
        }
    }

    public static void main(String[] args){
        Boisson.display(Boisson.Sauda);
    }
}