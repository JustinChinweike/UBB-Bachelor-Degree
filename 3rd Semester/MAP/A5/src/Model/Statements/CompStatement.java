// File: Model.Statements.CompStatement.java
package Model.Statements;

import Exceptions.StatementException;
import Model.Adt.MyIStack;
import Model.ProgramState;

public class CompStatement implements IStatement {
    private IStatement firstStatement;
    private IStatement secondStatement;

    public CompStatement(IStatement firstStatement, IStatement secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    public String toString(){
        return "(" + firstStatement.toString() + ", " + secondStatement.toString() + ")";
    }
    public ProgramState execute(ProgramState currentState) throws StatementException {
        MyIStack<IStatement> executionStack = currentState.getExeStack();
        executionStack.push(this.secondStatement);
        executionStack.push(this.firstStatement);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CompStatement(firstStatement.deepCopy(), secondStatement.deepCopy());
    }
}