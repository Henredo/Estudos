import java.util.Scanner;

public class Exercicio5dulpa {

    public static class Rectangle{
        //declaração de atributos
        Scanner scanner = new Scanner(System.in);
        double width,height;
        //métodos
        void SetWidth(){
            System.out.print("Insira a Largura : ");
            width = scanner.nextDouble();
        }
        void SetHeight(){
            System.out.print("Insira a Altura : ");
            height = scanner.nextDouble();
        }
        double area(){
            return width * height;
        }
        double perimeter(){
            return 2 * (width + height);
        }
        double diagonal(){
            return Math.sqrt(Math.pow(width,2)+Math.pow(height,2));
        }
        public String toString() {
            return String.format("Width = %.2f, Height = %.2f", width, height);
        }
    }

    public static void main(String[] args) {
        Rectangle r = new Rectangle();
        r.SetWidth();
        r.SetHeight();
        System.out.println("Para o retangulo "+r);
        System.out.println("Area : "+r.area());
        System.out.println("Perimetro : "+r.perimeter());
        System.out.println("Diagonal : "+r.diagonal());
    }
}
