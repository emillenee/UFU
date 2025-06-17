import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public abstract class AddMaterial extends JDialog {
    protected JPanel painelCampos;
    protected ArrayList<Material> materiais;
    protected JButton botaoAdicionar;

    public AddMaterial(String titulo, ArrayList<Material> materiais) {
        this.materiais = materiais;

        setTitle("Adicionar " + titulo);
        setSize(600, 300);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel addMaterial = new JPanel(new BorderLayout(10, 10));
        addMaterial.setBorder(BorderFactory.createEmptyBorder(30, 25, 30, 25));

        JLabel mensagem = new JLabel("Preencha as informações do(a) " + titulo + ":", JLabel.CENTER);
        mensagem.setFont(new Font("Arial", Font.BOLD, 16));
        addMaterial.add(mensagem, BorderLayout.NORTH);

        painelCampos = new JPanel();
        painelCampos.setLayout(new GridLayout(0, 2, 10, 10));
        painelCampos.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JPanel painelSul = new JPanel(new FlowLayout(FlowLayout.CENTER));
        botaoAdicionar = new JButton("Adicionar");
        botaoAdicionar.setPreferredSize(new Dimension(120, 40));
        painelSul.add(botaoAdicionar);

        addMaterial.add(painelCampos, BorderLayout.CENTER);
        addMaterial.add(painelSul, BorderLayout.SOUTH);
        setContentPane(addMaterial);

        configurarCampos();
        configurarAcaoBotao();
    }

    protected abstract void configurarCampos();
    protected abstract void adicionarMaterial();

    private void configurarAcaoBotao() {
        botaoAdicionar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                adicionarMaterial();
            }
        });
    }
}
