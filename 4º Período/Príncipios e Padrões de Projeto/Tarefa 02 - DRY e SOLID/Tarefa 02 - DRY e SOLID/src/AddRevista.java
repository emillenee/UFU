import javax.swing.*;
import java.util.ArrayList;

public class AddRevista extends AddMaterial {
    private JTextField campoTitulo;
    private JTextField campoEdicao;

    public AddRevista(ArrayList<Material> materiais) {
        super("Revista", materiais);
    }

    @Override
    protected void configurarCampos(){
        JLabel labelTitulo = new JLabel("Título:");
        campoTitulo = new JTextField();
        JLabel labelEdicao = new JLabel("Edição:");
        campoEdicao = new JTextField();

        painelCampos.add(labelTitulo);
        painelCampos.add(campoTitulo);
        painelCampos.add(labelEdicao);
        painelCampos.add(campoEdicao);
    }

    @Override
    protected void adicionarMaterial() {
        String titulo = campoTitulo.getText();
        String edicao = campoEdicao.getText();

        if( titulo.isEmpty() || edicao.isEmpty() ){
            JOptionPane.showMessageDialog(null, "Por favor, preencha todos os campos.");
        }else{
            try{
                int numero = Integer.parseInt(campoEdicao.getText());
                materiais.add(new Revista(titulo, numero));
                JOptionPane.showMessageDialog(null, "Revista adicionado com sucesso!");
                dispose();
            }catch (NumberFormatException exc){
                JOptionPane.showMessageDialog(null, "A edição da revista precisa ser um número!");
            }
        }
    }
}
