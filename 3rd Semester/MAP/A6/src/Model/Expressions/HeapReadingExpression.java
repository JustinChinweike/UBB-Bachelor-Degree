package Model.Expressions;
import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.IType;
import Model.Type.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class HeapReadingExpression implements IExpression{
    private IExpression expression;

    public HeapReadingExpression(IExpression expression){
        this.expression = expression;

    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType typ=expression.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft =(RefType) typ;
            return reft.getInner();
        } else
            throw new ExpressionException("the rH argument is not a Ref Type");
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable,MyIHeap heap)
            throws ExpressionException, DataStructureExceptions {
        // Evaluate the expression
        IValue evaluate = expression.evaluate(symbolTable, heap);
        // Ensure the value is of RefType
        if(!(evaluate instanceof RefValue)) {
            throw new ExpressionException("Expression does not evaluate to a reference type.");
        }// check if address is a key in the heap table
        Integer address = ((RefValue)evaluate).getAddress();
        IValue value = heap.getValueFromAddress(address);
        return value;

    }

    @Override
    public IExpression deepCopy() {
        return new HeapReadingExpression(expression.deepCopy());
    }
    public String toString() {
        return "(Read From Heap: " + expression.toString() + ")";
    }
}
