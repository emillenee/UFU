import javax.swing.*;
import java.util.ArrayList;

public class AddLivro extends AddMaterial {
    private JTextField campoTitulo;
    private JTextField campoAutor;

    public AddLivro(ArrayList<Material> materiais) {
        super("Livro", materiais);
    }

    @Override
    protected void configurarCampos() {
        JLabel labelTitulo = new JLabel("Título:");
        campoTitulo = new JTextField();
        JLabel labelAutor = new JLabel("Autor:");
        campoAutor = new JTextField();

        painelCampos.add(labelTitulo);
        painelCampos.add(campoTitulo);
        painelCampos.add(labelAutor);
        painelCampos.add(campoAutor);
    }

    @Override
    protected void adicionarMaterial() {
        String titulo = campoTitulo.getText();
        String autor = campoAutor.getText();

        if (!titulo.isEmpty() && !autor.isEmpty()) {
            materiais.add(new Livro(titulo, autor));
            JOptionPane.showMessageDialog(this, "Livro adicionado com sucesso!");
            dispose();
        } else {
            JOptionPane.showMessageDialog(this, "Por favor, preencha todos os campos.");
        }
    }
}