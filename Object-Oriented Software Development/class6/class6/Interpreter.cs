using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class6
{
    public class Context
    {
        private Dictionary<string, bool> context;

        public Context()
        {
            context = new Dictionary<string, bool>();
        }

        public bool GetValue(string VariableName)
        {
            return context[VariableName];
        }

        public void SetValue(string VariableName, bool Value)
        {
            context[VariableName] = Value;
        }
    }

    public abstract class AbstractExpression
    {
        public abstract bool Interpret(Context context);
    }

    public class ConstExpression : AbstractExpression
    {
        string variable;

        public ConstExpression(string variable)
        {
            this.variable = variable;
        }

        public override bool Interpret(Context context)
        {
            return context.GetValue(variable);
        }
    }

    public enum BinaryOperator
    {
        Alternative,
        Conjunction
    }

    public enum UnaryOperator
    {
        Negation,
        Identity
    }

    public class BinaryExpression : AbstractExpression
    {
        private AbstractExpression left;
        private AbstractExpression right;
        public BinaryOperator op;

        public BinaryExpression(AbstractExpression left, AbstractExpression right, BinaryOperator op)
        {
            if(left == null || right == null || op == null)
            {
                throw new ArgumentNullException();
            }
            this.left = left;
            this.right = right;
            this.op = op;
        }

        public override bool Interpret(Context context)
        {
            switch(op)
            {
                case BinaryOperator.Alternative:
                    return left.Interpret(context) | right.Interpret(context);
                case BinaryOperator.Conjunction:
                    return left.Interpret(context) & right.Interpret(context);
                default:
                    throw new ArgumentException();
            }
        }
    }

    public class UnaryExpression : AbstractExpression
    {
        private ConstExpression expr;
        private UnaryOperator op;

        public UnaryExpression(ConstExpression expr, UnaryOperator op)
        {
            this.expr = expr;
            this.op = op;
        }
        
        public override bool Interpret(Context context)
        {
            switch(op)
            {
                case UnaryOperator.Identity:
                    return expr.Interpret(context);
                case UnaryOperator.Negation:
                    return !expr.Interpret(context);
                default:
                    throw new ArgumentException();
            }
        }
    }
}
