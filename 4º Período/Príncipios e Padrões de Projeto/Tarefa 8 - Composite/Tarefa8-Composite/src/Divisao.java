public class Divisao extends Operacao{
    public Divisao(Expressao esquerda, Expressao direita){
        super(esquerda, direita);
    }

    @Override
    public double getResultado() {
        return esquerda.getResultado() / direita.getResultado();
    }
}
