import java.util.Objects;
public class DynArray{

    private int[] tab;

    public static void main(String[] args){
        DynArray is = DynArray.of(1, 2, 2, -1, 5);
        System.out.println(is);
        // is = [1, 2, 2, -1, 5];
        DynArray is2 = is.append(10);
        System.out.println(is2);
        // is2 = [10, 1, 2, 2, -1, 5];
        int j = is2.head();
        System.out.println(j);
        // j = 10
        DynArray tail = is2.pop();
        System.out.println(tail);
        // tail = [1, 2, 2, -1, 5];
        DynArray rev = tail.reversed();
        System.out.println(rev);
        // rev = [5, -1, 2, 2, 1]
        int size = rev.size();
        System.out.println(size);
        // size = 5
        boolean areEquals = is.equals(tail);
        System.out.println(areEquals);
        // areEquals = true
        DynArray result = is2.concat( DynArray.of(4,3,2) );
        System.out.println(result);
        // result = [1, 2, -1, 5, 4, 3, 2]
        String representation = result.toString();
        System.out.println(representation);
        // representation = [1, 2, -1, 5, 4, 3, 2]
    }

    private DynArray(int[] tab){
        this.tab = tab;
    }

    private DynArray(int length){
        this.tab = new int[length];
    }

    public static DynArray of(int ... numbers){
        DynArray d = new DynArray(numbers);
        return d;    
    }

    @Override
    public String toString(){
        String out = "[";
        for(int n : this.tab){
            out = out + n + ", "; 
        }
        out += "]";
        out = out.replace(", ]", "]");
        return out;
    }

    public DynArray append(int n){
        DynArray tmp = new DynArray(this.tab.length + 1);
        for(int i = 0; i<this.tab.length+1; i++){
            if(i==0)
                tmp.tab[i] = n;
            else
                tmp.tab[i] = this.tab[i-1];
        }
        return tmp; 
    }

    public DynArray reversed(){
        DynArray tmp = new DynArray(this.tab.length);
        for(int i = 0; i<this.tab.length; i++){
            tmp.tab[i] = this.tab[this.tab.length-i-1];
        }
        return tmp;
    }

    private static void tabPrint(int[] tab){
        for(int i=0; i<tab.length; i++){
            System.out.print(tab[i] + " ");
        }
        System.out.println();
    }

    public int head(){
        return this.tab[0];
    }

    public DynArray pop(){
        DynArray tmp = new DynArray(this.tab.length - 1);
        for(int i = 1; i<this.tab.length; i++){
            tmp.tab[i-1] = this.tab[i];
        }
        return tmp;
    }

    public DynArray concat(DynArray tab1){
        DynArray res = new DynArray(tab1.tab);
        for(int n : this.tab){
            res = res.append(n);
        }
        return res;  
    }

    public int size(){
        return this.tab.length;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) 
            return true;
        if(o == null || o.getClass() != this.getClass()) {
            return false; 
        }
        DynArray other = (DynArray)o;
        if(this.size() != other.size()){
            return false;
        }
        for(int i = 0; i < other.size(); i++){
            if( this.tab[i] != other.tab[i]){
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.tab);
    }
}