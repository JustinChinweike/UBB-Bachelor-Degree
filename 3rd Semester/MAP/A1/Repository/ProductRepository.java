package Repository;

import Model.Product;

public class ProductRepository implements ProductRepositoryInterface {
    private Product[] products;
    private int currentSize;

    public ProductRepository(int maxSize){
        this.products = new Product[maxSize];
        this.currentSize = 0;
    }

    @Override
    public void addProduct(Product product) throws RepositoryFullException {
        if(currentSize >= products.length){
            throw new RepositoryFullException("Repository is full. Cannot add more products.");
        }
        products[currentSize] = product;
        currentSize++;
    }

    @Override
    public void removeProduct(Product product) throws Exception {
        boolean found = false;
        for (int i = 0; i < currentSize; i++) {
            if (products[i].equals(product)) {
                found = true;
                products[i] = products[currentSize - 1]; // Swap with the last element
                products [currentSize - 1] = null; // Remove the last element
                currentSize--;
                break;
            }
        }
        if (!found) {
            throw new Exception("Product not found in repository.");
        }

    }
    @Override
    public Product[] getProductsMoreExpensiveThan( double price) {
        // We need a fixed array for the result, so we need to count first how many products
        // Match the criteria
        int count = 0;
        for (int i = 0; i < currentSize; i++) {
            if (products[i].getPricePerKg() > price) {
                count++;
            }
        }
        // Create a result array with the exact size
        Product[] result = new Product[count];
        int index = 0;
        for (int i = 0; i < currentSize; i++) {
            if (products[i].getPricePerKg() > price) {
                result[index] = products[i];
                index++;
            }
        }
        return result;
    }

}
