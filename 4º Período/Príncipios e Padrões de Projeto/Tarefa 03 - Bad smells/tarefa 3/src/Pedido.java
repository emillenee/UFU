class Pedido {
    private String cliente;
    private double valor;
    private boolean pedidoPago;
    private int quantidade;

    public Pedido(String cliente, double valor, int quantidade) {
        this.cliente = cliente;
        this.valor = valor;
        this.quantidade = quantidade;
        this.pedidoPago = false;
    }

    public void processarPedido() {
        // Validação dos dados
        if (cliente == null || cliente.isEmpty()) {
            System.out.println("Erro: Cliente inválido.");
            return;
        }
        if (valor <= 0) {
            System.out.println("Erro: Valor do pedido inválido.");
            return;
        }
        if (quantidade <= 0) {
            System.out.println("Erro: Quantidade inválida.");
            return;
        }

        // Aplicação de desconto
        double desconto = 0;
        if (valor > 500) {
            desconto = valor * 0.10;
        } else if (valor > 200) {
            desconto = valor * 0.05;
        }
        double valorFinal = valor - desconto;

        // Atualização do estoque (simulação)
        System.out.println("Atualizando estoque...");
        // Código para atualizar o estoque (não implementado)

        // Gerar fatura
        System.out.println("Gerando fatura para " + cliente);
        System.out.println("Valor original: R$" + valor);
        System.out.println("Desconto aplicado: R$" + desconto);
        System.out.println("Valor final: R$" + valorFinal);

        // Confirmar pagamento
        this.pedidoPago = true;
        System.out.println("Pedido processado com sucesso!");
    }
}

