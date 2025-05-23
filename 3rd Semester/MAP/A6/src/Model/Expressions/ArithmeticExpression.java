// File: Model.Expressions.ArithmeticExpression.java
package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression implements IExpression {
    private IExpression firstExpression;
    private IExpression secondExpression;
    private int operator; // 1-plus, 2-minus, 3-star, 4-divide
    private char operatorChar;

    public ArithmeticExpression (char operator, IExpression firstExpression,
                                 IExpression secondExpression){

        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        if (operator == '+') this.operator = 1;
        else if (operator == '-') this.operator = 2;
        else if (operator == '*') this.operator = 3;
        else if (operator == '/') this.operator = 4;
        else this.operator = -1;
        this.operatorChar = operator;
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType typ1, typ2;
        typ1=firstExpression.typecheck(typeEnv);
        typ2=secondExpression.typecheck(typeEnv);
        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new IntType();
            }else
                throw new ExpressionException("second operand is not an integer");
        }else
            throw new ExpressionException("first operand is not an integer");
    }

    public IValue evaluate(MyIDictionary<String ,IValue> symbolTable, MyIHeap heap)
                         throws ExpressionException{
        IValue firstValue, secondValue;
        firstValue = firstExpression.evaluate(symbolTable, heap);
        if (firstValue.getType().equals(new IntType())) {
            secondValue = secondExpression.evaluate(symbolTable, heap);
            if( secondValue.getType().equals(new IntType())){
                IntValue firstInteger = (IntValue) firstValue;
                IntValue secondInteger = (IntValue) secondValue;
                int firstNumber = firstInteger.getValue();
                int secondNumber = secondInteger.getValue();
                switch (operator) {
                    case 1: return new IntValue(firstNumber + secondNumber);
                    case 2: return new IntValue (firstNumber -  secondNumber);
                    case 3: return new IntValue( firstNumber * secondNumber);
                    case 4: if(secondNumber != 0)
                        return new IntValue(firstNumber / secondNumber) ;
                    else throw new ExpressionException("Division by zero");
                    default: throw new ExpressionException("Invalid operator");
                }
            }else {
                throw new ExpressionException("Second operand is not an integer");
            }
        }else {
            throw new ExpressionException("First operand is not an integer");

        }
    }
    @Override
    public IExpression deepCopy() {
        return new ArithmeticExpression(this.operatorChar, this.firstExpression.deepCopy(), this.secondExpression.deepCopy());
    }
    public String toString() {
        return firstExpression.toString() + " " + this.operatorChar + " " + secondExpression.toString();

    }
}
