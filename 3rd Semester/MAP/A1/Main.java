//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
import Model.*;
import Repository.*;
import Controller.*;


public class Main {
    public static void main(String[] args) {
        // Create a new repository
        ProductRepository repository = new ProductRepository(6);
        ProductController controller = new ProductController(repository);
        try {
            controller.addProduct(new Salt(25));
            controller.addProduct(new Sugar(18));
            controller.addProduct(new Flour(22));
            controller.addProduct(new Salt(19));
            controller.addProduct(new Sugar(21));
            controller.addProduct(new Sugar(10));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        //  Display products with a price higher than 20Ron/kg
        Product[] expensiveProducts = controller.getExpensiveProducts(20.0);
        System.out.println("Products more Expensive Than 20 RON per kg:");
        for (Product product : expensiveProducts) {
            System.out.println(product);
        }


    }
}