import javax.swing.*;
import java.awt.*;
import java.util.List;

class JanelaListagem extends JFrame {
    public JanelaListagem(ProdutoCRUD produtoCRUD) {
        setTitle("Lista de Produtos");
        setSize(600, 600);
        setLocationRelativeTo(null);

        JTextArea areaTexto = new JTextArea();
        areaTexto.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(areaTexto);

        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

        panel.add(scrollPane, BorderLayout.CENTER);

        add(panel);

        listarProdutos(produtoCRUD, areaTexto);

        setVisible(true);
    }

    private void listarProdutos(ProdutoCRUD produtoCRUD, JTextArea areaTexto) {
        List<String> produtos = produtoCRUD.lerProdutos();

        StringBuilder produtosTexto = new StringBuilder();
        for (String produto : produtos) {
            produtosTexto.append(produto).append("\n");
        }

        areaTexto.setText(produtosTexto.toString());
    }
}

