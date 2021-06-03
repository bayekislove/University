using System;
using Microsoft.CSharp;
using System.CodeDom.Compiler;

namespace _2._3._11
{
    class Program
    {
        static void Main(string[] args)
        {
            string a = $"public class karamba {{ public int a() {{";

            Console.WriteLine("Write your function definition here in one line");

            a += Console.ReadLine();
            a += "}}";

            CompilerResults res = (new CSharpCodeProvider()).CompileAssemblyFromSource(new CompilerParameters(), a);

            var type = res.CompiledAssembly.GetType("karamba");
            var func = type.GetMethod("a");

            Console.WriteLine(func.Invoke(Activator.CreateInstance(type), null));
            Console.ReadLine();
        }
    }
}
