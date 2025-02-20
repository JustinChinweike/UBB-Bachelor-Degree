// File:Model.Adt.MyDictionary.java
package Model.Adt;
import Exceptions.DataStructureExceptions;
import java.util.Map;
import java.util.HashMap;

public class MyDictionary<T,K> implements MyIDictionary<T, K> {
    private Map<T, K> dictionary;
    public  MyDictionary() {
        dictionary = new HashMap<>();
    }
    public MyDictionary(Map <T, K > dictionary){
        this.dictionary = dictionary;
    }
    public boolean isDefined(T key) {
        return this.dictionary.containsKey(key);
    }
    public K lookup(T key) throws  DataStructureExceptions {
        K value = this.dictionary.get(key) ;
        if (value == null) throw new DataStructureExceptions("Key not found");
        return value;
    }
    public void update (T key, K value){
        this.dictionary.put(key, value);
    }
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (Map.Entry<T, K> entry : this.dictionary.entrySet()){
            result.append(entry.getKey()).append(" --> ").append(entry.getValue()).append("\n");
        }
        return result.toString();
    }
    public void clear () {
        this.dictionary.clear();
    }

    @Override
    public int size() {
        return dictionary.size();
    }

    @Override
    public Map<T,K> getContent() {
        return this.dictionary;
    }

    @Override
    public void delete(T key) throws DataStructureExceptions {
        if (!this.isDefined(key)) throw new DataStructureExceptions("Key Not Found: ");
        this.dictionary.remove(key);
    }
}
