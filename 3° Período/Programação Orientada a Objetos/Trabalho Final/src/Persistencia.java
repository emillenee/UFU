import java.io.*;

public class Persistencia {
    public static void salvarDados(Object sistema, String arquivo) throws IOException {
        try (ObjectOutputStream escritor = new ObjectOutputStream(new FileOutputStream(arquivo))) {
            escritor.writeObject(sistema);
        }
    }

    public static Object carregarDados(String arquivo) throws IOException, ClassNotFoundException {
        try (ObjectInputStream leitor = new ObjectInputStream(new FileInputStream(arquivo))) {
            return leitor.readObject();
        }
    }
}
