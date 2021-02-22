import java.math.*;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Supplier;

public class calculatorModel 
{
    private String leftSideString;
    private String rightSideString;
    private BigInteger leftSide;
    private BigInteger rightSide;
    private int radix;
    private String op;
    private boolean leftToInsert;
    private boolean leftSideLocked;

    private Map<String, Supplier<BigInteger>> operations;

    public calculatorModel()
    {
        operations = new HashMap<String, Supplier<BigInteger>>();
        operations.put( "+", () -> leftSide.add(rightSide) );
        operations.put( "*", () -> leftSide.multiply(rightSide) );
        operations.put( "/", () -> rightSide.equals(BigInteger.ZERO) ? BigInteger.ZERO : leftSide.divide(rightSide) );
        operations.put( "-", () -> leftSide.subtract(rightSide) );
        operations.put( "**", () -> leftSide.pow(rightSide.intValue()) );
        operations.put( "%", () -> leftSide.mod(rightSide) );

        operations.put( "(  )", () -> factorial(leftSide).divide(factorial(rightSide).multiply(factorial(leftSide.subtract(rightSide)))));
        operations.put( "!", () -> factorial(leftSide) );
        operations.put( "*(-1)", () -> leftSide.multiply(new BigInteger("-1")) );

        leftToInsert = true;
        leftSideString = ""; rightSideString = ""; op = "";
        radix = 10;
    }

    private BigInteger factorial(BigInteger inp){
        BigInteger fact = BigInteger.ONE;
        BigInteger counter = BigInteger.ONE;

        while( counter.compareTo(inp) != 1 ){
            fact = fact.multiply(counter);
            counter = counter.add(BigInteger.ONE);
        }

        return fact;
    } 

    public String changeRadix(int radix)
    {
        //first we create number in decimal system, then we convert it to the system we want
        if(!leftSideString.equals("")) 
            this.leftSideString = (new BigInteger(leftSideString, this.radix)).toString(radix);
        if(!rightSideString.equals("")) 
            this.rightSideString = (new BigInteger(rightSideString, this.radix)).toString(radix);
        this.radix = radix;
        //convention -> curr;;prev
        
        if(!leftSideLocked) return leftSideString + op + rightSideString + ";";
        else return leftSideString + ";" + op + rightSideString;
    }

    public String eval()
    {
        if( leftSideString.equals("") || op.equals("") ) return leftSideString + op;

        this.leftSide = new BigInteger(this.leftSideString, this.radix);
        if(!(this.rightSideString.equals(""))) rightSide = new BigInteger(this.rightSideString, this.radix);

        BigInteger calcResult = operations.get( op ).get();
        this.leftSide = calcResult;
        this.rightSide = null;

        leftToInsert = false;
        leftSideLocked = true;
        this.leftSideString = leftSide.toString(radix);
        this.rightSideString = ""; this.op = "";
        return calcResult.toString(this.radix);
    }

    public String addOperator(String newOp)
    {
        op = newOp;
        leftToInsert = false;
        return leftSideLocked ? op + rightSideString : leftSideString + op + rightSideString;
    };

    public String addChar(String num)
    {
        if( leftToInsert && !leftSideLocked ) leftSideString += num;
        else if( leftSideLocked && op.equals("") ) return "";
        else rightSideString += op.equals("*(-1)") || op.equals("!") ? "" : num;

        return leftSideLocked ? op + rightSideString : leftSideString + op + rightSideString;
    }

    public String removeChar()
    {
        if( leftSideString.equals("") ) return "";

        if( !rightSideString.equals("") )
            rightSideString = rightSideString.substring(0, rightSideString.length() - 1);
        
        else
        {
            leftToInsert = true; //if user deleted operator, he can again insert left side of the expression 

            if( op.equals("") ){
                leftSideString = ""; rightSideString = "";
                leftSideLocked = false;
                return "";
            }
            if( !op.equals("") ) op = ""; 
            else leftSideString = leftSideString.substring(0, leftSideString.length() - 1);
        }

        return leftSideLocked ? rightSideString : leftSideString + op + rightSideString;
    }

    public int getRadix(){ return this.radix; };
}