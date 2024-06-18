import java.util.*;
import java.util.function.*;

class EmptyIntegerStack extends RuntimeException {
    public EmptyIntegerStack() { super("Stack is empty"); }
}

interface IntegerStack {
    // retourne et enlève l'élément de tête
    default int pop(){
        Optional<Integer> res = popOption();
        if(res.isPresent())
            return res.get();
        throw new EmptyIntegerStack();
    } 
        
    default Optional<Integer> popOption(){
        if(isEmpty())
            return Optional.empty();
        return Optional.of( pop() );
    }
    default void ifHeadIsPresent(Consumer<Integer> consumer){
        peekOption().ifPresent(consumer);
    }
    void push(int i); // ajoute un élément
    int size(); // retourne la taille
    default int peek(){
        int res = pop();
        push(res);
        return res;
    }
    default Optional<Integer> peekOption(){
        if(isEmpty())
            return Optional.empty();
        return Optional.of( peek() );
    }
    default boolean isEmpty(){
        return this.size()==0;
    }
}

class IntegerArrayStack implements IntegerStack{
    private ArrayList<Integer> listint;

    public IntegerArrayStack(){
        this.listint = new ArrayList<>();
    }

    @Override
    public int pop(){
        return this.listint.remove(this.size()-1);
    }

    @Override
    public void push(int i){
        this.listint.add(i);
    }

    @Override
    public int size() {
        return this.listint.size();
    }
}

class exercice7_1{
    static public void main(String args[]){
        IntegerStack stack = new IntegerArrayStack();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.ifHeadIsPresent( v -> System.out.println("head: " + v) ); // head: 3
    }
}

