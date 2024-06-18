/*
    Je n'arrive pas à faire une interface fonctionelle ayant 2 signatures différentes.
*/
import java.util.*;
import java.util.function.Consumer;

public class exercices6_1{
    public static void main(String[] args) {
        Account stephanie = Account.withName("Stéphanie").withAmount(1000);
        Account julia = Account.withName("Julia");
        Account stephanie2 = stephanie.deposite(1000);
        stephanie.transferTo(julia).amount(100).ifSuccesOrElse((originAccount, destinationAccount, amount) -> {
            System.out.println("All good");
            System.out.println("now " + originAccount.name() + " has " + originAccount.amount());
            System.out.println("now "+ destinationAccount.name() +" has " + destinationAccount.amount());
        },
        (String Errormsg) -> {System.out.println("Operation dennied : " + Errormsg);}
        );
    }
}

class Account {
    private final String owner;
    private final int amount;

    private Account(String name){
        this.owner = name;
        this.amount = 0;
    }

    private Account(String name, int amountGiven){
        this.owner = name;
        if(amountGiven < 0){
             throw new RuntimeException("You can't set a negative Amount");
        }
        this.amount = amountGiven;
    }

    public static Account withName(String name){
        return new Account(name);
    }

    public Account withAmount(int a){
        return new Account(this.owner, a);
    }

    public Account deposite(int value){
        if(value < 0){
            throw new RuntimeException("deposite value must be positive and superior than 0");
        }
        return new Account(this.owner, value + this.amount);
    }

    public String name(){
        return this.owner;
    }

    public PendingTransaction transferTo(Account a){
        return new PendingTransaction(this, a);
    }

    public int amount(){
        return this.amount;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) return true;
        if(o == null || o.getClass() != this.getClass()) {
          return false; 
        }
        Account other = (Account)o;
        return this.owner == other.owner && this.amount == other.amount;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.owner, this.amount);
    }
}

@FunctionalInterface
interface TransactionSuccess{
    void accept(Account from, Account to, int a);
}

class Transaction{
    private Account from;
    private Account to;
    private int amount;
    public Transaction(Account a1, Account a2, int amount){
        this.from=a1;
        this.to=a2;
        this.amount=amount;
    }
    public void ifSuccesOrElse(TransactionSuccess ifSuccess,Consumer<String> ifError){
        if(this.from.amount() >= this.amount){
            Account nextA2 = this.to.deposite(this.amount);
            Account nextA1 = this.from.withAmount(this.from.amount()-this.amount);
            ifSuccess.accept(nextA1, nextA2, this.amount);
        }else{
            ifError.accept("Pas assez d'argent à retirer de " + this.from.name());
        }
    }
}

class PendingTransaction{
    Account a1;
    Account a2;
    public PendingTransaction(Account a1, Account a2){
        this.a1=a1;
        this.a2=a2;
    }
    public Transaction amount(int a){
        return new Transaction(this.a1,this.a2,a);
    }
}