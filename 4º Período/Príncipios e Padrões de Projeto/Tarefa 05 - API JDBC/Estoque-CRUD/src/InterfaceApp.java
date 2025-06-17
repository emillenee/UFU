import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class InterfaceApp extends JFrame {
    private ProdutoCRUD produtoCRUD;

    public InterfaceApp() {
        this.produtoCRUD = new ProdutoCRUD();
        iniciarSistema();
    }

    private void iniciarSistema() {
        setTitle("Sistema de Estoque");
        setSize(600, 350);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel painelPrincipal = new JPanel(new BorderLayout(10, 10));
        painelPrincipal.setBorder(BorderFactory.createEmptyBorder(30, 25, 30, 25));
        add(painelPrincipal, BorderLayout.CENTER);

        JLabel mensagem = new JLabel("Escolha uma opção:", JLabel.CENTER);
        mensagem.setFont(new Font("Arial", Font.BOLD, 16));
        painelPrincipal.add(mensagem, BorderLayout.NORTH);

        JPanel painelCentro = new JPanel();
        painelCentro.setLayout(new BoxLayout(painelCentro, BoxLayout.X_AXIS));
        painelCentro.setBorder(BorderFactory.createEmptyBorder(20, 30, 20, 30));

        JButton btnListar = new JButton("Estoque");
        JButton btnAdicionar = new JButton("Adicionar");
        JButton btnRemover = new JButton("Remover");

        btnListar.setPreferredSize(new Dimension(120, 50));
        btnAdicionar.setPreferredSize(new Dimension(120, 50));
        btnRemover.setPreferredSize(new Dimension(120, 50));

        painelCentro.add(Box.createHorizontalGlue());
        painelCentro.add(btnListar);
        painelCentro.add(Box.createHorizontalStrut(20));
        painelCentro.add(btnAdicionar);
        painelCentro.add(Box.createHorizontalStrut(20));
        painelCentro.add(btnRemover);
        painelCentro.add(Box.createHorizontalGlue());

        painelPrincipal.add(painelCentro, BorderLayout.CENTER);

        JPanel painelSul = new JPanel();
        painelSul.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

        JButton btnComprar = new JButton("Comprar");
        JButton btnVender = new JButton("Vender");

        btnComprar.setPreferredSize(new Dimension(120, 50));
        btnVender.setPreferredSize(new Dimension(120, 50));

        btnComprar.addActionListener(e -> comprarProduto());
        btnVender.addActionListener(e -> venderProduto());

        painelSul.add(btnComprar);
        painelSul.add(btnVender);

        painelPrincipal.add(painelSul, BorderLayout.SOUTH);

        setVisible(true);

        // Botões
        btnListar.addActionListener(e -> new JanelaListagem(produtoCRUD).setVisible(true));
        btnRemover.addActionListener(e -> removerProduto());
        btnAdicionar.addActionListener(e -> adicionarProduto());
    }

    private void removerProduto() {
        try {
            int id = Integer.parseInt(JOptionPane.showInputDialog(this, "Digite o ID do produto que deseja remover:"));
            produtoCRUD.excluirProduto(id);
            JOptionPane.showMessageDialog(this, "Produto removido do estoque");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "ID inválido!");
        }
    }

    private void adicionarProduto() {
        try {
            String nome = JOptionPane.showInputDialog(this, "Nome do produto:");
            String descricao = JOptionPane.showInputDialog(this, "Descrição do produto:");
            double preco = Double.parseDouble(JOptionPane.showInputDialog(this, "Preço do produto:"));
            int estoque = Integer.parseInt(JOptionPane.showInputDialog(this, "Quantidade comprada:"));

            produtoCRUD.criarProduto(nome, descricao, preco, estoque);
            JOptionPane.showMessageDialog(this, "Produto adicionado ao estoque.");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Dados inválidos!");
        }
    }

    private void comprarProduto() {
        try {
            int id = Integer.parseInt(JOptionPane.showInputDialog(this, "Digite o ID do produto que deseja comprar:"));
            int quantidade = Integer.parseInt(JOptionPane.showInputDialog(this, "Digite a quantidade:"));

            if (quantidade <= 0) {
                JOptionPane.showMessageDialog(this, "A quantidade deve ser maior que zero!");
                return;
            }

            produtoCRUD.atualizarProduto(id, quantidade);
            JOptionPane.showMessageDialog(this, "Compra registrada! Estoque atualizado com sucesso.");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Dados inválidos! Certifique-se de inserir números corretamente.");
        }
    }

    private void venderProduto() {
        try {
            int id = Integer.parseInt(JOptionPane.showInputDialog(this, "Digite o ID do produto que deseja vender:"));
            int quantidade = Integer.parseInt(JOptionPane.showInputDialog(this, "Digite a quantidade:"));

            if (quantidade <= 0) {
                JOptionPane.showMessageDialog(this, "A quantidade deve ser maior que zero!");
                return;
            }

            int estoqueAtual = produtoCRUD.obterQuantidadeProduto(id);
            if (estoqueAtual >= quantidade) {
                produtoCRUD.atualizarProduto(id, -quantidade);
                JOptionPane.showMessageDialog(this, "Venda realizada! Estoque atualizado com sucesso.");
            } else {
                JOptionPane.showMessageDialog(this, "Estoque insuficiente para a venda!");
            }
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Dados inválidos! Certifique-se de inserir números corretamente.");
        }
    }
}
