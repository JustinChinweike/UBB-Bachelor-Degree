package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.BoolType;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

public class RelationalExpression implements IExpression {
    private IExpression leftExpression;
    private IExpression rightExpression;
    private String relationalOperator;

    public RelationalExpression(IExpression leftExpression, IExpression rightExpression, String relationalOperator) {
        this.leftExpression = leftExpression;
        this.rightExpression = rightExpression;
        this.relationalOperator = relationalOperator;
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType first = leftExpression.typecheck(typeEnv);
        IType second = rightExpression.typecheck(typeEnv);

        if (!first.equals(new IntType())){
            throw new ExpressionException("Result type does not match the value type for the LEFT OPERAND\"");
        }
        if (!second.equals(new IntType())) {
            throw new ExpressionException("Result type does not match the value type for the RIGHT OPERAND");
        }
        return new BoolType();
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException {
        IValue resultLeft = leftExpression.evaluate(symbolTable, heap);
        IValue resultRight = rightExpression.evaluate(symbolTable, heap);

        if (!resultLeft.getType().equals(new IntType())) {
            throw new ExpressionException("Result type does not match the value type for the LEFT OPERAND");
        }
        if (!resultRight.getType().equals(new IntType())) {
            throw new ExpressionException("Result type does not match the value type for the RIGHT OPERAND");
        }

        return switch(this.relationalOperator){
            case "<" -> new BoolValue(((IntValue)resultLeft).getValue() < ((IntValue)resultRight).getValue());
            case "<=" -> new BoolValue(((IntValue)resultLeft).getValue() <= ((IntValue)resultRight).getValue());
            case "==" -> new BoolValue(((IntValue)resultLeft).getValue() == ((IntValue)resultRight).getValue());
            case "!=" -> new BoolValue(((IntValue)resultLeft).getValue() != ((IntValue)resultRight).getValue());
            case ">" -> new BoolValue(((IntValue)resultLeft).getValue() > ((IntValue)resultRight).getValue());
            case ">=" -> new BoolValue(((IntValue)resultLeft).getValue() >= ((IntValue)resultRight).getValue());
            default -> throw new ExpressionException("Invalid relational operator");
        };
    }

    public IExpression deepCopy() {
        return new RelationalExpression(leftExpression.deepCopy(), rightExpression.deepCopy(), relationalOperator);
    }

    public String toString(){
        return "(" + leftExpression.toString() + " " + relationalOperator + " " + rightExpression.toString() + ")";
    }
}