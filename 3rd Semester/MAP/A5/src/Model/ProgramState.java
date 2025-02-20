package Model;

import Exceptions.ControllerException;
import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
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
    private MyIHeap heap;
    private int id;
    private static int generalId = 0;

    public ProgramState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable,
                        MyIList<IValue> out, MyIDictionary<IValue, BufferedReader> fileTable,
                        MyIHeap  heap,
                        IStatement originalProgram) {

        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.exeStack.push(originalProgram);
        this.originalProgram = originalProgram.deepCopy(); // deep copy
        this.fileTable = fileTable;
        this.heap = heap;
        this.id = generalId;
        idChange();
    }

    public MyIHeap getHeap() {
        return this.heap;
    }
    public void setHeap(MyIHeap heap){
        this.heap = heap;
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
        this.heap.clear();
        this.exeStack.push(this.originalProgram);
        this.originalProgram = originalProgram.deepCopy();
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public boolean  isNotCompleted() {
        return !(exeStack.empty());
    }

    public synchronized static void idChange(){
        generalId = generalId + 1;
    }

    public ProgramState oneStep() throws ControllerException, DataStructureExceptions, StatementException {
        if (exeStack.empty())
            throw new ControllerException("Program State Stack is empty");
        //Execute the top statement from the stack
        IStatement statement = exeStack.pop();
         return  statement.execute(this);
    }




    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("Program ID: ").append(id).append("\n");
        result.append("Execution Stack: \n");
        result.append(this.exeStack.toString());
        result.append("Symbol Table: \n");
        result.append(this.symbolTable.toString());
        result.append("OutPut: \n");
        result.append(this.out);
        result.append("FileTable: \n");
        result.append(this.fileTable);
        result.append("Heap: \n");
        result.append(this.heap.toString());
        result.append("-------------------------------------------------------------------------\n");
        return result.toString();
    }
}