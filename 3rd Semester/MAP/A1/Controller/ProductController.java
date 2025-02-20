package Controller;

import Model.Product;
import Repository.ProductRepositoryInterface;

public class ProductController {
    private ProductRepositoryInterface repository;

    public ProductController(ProductRepositoryInterface repository) {
        this.repository = repository;
    }

    public void addProduct(Product product) {
        try {
            repository.addProduct(product);
        } catch (Exception e) {
            System.out.println("Error adding product: " + e.getMessage());
        }
    }

    public void removeProduct(Product product) {
        try {
            repository.removeProduct(product);
        } catch (Exception e) {
            System.out.println("Error removing product: " + e.getMessage());
        }
    }

    public Product[] getExpensiveProducts(double price) {
        return repository.getProductsMoreExpensiveThan(price);
    }
}
