package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class MultiThreadRepo implements IRepository{
    private List<ProgramState> programStates;
    private String logFilePath;
    private List<ProgramState> originalProgramStates;

    public MultiThreadRepo(String logFilePath) {
        programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
        originalProgramStates = new ArrayList<>();
    }

    public MultiThreadRepo(List<ProgramState> programStates, String logFilePath) {
        this.programStates = programStates;
        this.logFilePath = logFilePath;
        this.originalProgramStates = new ArrayList<>();
        this.originalProgramStates.addAll(programStates);
    }

    public MultiThreadRepo(ProgramState programState, String logFilePath) {
        programStates = new ArrayList<>();
        programStates.add(programState);
        this.logFilePath = logFilePath;
        this.originalProgramStates = new ArrayList<>();
        this.originalProgramStates.add(programState);
    }

    public void logProgramStateExec(ProgramState programState) throws RepositoryException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)))) {
            logFile.println(programState.toString());
        } catch (IOException e) {
            throw new RepositoryException("Cannot create output file for the program!");
        }
    }

    public List<ProgramState> getProgramStateList() {
        return programStates;
    }

    public void setProgramStateList(List<ProgramState> programStates){
         this.programStates = programStates;
    }


    public void originalList() {
        this.programStates.addAll(originalProgramStates);
    }


//    public ProgramState getProgramState() throws RepositoryException {
//        if (!programStates.isEmpty()) {
//            return this.programStates.getFirst();
//        }
//        throw new RepositoryException("Repository is empty");
//    }

//    public void setProgramState(ProgramState programState) {
//        if (this.programStates.isEmpty()) {
//            this.programStates.add(programState);
//        }
//        else {
//            this.programStates.set(0, programState);
//        }
//    }





}