import java.io.Serial;
import java.io.Serializable;

public class Disciplina implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
    private String codigo;
    private String nome;
    private int cargaHoraria;

    public Disciplina(String codigo, String nome, int cargaHoraria) {
        this.codigo = codigo;
        this.nome = nome;
        this.cargaHoraria = cargaHoraria;
    }

    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setCargaHoraria(int cargaHoraria) {
        this.cargaHoraria = cargaHoraria;
    }

    public String getCodigo() {
        return codigo;
    }

    public String getNome() {
        return nome;
    }

    public int getCargaHoraria() {
        return cargaHoraria;
    }

    @Override
    public String toString() {
        return "      >>>Disciplina [Código: " + codigo + ", Nome: " + nome +
                ", Carga Horaria: " + cargaHoraria + "]\n";
    }
}
