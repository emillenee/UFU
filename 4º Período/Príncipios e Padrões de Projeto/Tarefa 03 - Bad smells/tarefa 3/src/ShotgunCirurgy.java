class Cliente {
    private String nome;
    private String endereco;

    public Cliente(String nome, String endereco) {
        this.nome = nome;
        this.endereco = endereco;
    }

    public void atualizarEndereco(String novoEndereco) {
        this.endereco = novoEndereco;
        System.out.println("Endereço do cliente atualizado para: " + endereco);

        // Cada vez que o endereço muda, temos que alterar várias classes...
        Logistica.atualizarRota(novoEndereco);
        Faturamento.atualizarEnderecoFatura(novoEndereco);
        Atendimento.abrirChamadoMudancaEndereco(nome, novoEndereco);
    }

    public String getNome() {
        return nome;
    }

    public String getEndereco() {
        return endereco;
    }
}

class Logistica {
    public static void atualizarRota(String novoEndereco) {
        System.out.println("Logística: Rota de entrega atualizada para o novo endereço: " + novoEndereco);
    }
}

class Faturamento {
    public static void atualizarEnderecoFatura(String novoEndereco) {
        System.out.println("Faturamento: Endereço de cobrança atualizado para: " + novoEndereco);
    }
}

class Atendimento {
    public static void abrirChamadoMudancaEndereco(String cliente, String novoEndereco) {
        System.out.println("Atendimento: Criado chamado para confirmar mudança de endereço do cliente " + cliente);
    }
}


class ClienteService {
    public void processarMudancaEndereco(String cliente, String novoEndereco) {
        Logistica.atualizarRota(novoEndereco);
        Faturamento.atualizarEnderecoFatura(novoEndereco);
        Atendimento.abrirChamadoMudancaEndereco(cliente, novoEndereco);
    }
}
