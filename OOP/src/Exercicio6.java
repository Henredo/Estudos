import java.util.Scanner;

public class Exercicio6 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int acc_num;
        String acc_holder,str_input;
        double acc_money=0,d_input;
        char c_opt;

        //primeiro acesso
        System.out.println("Enter account number: ");
        acc_num = scanner.nextInt();
        System.out.println("Enter account holder: ");
        acc_holder = scanner.next();
        System.out.println("Is there na initial deposit (y/n)?: ");
        c_opt = scanner.next().charAt(0);
        if(c_opt == 'y'|| c_opt == 'Y'){
            System.out.println("Enter initial deposit value: ");
            acc_money = scanner.nextInt();
        }

        //magia negra que faz nextline funcioar
        scanner.nextLine();
        //seguintes
        System.out.println("Account data: ");
        str_input = scanner.nextLine();
        if (!str_input.isEmpty()){
            acc_holder = str_input;
        }
        System.out.printf("\nUpdated Account data:\nAccount %d, Holder: %s, Balance: $ %.2f\n",acc_num,acc_holder,acc_money);

        System.out.println("Enter deposit value: ");
        d_input = scanner.nextDouble();
            if (d_input > 0){acc_money += d_input;
        }
        System.out.printf("\nUpdated Account data:\nAccount %d, Holder: %s, Balance: $ %.2f\n",acc_num,acc_holder,acc_money);

        System.out.println("Enter withdraw value: ");
        d_input = scanner.nextDouble();
        if (d_input > 0){acc_money -= d_input+5;
        }
        System.out.printf("\nUpdated Account data:\nAccount %d, Holder: %s, Balance: $ %.2f\n",acc_num,acc_holder,acc_money);
    }
}