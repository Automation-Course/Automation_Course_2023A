package calculator;
import java.util.Scanner;
public class convert {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		;
		String[] str = null;
		
		Scanner myObj = new Scanner(System.in);  // Create a Scanner object
		System.out.println("what action would you like to do?");
		System.out.println("1. convert binary to decimal");
		System.out.println("2. convert decimal to binary");
		System.out.println("3. end program");
		
		String choice = myObj.nextLine();  // Read user input
		
		if(choice.equalsIgnoreCase("1")) 
		{
			System.out.println("please enter a binary string");
			
			String query = myObj.nextLine();
			try {
				System.out.println("the decimal number is: "+ binToDec(query) );
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				try {
					Thread.sleep(100);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				System.out.println("please try again!");
				
			}
			finally{
				main(str);
			}
		}
		else if(choice.equalsIgnoreCase("2")) 
		{
			System.out.println("please enter your number (must be integer)");
			try{
				int query = myObj.nextInt();
				System.out.println("the binary string is: "+decToBin(query));}
			catch (Exception ex) {
				// TODO Auto-generated catch block
				ex.printStackTrace();
				System.out.println("please try again");	
				
			}
			
			finally{
				main(str);
			}
		}
		else if(choice.equalsIgnoreCase("3")){
			
		}
		else {
			System.out.println("please choose a valid option");
			main(str);
		}
		
		
		}

	

	public static int binToDec(	String bin) throws Exception {
		if(bin.charAt(0)== '-') {
			return -binToDec(bin.substring(1));
		}
		int result = 0;
		for(int i =0; i <bin.length();i++) {
			if(Character.getNumericValue(bin.charAt(bin.length()-1-i))!=0 && Character.getNumericValue(bin.charAt(bin.length()-1-i))!=1) {
				throw new Exception("the input is not valid, please enter a binary number");
			};
			result = (int) (result + Math.pow(2,i)*Character.getNumericValue(bin.charAt(bin.length()-1-i)));
						
		}
		return result;
	}
	
	public static String decToBin(int dec)throws Exception {
		
		if(dec<0) {
			return "-" + decToBin(-dec);
		}
		int l = 0;
		String res = "";
		while(dec>Math.pow(2, l)) {
			l++;
		}
		
		for(int i = l-1;i >=0; i--) {
			if(dec >= Math.pow(2, i)) {
				res += "1";
				dec -= Math.pow(2, i);
			}
			else {
				res +="0";
			}
			
		}
		return res;
	}
}
