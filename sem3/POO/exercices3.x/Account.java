import java.util.Objects;

public class Account{
    private final String owner;
    private int amount;

    public Account(String name){
        this.owner = name;
        this.amount = 0;
    }

    public Account(String name, int amountGiven){
        this.owner = name;
        if(amountGiven < 0){
             throw new RuntimeException("You can't set a negative Amount");
        }
        this.amount = amountGiven;
    }

    public void withdraw(int value) {
        if (value <= 0) {
            throw new RuntimeException("Amount must be positive");
        } else if (this.amount - value <= -2000) {
            throw new RuntimeException("operation impossible: capital would have become inferior than -2000.-");
        }
        this.amount -= value;
    }

    public void deposite(int value) {
        if(value < 0){
            throw new RuntimeException("Amount must be positive and superior than 0");
        }
        this.amount += value;        
    }

    public void transfer(Account dest, int value){
        if(value < 0){
            throw new RuntimeException("Amount must be positive and superior than 0");
        }else if (this.amount - value <= -2000) {
            throw new RuntimeException("operation impossible: capital would have become inferior than -2000.-");
        }
        this.amount -= value;
        dest.amount += value;
    }

    public String name(){
        return this.owner;
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