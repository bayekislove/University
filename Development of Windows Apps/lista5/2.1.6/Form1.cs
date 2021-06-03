using System;
using System.Threading;
using System.Windows.Forms;

namespace _2._1._6
{
    public partial class Form1 : Form
    {
        private bool isPrime(int n)
        {
            for(int i = 2; i < n; i++ )
            {
                if (n % i == 0)
                    return true;
            }
            return n == 0 || n == 1;
        }   

        public Form1()
        {
            //jak klikniemy przycisk to wyrzuci błąd że próbujemy dostać się do elementu który nie został utworzony
            //w tym wątku (w tym nowym który tworzymy po naciśnięciu przycisku 
            InitializeComponent();
            backgroundWorker1.WorkerReportsProgress = true;
            backgroundWorker1.WorkerSupportsCancellation = true;
            backgroundWorker1.RunWorkerAsync();
        }

        private void threadFunc()
        {
            for (int i = 0; i < 100000; i++)
            {
                isPrime(i);
                progressBar1.Value = i / 1000;
            }
        }

        private void backgroundWorker1_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            for (int i = 0; i < 100000; i++)
            {
                isPrime(i);
                backgroundWorker1.ReportProgress(i / 1000);
            }       
        }

        private void backgroundWorker1_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
        {
            progressBar1.Value = e.ProgressPercentage;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var a = new Thread(new ThreadStart(threadFunc));
            a.Start();
        }
    }
}
