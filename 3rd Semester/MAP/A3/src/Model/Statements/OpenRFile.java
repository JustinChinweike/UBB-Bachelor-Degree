package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Type.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFile implements IStatement {
    private final IExpression exp;

    public OpenRFile(IExpression exp) {
        this.exp = exp;
    }

    /**
     * Executes the openRFile statement by opening a file and adding it to the FileTable.
     *
     * @param currentState the current program state
     * @return the updated program state
     * @throws StatementException if the expression does not evaluate to a StringType or the file cannot be opened
     * @throws DataStructureExceptions if the file is already in the FileTable
     */

    @Override
    public ProgramState execute(ProgramState currentState) throws StatementException,
            DataStructureExceptions , ExpressionException {
        IValue evaluatedExp = exp.evaluate(currentState.getSymbolTable());

        // Ensure the expression is a StringType
        if (!evaluatedExp.getType().equals(new StringType())) {
            throw new StatementException("Expression is not of type StringType");
        }

        StringValue fileNameValue = (StringValue) evaluatedExp;

        MyIDictionary <IValue, BufferedReader> fileTable = currentState.getFileTable();

        // Check if the file is already open
        if (fileTable.isDefined(fileNameValue)) {
            throw new DataStructureExceptions("File is already open: " + fileNameValue.getVal());
        }

        try {
            BufferedReader fileReader = new BufferedReader(new FileReader(fileNameValue.getVal()));
            fileTable.update(fileNameValue, fileReader);
        } catch (IOException e) {
            throw new StatementException("Error opening file: " + fileNameValue);
        }

        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new OpenRFile(exp.deepCopy());
    }


    public String toString() {
        return "openRFile(" + exp.toString() + ")";
    }
}
