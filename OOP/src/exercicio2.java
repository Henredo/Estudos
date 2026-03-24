import java.util.Scanner;

public class exercicio2 {
    public static void main(String[] args) {
        //menu de questões
        boolean on = true;
        while (on) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Digite o exercicio a ser realizado (1-8).\nInput : ");
            int selector = scanner.nextInt();
            switch (selector) {
                case 1:
                    System.out.print("Atividade) Input : ");
                    int input = scanner.nextInt();
                    if (input < 0) {
                        System.out.print("\nNegativo");
                    } else {
                        System.out.print("\nNao negativo");
                    }
                    break;
                case 2:
                    System.out.print("Atividade) Input : ");
                    int input2 = scanner.nextInt();
                    if ((input2 % 2) == 0) {
                        System.out.print("\nPar");
                    } else {
                        System.out.print("\nImpar");
                    }
                    break;
                case 3:
                    System.out.print("Atividade) Input 1 : ");
                    int input31 = scanner.nextInt();
                    System.out.print("Atividade) Input 2 : ");
                    int input32 = scanner.nextInt();
                    if (input31 % input32 == 0) {
                        System.out.print("Sao Multiplos");
                    } else if (input32 % input31 == 0) {
                        System.out.print("Sao Multiplos");
                    } else {
                        System.out.print("Nao sao Multiplos");
                    }
                    break;
                case 4:
                    System.out.print("Atividade) Input 1 : ");
                    int input41 = scanner.nextInt();
                    System.out.print("Atividade) Input 2 : ");
                    int input42 = scanner.nextInt();
                    int horas = 0;
                    boolean match = false;
                    while (!match) {
                        input41++;
                        horas++;
                        if (input41 >= 24) {
                            input41 = 0;
                        }
                        if (input41 == input42) {
                            match = true;
                        }
                    }
                    System.out.printf("O jogo durou %d horas", horas);
                    break;
                case 5:
                    System.out.print("Tabela de preços :\n1) Cachorro quente - 4,00\n2) X-Salada 4,50\n3) X-Bacon 5,00\n4) Torrada Simples 2,00\n5) Refrigerante 1,50\n");
                    System.out.print("Atividade) Input 1 : ");
                    int input51 = scanner.nextInt();
                    System.out.print("Atividade) Input 2 : ");
                    float input52 = scanner.nextFloat();
                    float[] item_prices = {4.0f, 4.5f, 5.0f, 2.0f, 1.5f};
                    System.out.printf("Total : R$ %.2f", item_prices[input51 - 1] * input52);
                    break;
                case 6:
                    System.out.print("Atividade) Input : ");
                    float input6 = scanner.nextFloat();
                    if (input6 < 0) {
                        System.out.print("Fora de intervalo");
                        break;
                    } else if (input6 < 25) {
                        System.out.print("Intervalo [0,25]");
                        break;
                    } else if (input6 < 50) {
                        System.out.print("Intervalo [25,50]");
                        break;
                    } else if (input6 < 75) {
                        System.out.print("Intervalo [50,75]");
                        break;
                    } else if (input6 <= 100) {
                        System.out.print("Intervalo [75,100]");
                        break;
                    } else {
                        System.out.print("Fora de intervalo");
                        break;
                    }
                case 7:
                    System.out.print("Atividade) Input 1 : ");
                    float input71 = scanner.nextFloat();
                    System.out.print("Atividade) Input 2 : ");
                    float input72 = scanner.nextFloat();
                    if (input71 < 0) {
                        if (input72 < 0) {
                            //q3
                            System.out.print("Q3");
                        } else if (input72 > 0) {
                            //q2
                            System.out.print("Q2");
                        } else {
                            //eixo y
                            System.out.print("Eixo x");
                        }
                    } else if (input71 > 0) {
                        if (input72 < 0) {
                            //q4
                            System.out.print("Q4");
                        } else if (input72 > 0) {
                            //q1
                            System.out.print("Q1");
                        } else {
                            //eixo y
                            System.out.print("Eixo x");
                        }
                    } else if (input72 == 0) {
                        //origem
                        System.out.print("Origem");
                    } else {
                        // eixo x
                        System.out.print("Eixo y");
                    }
                    break;
                case 8:
                    System.out.print("Atividade) Input : ");
                    double input8 = scanner.nextDouble(), imposto=0;
                    if (input8 <= 2000.00) {
                        System.out.print("Isento\n");
                    } else if (input8 <= 3000.00) {
                        imposto = (input8 - 2000.00) * 0.08;
                    } else if (input8 <= 4500.00) {
                        imposto = 1000.00 * 0.08 + (input8 - 3000.00) * 0.18;
                    } else {
                        imposto = 1000.00 * 0.08 + 1500.00 * 0.18 + (input8 - 4500.00) * 0.28;
                    }
                        System.out.printf("R$ %.2f\n", imposto);
                    break;
                default:
                    on = false;
            }
        }
    }
}
