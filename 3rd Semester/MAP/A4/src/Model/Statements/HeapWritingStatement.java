package Model.Statements;
import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Type.IType;
import Model.Type.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class HeapWritingStatement implements IStatement{
    private IExpression expression;
    private String variableName;

    public HeapWritingStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState currentState) throws StatementException,
            ExpressionException , DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue value = symbolTable.lookup(variableName);
        IType valueType = value.getType();

        if (!(value instanceof RefValue)) {
            throw new StatementException("The variable " + variableName + " is not of type " + valueType);
        }
        Integer address = ((RefValue) value).getAddress();
        if (!heap.checkAddress(address)) {
            throw new StatementException("The heap address " + address + " is not valid");
        }

        IValue evaluate = this.expression.evaluate(symbolTable, heap);
        if (!evaluate.getType().equals(((RefType) valueType).getInner())) {
            throw new StatementException("The variable " + variableName + " is not of type " + evaluate.getType());
        }
        heap.addToAddress(address, evaluate);
        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapWritingStatement(variableName, expression.deepCopy());
    }

    public String toString(){
        return "(Write in Heap: " + variableName + "---> " + expression.toString() + ")" ;
    }
}
