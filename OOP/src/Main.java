import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        //variaveis
        int on=1;
        //menu
        while (on == 1){
            float total;
            Scanner scanner = new Scanner(System.in);
            System.out.print("\nSelecione o plano para ser utilizado\n (Basico : B)\n (Plus : P)\n : ");
            String plano_gato = scanner.next();
            char plano = plano_gato.charAt(0);
            System.out.print("Digite a entrada : ");
            float entrada = scanner.nextFloat();
            if (plano == 'b' || plano == 'B'){
                entrada -= 100;
                if (entrada<0){
                    entrada=0;
                }
                total = 50 + (2*entrada);
            } else if (plano == 'p' || plano == 'P') {
                entrada -= 300;
                if (entrada<0){
                    entrada=0;
                }
                total = 100 + entrada;
            }
            else {
                break;
            }
            System.out.printf("Valor a pagar = %.2f",total);
        }
    }
}