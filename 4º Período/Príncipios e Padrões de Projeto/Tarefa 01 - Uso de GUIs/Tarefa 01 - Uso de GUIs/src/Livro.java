public class Livro extends Material{
    private String autor;

    public Livro(String titulo, String autor) {
        super(titulo);
        this.autor = autor;
    }

    public String getAutor() {
        return autor;
    }

    @Override
    public String getTipo() {
        return "Livro";
    }

    @Override
    public String getDetalhes(){
        return getTipo() + " - " + "Título: " + getTitulo() + ", Autor: " + autor;
    }
}
