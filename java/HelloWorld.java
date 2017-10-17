public class HelloWorld
{
    /**
     * (1) Java is Case Sensitivity.
     * (2) Class Names: HelloWorld (FirstLetterInUpperCase)
     * (3) Method Names: myMethodName (firstLetterInLowerCase)
     * (4) Program File Name ==  Class Name\
     */
    public static void main(String[] args)
    {
        System.out.println("Hello World JAVA\n");

        /* this is how to access and use args */
        // println: print a new line
        System.out.println(args.length);
        for (int i = 0; i < args.length; i++)
        {
            // printf: print with format
            System.out.printf("args[%d] = %s\n", i, args[i]);
        }

    }
}
