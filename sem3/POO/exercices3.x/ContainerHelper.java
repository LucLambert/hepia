import java.util.*;

public class ContainerHelper{

    public static List<Integer> transfer(int orig, int dest, int ... dests){
        List<Integer> tab = new ArrayList<>(); 
        
        if (orig  < dest){
            tab.add(orig);
        }
        else{
            tab.add(dest);
            orig -= dest;
        }
        
        for(int n : dests){
            orig -= n;
            if (orig < 0){
                tab.add(n+orig);
            }
            else{
                tab.add(n);
            }
        }
        return tab;
    }

    public static void main(String[] args){
        List<Integer> tab = transfer(100, 10, 40, 30, 50);
        System.out.println(tab);
    }
}