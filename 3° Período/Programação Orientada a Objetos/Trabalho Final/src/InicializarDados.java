public class InicializarDados {
        public static void inicializar() {
            SistemaUniversidade sistema = new SistemaUniversidade();

            try {

                sistema.addEstudante(new AlunosGraduacao("836.289.018-77", "Ana", "03/07/2001", 67.5f, "ML"));
                sistema.addEstudante(new AlunosGraduacao("937.289.786-89", "Fabio", "25/04/2002", 78.7f, "TI"));
                sistema.addEstudante(new AlunosGraduacao("384.728.999-86", "Luana", "03/11/1999", 88.4f, "Ciberseguranca"));
                sistema.addEstudante(new AlunosGraduacao("352.244.276-34", "Marcelo", "21/03/2002", 65.4f, "TI"));

                sistema.addEstudante(new AlunosPos("465.345.243-00", "Rafaela", "03/11/2002", 87.5f, "Computação grafica"));
                sistema.addEstudante(new AlunosPos("937.289.786-89", "Eduarda", "23/05/2002", 72.7f, "PDI"));
                sistema.addEstudante(new AlunosPos("384.728.999-86", "Otavio", "11/12/1999", 68.4f, "ML"));
                sistema.addEstudante(new AlunosPos("352.244.276-34", "Beto", "01/09/2003", 69.5f, "Jogos Digitais"));

                sistema.addProfessor(new Professor("879.488.326-11", "Roberto", "02/08/1972", "16/01/2008", "FACOM"));

                Disciplina POO = new Disciplina("GBC2009", "Programação Orientada a Objetos", 60);
                Disciplina LFA = new Disciplina("GBC3094", "Linguagens Formais e Autômatos", 60);
                sistema.addDisciplina(POO);
                sistema.addDisciplina(LFA);

                sistema.addTurma(new Turma(POO, "1", "2017"));
                sistema.addTurma(new Turma(LFA, "2", "2024"));
                sistema.addTurma(new Turma(POO, "2", "2024"));

                Persistencia.salvarDados(sistema, "sistema.dat");
                System.out.println("Dados iniciais foram serializados em sistema.dat");

            } catch (Exception e) {
                System.err.println("Erro ao inicializar dados: " + e.getMessage());
            }
        }
}
