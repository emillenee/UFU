public class Main {
    public static void main(String[] args) {
        GUIFactory factory;

        String os = System.getProperty("os.name").toLowerCase();
        if (os.contains("win")) {
            factory = new WindowsFactory();
        } else if (os.contains("mac")) {
            factory = new MacOSFactory();
        } else if (os.contains("linux")) {
            factory = new LinuxFactory();
        } else {
            throw new UnsupportedOperationException("Sistema operacional não suportado");
        }

        Application app = new Application(factory);
        app.renderUI();
    }
}