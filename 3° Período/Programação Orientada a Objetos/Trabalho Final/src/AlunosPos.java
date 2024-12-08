import java.io.Serial;

public class AlunosPos extends Estudante implements Comparar<Estudante>{
    @Serial
    private static final long serialVersionUID = 1L;
    protected String temaPesquisa;

    public AlunosPos(String CPF, String nome, String dataNascimento, float CRA, String temaPesquisa){
        super(CPF, nome, dataNascimento, CRA);
        this.temaPesquisa = temaPesquisa;
    }

    public void setTemaPesquisa(String temaPesquisa) {
        this.temaPesquisa = temaPesquisa;
    }

    public String getTemaPesquisa() {
        return temaPesquisa;
    }

    public int compara(Estudante cmp){
        if(this.CRA < cmp.CRA){
            return -1;
        } else if(this.CRA > cmp.CRA){
            return 1;
        } else {
            return 0;
        }
    }

    @Override
    public String toString() {
        return ">>>Aluno [CPF: " + CPF + ", Nome: " + nome +
                ", Data de Nascimento: " + dataNascimento + ", CRA:" + CRA + ", Tema de Pesquisa: " + temaPesquisa + "]\n";
    }
}