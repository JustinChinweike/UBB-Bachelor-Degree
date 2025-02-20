//File: Model.Expressions.IExpression.java
package Model.Expressions;
import Exceptions.ExpressionException;
import Model.Adt.MyIHeap;
import Model.Type.IType;
import Model.Values.IValue;
import Model.Adt.MyIDictionary;

public interface IExpression {
    IType typecheck(MyIDictionary<String,IType> typeEnv) throws ExpressionException;
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap)
                   throws ExpressionException;
    IExpression deepCopy() ;
}

