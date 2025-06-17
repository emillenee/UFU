import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class AddFilme extends AddMaterial {
    private JTextField campoTitulo;
    private JTextField campoDiretor;
    private JTextField campoGenero;

    public AddFilme(ArrayList<Material> materiais) {
        super("Filme", materiais);
    }

    @Override
    protected void configurarCampos() {
        JLabel labelTitulo = new JLabel("Título:");
        campoTitulo = new JTextField();
        JLabel labelDiretor = new JLabel("Diretor:");
        campoDiretor = new JTextField();
        JLabel labelGenero = new JLabel("Gênero:");
        campoGenero = new JTextField();

        painelCampos.add(labelTitulo);
        painelCampos.add(campoTitulo);
        painelCampos.add(labelDiretor);
        painelCampos.add(campoDiretor);
        painelCampos.add(labelGenero);
        painelCampos.add(campoGenero);
    }

    @Override
    protected void adicionarMaterial() {
        String titulo = campoTitulo.getText();
        String diretor = campoDiretor.getText();
        String genero = campoGenero.getText();

        if (titulo.isEmpty() || diretor.isEmpty() || genero.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Por favor, preencha todos os campos.");
        } else {
            materiais.add(new Filme(titulo, diretor, genero));
            JOptionPane.showMessageDialog(this, "Filme adicionado com sucesso!");
            dispose();
        }
    }
}