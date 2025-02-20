package Model.Statements;
import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Exceptions.ExpressionException;
import Model.Adt.MyHeap;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.ProgramState;
import Model.Type.IType;
import Model.Type.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

import Model.Expressions.IExpression;

public class HeapAllocationStatement implements IStatement{
    private String variableName; // Variable name to store reference
    private IExpression expression;// Expression to evaluate and allocate in the heap

    public HeapAllocationStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState currentState) throws StatementException , ExpressionException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        //Check if the variabel is defined in the symbol table
        if(!symbolTable.isDefined(variableName)) {
            throw new StatementException("Variable " + variableName + "is not defined in the symbol Table.");
        }
       IValue value =  symbolTable.lookup(variableName);
        IType valueType = value.getType();

        if(!(valueType instanceof RefType)){
            throw new StatementException("Value of variable " + variableName + " is not of type " + valueType.toString());
        }

        MyIHeap heap = currentState.getHeap();
        IValue evaluate = this.expression.evaluate(symbolTable, heap);
        IType evaluateType = evaluate.getType();
        if(!((RefType) valueType).getInner().equals(evaluateType)){
            throw new StatementException("Value of variable " + variableName + " is not of type " + evaluateType.toString());
        }
        heap.addToNewAddress(evaluate);

        //Update the variable in the symbol table to point to the new address in the heap
        symbolTable.update(variableName, new RefValue(heap.getLastAddedAddress(), ((RefType)valueType).getInner()));
        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapAllocationStatement(this.variableName, this.expression.deepCopy());
    }

    public String toString() {
        return "( Allocate in heap: " + variableName + " --> " + expression.toString() + ")" ;
    }
}
