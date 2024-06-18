import java.util.*;

class exercices5_5 {

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
                return new Err();
        }       
    };

    boolean isOn();
    boolean isOff();
    boolean isError();

    String getErrorMessage();

    static Status makeError(String s){
        System.out.println(s);
        return new Err();
    }
}

class On implements Status{
    public boolean isOn(){
        return true;
    }
    public boolean isOff(){
        return false;
    }
    public boolean isError(){
        return false;
    }
    public String getErrorMessage(){
        return "";
    }
}

class Off implements Status{
    public boolean isOn(){
        return false;
    }
    public boolean isOff(){
        return true;
    }
    public boolean isError(){
        return false;
    }
    public String getErrorMessage(){
        return "";
    }
}

class Err implements Status{
    public boolean isOn(){
        return false;
    }
    public boolean isOff(){
        return false;
    }
    public boolean isError(){
        return true;
    }
    public String getErrorMessage(){
        return "Error";
    }
}
