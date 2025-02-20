// File: Model.Statements.NopStatement.java
package Model.Statements;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.ProgramState;
import Model.Type.IType;

public class NopStatement implements IStatement {
    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
      return typeEnv;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        return null; // No changes to the state
    }
    @Override
    public IStatement deepCopy(){
        return new NopStatement();
    }
    public String toString() {
        return "()";
    }
}
