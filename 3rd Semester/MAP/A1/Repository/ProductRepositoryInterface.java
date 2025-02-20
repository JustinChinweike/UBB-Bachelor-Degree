package Repository;

import Model.Product;

public interface ProductRepositoryInterface {
    void addProduct(Product product) throws Exception;

    void removeProduct(Product product) throws Exception;

    Product[] getProductsMoreExpensiveThan(double price);
}


