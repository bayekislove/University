using System;
using System.Linq.Expressions;

namespace class6
{
    class Program
    {
        public static void exampleMethod()
        {
        }

        public class exampleClass
        {
            public exampleClass()
            {

            }
        }

        static void Main(string[] args)
        {
            #region NullObject
            LoggerFactory factory = LoggerFactory.Instance();

            ILogger fileLogger = factory.GetLogger(LogType.File, "./aaa.txt");
            ILogger nullLogger = factory.GetLogger(LogType.None);
            ILogger consoleLogger = factory.GetLogger(LogType.Console);

            fileLogger.Log("test");
            nullLogger.Log("test");
            consoleLogger.Log("test");
            #endregion

            #region Interpreter
            Context context = new Context();
            context.SetValue("a", true);
            context.SetValue("b", true);
            context.SetValue("c", false);

            ConstExpression a = new ConstExpression("a");
            ConstExpression b = new ConstExpression("b");
            ConstExpression c = new ConstExpression("c");

            UnaryExpression negC = new UnaryExpression(c, UnaryOperator.Negation);
            BinaryExpression conAB = new BinaryExpression(a, b, BinaryOperator.Conjunction);
            BinaryExpression result = new BinaryExpression(conAB, negC, BinaryOperator.Conjunction);
            Console.WriteLine(result.Interpret(context));
            #endregion

            #region Visitor
            Tree root = new TreeNode()
            {
                Left = new TreeNode()
                {
                    Left = new TreeLeaf() { Value = 1 },
                    Right = new TreeLeaf() { Value = 2 }
                },
                Right = new TreeLeaf() { Value = 3 }
            };

            Tree root2 = new TreeNode()
            {
                Left = new TreeLeaf() { Value = 3 },
                Right = new TreeLeaf() { Value = 3 }
            };

            Console.WriteLine(new TreeHeightVisitor().Visit(root));
            Console.WriteLine(new TreeHeightVisitor().Visit(root2));
            #endregion

            #region VistorNET
            Expression<Func<bool>> f = () => typeof(int).IsValueType;
            System.Linq.Expressions.UnaryExpression negate1 = Expression.Negate(Expression.Constant(1));
            MethodCallExpression method1 = Expression.Call(typeof(Program).GetMethod("exampleMethod"));
            NewExpression newExpr = Expression.New(typeof(exampleClass).GetConstructor(Type.EmptyTypes));

            PrintExpressionVisitor v = new PrintExpressionVisitor();
            v.Visit(f);
            v.Visit(negate1);
            v.Visit(method1);
            v.Visit(newExpr);
            #endregion
        }
    }
}
