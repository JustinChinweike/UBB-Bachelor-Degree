package Model;

public class Salt implements Product {
    private double pricePerKg;

    public Salt(double pricePerKg) {
        this.pricePerKg = pricePerKg;
    }

    @Override
    public double getPricePerKg() {
        return  pricePerKg;
    }

    @Override
    public String toString() {
        return "Salt - " + pricePerKg + " RON/Kg";
    }

}
