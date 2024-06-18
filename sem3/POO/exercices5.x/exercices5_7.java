//realiser tout seul
public class exercices5_7 {
    
}

class A{
    public A() {}
    public void test(){
        a();
        b();
    }
    public void a(){};
    public void b(){};
}

class B{
    public B(){}
    public void test(){
        A aa=new A();
        aa.a();
        aa.b();
    }
}
