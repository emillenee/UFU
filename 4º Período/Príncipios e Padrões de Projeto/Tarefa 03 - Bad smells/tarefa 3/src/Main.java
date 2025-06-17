import java.util.ArrayList;
import java.util.List;

class ContaCliente {
    private String nome;
    private String email;
    private String endereco;
    private String telefone;
    private List<String> historicoPedidos = new ArrayList<>();
    private double saldoDevedor;

    public ContaCliente(String nome, String email, String endereco, String telefone) {
        this.nome = nome;
        this.email = email;
        this.endereco = endereco;
        this.telefone = telefone;
        this.saldoDevedor = 0.0;
    }

    public void adicionarPedido(String pedido, double valor) {
        historicoPedidos.add(pedido);
        saldoDevedor += valor;
    }

    public void imprimirHistoricoPedidos() {
        System.out.println("Histórico de pedidos de " + nome + ":");
        for (String pedido : historicoPedidos) {
            System.out.println("- " + pedido);
        }
    }

    public void enviarEmailPromocional() {
        if (validarEmail()) {
            System.out.println("Enviando e-mail promocional para " + email);
        } else {
            System.out.println("E-mail inválido, não foi possível enviar a promoção.");
        }
    }

    public boolean validarEmail() {
        return email.contains("@") && email.contains(".");
    }

    public void gerarFatura() {
        System.out.println("Gerando fatura para " + nome);
        System.out.println("Total devido: R$" + saldoDevedor);
    }

    public void aplicarDesconto(double desconto) {
        if (desconto > saldoDevedor) {
            System.out.println("Desconto maior que a dívida, ajuste necessário.");
        } else {
            saldoDevedor -= desconto;
            System.out.println("Desconto de R$" + desconto + " aplicado. Novo saldo: R$" + saldoDevedor);
        }
    }

    public void atualizarEndereco(String novoEndereco) {
        this.endereco = novoEndereco;
        System.out.println("Endereço atualizado para: " + novoEndereco);
    }

    public void atualizarTelefone(String novoTelefone) {
        this.telefone = novoTelefone;
        System.out.println("Telefone atualizado para: " + novoTelefone);
    }

    public void imprimirDetalhesCliente() {
        System.out.println("Cliente: " + nome);
        System.out.println("Email: " + email);
        System.out.println("Endereço: " + endereco);
        System.out.println("Telefone: " + telefone);
        System.out.println("Saldo devedor: R$" + saldoDevedor);
    }

    public void gerarRelatorioCliente() {
        System.out.println("\n=== Relatório do Cliente ===");
        imprimirDetalhesCliente();
        imprimirHistoricoPedidos();
        System.out.println("===========================\n");
    }
}
