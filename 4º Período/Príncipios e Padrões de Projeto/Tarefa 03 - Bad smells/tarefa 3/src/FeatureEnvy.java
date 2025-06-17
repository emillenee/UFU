class Cliente {
    private String nome;
    private boolean clienteVip;
    private double descontoVip;

    public Cliente(String nome, boolean clienteVip, double descontoVip) {
        this.nome = nome;
        this.clienteVip = clienteVip;
        this.descontoVip = descontoVip;
    }

    public boolean isClienteVip() {
        return clienteVip;
    }

    public double getDescontoVip() {
        return descontoVip;
    }

    public String getNome() {
        return nome;
    }
}

class Pedido {
    private Cliente cliente;
    private double valor;

    public Pedido(Cliente cliente, double valor) {
        this.cliente = cliente;
        this.valor = valor;
    }

    public double calcularTotalComDesconto() {
        if (cliente.isClienteVip()) {
            return valor - (valor * cliente.getDescontoVip());
        }
        return valor;
    }

    public void imprimirDetalhesPedido() {
        System.out.println("Cliente: " + cliente.getNome());
        System.out.println("Total com desconto: R$" + calcularTotalComDesconto());
    }
}
