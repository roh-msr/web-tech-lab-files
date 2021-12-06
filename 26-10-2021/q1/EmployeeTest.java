class Employee {
    private String firstName;
    private String lastName;
    private double monthlySalary;

    public Employee(String firstName, String lastName, double monthlySalary) {
        if(monthlySalary <= 0){
            System.out.println("Salary must be greater than zero!" );
            System.out.println("Salary automatically set to zero!" );
            monthlySalary = 0;
        }

        this.firstName = firstName;
        this.lastName = lastName;
        this.monthlySalary = monthlySalary;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public double getMonthlySalary() {
        return monthlySalary;
    }

    public void setMonthlySalary(double monthlySalary) {
        if(monthlySalary <= 0){
            System.out.println("Salary must be greater than zero!" );
            return;
        }

        this.monthlySalary = monthlySalary;
    }

    public double getYearlySalary() {
        return monthlySalary * 12;
    }

    public void giveHike(double percentage){
        monthlySalary += monthlySalary * (percentage / 100.0);
    }
}

public class EmployeeTest {
    public static void main(String[] args) {
        Employee e1 = new Employee("Kohli", "Virat", 2000);
        Employee e2 = new Employee("Rahul", "Dravid", 3000);

        e1.setFirstName("Virat");
        e1.setLastName("Kohli");

        e1.setMonthlySalary(-99);
        e1.setMonthlySalary(3590);

        System.out.println("Employee 1 = " + e1.getFirstName() + " " + e1.getLastName() + " " + e1.getMonthlySalary());
        System.out.println("Employee 2 = " + e2.getFirstName() + " " + e2.getLastName() + " " + e2.getMonthlySalary());
        
        System.out.println("Employee 1 Yearly Salary = " + e1.getYearlySalary());
        System.out.println("Employee 2 Yearly Salary = " + e2.getYearlySalary());
        
        System.out.println("Let's give 10% hike! to Dravid!");
        e2.giveHike(10);
        System.out.println("Employee 2 New Salary = " + e2.getMonthlySalary());
    }
}
