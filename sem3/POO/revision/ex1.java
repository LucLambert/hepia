import java.time.LocalDate;

public class ex1{
    static void println(int n){}
    static void println(String s){}
    public static void main(String[] args) {
        Test test = new TestImpl();
        test.blah( (int i, LocalDate l) -> println(i + l));
        test = test.next();
        test.show(5.0);
        test.guess( (int i, double j) -> i + j );
        test.guess( (String s) -> println(s) );
        if (test.isTrue()) {
        	int u = test.getFinalValue();
        }
    }   
}

interface my_Consumer{
    void accept(int i, LocalDate l);
}

interface guessing1{
    double accept(int i, double j);
}

interface guessing2{
    void accept(String s);
}

class TestImpl extends Test{
    public TestImpl(){}
}

class Test{
    
    public void blah(my_Consumer c){
        c.accept(2,LocalDate.MAX);
    }
    public Test next(){
        return new Test();
    }

    public void show(double d){}
    public void guess(guessing1 g){
        g.accept(0,0);
        //return 0;
    }
    public void guess(guessing2 g){
        g.accept("");
    }
    public boolean isTrue(){
        return true;
    }
    public int getFinalValue(){
        return 0;
    }
}