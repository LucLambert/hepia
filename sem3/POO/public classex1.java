public class ex1{
    public static void main(String[] args) {
        Test test = new TestImpl();
        test.blah( (int i, LocalDate l) -> println(i + l) );
        test = test.next();
        test.show(5.0);
        test.guess( (int i, double j) -> i + j );
        test.guess( (String s) -> println(s) );
        if (test.isTrue()) {
        	int u = test.getFinalValue();
        }
    }   
}

public interface my_Consumer{
    void accept(int i, LocalDate l);
}

public interface guessing1{
    void accept(int i, double j);
}

public interface guessing2{
    void accept(String s);
}

class Test{
    public Test TestImpl(){}
    public blah(my_Consumer c){
        c.accept();
    }
    public next(){
        return new Test();
    }

    public show(double d){}
    public guess(guessing1 g){
        g.accept();
    }
    public guess(guessing2 g){
        g.accept();
    }
}