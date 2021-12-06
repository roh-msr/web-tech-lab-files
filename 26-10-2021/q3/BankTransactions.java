import java.util.*;

enum AccountType {
    SAVINGS, CURRENT, NONE;
}

class InvalidBalanceException extends Exception {  
    public InvalidBalanceException ()  
    {
        super("An account balance must be greater than or equal to zero.");  
    }  
    
    public InvalidBalanceException (String str)  
    {
        super(str);  
    }  
}

class InvalidAccountNumberException extends Exception {  
    public InvalidAccountNumberException ()  
    {
        super("An account number must atleast have 15 digits.");  
    }  
}

class InvalidAccountNameException extends Exception {  
    public InvalidAccountNameException ()  
    {
        super("An account name must have at least 8 characters.");   
    }  
}

class BankAccount {
    private String account_number;
    private String account_holder_name;
    private AccountType account_type;
    private double balance;

    public BankAccount(String number, String name, AccountType type, double amt) {
        try{
            if(number.length() < 15){
                throw new InvalidAccountNumberException();
            }

            if(amt < 0){
                throw new InvalidBalanceException();
            }

            if(name.length() < 8){
                throw new InvalidAccountNameException();
            }

            this.account_number = number;
            this.account_holder_name = name;
            this.account_type = type;
            this.balance = amt;
        }
        catch(InvalidBalanceException e){
            System.out.printf("%s\n", e);
        }
        catch(InvalidAccountNameException e){
            System.out.printf("%s\n", e);
        }
        catch(InvalidAccountNumberException e){
            System.out.printf("%s\n", e);
        }
    }
    
    public void depositMoney(double amount){
        try{
            if(amount <= 0){
                throw new InvalidBalanceException("Amount must be positive!");
            }
            
            this.balance += amount;
            System.out.println("Amount successfully deposited!");
        }
        catch(InvalidBalanceException e){
            System.out.printf("%s\n", e);
        }   
    }
    
    public void withdrawMoney(double amount){
        try{
            if(amount <= 0){
                throw new InvalidBalanceException("Amount must be positive!");
            }
            
            if(this.balance < amount){
                throw new InvalidBalanceException("Insufficient amount!");
            }

            this.balance -= amount;
            System.out.println("Amount successfully withdrawn!");
        }
        catch(InvalidBalanceException e){
            System.out.printf("%s\n", e);
        }
    }
    
    public void transferMoney(BankAccount account, double amount){
        try{
            this.withdrawMoney(amount);
            account.depositMoney(amount);
            System.out.println("Amount successfully transferred!");
        }
        catch(Exception e){
            System.out.printf("%s\n", e);
        }
    }

    public void getDetails() {
        System.out.println("Account Name: " + this.account_holder_name);
        System.out.println("Account Number: " + this.account_number);
        System.out.println("Account Type: " + this.account_type);
        System.out.println("Balance: " + this.balance);
    }
}

public class BankTransactions {
    public static void main(String[] args){
        BankAccount account1 = new BankAccount("19080234879876512388", "Mr. Rohith M S R", AccountType.SAVINGS, 90000);
        BankAccount account2 = new BankAccount("19456324879876574365", "Mr. Satoshi Nakamoto", AccountType.CURRENT, 100000);

        account1.getDetails();
        System.out.println();
        account2.getDetails();
        System.out.println();
        
        account1.withdrawMoney(1000);
        account2.depositMoney(1000);
        account2.transferMoney(account1, 90000);
        System.out.println();
        
        account1.getDetails();
        System.out.println();
        account2.getDetails();
        System.out.println();

        account1.depositMoney(-9);
        account1.withdrawMoney(9999999);

        BankAccount account3 = new BankAccount("19080234879876512388", "R", AccountType.SAVINGS, 900);
        BankAccount account4 = new BankAccount("76512388", "Mr. Rohith M S R", AccountType.SAVINGS, 9000);
        
    }
}
