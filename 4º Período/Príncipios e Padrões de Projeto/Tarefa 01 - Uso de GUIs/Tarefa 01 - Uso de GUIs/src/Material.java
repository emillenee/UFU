public abstract class Material {
    protected String titulo;

    public Material(String titulo) {
        this.titulo = titulo;
    }

    public String getTitulo() {
        return titulo;
    }

    public abstract String getTipo();
    public abstract String getDetalhes();
}
