public class Filme extends Material{
    private String diretor;
    private String genero;

    public Filme(String titulo, String diretor, String genero) {
        super(titulo);
        this.diretor = diretor;
        this.genero = genero;
    }

    public String getDiretor() {
        return diretor;
    }

    public String getGenero() {
        return genero;
    }

    @Override
    public String getTipo(){
        return "Filme";
    }

    @Override
    public String getDetalhes(){
        return getTipo() + " - " + "Título: " + getTitulo() + ", Diretor: " + diretor + ", Gênero: " + genero;
    }
}
