import java.util.*;
class exercices6_2 {

    public static void main(String[] Args){
        Status s1 = Status.process();
        if( s1.isOn() ) {
            System.out.println("L'appareil fonctionne");
        } else if ( s1.isOff() ) {
            System.out.println("L'appareil est éteint");
        } else {
            System.out.println("L'appareil est instable: " + s1.getErrorMessage());
        }
        Status s2 = Status.makeError("Oups");
    }
}

//faire une classe pour on off err et interface pour status

interface Status{

    static Status process() {
        Random r = new Random();
        int n = r.nextInt(3);
        switch(n){
            case 0: 
                return new On();
            case 1:
                return new Off();
            default:
                return new Err("Oups");
        }       
    };

    default boolean isOn(){return false;};
    default boolean isOff(){return false;};
    default boolean isError(){return false;};
    default String getErrorMessage(){throw new RuntimeException("cant get error Message");};

    static Status makeError(String s){
        return new Err(s);
    }

    static class On implements Status{
        private On(){}
        @Override
        public boolean isOn(){
            return true;
        }
    }
    
    static class Off implements Status{
        private Off(){}
        @Override
        public boolean isOff(){
            return true;
        }
    }
    
    static class Err implements Status{
        private String mess="Err";
        
        Err(String Errmess){
            this.mess=Errmess;
        }
    
        @Override
        public boolean isError(){
            return true;
        }
    
        @Override
        public String getErrorMessage(){
            return this.mess;
        }
    }
}


