package Model.Statements;

import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyStack;
import Model.ProgramState;
import Model.Type.IType;

public class ForkStatement implements  IStatement{
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }


    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        this.statement.typecheck(typeEnv.deepCopy());
        return typeEnv;
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
