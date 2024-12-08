import java.io.Serial;

public abstract class Estudante extends Pessoa implements Comparar<Estudante>{
    @Serial
    private static final long serialVersionUID = 1L;
    protected float CRA;

    public Estudante(String CPF, String nome, String dataNascimento, float CRA){
        super(CPF, nome, dataNascimento);
        this.CRA = CRA;
    }

    public int compara(Comparar obj){
        Estudante cmp = (Estudante) obj;
        if(this.CRA < cmp.CRA){
            return -1;
        } else if(this.CRA > cmp.CRA){
            return 1;
        } else {
            return 0;
        }
    }

    public static void setCRA(float CRA) throws CraException{
        if(CRA < 0){
            throw new CraException("CRA não pode ser inferior a zero. Digite novamente.");
        }
        if(CRA > 100){
            throw new CraException("CRA não pode ser superior a cem. Digite novamente.");
        }
    }

    public float getCRA() {
        return CRA;
    }

    public abstract String toString();
}
