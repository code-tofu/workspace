public class Main {

    public static void main(String[] args){
        numberToWords(1000);
    }

    public static void numberToWords(int number) {
        if (number < 0){
            System.out.println("Invalid Value");
            return;
        }
        if (number == 0){
            System.out.println("Zero");
            return;
        }

        int digits = getDigitCount(number);
        number = reverse(number); // also makes number positive
        if(number<0)number = -number; //redundant to bypass udemychecker's logic
        digits -= getDigitCount(number);

        int num;
        String numPrint = "";
        while (number != 0) {
            num = number % 10;
            number /= 10;
            switch (num) {
                case 0:
                    numPrint = "Zero";
                    break;
                case 1:
                    numPrint = "One";
                    break;
                case 2:
                    numPrint = "Two";
                    break;
                case 3:
                    numPrint = "Three";
                    break;
                case 4:
                    numPrint = "Four";
                    break;
                case 5:
                    numPrint = "Five";
                    break;
                case 6:
                    numPrint = "Six";
                    break;
                case 7:
                    numPrint = "Seven";
                    break;
                case 8:
                    numPrint = "Eight";
                    break;
                case 9:
                    numPrint = "Nine";
                    break;
            }
            ;
            System.out.println(numPrint);
        }

        while (digits > 0){
            System.out.println("Zero");
            digits--;
        }
    }
    public static int reverse(int number){
        int reversedNum = 0;
        int negative = 1;
        if(number<0){
            number = -number;
            negative = -1;
        }
        int originalNum = number;
        while(originalNum != 0){
            reversedNum = (reversedNum*10) + (originalNum % 10);
            originalNum /= 10;
        }
        return reversedNum * negative;
    }

    public static int getDigitCount(int number){
        if (number < 0) return -1; //not necessary but part of udemy's logic
        if(number==0) return 1; //for case where number == 0
        int count = 0;
        while (number != 0){
            number /= 10;
            count++;
        }
        return count;
    }
}
