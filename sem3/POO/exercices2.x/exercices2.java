// 02_exercices.java
import java.time.LocalDate;
import java.util.List;
import java.util.ArrayList;

public class exercices2 {
    
    public static void main(String[] args) {

        //double d = minMaxRange(-4.3,0.0,3.0);
        //double d = normalize(-1.0,0.0,1.0,500.0,600.0);
        // List<List<Double>> alt = new ArrayList<>();
        // int size = random(5,10);
        // for(int i = 0; i<size; i++){
        //     alt.add(random(size,500.0,600.0));
        // }
        // List<List<Double>> grey = altitudeToShadesOfGray(alt);
        // System.out.println(grey);
        // System.out.println(alt);
        System.out.println(check("_____","samis",'s'));
    }

    private static double minMaxRange(double value, double minValue, double maxValue){
        return Math.max(Math.min(value,maxValue), minValue);
    }
    
    private static double normalize(double value, double minSource, double maxSource, double minTarget, double maxTarget){
        if(value != minMaxRange(value, minSource, maxSource))
            throw new RuntimeException("valeur en dehors de la Source");
        return (maxTarget-minTarget)/(maxSource-minSource)*(value-minSource) + minTarget;
    }

    private static double random(double minValue, double maxValue){
        return normalize(Math.random(),0.0,1.0,minValue,maxValue);
    }

    private static int random(int minValue, int maxValue){
        return (int)Math.floor(random((double)minValue, (double)maxValue));
    }

    private static List<Double> random(int nb, double minValue, double maxValue){
        List<Double> d = new ArrayList<>();
        for(int i = 0; i < nb; i++){
            d.add(random(minValue,maxValue));
        }
        return d;
    }

    private static List<Integer> random(int nb, int minValue, int maxValue){
        List<Integer> d = new ArrayList<Integer>();
        for(int i = 0; i < nb; i++){
            d.add(random(minValue,maxValue));
        }
        return d;
    }

    private static double min(List<List<Double>> lst){
        double min = lst.get(0).get(0);
        for(List<Double> l : lst){
            for(Double d : l){
                if(d < min){
                    min = d;
                }
            }
        }
        return min;
    }

    private static double max(List<List<Double>> lst){
        double max = lst.get(0).get(0);
        for(List<Double> l : lst){
            for(Double d : l){
                if(d > max){
                    max = d;
                }
            }
        }
        return max;
    }
    
    private static List<List<Double>> altitudeToShadesOfGray(List<List<Double>> altitudes){
        List<List<Double>> shadesOfGray = new ArrayList<>();
        List<Double> tmp = new ArrayList<>();

        for(List<Double> lst : altitudes){
            for(Double d : lst){
                tmp.add(normalize(d,min(altitudes), max(altitudes),0.0,255.0));
            }
            shadesOfGray.add(tmp);
            tmp = new ArrayList<>();
        }
        return shadesOfGray;
    }

    //ex 11
    /* Retourne une nouvelle liste où toutes les valeurs sont doublées */
    public static List<Integer> doubleThat(List<Integer> is) {
        List<Integer> tmp = new ArrayList<>();
        for(int i : is){
            tmp.add(i*2);
        }
        return tmp;
    }
    /* Retourne une nouvelle liste où toutes les valeurs sont plus grandes ou
    égale à un seuil */
    public static List<Integer> filterGreaterOrEqual(List<Integer> is, int value) {
        List<Integer> tmp = new ArrayList<>();
        for(int i : is){
            if(i >= value)
                tmp.add(i);
        }
        return tmp;
    }
    /* Retourne une nouvelle liste où toutes les valeurs positives sont
    multipliées par deux. Les valeurs négatives sont omises */
    public static List<Integer> filterPositiveAndThenDoubleThem(List<Integer> is) {
    // Faites simple, ne cherchez pas l'efficacité
        List<Integer> tmp = new ArrayList<>();
        for(int i : is){
            if(i>0)
                tmp.add(i*2);
        }
        return tmp;
    }

    /**
    Exercice 2.14
    * Supprime une lettre d'une chaîne de caractères
    * removeFirstOccurrence("abracadabra", 'a') retournerait "bracadabra"
    * removeFirstOccurrence("babar", 'r') retournerait "baba"
    * removeFirstOccurrence("babar", 'z') retournerait "babar"
    * removeFirstOccurrence("", 'r') retournerait ""
    */
    public static String removeFirstOccurrence(String s, char letter) {
        /* méthode fournie */
        /* Rien à faire ici */
        return "";
    }
    /**
    * Retourne true si la lettre se trouve dans le mot
    * contains("babar", 'z') retournerait false
    * contains("babar", 'a') retournerait true
    * contains("", 'a') retournerait false
    */
    public static boolean contains(String s, char letter) {
    /* méthode fournie */
    /* Rien à faire ici */
    return true;
    }
    /**
    * Supprime toutes les occurrences d'une lettre dans un mot.
    * Retourne la version sans occurrence.
    * removeAll("abracadabra", 'a') retournerait "brcdbr"
    * removeAll("salsa", 's') retournerait "ala"
    * removeAll("biere", 's') retournerait "biere"
    */

    public static String removeAll(String s, char letter){
        while(contains(s, letter)){
            s = removeFirstOccurrence(s, letter);
        }
        return s;
    }

    //Ex 2.10
    //check("___", "lolu", l) return l_l_
    public static String check(String currentWord, String guessWord, char letter){
        String s = "";
        for (int i = 0; i < currentWord.length(); i++){
            if(guessWord.charAt(i) == letter){
                s += guessWord.charAt(i);
            }else{
                s += currentWord.charAt(i);
            }
        }
        return s;
    }
}