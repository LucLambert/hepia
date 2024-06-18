public class AccountToBreak {

    public int amount;
    private String owner;
    
    public AccountToBreak(String owner, int amount) {
        this.amount = amount;
        this.owner = owner;
    }
    public static AccountToBreak of(String owner, int amount) {
        if (amount <= 0) {
            throw new RuntimeException("Amount must be positive");
        }
        return new AccountToBreak(owner, amount);
    }
    public int amount() {
        return this.amount;
    }
    public void deposite(int value) {
        this.amount += value;
    }
    public void withdraw(int value) {
        if (value <= 0) {
            throw new RuntimeException("Amount must be positive");
        } else if (this.amount - value <= 0) {
            throw new RuntimeException("operation impossible: capital would have become negative");
        }
        this.amount -= value;
    }

    public void transfer(Account dest, int value){
        
    }

    public static void main(String[] args){
        AccountToBreak a = new AccountToBreak("Luc", -300);
        System.out.println(a.amount);
        a.deposite(-300);
        System.out.println(a.amount);
        a.deposite(601);
        System.out.println(a.amount);
        int MAX_INT = 2147483647;
        a.deposite(MAX_INT);
        System.out.println(a.amount);
        a.amount = -5000;
        System.out.println(a.amount);
    }
}