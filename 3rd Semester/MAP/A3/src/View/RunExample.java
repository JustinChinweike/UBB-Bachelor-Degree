package View;
import Controller.Controller;
import Exceptions.*;

public class RunExample extends Command {
    private Controller ctr;
    public RunExample(String key, String desc,Controller ctr){
        super(key, desc);
        this.ctr=ctr;
    }
    @Override
    public void execute() {
        try{
            ctr.allStep(); }
        catch (RepositoryException | ControllerException | StatementException| ExpressionException| DataStructureExceptions e) {
            System.out.println(e.getMessage());
        } //here you must treat the exceptions that can not be solved in the controller
        this.ctr.clearState();
    }

}
