public class Moto extends Veiculo {

    public Moto(String modelo, String marca, int ano) {
        super(modelo, marca, ano);
    }

    @Override
    public void ligar() {
        System.out.println("Ligando a moto " + getModelo());
    }
}