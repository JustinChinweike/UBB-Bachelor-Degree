
package Model;

public class Flour implements Product {

    private double pricePerKg;


    public Flour (double pricePerKg) {

        this.pricePerKg = pricePerKg;

    }

    @Override
    public double getPricePerKg() {

        return pricePerKg  ;

    }

    @Override
    public String toString() {

        return "Flour - " + pricePerKg + "RON/Kg ";

    }

}
