import java.util.ArrayList;

public class ListagemController {
    public static String obterListagem(ArrayList<Material> materiais) {
        String result = "";
        for (Material material : materiais) {
            result += material.getDetalhes() + "\n";
        }
        return result;
    }
}
