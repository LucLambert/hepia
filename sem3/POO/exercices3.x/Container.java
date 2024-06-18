public class Container{
    private int capacity;
    private int objSize;

    public Container(int cap){
        this.capacity = cap;
        this.objSize = 0;
    }

    public static Container withCapacity(int cap){
        return new Container(cap);
    }

    public void fillToTheMax(){
        this.objSize = this.capacity;
    }

    public void fillWith(int n){
        this.objSize = n;
    }

    public void fillTo(Container ... dests){
        for(Container n : dests){
            this.objSize -= n.capacity();
            if (this.objSize < 0){
                n.fillWith(n.capacity()+this.objSize);
                this.objSize = 0;
            }
            else{
                n.fillWith(n.capacity());
            }
        }
    }

    public int quantity(){
        return this.objSize;
    }

    private int capacity(){
        return this.capacity;
    }

    public int remaining(){
        return this.capacity - this.objSize;
    }

    public boolean isFull(){
        return this.capacity == this.objSize;
    }

    public void flush(){
        this.objSize = 0;
    }

    public void remove(int n){
        this.objSize -= n;
    }

    @Override
    public String toString(){
        return  this.objSize + "/" + this.capacity;
    }

    public static void main(String[] args){
        Container origin = Container.withCapacity(10); // récipient vide par défaut
        origin.fillToTheMax(); // remplissage
        Container destination1 = new Container(5); // idem que Container.withCapacity(5);
        destination1.fillWith(2);
        Container destination2 = Container.withCapacity(3);
        Container destination3 = Container.withCapacity(10);
        origin.fillTo(destination1, destination2, destination3);
        assert destination1.isFull() ;
        assert destination2.isFull() ;
        assert destination2.remaining() == 0 ;
        destination2.remove(2);
        assert destination2.remaining() == 2 ;
        assert !destination3.isFull() ;
        assert destination3.quantity() == 4;
        destination3.flush();
        assert destination3.quantity() == 0;
    } 
}