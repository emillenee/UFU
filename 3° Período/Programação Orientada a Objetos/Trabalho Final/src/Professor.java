import java.io.Serial;

public class Professor extends Pessoa implements Comparar<Professor>{
    @Serial
    private static final long serialVersionUID = 1L;
    protected String inicioContrato;
    protected String departamentoVinculado;

    public Professor(String CPF, String nome, String dataNascimento, String inicioContrato, String  departamentoVinculado){
        super(CPF, nome, dataNascimento);
        this.inicioContrato = inicioContrato;
        this.departamentoVinculado = departamentoVinculado;
    }

    public void setInicioContrato(String inicioContrato) {
        this.inicioContrato = inicioContrato;
    }

    public void setDepartamentoVinculado(String departamentoVinculado) {
        this.departamentoVinculado = departamentoVinculado;
    }

    public String getInicioContrato() {
        return inicioContrato;
    }

    public String getDepartamentoVinculado() {
        return departamentoVinculado;
    }

    public int compara(Professor obj) {
        Professor cmp =  obj;
        if (this.getInicioContrato().compareToIgnoreCase(cmp.getInicioContrato())<0) return -1;
        if (this.getInicioContrato().compareToIgnoreCase(cmp.getInicioContrato())>0) return 1;
        return 0;
    }

    @Override
    public String toString() {
        return  ">>>Professor [CPF: " + CPF +
                ", Nome: " + nome +
                ", Data de Nascimento: " + dataNascimento +
                ", Inicio do Contrato: " + inicioContrato +
                ", Departamento Vinculado: " + departamentoVinculado +
                "}\n";
    }
}
