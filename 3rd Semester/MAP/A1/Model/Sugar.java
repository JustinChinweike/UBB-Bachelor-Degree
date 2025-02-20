package Model;

public class  Sugar implements Product {
    private double pricePerKg;

    public Sugar(double pricePerKg){
        this.pricePerKg = pricePerKg;
    }
    @Override
    public double getPricePerKg(){
        return pricePerKg;
    }
    @Override
    public String toString(){
        return "Sugar - " + pricePerKg + " RON/Kg";
    }
}
