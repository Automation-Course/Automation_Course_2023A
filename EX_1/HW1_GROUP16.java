import java.util.Scanner;
public class HW1 {
    static Scanner sc = new Scanner(System.in); // Scanner object
    public static void main(String[] args) {
        while(true){
        boolean isChoiceValid = false;
        System.out.println("Welcome to our Base Converter!\n");
        while(!isChoiceValid){ // keep trying until the choice is valid
           System.out.println("Please choose the prefferd option:");
           System.out.println("1 - Binary to Decimal   2 - Decimal to Binary");
          
           String choice = sc.nextLine();
           switch(choice){
               case "1":
                   convertBinToDec(); // if chose 1 - convert binary number to decimal number
                   isChoiceValid = true;
                   break;
               case "2":
                   convertDecToBin(); // if chose 2 - convert decimal number to binary number
                   isChoiceValid = true; 
                   break;
               default: System.out.println("Error! Please choose one of the existing options!"); // the option is not 1 or 2 
           }
           }
          
        }
    }
	   
    public static void convertDecToBin(){
          boolean done = false;
          while(!done){
            System.out.println("Enter a decimal number");
            try{
	        String decNum = sc.nextLine();
	        int Dec = Integer.parseInt(decNum);
	        String bin = Integer.toBinaryString(Dec); // converting from a decimal number to a binary number 
	  	    System.out.println("The decimal num as a binary num is: "+bin+"\n");
	  	    done = true;
            }
            catch(Exception e){ // not a valid decimal number
                 System.out.println("Please enter a valid decimal number");
                 
            }
      }
    }
    
    public static void convertBinToDec(){
        boolean done = false;
        while(!done){
          System.out.println("Enter a binary number");
	      String binNum = sc.nextLine();
	      try{
	          long Bin = Long.parseLong(binNum); // first input check
	          if(checkIfBin(Bin, binNum)){ // second input check
	              convertBinaryToDecimal(Bin); // converting from binary number to a decimal number 
	              done = true;
	          }
	          else{
	              System.out.println("Please enter a valid binary number");
	              done = false;
	          }
	      }
	      catch(Exception e){
	           System.out.println("Please enter a valid binary number");
	           done = false;
	      }
          }
	}
	
	 public static boolean checkIfBin(long bin, String strbin){ // check if number contains only 1s and 0s
        int size = strbin.length();
        long ReducedBin = bin;
        long digit;
        for(int i = 1; i <= size; i++){
            digit = ReducedBin % 10;
            if(digit != 0 && digit != 1){
                return false;
            }
            ReducedBin = ReducedBin / 10;
        }
        return true;
    }

	public static void convertBinaryToDecimal(long num){
		int decimalNumber = 0, i = 0;
		long remainder;
		    
		while (num != 0) {
		   remainder = num % 10;
		   num /= 10;
		   decimalNumber += remainder * Math.pow(2, i);
		   ++i;
		    }
		  System.out.println("The binary num as a decimal num is: "+decimalNumber+"\n");
    }
}