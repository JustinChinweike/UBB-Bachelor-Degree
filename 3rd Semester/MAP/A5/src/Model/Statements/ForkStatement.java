package Model.Statements;

import Exceptions.StatementException;
import Model.Adt.MyStack;
import Model.ProgramState;

public class ForkStatement implements  IStatement{
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }


    public ProgramState execute(ProgramState currentState) throws StatementException {
        return new ProgramState(
               new MyStack<>(), // New execution stack for the forked thread
                currentState.getSymbolTable().deepCopy(), // Deep copy of the symbol table
                currentState.getOut(), // Shared output list
                currentState.getFileTable(), // Shared file table
                currentState.getHeap(), this.statement ); // Shared heap

    }

    public String toString() {
        return "Fork: " + statement.toString();
    }


    public IStatement deepCopy() {
        return new ForkStatement(statement.deepCopy()); // Calls deepCopy on the inner statement
    }
}
