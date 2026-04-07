import java.util.Scanner;

public class exercicio3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean on = true;
        int selector;
        while (on) {
            System.out.print("\nSelecione o Exercicio para executar : ");
            selector = scanner.nextInt();
            switch (selector){
                case 1:
                    int senha;
                    do {
                        System.out.print("\nInput : ");
                        senha = scanner.nextInt();
                        if (senha != 2002) {
                            System.out.print("Senha invalida");
                        } else {System.out.print("Acesso permitido");}
                    } while (senha != 2002);
                    break;
                case 2:
                    do {
                        System.out.print("\nAtividade) Input x : ");
                        float x = scanner.nextFloat();
                        System.out.print("\nAtividade) Input y : ");
                        float y = scanner.nextFloat();
                        if (x < 0) {
                            if (y < 0) {
                                //q3
                                System.out.print("terceiro");
                            } else if (y > 0) {
                                //q2
                                System.out.print("segundo");
                            } else {
                                //eixo y
                                break;
                            }
                        } else if (x > 0) {
                            if (y < 0) {
                                //q4
                                System.out.print("quarto");
                            } else if (y > 0) {
                                //q1
                                System.out.print("primeiro");
                            } else {
                                //eixo y
                                break;
                            }
                        } else if (y == 0) {
                            //origem
                            break;
                        } else {
                            // eixo x
                            break;
                        }
                    } while (true);
                    break;
                case 3:
                    int input;
                    int[] preferencia={0,0,0};
                    while(true){
                        System.out.print("\nInput : ");
                        input = scanner.nextInt();
                        if (input==1){
                            preferencia[0]++;
                        } else if (input==2) {
                            preferencia[1]++;
                        } else if (input==3) {
                            preferencia[2]++;
                        } else if (input==4) {
                            break;
                        }
                    }
                    System.out.println("MUITO OBRIGADO");
                    System.out.printf("\n Alcool : %d \n Gasolina: %d \n Disel: %d \n", preferencia[0],preferencia[1],preferencia[2]);
                default:
                    on = false;
            }

        }
    }
}
