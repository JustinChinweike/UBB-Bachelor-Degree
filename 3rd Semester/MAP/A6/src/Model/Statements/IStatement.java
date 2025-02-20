package Model.Statements;

import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.ProgramState;
import Model.Type.IType;

public interface IStatement {
    MyIDictionary<String,IType> typecheck(MyIDictionary<String, IType> typeEnv) throws
            StatementException;
    ProgramState execute(ProgramState currentState) throws StatementException;
    IStatement deepCopy();
}