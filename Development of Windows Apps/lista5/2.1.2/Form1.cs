using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace _2._1._2
{
    public partial class Form1 : Form
    {
        private int counter = 0;
        public Form1()
        {
            InitializeComponent();
            Random r = new Random();
            for (int i = 0; i < 100; i++)
            {
                pogBar.ForeColor = Color.FromArgb(r.Next(256), r.Next(256), r.Next(256));
                pogBar.Increment(1);
                Thread.Sleep(10);
                Console.WriteLine(i.ToString());
            }
        }

        public void a()
        {
            Random r = new Random();
            for (int i = 0; i < 100; i++)
            {
                pogBar.ForeColor = Color.FromArgb(r.Next(256), r.Next(256), r.Next(256));
                pogBar.Increment(1);
                Thread.Sleep(10);
                Console.WriteLine(i.ToString());
            }
        }

        private void monthCalendar1_DateChanged(object sender, DateRangeEventArgs e)
        {
            monthCalendar1.TrailingForeColor = counter % 2 == 0 ? Color.Red : Color.Blue;
            counter++;
        }
    }
}
