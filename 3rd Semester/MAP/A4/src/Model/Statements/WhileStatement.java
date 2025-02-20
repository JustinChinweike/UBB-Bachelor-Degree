package Model.Statements;

import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Adt.MyIHeap;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIStack;
import Model.Type.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;


public class WhileStatement implements IStatement {
    private IExpression condition;
    private IStatement body;

    public WhileStatement(IExpression condition, IStatement body) {
        this.condition = condition;
        this.body = body;
    }

    @Override
    public ProgramState execute(ProgramState currentState) throws StatementException , ExpressionException {
        MyIStack<IStatement> executionStack = currentState.getExeStack();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue evaluate = this.condition.evaluate(symbolTable, heap);

        if (!evaluate.getType().equals(new BoolType())) {
            throw new StatementException("Condition expression is not a boolean type!");
        }
        if (evaluate.equals(new BoolValue(true) )){
            executionStack.push(this);
            executionStack.push(this.body);
        }
        return currentState;
    }

    public String toString() {
        return "(While" + this.condition.toString() + "Execute " + this.body.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(condition.deepCopy(), body.deepCopy());
    }
}
