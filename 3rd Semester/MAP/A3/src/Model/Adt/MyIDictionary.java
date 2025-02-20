// File: Model.Adt.MyIDictionary.java
package Model.Adt;
import Exceptions.DataStructureExceptions;

public interface MyIDictionary <T, K>{
    boolean isDefined(T key);
    K lookup (T key) throws DataStructureExceptions;
    void update (T key, K value);
    String toString();
    public void clear();
    void delete(T key) throws DataStructureExceptions;
}
