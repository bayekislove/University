using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;

namespace _2._3._9
{
    public partial class Service1 : ServiceBase
    {
        public Service1()
        {
            InitializeComponent();
        }

        System.Timers.Timer t;

        protected override void OnStart(string[] args)
        {
            t = new System.Timers.Timer(1000);
            t.Elapsed += (s, e) =>
            {
                using (FileStream a = new FileStream("a.txt", FileMode.CreateNew))
                using (StreamWriter wr = new StreamWriter(a))
                {
                    foreach (Process p in Process.GetProcesses())
                    {
                        if (!String.IsNullOrEmpty(p.MainWindowTitle))
                        {
                            wr.WriteLine(p.MainWindowTitle);
                        }
                    }
                }
            };
            t.Start();
        }

        protected override void OnStop()
        {
        }
    }
}
