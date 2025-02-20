package Model;

import Model.Adt.*;
import Model.Statements.IStatement;
import Model.Values.IValue;

import java.io.BufferedReader;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;
    private MyIDictionary<IValue, BufferedReader> fileTable;

    public ProgramState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable,
                        MyIList<IValue> out,
                        MyIDictionary<IValue, BufferedReader> fileTable, IStatement originalProgram) {
        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = originalProgram.deepCopy(); // deep copy
        this.exeStack.push(originalProgram);
    }

    public MyIStack<IStatement> getExeStack() {
        return this.exeStack;
    }

    public void setExeStack(MyIStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public void setSymbolTable(MyIDictionary<String, IValue> symbolTable) {
        this.symbolTable = symbolTable;
    }

    public MyIList<IValue> getOut() {
        return this.out;
    }

    public void setFileTable(  MyIDictionary<IValue, BufferedReader> fileTable){
        this.fileTable = fileTable;
    }

    public  MyIDictionary<IValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setOut(MyIList<IValue> out) {
        this.out = out;
    }

    public IStatement getOriginalProgram() {
        return this.originalProgram;
    }

    public void clear () {
        this.fileTable.clear();
        this.symbolTable.clear();
        this.out.clear();
        this.exeStack.clear();
        this.exeStack.push(this.originalProgram);
        this.originalProgram = originalProgram.deepCopy();
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("ExeStack: \n");
        result.append(this.exeStack.toString());
        result.append("SymbolTable: \n");
        result.append(this.symbolTable.toString());
        result.append("Out: \n");
        result.append(this.out);
        result.append("FileTable: \n");
        result.append(this.fileTable);
        result.append("-------------------------------------------------------------------------\n");
        return result.toString();
    }
}