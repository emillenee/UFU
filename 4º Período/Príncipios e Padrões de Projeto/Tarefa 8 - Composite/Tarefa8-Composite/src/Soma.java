public class Soma extends Operacao{
    public Soma(Expressao esquerda, Expressao direita) {
        super(esquerda, direita);
    }

    @Override
    public double getResultado() {
        return esquerda.getResultado() + direita.getResultado();
    }
}
