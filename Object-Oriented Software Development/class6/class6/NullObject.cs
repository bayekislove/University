using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class6
{
    public interface ILogger
    {
        void Log(string Message);
    }

    public enum LogType { None, Console, File }

    public class LogNull : ILogger
    {
        public void Log(string Message)
        {

        }
    }

    public class LogToFile : ILogger
    {
        string path;

        public LogToFile(string path)
        {
            this.path = path;
        }

        public void Log(string Message)
        {
            using(var writer = new StreamWriter(path))
            {
                writer.WriteLine(Message);
            }
        }
    }

    public class LogToConsole : ILogger
    {
        public void Log(string Message)
        {
            Console.WriteLine(Message);
        }
    }

    public class LoggerFactory
    {
        static LoggerFactory instance = null;

        public ILogger GetLogger(LogType LogType, string Parameters = null)
        {
            switch(LogType)
            {
                case LogType.Console:
                    return new LogToConsole();
                case LogType.File:
                    return new LogToFile(Parameters);
                default:
                    return new LogNull();
            }
        }

        public static LoggerFactory Instance()
        {
            return (instance is null) ? new LoggerFactory() : instance;
        }
    }
}
