package Model.Adt;

import Exceptions.DataStructureExceptions;
import Model.Values.IValue;
import Model.Values.RefValue;

import java.util.HashMap;
import java.util.Map;

public class MyHeap implements MyIHeap {
    private Map<Integer, IValue> map;
    private int lastAddedAddress;


    public MyHeap() {
        this.map = new HashMap<Integer, IValue>();
        this.lastAddedAddress = 0;
    }

    @Override
    public boolean isValid(Integer address) {
        return address !=0 ;
    }

    @Override
    public void addToNewAddress(IValue value) {
        lastAddedAddress++;
        map.put(lastAddedAddress, value);



    }

    @Override
    public void addToAddress(Integer address, IValue value) {
        if(this.map.containsKey(address)) {
            this.map.put(address, value);
        }
        else {
            throw new DataStructureExceptions("Address " + address + " is not valid. ");
        }
    }
    @Override
    public boolean checkAddress(Integer address) {
        return this.map.containsKey(address);
    }

    public Integer getLastAddedAddress() {
        return this.lastAddedAddress;
    }

    @Override
    public IValue getValueFromAddress(Integer address) throws DataStructureExceptions {
        if(map.containsKey(address)) {
            return map.get(address);
        }
        throw new DataStructureExceptions("Address is not valid ");

    }

    @Override
    public void setContent(Map<Integer, IValue> content) {
        this.map = content;
    }

    @Override
    public Map<Integer, IValue> getContent() {
        return this.map;
    }


    @Override
    public void clear() {
        this.map.clear();

    }


    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<Integer, IValue> entry : this.map.entrySet()) {
            result.append(entry.getKey().toString()).append(" --> ").append(entry.getValue().toString()).append("\n");
        }

        return result.toString();
    }

}
