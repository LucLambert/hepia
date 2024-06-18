import java.util.function.*;

public class Pair<A,B>{
    private final A x;
    private final B y;

    private Pair(A x, B y) {
        this.x=x;
        this.y=y;
    }
    public A getx(){
        return this.x;
    }
    public B gety(){
        return this.y;
    }
    public Pair<A,B> mapx(Function<A, A> f){
        return new Pair<>(f.apply(this.x), this.y);
    }
    public Pair<A,B> mapy(Function<B, B> f){
        return new Pair<>(this.x, f.apply(this.y));
    }
    public Pair<A,B> mapxy(Function<A, A> fx, Function<B, B> fy){
        return new Pair<>(fx.apply(this.x), fy.apply(this.y));
    }
}