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
import Repository.IRepository;

public class Controller {
    private IRepository repo;
    private int displayFlag;

    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
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

    /**
     * Executes the entire program by calling oneStep in a loop.
     * Logs the program state to a file after each step as required by Lab5 Task 1.3.
     *
     * @throws RepositoryException if an error occurs in accessing or logging the repository
     * @throws ControllerException if an error occurs in program execution
     * @throws DataStructureExceptions if a data Structure error occurs
     * @throws StatementException if an error occurs in executing a statement
     */
    public void allStep() throws RepositoryException, ControllerException, DataStructureExceptions, StatementException {
        ProgramState state = repo.getProgramState();

        // Initial logging of program state before execution begins
        repo.logProgramStateExec();

//        // Run until the execution stack is empty
        if (displayFlag == 1) {
            displayCurrentState();
        }

        // Run until the execution stack is empty
        while (!state.getExeStack().empty()) {
            try {
                this.oneStep(state); // Execute one step

                // Log the program state after each step
                repo.logProgramStateExec();

                // Display state if displayFlag is set
                if (displayFlag == 1) displayCurrentState(); // Display state if needed
            } catch (StatementException | ExpressionException | DataStructureExceptions e) {
                System.out.println("Error during execution: " + e.getMessage());
                break; // Stop execution if an error occurs
            }
        }
        if (displayFlag == 0 ) displayCurrentState();
    }

    // Display the current program state
    public void displayCurrentState() {
        if (displayFlag == 1) {
            System.out.println(this.repo.getProgramState().toString());
        }
    }

    public void clearState() {
        ProgramState state = this.repo.getProgramState();
        state.clear();
    }
}



