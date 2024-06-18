interface Pushable{
    void push();
}
class exercices6_4{
    public static void main(String[] Args){
        push(()->{System.out.println("Push");});
    }
    public static void push(Pushable p){
        p.push();
        System.out.println("Button has been push");
    }
    
}
