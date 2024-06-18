//realiser tout seul
public class exercices5_8 {
    public static void main(String[] args) {    
        ListInt list = new ArrayListInt();
        list.insert(0);
        list.insert(3);
        list.insertAll(2,1); // insertAll prend un nombre arbitraire d'éléments 
        System.out.println( "Size: " + list.size() );

        for (int i = 0; i < list.size(); i+=1) {
            int v = list.get(i);
            System.out.println("Value: " + v);
        }

        list.clear();
        System.out.println( "Size: " + list.size() );

     /*
     * Cet exemple afficherait
     * Size: 4
     * Value: 0
     * Value: 3
     * Value: 2
     * Value: 1
     * Size: 0
     */
    }
}

interface ListInt{
    void insert(int n);
    void insertAll(int ... n);
    int size();
    int get(int n);
    void clear();
    default boolean isEmpty() {
        return size()==0;
    }
    default void addALL(int ... n) {
        insertAll(n);
    }
}

class ArrayListInt implements ListInt{
    
    private int[] array;
    private int len;
    private int i=0;
    
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
        if(this.i >= this.len){
            int[] tab = new int[this.len+10];
            for(int y : this.array){
                tab[y] = this.array[y];
            }
            tab[this.i++]=n;
            this.array = tab;
        }else{
            this.array[this.i++]=n;
        }
    }

    public int size(){
        return this.i;
    }

    public int get(int n){
        return this.array[n];
    }

    public void clear(){
        this.array=new int[10];
        this.len=10;
        this.i=0;
    }

}
    