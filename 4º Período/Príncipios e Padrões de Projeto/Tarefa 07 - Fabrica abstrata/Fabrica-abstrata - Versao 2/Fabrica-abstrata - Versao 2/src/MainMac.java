public class MainMac {
    public static void main(String[] args) {
        GUIFactory factory = new MacOSFactory();
        Application app = new Application(factory);
        app.renderUI();
    }
}
