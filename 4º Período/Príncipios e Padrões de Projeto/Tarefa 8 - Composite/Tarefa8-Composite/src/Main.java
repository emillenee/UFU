public class Main {
    public static void main(String[] args) {
        Expressao expA = new Numero(0);
        Expressao expB = new Soma(new Numero(1), new Numero(2));
        Expressao expC = new Multiplicacao(new Numero(1),
                            new Soma(new Numero(2), new Numero(3)));
        Expressao expD = new Soma(
                            new Multiplicacao(new Numero(2),new Numero(3)),
                            new Divisao(new Numero(4), new Subtracao(new Numero(5), new Numero(3))));

        System.out.println("a) " + expA.getResultado());
        System.out.println("b) " + expB.getResultado());
        System.out.println("c) " + expC.getResultado());
        System.out.println("d) " + expD.getResultado());
    }
}