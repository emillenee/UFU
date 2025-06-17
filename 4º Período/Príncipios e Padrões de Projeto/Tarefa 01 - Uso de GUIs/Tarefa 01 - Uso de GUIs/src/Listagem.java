import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Listagem extends JFrame {
    private JTextArea areaListagem;

    public Listagem(ArrayList<Material> materiais){
        setTitle("Listagem");
        setSize(600, 300);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        areaListagem = new JTextArea();
        areaListagem.setEditable(false);
        areaListagem.setFocusable(false);
        areaListagem.setMargin(new Insets(20, 25, 20, 25));

        areaListagem.setFont(new Font("Arial", Font.BOLD, 14));

        JScrollPane scrollListagem = new JScrollPane(areaListagem);

        add(scrollListagem, BorderLayout.CENTER);

        //Delegar funcionalidade da janela para um controlador
        String result = ListagemController.obterListagem(materiais);
        areaListagem.setText(result);
    }
}
