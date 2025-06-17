public class Multiplicacao extends Operacao{
    public Multiplicacao(Expressao esquerda, Expressao direta){
        super(esquerda, direta);
    }

    public double getResultado(){
        return esquerda.getResultado() * direita.getResultado();
    }
}
