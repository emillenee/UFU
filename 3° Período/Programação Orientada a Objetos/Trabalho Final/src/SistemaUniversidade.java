import java.io.*;
import java.util.*;

public class SistemaUniversidade implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
    private List<Estudante> estudantes = new ArrayList<>();
    private List<Professor> professores = new ArrayList<>();
    private List<Disciplina> disciplinas = new ArrayList<>();
    private List<Turma> turmas = new ArrayList<>();

    public SistemaUniversidade() {
    }

    public List<Turma> buscarTurmasPorProfessor(Professor professor) {
        List<Turma> turmasDoProfessor = new ArrayList<>();
        for (Turma turma : turmas) {
            if (turma.getProfessor() != null && turma.getProfessor().equals(professor)) {
                turmasDoProfessor.add(turma);
            }
        }
        return turmasDoProfessor;
    }

    public void associarTurmaProfessor(Turma turma, Professor professor) {
        turma.setProfessor(professor);
    }

    public void associarTurmaEstudantes(Turma turma, List<Estudante> estudantes) {
        turma.setEstudantes(estudantes);
    }

    public void addEstudante(Estudante estudante) {
        estudantes.add(estudante);
    }

    public void addProfessor(Professor professor) {
        professores.add(professor);
    }

    public void addDisciplina(Disciplina disciplina) {
        disciplinas.add(disciplina);
    }

    public void addTurma(Turma turma) {
        turmas.add(turma);
    }

    public List<Estudante> getEstudantes() {
        return estudantes;
    }

    public List<Professor> getProfessores() {
        return professores;
    }

    public List<Disciplina> getDisciplinas() {
        return disciplinas;
    }

    public List<Turma> getTurmas() {
        return turmas;
    }

    public Disciplina buscarDisciplinaPorCodigo(String codigo) throws DisciplinaNaoEncontradaException {
        for (Disciplina d : disciplinas) {
            if (d.getCodigo().equals(codigo)) {
                return d;
            }
        }
        throw new DisciplinaNaoEncontradaException("Disciplina não encontrada com o código: " + codigo);
    }

}