import java.util.ArrayList;
import java.util.Scanner;
public class Calculator {
	static ArrayList <Integer> arr = new ArrayList <Integer>();
	public static Scanner sc  = new Scanner (System.in);
	public static String input;
	public static int base;
	public static int ansInDecimal;


	public static void main(String[] args) {
		
		System.out.println("Welcome to our decimal calculator!");
		while (startCalc()) {
			System.out.println("please type the number you want to convert:");
			start();
		}

	}
	private static void start() {
		input = sc.next();
		int arr[] = new int[input.length()];
		for (int i = 0; i < input.length(); i++) {
			char c = input.charAt(i);
			String str = String.valueOf(c);// converting char to string
			try{
				int digit = Integer.parseInt(str); // converting to int
				arr[i]=digit;
			}
			catch (NumberFormatException ex){// if the user entered a char which is not int he will get a message
				System.out.println("please enter digits only!!");
				return;
			}

		}
		System.out.println("to what base do you want to convert your number? \n 1. Decimal \n 2. Binary");
		base = sc.nextInt();
		if (base == 1) {// convert to decimal
			if(!isBinary(arr)) {
				System.out.println("in order to convert to a decimal base your current base has to be Binary \nplease try again");
				return;
			}
			ansInDecimal = convertToDecimal(arr);
			System.out.println("your number in decimal base is: "+ansInDecimal);
		}

		else if (base == 2) {// convert to binary
			if (!isDecimal(arr)) {
				System.out.println("in order to convert to a Binary base your current base has to be Decimal \n please try again");
				return;
			}
			int num = Integer.parseInt(input);
			convertToBinary(num);
		}
		
		else {
			System.out.println("you have to choose a number only from the option above !");
		}
	}






	private static int convertToDecimal(int[] arr) {
		int sum= 0;
		int size = arr.length-1;
		int[] temp= new int[arr.length];//Temporary array in order to store the solutions of each calculation before sum.
		for (int i = 0; i < arr.length; i++) {
			temp[i]=(int) (arr[i]*Math.pow(2, size));// the calculation of each digit
			size--;
		}
		for (int j=0; j<temp.length; j++ ) {
			sum += temp[j];
		}
		return sum;
	}
	
	private static void convertToBinary(int n) {

		int binary[] = new int[32];   //max 32 bit 
		int index = 0;    
		while (n > 0) {
			binary[index++] = n%2;   // remainder 
			n = n/2;    
		}
		System.out.print("your number in decimal base is: ");
		for(int i = index-1;i >= 0;i--){    // print binary solution 
			System.out.print(binary[i]);  

		}
	}

	private static boolean isDecimal(int[] arr) {// check if the input is a decimal number
		if (arr[0] == 0) {
			return false;
		}
		return true;
	}
	private static boolean isBinary(int[] arr) {// check if the input is binary
		for (int i = 0 ; i < arr.length ; i++ ) {
			if (arr[i] != 0 && arr[i] != 1) {
				return false;
			}
		}
		return true;
	}
	public static boolean startCalc(){// start or exit the calculator
		int startExit;
		System.out.println("\n To start converting press 1, to exit press any other number:");
		startExit = sc.nextInt();
		if (startExit == 1 ) {
			return true;
		}
		System.out.println("Bye Bye!");
		return false;
	}
}