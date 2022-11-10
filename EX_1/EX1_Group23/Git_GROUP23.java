import java.util.Scanner;

public class Git_GROUP23 {

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		//Choosing your option in the calculator.
		System.out.println("Welocme To The Base Calculator, Please Choose Your Option:");
		System.out.println("1. Convet Number From Base 10 to Base 2:");
		System.out.println("2. Convet Number From Base 2 to Base 10:");
		System.out.println("3. Exit Calculator");
		String option=sc.next();
		// As long as input in invalid, choose again.
		while(option.equals("1")==false & option.equals("2")==false & option.equals("3")==false) {
			System.out.println("Invalid Input, Try Again:");
			System.out.println("1. Convet Number From Base 10 to Base 2:");
			System.out.println("2. Convet Number From Base 2 to Base 10:");
			System.out.println("3. Exit Calculator");
			option=sc.next();
		}
		// As long as you did not exit the calculator.
		while(option.equals("3")==false) {
		//If you choose option number 1.
		if(option.equals("1")==true) {
			System.out.println("Please Choose Your Base 10 Number:");
			String num=sc.next();
			while(isbaseten(num)==false) {
				System.out.println("Invalid Input, Please Choose Your Base 10 Number:");
				num=sc.next();
			}
			long number=tenbasenum(num);
			String str=basetentotwo(number);
			System.out.println("The Number " + number+ " In Base 2 Is: "+ str);
		}
		//If you choose option number 2.
		else {
			System.out.println("Please Choose Your Base 2 Number:");
			String str=sc.next();
			while(isbasetwo(str)==false) {
				System.out.println("Invalid Input, Please Choose Your Base 2 Number:");
				str=sc.next();
			}
			long number=basetwototen(str);
			System.out.println("The Number " + str+ " In Base 10 Is: "+ number);
		}
		// Again choosing your option in the calculator.
		System.out.println("Welocme Back To The Base Calculator, Please Choose Your Option:");
		System.out.println("1. Convet Number From Base 10 to Base 2:");
		System.out.println("2. Convet Number From Base 2 to Base 10:");
		System.out.println("3. Exit Calculator");
		option=sc.next();
		while(option.equals("1")==false & option.equals("2")==false & option.equals("3")==false) {
			System.out.println("Invalid Input, Try Again:");
			System.out.println("1. Convet Number From Base 10 to Base 2:");
			System.out.println("2. Convet Number From Base 2 to Base 10:");
			System.out.println("3. Exit Calculator");
			option=sc.next();
		}
		
		}
		System.out.println("Thank You For Using Our Calculator! To Use The Calculator Again Please Run Again The Program");

	}
	
	//function is converting a number from base 2 to base 10 
	public static long basetwototen (String str) {
		
		long num=0;
		int count=str.length()-1;
		for(int i = 0; i < str.length(); i++) {
			if(str.charAt(i)=='1') {
				num+=Math.pow(2, count);
			}
			count--;
		}
		
		return num;
	}
	
	
	//function is converting a number from base 10 to base 2 
	public static String basetentotwo(long num) {
		String str="";
		while(num !=0) {
			if(num%2 ==1)
				str+="1";
			else
				str+="0";
			num=num/2;
		}
		str=reverse(str);
		return str;
		
	}
	

	//function is getting a string and reverse it.
	public static String reverse(String str) {
		 	String x="";
	        char ch;
	        
	      for (int i=0; i<str.length(); i++)
	      {
	        ch= str.charAt(i);
	        x= ch+x; 
	      }
	      return x;
	}
	
	// function checking if the base two number is valid.
	public static boolean isbasetwo(String str) {
		for (int i=0; i<str.length(); i++) {
			if(str.charAt(i) != '0' && str.charAt(i) !='1')
				return false;
		}
		return true;
	}
	
	// function checking if the base ten number is valid.
	public static boolean isbaseten(String str) {
		for (int i=0; i<str.length(); i++) {
			if(str.charAt(i)!='0' && str.charAt(i)!='1' && str.charAt(i)!='2' && str.charAt(i)!='3' && str.charAt(i)!='4' 
					&& str.charAt(i)!='5' && str.charAt(i)!='6' && str.charAt(i)!='7' 
					&& str.charAt(i)!='8' && str.charAt(i)!='9')
				return false;
		}
		
		return true;
	}
	
	// converting the string to long type number.
	public static long tenbasenum(String str) {
		
		long number=0;
		int count=str.length()-1;
		for(int i = 0; i < str.length(); i++) {
			if(str.charAt(i)=='0')
				number+=0*(Math.pow(10, count));
			if(str.charAt(i)=='1')
				number+=1*(Math.pow(10, count));
			if(str.charAt(i)=='2')
				number+=2*(Math.pow(10, count));
			if(str.charAt(i)=='3')
				number+=3*(Math.pow(10, count));
			if(str.charAt(i)=='4')
				number+=4*(Math.pow(10, count));
			if(str.charAt(i)=='5')
				number+=5*(Math.pow(10, count));
			if(str.charAt(i)=='6')
				number+=6*(Math.pow(10, count));
			if(str.charAt(i)=='7')
				number+=7*(Math.pow(10, count));
			if(str.charAt(i)=='8')
				number+=8*(Math.pow(10, count));
			if(str.charAt(i)=='9')
				number+=9*(Math.pow(10, count));
			count--;
		}
		
		return number;
	}

	

}
