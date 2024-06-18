import java.util.*;
import java.util.NoSuchElementException;
import java.util.Optional;

public class ex2{

    interface HasId {
        String getId();
    }
    
    class User implements HasId {
        private String uniqueId;
        private int age;
        public User(String uniqueId, String name, int age) {
            this.uniqueId = uniqueId;
            this.age = age;
        }
        public String getId() { return uniqueId; }
    }
    
    record Patient(String getId, int room) implements HasId {}
    
    class Database<T extends HasId> {
        private Map<String, T> map = new HashMap<>(); // data structure of your choice to help you do the job
        public Optional<T> get(String id) { 
            if(map.containsKey(id))
                return Optional.of(map.get(id));
            return Optional.empty();
        }
        public T getOrThrows(String id) { 
            if(this.get(id).equals(Optional.empty()))
                throw new NoSuchElementException();
            return this.get(id);
        }
        public void insertOrReplace(T t) { 
            if(map.containsValue(t)){
                map.replace(t.uniqueId, this.getOrThrows(t), t);
            }else{
                map.put(t.uniqueId, t);
            }
        }
        public void insertOrThrows(T t) { 
            if(map.containsValue(t))
                throw new RuntimeException();
            map.put(t.uniqueId, t);
        }
    }
    
    public static void main(String[] args) {
        // should work
        Database<User> dbUser = new Database<>();
        Database<Patient> dbPatient = new Database<>();
        // should not work (String doesn't implement HasId)
        Database<String> dbUser = new Database<>();
    }
}