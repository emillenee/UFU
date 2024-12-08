import java.io.Serial;

public class AlunosGraduacao extends Estudante implements Comparar<Estudante>{
    @Serial
    private static final long serialVersionUID = 1L;
    protected String estagio;

    public AlunosGraduacao(String CPF, String nome, String dataNascimento, float CRA, String estagio){
        super(CPF, nome, dataNascimento, CRA);
        this.estagio = estagio;
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

    public void setEstagio(String estagio) {
        this.estagio = estagio;
    }

    public String getEstagio() {
        return estagio;
    }


    @Override
    public String toString(){
        return ">>>Aluno [CPF: " + super.CPF + ", Nome: " + super.nome +
                ", Data de Nascimento: " + super.dataNascimento + ", CRA:" + super.CRA + ", Estagio: " + estagio + "]\n";
    }
}