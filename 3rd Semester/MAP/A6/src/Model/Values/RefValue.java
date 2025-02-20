package Model.Values;

import Model.Type.IType;
import Model.Type.RefType;


public class RefValue implements IValue {
    private int address;
    private IType locationType;

    public RefValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddress (){
        return address;
    }

    public IType getLocationType() {
        return locationType;
    }

    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    @Override
    public boolean equals(IValue other) {
        if (other instanceof RefValue){
            return address == ((RefValue) other).getAddress() &&
                    locationType.equals(((RefValue)other).getLocationType());
        }
        return false;
    }

    @Override
    public IValue deepCopy() {
        return new RefValue(address, locationType.deepCopy());
    }

    @Override
    public String toString(){
        return"(" + address + ", " + locationType + ")";
    }
}
