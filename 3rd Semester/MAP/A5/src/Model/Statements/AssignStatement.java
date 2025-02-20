// File: Model.Statements.AssignStatement.java
package Model.Statements;
import Exceptions.DataStructureExceptions;
import  Exceptions.StatementException;
import  Exceptions.ExpressionException;
 import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
 import Model.ProgramState;
 import Model.Type.IType;
 import Model.Values.IValue;


public class AssignStatement implements IStatement {
    private String id;
    private IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState currentState) throws StatementException , DataStructureExceptions{
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();

        //Check if the variable exists in the symbol table
        if (symbolTable.isDefined(id)) {
            //Evaluate the expression to get the value to assign
            IValue value = expression.evaluate(symbolTable, heap);
            // Get the declared type of the variables in the symbol table
            IType idType = (symbolTable.lookup(id).getType());
            // check for type compatibility
            if (value.getType().equals(idType)) {
                symbolTable.update(id,value); // Update if types match
            }else {
                throw new StatementException("The Variable with the name: " + id + "has a different type than the assignment value");
            }
        } else {
            throw new StatementException("Undeclared Variable: "+ id );
        }
        return null;
    }

    public String toString() {
        return "(Variable name: " + id + " = " + expression.toString() + ")";
    }


    @Override
    public IStatement deepCopy() {
        return new AssignStatement(this.id, this.expression.deepCopy());
    }
}
