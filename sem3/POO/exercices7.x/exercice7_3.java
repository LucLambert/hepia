import java.util.function.Supplier;
import java.util.Optional;

public class exercice7_3 {

    public static Optional<Integer> test(Supplier<Integer> sup){
        try{
            return Optional.of(sup.get());
        }
        catch(Exception e){
            return Optional.empty();
        }  
    }

    public static void main(String[] args) {
        System.out.println(test( () -> 3 )); // retourne Optional contenant 3
        System.out.println(test( () -> 3 + 4 )); // retourne Optional contenant 7
        System.out.println(test( () -> 3 / 0 )); // retourne Optional vide
        System.out.println(test( () -> null )); // retourne Optional vide
        System.out.println(test( () -> {
            throw new RuntimeException();
        })); // retourne un Optional vide
    }

}