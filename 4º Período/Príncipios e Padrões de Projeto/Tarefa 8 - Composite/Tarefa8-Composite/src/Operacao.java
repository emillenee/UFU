abstract class Operacao implements Expressao{
    protected Expressao esquerda;
    protected Expressao direita;

    public Operacao(Expressao esquerda, Expressao direita) {
        this.esquerda = esquerda;
        this.direita = direita;
    }
}
