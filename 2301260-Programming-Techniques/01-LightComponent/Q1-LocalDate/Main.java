import java.time.LocalDate;
import java.util.Scanner;
import java.time.Period;

public class Main {
    public static void main(String[] args) {
        LocalDate today = LocalDate.now();
        System.out.println("Current Date: " + today);
        
        Scanner scanner = new Scanner(System.in); // create scanner to get input from console

        int day, month, year; // define variables
        
        System.out.print("Enter day: ");
        day = scanner.nextInt();            // get input from console type int
        
        System.out.print("Enter month: ");
        month = scanner.nextInt();
        
        System.out.print("Enter year: ");
        year = scanner.nextInt();
        
        LocalDate thatDay = LocalDate.of(year, month, day); // create date from input data

        Period period = Period.between(today, thatDay); // find period between today and input day

        System.out.println("Number of days: " + period.getDays()); // print number of day
    }
}