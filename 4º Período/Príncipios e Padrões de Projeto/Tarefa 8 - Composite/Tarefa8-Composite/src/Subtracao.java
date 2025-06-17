public class Subtracao extends Operacao{
    public Subtracao(Expressao esquerda, Expressao direita) {
        super(esquerda, direita);
    }

    @Override
    public double getResultado() {
        return esquerda.getResultado() - direita.getResultado();
    }
}
