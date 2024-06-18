import java.util.NoSuchElementException;
import java.util.Random;
import java.util.function.Consumer;

public class StatusApp{

    public static void log(Object o) { System.out.println(o); }

    public static Status<Integer, String> random() {
        int chance = new Random().nextInt(3);
        if( chance == 0 ) {
            return Status.onWith(42);
        } else {
            return chance == 1 ? Status.off() : Status.errorWith("Oups");
        }
    }
    public static void main(String[] args) {
        Status<Integer, String> s = random();
        if( s.isOn() ) {
            int i = s.get();
            log("Status On: " + i);
        } else if( s.isError() ) {
            String msg = s.getError();
            log("Status Unstable: " + msg);
        } else {
            log("Status Off");
        }
        s.accept( 
            (Integer i) -> log("Status On: " + i) ,
            () -> log("Status Off"),
            (String msg) -> log("Status Unstable: " + msg)
        );
    }

    interface Status<T1,T2>{

        default boolean isOn(){return false;};
        static <T1,T2> Status<T1, T2> errorWith(T2 string) {
            return new Err<>(string);
        }
        static <T1,T2> Status<T1, T2> off() {
            return new Off<>();
        }
        static <T1,T2> Status<T1, T2> onWith(T1 i) {
            return new On<>(i);
        }
        default boolean isOff(){return false;};
        default boolean isError(){return false;};
        default T2 getError(){throw new RuntimeException("cant get error Message");};
        default T1 get(){throw new NoSuchElementException("cant get error Message");};
    
        default public void accept(Consumer<T1> c1, Runnable r, Consumer<T2> c2){
            if(this.isOn()){
                c1.accept(this.get());
            }else if(this.isError()){
                c2.accept(this.getError());
            }else{
                r.run();
            }
        }
    
        static <T1,T2> Status<T1,T2> makeError(T2 s){
            return new Err<>(s);
        }
    
        static class On<T1,T2> implements Status<T1,T2>{
            private T1 n;
            public On(T1 n){
                this.n = n;
            }
            @Override
            public boolean isOn(){
                return true;
            }
            public T1 get(){
                return this.n;
            }
        }
        
        static class Off<T1,T2> implements Status<T1,T2>{
            public Off(){}
            @Override
            public boolean isOff(){
                return true;
            }
        }
        
        static class Err<T1,T2> implements Status<T1,T2>{
            private T2 mess;
            
            public Err(T2 Errmess){
                this.mess=Errmess;
            }
        
            @Override
            public boolean isError(){
                return true;
            }
        
            @Override
            public T2 getError(){
                return this.mess;
            }
        }
    }
}
