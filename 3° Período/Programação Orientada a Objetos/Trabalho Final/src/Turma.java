import java.io.*;
import java.util.*;

public class Turma implements Serializable, Comparar<Turma>{
    @Serial
    private static final long serialVersionUID = 1L;
    private Disciplina disciplina;
    private String semestre;
    private String ano;
    private Professor professor;
    private List<Estudante> estudantes;

    public Turma(Disciplina disciplina, String semestre, String ano) {
        this.disciplina = disciplina;
        this.semestre = semestre;
        this.ano = ano;
    }

    public List<Estudante> getEstudantes() {
        return estudantes;
    }

    public Professor getProfessor() {
        return professor;
    }

    public void setProfessor(Professor professor) {
        this.professor = professor;
    }

    public void setEstudantes(List<Estudante> estudantes) {
        this.estudantes = estudantes;
    }

    public void setSemestre(String semestre) {
        this.semestre = semestre;
    }

    public void setAno(String ano) {
        this.ano = ano;
    }

    public void setDisciplina(Disciplina disciplina) {
        this.disciplina = disciplina;
    }

    public String getSemestre() {
        return semestre;
    }

    public String getAno() {
        return ano;
    }

    public Disciplina getDisciplina() { return disciplina; }

    public int compara(Turma o) {
        Turma compara = (Turma) o;
        if (this.getAno().compareToIgnoreCase(compara.getAno())<0) return -1;
        if (this.getAno().compareToIgnoreCase(compara.getAno())>0) return 1;
        if(this.getSemestre().compareToIgnoreCase(compara.getSemestre())<0) return -1;
        if(this.getSemestre().compareToIgnoreCase(compara.getSemestre())>0)return 1;
        return 0;
    }

    @Override
    public String toString() {
        return ">>>Turma [Disciplina: " + disciplina.getNome() + "\n      Semestre: " + semestre + "\n      Ano: " + ano + "\n      Professor: " + professor + "\n      Alunos{\n" + estudantes + "}\n]\n";
    }
}
