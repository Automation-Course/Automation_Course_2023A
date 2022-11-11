import java.util.Scanner;
public class calculator{
    static Scanner sc= new Scanner (System.in);
    public static void convertDecToBin(String number)
    {
        int num = Integer.parseInt(number);
        if (num==0)
            System.out.println("The converted value is " +num);
        else {
        String converted= "";
        String sheerit = "";
        int numOfDigits = 0;
        while (num != 0)
        {
            int left = num%2;
            numOfDigits++;
            char leftt = (char)(left + 48);
            sheerit += leftt;
            num = num/2;
        }
        for (int i=numOfDigits-1; i>=0; i--)
            converted += sheerit.charAt(i);
        System.out.println("The converted value is " + converted);
    }}

    public static void convertBinToDec(String num)
    {
        int converted = 0;
        int numOfDigits = num.length();
        int digit;
        for (int i=0; i<numOfDigits; i++)
        {
            digit =	(int) num.charAt(i) -48;
            converted = (int) (converted + digit*(Math.pow(2, (numOfDigits-i-1))));
        }
        System.out.println("The converted value is " + converted);
    }

    public static boolean isBinary (String num)
    {
        boolean isBin = true;
        int numOfDigits = num.length();
        int digit;
        for (int i=0; i<numOfDigits; i++)
        {
            digit =	(int) num.charAt(i) -48;
            if ((digit !=0) && (digit !=1))
                isBin = false;
        }
        return isBin;
    }
    public static boolean isDecimal (String num)
    {
        boolean isDec = true;
        int numOfDigits = num.length();
        int digit;
        for (int i=0; i<numOfDigits; i++)
        {
            digit =	(int) num.charAt(i) -48;
            if ((digit<0||digit>=10))
                isDec = false;
        }
        return isDec;
    }

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        System.out.println("To convert from Decimal press 1, from binary press 2");
        int choose = sc.nextInt();
        while (choose !=1 && choose !=2) {
            System.out.println("Your choose is undefined, please choose 1 or 2");
            choose = sc.nextInt();}
        System.out.println("enter a number to convert");
        if (choose == 1)
        {
            String num = sc.next();
            while (!isDecimal(num))
            {
                System.out.println("you entered an invalid number , please enter again");
                num = sc.next();
            }
            convertDecToBin(num);
        }
        if (choose == 2)
        {
            String num = sc.next();
            while (!isBinary(num))
            {
                System.out.println("your number is not binary, please enter again");
                num = sc.next();
            }
            convertBinToDec(num);
        }
    }

}
