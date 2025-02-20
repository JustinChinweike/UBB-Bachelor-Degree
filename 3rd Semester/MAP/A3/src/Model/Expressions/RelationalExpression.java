package Model.Expressions;
import Exceptions.ExpressionException;
import Model.Type.IntType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.IValue;
import Model.Adt.MyIDictionary;

public class RelationalExpression  implements IExpression {
    private IExpression Exp1, Exp2;
    private String Operator;

    public RelationalExpression(String Operator, IExpression Exp1, IExpression Exp2) {
        this.Operator = Operator;
        this.Exp1 = Exp1;
        this.Exp2 = Exp2;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionException {
        IValue Value1 = Exp1.evaluate(symbolTable);
        IValue Value2 = Exp2.evaluate(symbolTable);

        // Ensure both values are of type IntType
        if (!(Value1.getType().equals(new IntType()) && Value2.getType().equals(new IntType()))) {
            throw new ExpressionException("Both operands must be of IntType");
        }
        int num1 = ((IntValue) Value1).getValue();
        int num2 = ((IntValue) Value2).getValue();
        // Evaluate based on the operator
        return switch (Operator) {
            case "<" -> new BoolValue(num1 < num2);
            case "<=" -> new BoolValue(num1 <= num2);
            case "==" -> new BoolValue(num1 == num2);
            case "!=" -> new BoolValue(num1 != num2);
            case ">" -> new BoolValue(num1 > num2);
            case ">=" -> new BoolValue(num1 >= num2);
            default -> throw new ExpressionException("Invalid operator: " + Operator);
        };
    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(Operator, Exp1.deepCopy(), Exp2.deepCopy());
    }

    public String toString() {
        return Exp1.toString() + " " + Operator + " " + Exp2.toString();
    }
}

