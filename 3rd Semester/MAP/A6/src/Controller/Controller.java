// File: Controller.Controller.java
package Controller;

import Exceptions.*;
import Model.Adt.MyIHeap;
import Model.ProgramState;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public class Controller {
    private IRepository repo;
    private int displayFlag;
    private ExecutorService executorService ;
    private boolean muteLogProgramStateExecution;
    private boolean mutePrintProgramStateExecution;


    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
        this.muteLogProgramStateExecution = false;
        this.mutePrintProgramStateExecution = false;

    }


    /**
     *  Filters the input by keeping only the address field
     *  from the Values in symbol table which are RefValue.
     * @param symbolTableValues all entries in a symbol table (type Collection<Value>)
     * @return the update symbolTableValues (type List<int>)
     */
    List<Integer> getAddressesFromSymbolTable(Collection<IValue> symbolTableValues){
        return symbolTableValues.stream()
                .filter(value -> value instanceof RefValue)
                .map(value -> {RefValue valueFromSymbolTable = (RefValue)value; return valueFromSymbolTable.getAddress();})
                .collect(Collectors.toList());
    }

    /**
     * Filters the input by keeping only the address field
     * from the Values in heap which are RefValue.
     * @param heapValues all entries in a heap(type Collection<Value>)
     * @return the update heapValues (type List<int>)
     */
    List <Integer> getAddressesFromHeap(Collection<IValue> heapValues){
        return heapValues.stream()
                .filter(value->value instanceof RefValue)
                .map(value ->{RefValue valueFromHeap = (RefValue) value; return valueFromHeap.getAddress();})
                .collect(Collectors.toList()) ;
    }

    /**
     * It removes all entries in heap which don't have the key in addressesFromSymbolTable or addressesFromHeapValues.
     * @param addressesFromSymbolTable (type List<Integer>) all keys from a ProgramState's symbolTable
     * @param addressesFromHeapValues (type List<Integer>) all keys from a ProgramState's heap (or found in RefValues's address)
     * @param heap (type Map<Integer, Value>)
     * @return the modified heap
     */
    Map<Integer, IValue> garbageCollector(List<Integer> addressesFromSymbolTable, List<Integer> addressesFromHeapValues,
                                          Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(entry -> addressesFromSymbolTable.contains(entry.getKey()) ||
                        addressesFromHeapValues.contains(entry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));

    }

    public void setMuteLogProgramStateExecution(boolean muteLogProgramStateExecution) {
        this.muteLogProgramStateExecution = muteLogProgramStateExecution;
    }

    public void setMutePrintProgramStateExecution(boolean mutePrintProgramStateExecution) {
        this.mutePrintProgramStateExecution = mutePrintProgramStateExecution;
    }




    /**
     * It filters all ProgramStates by removing the ones which are "completed" (isNotCompleted returns false)
     * @param inProgramList an initial list of ProgramState (type List<ProgramState>)
     * @return the modified programList
     */
    List<ProgramState> removeCompletedPrograms(List<ProgramState> inProgramList){
        return inProgramList.stream().filter(ProgramState::isNotCompleted).collect(Collectors.toList());
    }

    /**
     * <p>
     *     Firstly, it creates a List of Callables from programStateList. Then, the executorService creates a List
     * of Futures which used as a stream will give update programStateList by executing one step for each ProgramState
     * (which should be in a separate thread). The programStateList is updated by adding ProgramStates for which one step returned
     * not null (one step executed a ForkStatement).
     * </p>
     * <p>
     *     Basically for each ForkStatement executed, there will be a new ProgramState in programStateList.
     * </p>
     * <p>
     *      ProgramStates are logged into a file if "not muted"(muteLogProgramStateExecution is false).
     * </p>
     * @param programStateList (type List<ProgramState>) repository's programStates
     */
    void oneStepForAllProgramStates(List<ProgramState> programStateList) {
        if(!muteLogProgramStateExecution)
            programStateList.forEach(repo::logProgramStateExec);

        // now we want to execute one step for each program states
        List<Callable<ProgramState>> callableProgramStateList = programStateList
                .stream()
                .map(
                        // we change each programState into a Callable<ProgramState>
                        (ProgramState programState) -> (Callable<ProgramState>)(programState::oneStep)
                )
                .collect(Collectors.toList());

        try {
            List<ProgramState> newProgramStateList = executorService.invokeAll(callableProgramStateList)
                    // in the stream we will have a Future for each program state containing its execution result
                    .stream()
                    .map(programStateFuture -> {
                        try {
                            return programStateFuture.get();
                        } catch (InterruptedException e) {
                            throw new RuntimeException("InterruptedException()\n");
                        } catch (ExecutionException e) {
                            e.printStackTrace();
                            throw new RuntimeException("ExecutionException()\n");
                        }
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

            // add the new ProgramStates
            programStateList.addAll(newProgramStateList);
            if(!muteLogProgramStateExecution)
                programStateList.forEach(repo::logProgramStateExec);

            // save the modifications in the repository
            repo.setProgramStateList(programStateList);
        } catch (InterruptedException e) {
            throw new RuntimeException("InterruptedException\n");
        }
    }

    /**
     *  <p>
     *      It executes oneStepForAllProgramStates until programStateList becomes empty.
     *      Also clears the heap for each ProgramState using garbageCollector method.
     *  </p>
     *  <p>
     *      ProgramStates are logged into a file if "not muted"(muteLogProgramStateExecution is false).
     *      ProgramStates are printed on the screen if "not muted"(mutePrintProgramStateExecution is false).
     *  </p>
     */
    public void allStep() {
        executorService = Executors.newFixedThreadPool(2);

        // remove completed
        List<ProgramState> programStateList = removeCompletedPrograms(repo.getProgramStateList());
        if (!mutePrintProgramStateExecution)
            System.out.println(programStateList.get(0).toString());
        while(programStateList.size() > 0){
            // use garbageCollector
            // we can take the heap from the first programState since it's shared
            // Perform garbage collection for the shared heap
            MyIHeap heap = programStateList.get(0).getHeap(); // Shared heap
            for (ProgramState programState: programStateList) {
                // for the symbol table we must take it for each due to it being a local state
                programState.getHeap().setContent(garbageCollector(
                                getAddressesFromSymbolTable(programState.getSymbolTable().getContent().values()),
                                getAddressesFromHeap(heap.getContent().values()),
                                heap.getContent()
                        )
                );
            }

            // Execute one step for all program states
            oneStepForAllProgramStates(programStateList);

            // Print states if not muted
            if (!mutePrintProgramStateExecution)
                for (ProgramState programState: programStateList) {
                    System.out.println(programState.toString());
                }

            // Remove completed programs
            programStateList = removeCompletedPrograms(repo.getProgramStateList());
        }
        executorService.shutdown();

        // Update the repository with the remaining program states
        repo.setProgramStateList(programStateList);
    }



    public void clearState() {
        this.repo.originalList();
        ProgramState state = this.repo.getProgramStateList().getFirst();
        state.clear();
    }
}



