import java.util.*;   /* import all from java.util: scanner*/

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Print output to STDOUT.
         * Your class should be named Solution.
         */

        /* Welcome to Java! */
        // System.out.println("Hello, World.");
        // System.out.println("Hello, Java.");

        /* Java Stdin and Stdout I */
        // Scanner scanner = new Scanner(System.in);
        // int myInt1 = scanner.nextInt();
        // int myInt2 = scanner.nextInt();
        // int myInt3 = scanner.nextInt();
        // scanner.close();
        // System.out.println(myInt1);
        // System.out.println(myInt2);
        // System.out.println(myInt3);

        /* Java If-Else */
        Scanner scan = new Scanner(System.in);
        int positiveInteger = scan.nextInt();
        scan.close();

        if ((positiveInteger % 2) != 0)
        {
            System.out.println("Weird");
        }
        else
        {
            if ((positiveInteger >=2 ) && (positiveInteger <= 5))
            {
                System.out.println("Not Weird");
            }
            else if ((positiveInteger >=6 ) && (positiveInteger <= 20))
            {
                System.out.println("Weird");
            }
            else if (positiveInteger > 20)
            {
                System.out.println("Not Weird");
            }
        }
    }
}