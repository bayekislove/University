using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace class6
{
    public class PrintExpressionVisitor : ExpressionVisitor
    {
        protected override Expression VisitBinary(System.Linq.Expressions.BinaryExpression expression)
        {
            Console.WriteLine("{0} {1} {2}",
            expression.Left, expression.NodeType, expression.Right);
            return base.VisitBinary(expression);
        }

        protected override Expression VisitUnary(System.Linq.Expressions.UnaryExpression expression)
        {
            Console.WriteLine("{0} {1}d", expression.Operand, expression.NodeType);
            return base.VisitUnary(expression);
        }

        protected override Expression VisitMethodCall(MethodCallExpression node)
        {
            Console.WriteLine("Metoda {0} {1} jest generyczna", node.Method.Name, 
                (node.Method.IsGenericMethod) ? "" : "nie");
            return base.VisitMethodCall(node);
        }

        protected override Expression VisitLambda<T>(Expression<T> expression)
        {
            Console.WriteLine("{0} -> {1}",
            expression.Parameters.Aggregate(string.Empty, (a, e) => a += e),
            expression.Body);
            return base.VisitLambda<T>(expression);
        }

        protected override Expression VisitNew(NewExpression node)
        {
            Console.WriteLine("Wywołanie konstruktora z {0} parametrem(-ami)", node.Constructor.GetParameters().Length);
            return base.VisitNew(node);
        }
    }
}
