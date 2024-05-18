import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // init variable
        int spaceIndex, secondIndex;
        String ultimate, firstname, lastname, age;
        
        Scanner scanner = new Scanner(System.in); // create scanner to get input from console

        System.out.print("Enter firstname lastname age: ");
        ultimate = scanner.nextLine().trim();  // get input from console and trim space out

        spaceIndex = ultimate.indexOf(" "); // find location of first space (space before lastname)
        secondIndex = ultimate.indexOf(" ", spaceIndex+1); // find location of second space (space before age)

        firstname = ultimate.substring(0, spaceIndex); // select firstname start from begin to location of first space
        lastname = ultimate.substring(spaceIndex+1, secondIndex); // select lastname start location of first space to location of second space
        age = ultimate.substring(secondIndex+1); // select age start from location of second space to end

        System.out.println(lastname + ", " + firstname + " is " + age + " years old."); // combine and print
    }
}