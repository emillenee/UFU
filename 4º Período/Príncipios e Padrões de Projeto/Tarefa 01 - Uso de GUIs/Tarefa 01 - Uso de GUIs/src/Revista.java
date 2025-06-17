public class Revista extends Material{
    private int edicao;

    public Revista(String titulo, int edicao){
        super(titulo);
        this.edicao = edicao;
    }

    public int getEdicao(){
        return edicao;
    }

    @Override
    public String getTipo(){
        return "Revista";
    }

    @Override
    public String getDetalhes(){
        return getTipo() + " - " + "Título: " + getTitulo() + ", Edição: " + edicao;
    }
}
