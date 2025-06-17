public class MainLin {
    public static void main(String[] args){
        GUIFactory factory = new LinuxFactory();
        Application app = new Application(factory);
        app.renderUI();
    }
}
