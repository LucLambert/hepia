import java.util.*;

public class exolists {
    public static void main(String[] args) {    
        myList<Integer> list = new myArrayList();
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

        myList<Integer> llist = new myLinkedList();
        llist.insert(12);
        llist.insert(45);
        llist.insert(1);
        llist.insertAll(99, 37);
        llist.forEach( v -> System.out.println("Value: " + v));
    }
}

interface myList<E> extends Iterable<E>{
    void insert(E e);
    void insertAll(E ... elems);
    int size();
    E get(int n);
    void clear();
    default boolean isEmpty() {
        return size()==0;
    }
}

class myArrayList<E> implements myList<E>{  
    private E[] array;
    private int len;
    private int pos=0; 
    
    public myArrayList(){
        this.len = 10;
        this.array = (E[])new Object[this.len];
    }

    public void insert(E e){
        this.safeInsert(e);
    }

    public void insertAll(E ... elems){
        for(E e : elems)
            this.safeInsert(e);
    }

    private void safeInsert(E e){
        if(this.pos >= this.len){
            E[] tab = (E[])new Object[this.len+10];
            for(int y=0; y<this.size(); y++){
                tab[y] = this.array[y];
            }
            tab[this.pos++]=e;
            this.array = tab;
        }else{
            this.array[this.pos++]=e;
        }
    }

    public int size(){
        return this.pos;
    }

    public E get(int n){
        if(n>this.size())
            throw new NoSuchElementException();
        return this.array[n];
    }

    public void clear(){
        this.array=(E[])new Object[10];
        this.len=10;
    }

    @Override
    public Iterator<E> iterator() {
        return new Iterator<E>(){
            private int current=0;
            @Override
            public E next(){
                if( !hasNext() )
                    throw new NoSuchElementException();  
                return array[current++];  
            }
            @Override
            public boolean hasNext(){
                return this.current < size();
            }
        };
    }
}

class myLinkedList<E> implements  myList<E>{
    private Elem firstElem;

    class Elem{
        private E e;
        private Elem next;

        public Elem(E e){
            this.e = e;
            this.next = null;
        }
    }

    public  myLinkedList(){
        this.firstElem = new Elem(null);
    }

    @Override
    public Iterator<E> iterator() {
        return new Iterator<E>(){
            private int current=0;
            @Override
            public E next(){
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
    public void insert(E e) {
        if(firstElem.next != null){
            Elem curElem = firstElem.next;
            while(curElem.next != null){
                curElem = curElem.next;
            }    
            curElem.next = new Elem(e);
        }else{
            firstElem.next = new Elem(e);
        }  
    }

    @Override
    public void insertAll(E ... elems) {
        for(E e : elems){
            insert(e);
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
    public E get(int n) {
        int cpt = 0;
        Elem curElem = firstElem.next;
        while(cpt < n){
            curElem = curElem.next;
            cpt++;
        }
        return curElem.e;
    }

    @Override
    public void clear() {
        firstElem.next = null;
    }
}
