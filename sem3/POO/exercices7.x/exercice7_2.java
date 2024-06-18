// je ne comprends pas comment me passer du champs d'indice de position dans la classe Arraylist Int
import java.util.*;

public class exercice7_2 {
    public static void main(String[] args) {    
        ListInt list = new ArrayListInt();
        list.insert(0);
        list.insert(3);
        list.insertAll(2,1);
    
        for (int i = 0; i < list.size(); i+=1) {
            int v = list.get(i);
            System.out.println("Value: " + v);
        }
        
        /* l'itérateur permet maintenant le code ci-dessous */
        for (int v: list) {
            System.out.println("Value: " + v);
        }
        
        /* ou */
        Iterator<Integer> it = list.iterator();
        while (it.hasNext()) {
            System.out.println("Value: " + it.next());
        }
        
        /* et même */
        list.forEach( v -> System.out.println("Value: " + v));

        ListInt llist = new LinkedListInt();
        llist.insert(12);
        llist.insert(45);
        llist.insert(1);
        llist.insertAll(99, 37);
        llist.forEach( v -> System.out.println("Value: " + v));
    }
}

interface ListInt extends Iterable<Integer>{
    void insert(int n);
    void insertAll(int ... n);
    int size();
    int get(int n);
    void clear();
    default boolean isEmpty() {
        return size()==0;
    }
}

class ArrayListInt implements ListInt{  
    private int[] array;
    private int len;
    private int pos=0; 
    
    public ArrayListInt(){
        this.len = 10;
        this.array = new int[this.len];
    }

    public void insert(int n){
        this.safeInsert(n);
    }

    public void insertAll(int ... n){
        for(int a : n)
            this.safeInsert(a);
    }

    private void safeInsert(int n){
        if(this.pos >= this.len){
            int[] tab = new int[this.len+10];
            for(int y : this.array){
                tab[y] = this.array[y];
            }
            tab[this.pos++]=n;
            this.array = tab;
        }else{
            this.array[this.pos++]=n;
        }
    }

    public int size(){
        return this.pos;
    }

    public int get(int n){
        if(n>this.size())
            throw new NoSuchElementException();
        return this.array[n];
    }

    public void clear(){
        this.array=new int[10];
        this.len=10;
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<Integer>(){
            private int current=0;
            @Override
            public Integer next(){
                if( !hasNext() )
                    throw new NoSuchElementException();  
                this.current++;
                return array[current];  
            }
            @Override
            public boolean hasNext(){
                return this.current < size();
            }
        };
    }
}

class LinkedListInt implements ListInt{
    private Elem firstElem;

    static class Elem{
        private int a;
        private Elem next;

        public Elem(int n){
            this.a = n;
            this.next = null;
        }
    }

    public LinkedListInt(){
        this.firstElem = new Elem(0);
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<Integer>(){
            private int current=0;
            @Override
            public Integer next(){
                if( !hasNext() )
                    throw new NoSuchElementException();  
                return get(current++);  
            }
            @Override
            public boolean hasNext(){
                return this.current < size();
            }
        };
    }

    @Override
    public void insert(int n) {
        if(firstElem.next != null){
            Elem curElem = firstElem.next;
            while(curElem.next != null){
                curElem = curElem.next;
            }    
            curElem.next = new Elem(n);
        }else{
            firstElem.next = new Elem(n);
        }  
    }

    @Override
    public void insertAll(int... n) {
        for(int x : n){
            insert(x);
        }
    }

    @Override
    public int size() {
        int cpt = 0;
        if(firstElem.next != null){
            cpt++;
            Elem curElem = firstElem.next;
            while(curElem.next != null){
                curElem = curElem.next;
                cpt++;
            }
        }
        return cpt;
    }

    @Override
    public int get(int n) {
        int cpt = 0;
        Elem curElem = firstElem.next;
        while(cpt < n){
            curElem = curElem.next;
            cpt++;
        }
        return curElem.a;
    }

    @Override
    public void clear() {
        firstElem.next = null;
    }
}
