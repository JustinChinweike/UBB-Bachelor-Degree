
package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState;

import java.util.List;

public interface IRepository {
    //ProgramState getProgramState() throws RepositoryException;
   // void setProgramState(ProgramState programState);

    void logProgramStateExec(ProgramState programState) throws RepositoryException;
    List<ProgramState> getProgramStateList();
    void setProgramStateList(List<ProgramState> programStates);
    void originalList();


}
