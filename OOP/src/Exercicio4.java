import java.util.Scanner;

public class Exercicio4 {
    public static void main(String[] args) {
        // menu de questões
        boolean on = true;
        Scanner scanner = new Scanner(System.in);

        while (on) {
            System.out.print("Digite o exercicio a ser realizado (1-7).\nInput : ");
            int selector = scanner.nextInt();

            switch (selector) {
                case 1:
                    System.out.print("Digite um valor maior que 0 e menor ou igual a 1000 : ");
                    int input1 = scanner.nextInt();
                    if (input1 >= 1 && input1 <= 1000) {
                        for (int i = 0; i <= input1; i++) {
                            if (i % 2 != 0) {
                                System.out.printf("%d\n", i);
                            }
                        }
                    }
                    break;

                case 2:
                    System.out.print("Digite o numero de entradas : ");
                    int input2 = scanner.nextInt(), in = 0, out = 0, input21;
                    for (int i = 0; i < input2; i++) {
                        System.out.print("Digite um numero : ");
                        input21 = scanner.nextInt();
                        if (input21 < 10 || input21 > 20) {
                            out++;
                        } else {
                            in++;
                        }
                    }
                    System.out.printf("%d In\n%d Out\n", in, out);
                    break;

                case 3:
                    System.out.print("Digite o numero de entradas : ");
                    int input3 = scanner.nextInt();
                    for (int i = 0; i < input3; i++) {
                        double valor1 = scanner.nextDouble(), valor2 = scanner.nextDouble(), valor3 = scanner.nextDouble();
                        double media = (valor1*2.0 + valor2*3.0 + valor3*5.0) / 10.0;
                        System.out.printf("%.1f\n", media);
                    }
                    break;

                case 4:
                    double input4, numerador, denominador;
                    System.out.print("Digite o numero de entradas : ");
                    input4 = scanner.nextDouble();
                    for (int i = 0; i < input4; i++) {
                        System.out.print("Digite o numerador : ");
                        numerador = scanner.nextDouble();
                        System.out.print("Digite o denominador : ");
                        denominador = scanner.nextDouble();
                        if (denominador == 0) {
                            System.out.println("divisao impossivel");
                        } else {
                            System.out.printf("%.1f\n", numerador / denominador);
                        }
                    }
                    break;

                case 5:
                    System.out.print("Digite um valor N para o fatorial: ");
                    int input5 = scanner.nextInt(),fat = 1;
                    for (int i = 1; i <= input5; i++) {
                        fat *= i;
                    }
                    System.out.println(fat);
                    break;

                case 6:
                    System.out.print("Digite um numero inteiro N para ver seus divisores: ");
                    int input6 = scanner.nextInt();
                    for (int i=1; i <= input6; i++) {
                        if (input6%i == 0) {
                            System.out.println(i);
                        }
                    }
                    break;

                case 7:
                    System.out.print("Digite um numero inteiro positivo N: ");
                    int input7 = scanner.nextInt();
                    for (int i = 1; i <= input7; i++) {
                        System.out.printf("%d %d %d\n", i, (i * i), (i * i * i));
                    }
                    break;

                default:
                    on = false;
            }
        }
    }
}