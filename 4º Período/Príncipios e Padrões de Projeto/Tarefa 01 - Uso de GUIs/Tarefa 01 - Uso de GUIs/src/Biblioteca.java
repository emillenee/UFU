import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Biblioteca extends JFrame {
    private ArrayList<Material> materiais;

    public Biblioteca() {
        materiais = new ArrayList<>();
        iniciarSistema();
    }

    public void iniciarSistema() {
        setTitle("Sistema Bibliotecário");
        setSize(600, 300);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel painelPrincipal = new JPanel(new BorderLayout(10, 10));
        painelPrincipal.setBorder(BorderFactory.createEmptyBorder(30, 25, 30, 25));

        add(painelPrincipal, BorderLayout.CENTER);

        JLabel mensagem = new JLabel("Qual material deseja adicionar?", JLabel.CENTER);
        mensagem.setFont(new Font("Arial", Font.BOLD, 16));
        painelPrincipal.add(mensagem, BorderLayout.NORTH);

        JPanel painelCentro = new JPanel();
        painelCentro.setLayout(new BoxLayout(painelCentro, BoxLayout.X_AXIS));
        painelCentro.setBorder(BorderFactory.createEmptyBorder(20, 30, 20, 30));

        JButton botaoLivro = new JButton("Livro");
        JButton botaoRevista = new JButton("Revista");
        JButton botaoFilme = new JButton("Filme");

        botaoLivro.setPreferredSize(new Dimension(120, 50));
        botaoRevista.setPreferredSize(new Dimension(120, 50));
        botaoFilme.setPreferredSize(new Dimension(120, 50));

        painelCentro.add(Box.createHorizontalGlue());
        painelCentro.add(botaoLivro);
        painelCentro.add(Box.createHorizontalStrut(20));
        painelCentro.add(botaoRevista);
        painelCentro.add(Box.createHorizontalStrut(20));
        painelCentro.add(botaoFilme);
        painelCentro.add(Box.createHorizontalGlue());

        painelPrincipal.add(painelCentro, BorderLayout.CENTER);

        JPanel painelSul = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JButton listagem = new JButton("Exibir Listagem");
        painelSul.add(listagem);
        painelPrincipal.add(painelSul, BorderLayout.SOUTH);

        setVisible(true);

        //Cada botão chama sua respectiva janela
        botaoLivro.addActionListener(e -> new AddLivro(materiais).setVisible(true));
        botaoRevista.addActionListener(e -> new AddRevista(materiais).setVisible(true));
        botaoFilme.addActionListener(e -> new AddFilme(materiais).setVisible(true));
        listagem.addActionListener(e -> new Listagem(materiais).setVisible(true));
    }
}