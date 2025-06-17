public class Cliente {
    private String nome;
    private ContaBancaria conta;

    public Cliente(String nome, ContaBancaria conta) {
        this.nome = nome;
        this.conta = conta;
    }

    public void exibirSaldoComJuros() {
        double juros = conta.calcularJuros();
        System.out.println("Cliente: " + nome);
        System.out.println("Saldo atual: R$" + conta.getSaldo());
        System.out.println("Juros aplicados: R$" + conta.calcularJuros());
        System.out.println("Saldo final: R$" + (conta.getSaldo() + conta.calcularJuros()));
    }
}