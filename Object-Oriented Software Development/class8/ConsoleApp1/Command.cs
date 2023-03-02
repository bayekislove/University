using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public interface Command
    {
        public void Run();
    }

    //https://stackoverflow.com/questions/2781654/ftpwebrequest-download-file
    public class FTP : Command
    {
        string name;

        public FTP(string name)
        {
            this.name = name;
        }

        public void Run()
        {
            (new WebClient()).DownloadFile(this.name, "D:/");
        }
    }

    public class HTTP : Command
    {
        string name;

        public HTTP(string name)
        {
            this.name = name;
        }

        public void Run()
        {
            (new WebClient()).DownloadFile(this.name, "D:/");
        }
    }

    public class Empty : Command
    {
        string path;

        public Empty(string path)
        {
            this.path = path;
        }

        public void Run()
        {
            File.Create(path);
            using(var writer = new StreamWriter(this.path))
            {
                writer.Write(new Random().Next().ToString());
            }
        }
    }

    public class Move : Command
    {
        string from, to;

        public Move(string from, string to)
        {
            this.from = from;
            this.to = to;
        }

        public void Run()
        {
            File.Move(from, to);
        }
    }
}
