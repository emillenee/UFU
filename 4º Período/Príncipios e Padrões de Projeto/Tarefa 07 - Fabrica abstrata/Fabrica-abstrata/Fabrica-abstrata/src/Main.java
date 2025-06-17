public class Main {
    public static void main(String[] args) {
        GUIFactory factory;

        // Detecta o sistema operacional
        String os = System.getProperty("os.name").toLowerCase();
        if (os.contains("win")) {
            factory = new WindowsFactory();
        } else {
            factory = new MacOSFactory();
        }

        // Cria a aplicação com a fábrica adequada
        Application app = new Application(factory);
        app.renderUI();
    }
}