public class Pessoa {
    private Endereco endereco;
    private String nome;
    private String email;
    private String telefone;

    public Pessoa(String nome, String email, String telefone, String rua, String cidade, String estado, String cep) {
        this.nome = nome;
        this.email = email;
        this.telefone = telefone;
        this.endereco = new Endereco(rua, cidade, estado, cep);
    }

    public void exibirInformacoes() {
        System.out.println("Nome: " + nome);
        System.out.println("Email: " + email);
        System.out.println("Telefone: " + telefone);
        System.out.println(endereco.toString());
    }

}