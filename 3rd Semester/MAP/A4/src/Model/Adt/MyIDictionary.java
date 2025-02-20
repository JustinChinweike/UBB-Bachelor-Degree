// File: Model.Adt.MyIDictionary.java
package Model.Adt;
import Exceptions.DataStructureExceptions;

import java.util.Map;

public interface MyIDictionary <T, K>{
    boolean isDefined(T key);
    K lookup (T key) throws DataStructureExceptions;
    void update (T key, K value);
    String toString();
    public void clear();
    int size(); // method to get the number of elements (size) of the dictionary.
    void delete(T key) throws DataStructureExceptions;
    Map <T,K> getContent();
}
