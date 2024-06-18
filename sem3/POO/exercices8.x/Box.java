import java.util.Objects;
import java.util.function.Function;
  
public final class Box<T> implements Comparable<Box<T>> {

  private T value;

  public Box(T value) { this.value = value; }

  public T get() { return this.value; }

  public void set(T newValue) { this.value = newValue; }

  @Override
  public String toString() { return "[" + this.value.toString() + "]"; }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (o == null || o.getClass() != this.getClass()) {
      return false;
    }
    Box<?> other = (Box<?>)o;
    return this.value.equals(other.value);
  }
  public <R> Box<R> map(Function<T, R> f) {
    return new Box<R>(f.apply(this.value));
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.value);
  }
  @Override
  public int compareTo(Box<T> arg0) {
      return (Integer)arg0.get()-(Integer)this.get();
  }
  public static void main(String[] argv){
    Box<Integer> b1 = new Box<>(2);
    Box<Integer> b2 = new Box<>(1);
    System.out.println(Util.isBigger(b1, b2));
  }
}

class Util{
  public static <T> boolean isBigger(Box<T> b1, Box<T> b2){
    return b1.compareTo(b2)<0;
  }
}