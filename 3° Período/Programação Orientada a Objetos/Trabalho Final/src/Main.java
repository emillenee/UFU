import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        SistemaUniversidade sistema = new SistemaUniversidade();
        Scanner sc = new Scanner(System.in);
        String cpf, nome, dataNascimento, estagio, inicioContrato, codigo, semestre, ano;
        float cra;

        int opcao, id = 0;
        do {
            System.out.println("----------MENU----------");
            System.out.println("" +
                    "1) Criar arquivo\n" +
                    "2) Popular o sistema\n" +
                    "3) Cadastrar novo aluno\n" +
                    "4) Cadastrar novo Professor\n" +
                    "5) Cadastrar nova Disciplina\n" +
                    "6) Cadastrar nova Turma\n" +
                    "7) Associar Professor à Turma\n" +
                    "8) Associar Lista de Estudantes à Turma\n" +
                    "9) Mostrar Estudantes\n" +
                    "10) Mostrar Professores\n" +
                    "11) Mostrar Disciplinas\n" +
                    "12) Mostrar Turmas\n" +
                    "13) Encontrar Turmas de um Professor\n" +
                    "14) Sair");
            opcao = sc.nextInt();
            sc.nextLine();

            switch (opcao) {
                case 1:
                    InicializarDados.inicializar();
                    break;
                case 2:
                    try {
                        sistema = (SistemaUniversidade) Persistencia.carregarDados("sistema.dat");
                    } catch (IOException | ClassNotFoundException e) {
                        System.err.println("Erro ao carregar dados de sistema.dat: " + e.getMessage());
                        sistema = new SistemaUniversidade();
                    }
                    break;
                case 3:
                    System.out.print("CPF: ");
                    cpf = sc.nextLine();
                    System.out.print("Nome: ");
                    nome = sc.nextLine();
                    System.out.print("Data de Nascimento (dd/MM/yyyy): ");
                    dataNascimento = sc.nextLine();
                    while(true){
                        try{
                            System.out.print("CRA: ");
                            cra = sc.nextFloat();
                            sc.nextLine();
                            Estudante.setCRA(cra);
                            break;
                        } catch(CraException e) {
                            System.err.println("Erro: " + e.getMessage());
                        }
                    };
                    System.out.print("Tipo (1-Graduação, 2-Pós-Graduação): ");
                    int tipo = sc.nextInt();
                    sc.nextLine();
                    if (tipo == 1) {
                        System.out.print("Estágio Supervisionado: ");
                        estagio = sc.nextLine();
                        sistema.addEstudante(new AlunosGraduacao(cpf, nome, dataNascimento, cra, estagio));
                    } else if (tipo == 2) {
                        System.out.print("Tema de Pesquisa: ");
                        String pesquisa = sc.nextLine();
                        sistema.addEstudante(new AlunosPos(cpf, nome, dataNascimento, cra, pesquisa));
                    }
                    break;
                case 4:
                    System.out.print("CPF: ");
                    cpf = sc.nextLine();
                    System.out.print("Nome: ");
                    nome = sc.nextLine();
                    System.out.print("Data de Nascimento (dd/MM/yyyy): ");
                    dataNascimento = sc.nextLine();
                    System.out.print("Início do Contrato (dd/MM/yyyy): ");
                    inicioContrato = sc.nextLine();
                    System.out.print("Departamento: ");
                    String departamento = sc.nextLine();
                    sistema.addProfessor(new Professor(cpf, nome, dataNascimento, inicioContrato, departamento));
                    break;
                case 5:
                    System.out.print("Código: ");
                    codigo = sc.nextLine();
                    System.out.print("Nome: ");
                    nome = sc.nextLine();
                    System.out.print("Carga Horária: ");
                    int cargaHoraria = sc.nextInt();
                    sc.nextLine();
                    sistema.addDisciplina(new Disciplina(codigo, nome, cargaHoraria));
                    break;
                case 6:
                    try {
                        System.out.print("Código da Disciplina: ");
                        codigo = sc.nextLine();
                        Disciplina disciplina = sistema.buscarDisciplinaPorCodigo(codigo);
                        System.out.print("Semestre: ");
                        semestre = sc.nextLine();
                        System.out.print("Ano: ");
                        ano = sc.nextLine();
                        sistema.addTurma(new Turma(disciplina, semestre, ano));
                        System.out.println("Turma cadastrada com sucesso!");
                    } catch (DisciplinaNaoEncontradaException e) {
                        System.err.println("Erro: " + e.getMessage());
                    }
                    break;
                case 7:
                    id = 0;
                    System.out.println("\n--- Turmas ---");
                    for (Turma turmas : sistema.getTurmas()){
                        System.out.printf("ID da turma: %d\n", id);
                        System.out.println(turmas.toString());
                        id++;
                    }
                    System.out.print("Digite o ID da Turma a ser adicionado o professor: ");
                    int idTurma = sc.nextInt();
                    sc.nextLine();

                    System.out.println("\n--- Professores ---");
                    for (Professor professores : sistema.getProfessores())
                        System.out.println(professores.toString());

                    if (idTurma >= 0 && idTurma < sistema.getTurmas().size()) {
                        Turma turma = sistema.getTurmas().get(idTurma);
                        System.out.print("Digite o CPF do Professor, com '.' e '-': ");
                        cpf = sc.nextLine();
                        for (Professor professor : sistema.getProfessores()) {
                            if (professor.getCPF().equals(cpf)) {
                                sistema.associarTurmaProfessor(turma, professor);
                                System.out.println("Professor associado com sucesso!");
                                break;
                            }
                        }
                    } else {
                        System.err.println("ID da turma inválido.");
                    }
                    break;
                case 8:
                    id = 0;
                    System.out.println("\n--- Turmas ---");
                    for (Turma turmas : sistema.getTurmas()){
                        System.out.printf("ID da turma: %d\n", id);
                        System.out.println(turmas.toString());
                        id++;
                    }
                    System.out.print("Digite o ID da Turma a qual serão adicionados os alunos: ");
                    idTurma = sc.nextInt();
                    sc.nextLine();
                    if (idTurma >= 0 && idTurma < sistema.getTurmas().size()) {
                        Turma turma = sistema.getTurmas().get(idTurma);

                        System.out.println("\n--- Estudantes ---");
                        for (Estudante estudantes : sistema.getEstudantes())
                            System.out.println(estudantes.toString());

                        System.out.print("Digite os CPF dos Estudantes (com pontuação e separados por vírgula): ");
                        String[] cpfsEstudantes = sc.nextLine().split(",");
                        List<Estudante> listaEstudantes = new ArrayList<>();
                        for (String cpfEstudante : cpfsEstudantes) {
                            for (Estudante estudante : sistema.getEstudantes()) {
                                if (estudante.getCPF().equals(cpfEstudante.trim())) {
                                    listaEstudantes.add(estudante);
                                }
                            }
                        }
                        sistema.associarTurmaEstudantes(turma, listaEstudantes);
                        System.out.println("Estudantes associados com sucesso!");
                    } else {
                        System.err.println("ID da turma inválido.");
                    }
                    break;
                case 9:
                    Ordenar.ordenacao(sistema.getEstudantes());
                    System.out.println("\n--- Estudantes ---");
                    for (Estudante estudantes : sistema.getEstudantes())
                        System.out.println(estudantes.toString());
                    break;
                case 10:
                    Ordenar.ordenacao(sistema.getProfessores());
                    System.out.println("\n--- Professores ---");
                    for (Professor professores : sistema.getProfessores())
                        System.out.println(professores.toString());
                    break;
                case 11:
                    System.out.println("\n--- Disciplinas ---");
                    for (Disciplina disciplinas : sistema.getDisciplinas())
                        System.out.println(disciplinas.toString());
                    break;
                case 12:
                    Ordenar.ordenacao(sistema.getTurmas());
                    System.out.println("\n--- Turmas ---");
                    for (Turma turmas : sistema.getTurmas())
                        System.out.println(turmas.toString());
                    break;
                case 13:
                    System.out.print("CPF do Professor: ");
                    cpf = sc.nextLine();
                    for (Professor professor : sistema.getProfessores()) {
                        if (professor.getCPF().equals(cpf)) {
                            List<Turma> turmasDoProfessor = sistema.buscarTurmasPorProfessor(professor);
                            System.out.println("Turmas do Professor " + professor.getNome() + ":");
                            for (Turma turma : turmasDoProfessor) {
                                System.out.println(turma);
                            }
                            break;
                        }
                    }
                    break;
                case 14:
                    System.out.println("Saindo do programa...");
                    break;
                default:
                    System.out.println("Opção inválida, tente novamente.");
                    break;
            }
        } while (opcao != 14);

        try {
            Persistencia.salvarDados(sistema, "sistema.dat");
        } catch (IOException e) {
            System.err.println("Erro ao salvar dados: " + e.getMessage());
        }
        sc.close();
    }
}
