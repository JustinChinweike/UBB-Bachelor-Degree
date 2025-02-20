// File: Controller.Controller.java
package Controller;

import Exceptions.ControllerException;
import Exceptions.DataStructureExceptions;
import Exceptions.RepositoryException;
import Exceptions.StatementException;
import Exceptions.ExpressionException;
import Model.Adt.*;
import Model.ProgramState;
import Model.Statements.*;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepository;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository repo;
    private int displayFlag;

    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
    }


    List<Integer> getAddressesFromSymbolTable(Collection<IValue> symTableValues){
        return symTableValues.stream()
                .filter(value -> value instanceof RefValue)
                .map(value -> {RefValue valueFromSymbolTable = (RefValue)value; return valueFromSymbolTable.getAddress();})
                .collect(Collectors.toList());
    }

    List <Integer> getAddressesFromHeap(Collection<IValue> heapValues){
        return heapValues.stream()
                .filter(value->value instanceof RefValue)
                .map(value ->{RefValue valueFromHeap = (RefValue) value; return valueFromHeap.getAddress();})
                .collect(Collectors.toList()) ;
    }

    Map<Integer, IValue> garbageCollector(List<Integer> addressesFromSymbolTable, List<Integer> addressesFromHeapValues,
                                          Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(entry -> addressesFromSymbolTable.contains(entry.getKey()) ||
                        addressesFromHeapValues.contains(entry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));

    }


    // changed to void until the program state returned is used
    public void oneStep(ProgramState state) throws ControllerException, DataStructureExceptions, StatementException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        if (exeStack.empty())
            throw new ControllerException("ExeStack is empty");
        //Execute the top statement from the stack
        IStatement statement = exeStack.pop();
        statement.execute(state);
    }

    public void allStep() throws RepositoryException, ControllerException, DataStructureExceptions, StatementException {
        ProgramState state = repo.getProgramState();

        // Initial logging of program state before execution begins
        repo.logPrgStateExec();
        switch (displayFlag) {
            case 0:
                while (!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                    state.getHeap().setContent(garbageCollector(getAddressesFromSymbolTable(
                            state.getSymbolTable().getContent().values() ),
                            getAddressesFromHeap(state.getHeap().getContent().values()),
                            state.getHeap().getContent()
                    ));

                }
                System.out.println(state.toString());
                break;
            case 1:
                System.out.println(state.toString());
                while(!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                    state.getHeap().setContent(garbageCollector(getAddressesFromSymbolTable(
                            state.getSymbolTable().getContent().values()  ),
                    getAddressesFromHeap(state.getHeap().getContent().values()),
                    state.getHeap().getContent() ));


                    System.out.println(state.toString());
                }
                break;
            default:
                break;
        }
    }

    public void clearState() {
        ProgramState state = this.repo.getProgramState();
        state.clear();
    }
}



