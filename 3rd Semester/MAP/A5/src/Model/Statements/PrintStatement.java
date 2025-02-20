//File: Model.Statements.PrintStatement.java
package Model.Statements;
import Exceptions.StatementException;
import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary ;
import Model.Adt.MyIHeap;
import Model.Adt.MyIList ;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Values.IValue;

public class PrintStatement implements IStatement {
    private IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }


    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException {
        MyIList<IValue> out = currentState.getOut();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();

        // Evaluate the expression and add the result to the output list
        IValue value = this.expression.evaluate(symbolTable, heap);
        out.add(value);
        return null;
    }

    public String toString() {
        return "(Print(" + expression.toString() + "))";
    }


    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }
}
