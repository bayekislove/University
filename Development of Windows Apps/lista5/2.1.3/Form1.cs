using System;
using System.Drawing;
using System.Windows.Forms;

namespace _2._1._3
{
    public partial class Form1 : Form
    {
        Timer t = new Timer();

        int WIDTH = 150, HEIGHT = 150, minHAND = 60, hrHAND = 40;
        int cx, cy;

        Bitmap bmp;
        Graphics g;

        public Form1()
        {
            InitializeComponent();
            this.BackColor = Color.Gray;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            bmp = new Bitmap(WIDTH + 1, HEIGHT + 1);

            cx = WIDTH / 2;
            cy = HEIGHT / 2;

            t.Interval = 600;
            t.Tick += new EventHandler(this.t_Tick);
            t.Start();
        }

        private void t_Tick(object sender, EventArgs e)
        {
            g = Graphics.FromImage(bmp);

            int[] handCoord = new int[2];
            int minutes = DateTime.Now.Minute;
            int hours = DateTime.Now.Hour;

            g.Clear(Color.Gray);
            g.DrawEllipse(new Pen(Color.Black, 1f), 0, 0, WIDTH, HEIGHT);

            handCoord = minutesPos(minutes, minHAND);
            g.DrawLine(new Pen(Color.Blue, 2f), new Point(cx, cy), new Point(handCoord[0], handCoord[1]));

            handCoord = hrPos(hours % 12, minutes, hrHAND);
            g.DrawLine(new Pen(Color.Red, 3f), new Point(cx, cy), new Point(handCoord[0], handCoord[1]));

            pictureBox1.Image = bmp;
            g.Dispose();
        }

        private int[] hrPos(int hourVal, int minuteVal, int hourLen)
        {
            int val = (int)((hourVal * 30) + (minuteVal * 0.5));
            int[] coord = new int[2];

            if (val > -1 && val < 181)
            {
                coord[0] = cx + (int)(hourLen * Math.Sin(Math.PI * val / 180));
                coord[1] = cy - (int)(hourLen * Math.Cos(Math.PI * val / 180));
            }
            else
            {
                coord[0] = cx - (int)(hourLen * -Math.Sin(Math.PI * val / 180));
                coord[1] = cy - (int)(hourLen * Math.Cos(Math.PI * val / 180));
            }
            return coord;
        }

        private int[] minutesPos(int val, int hlen)
        {
            int[] coord = new int[2];
            val *= 6;

            if (val >= 0 && val <= 180)
            {
                coord[0] = cx + (int)(hlen * Math.Sin(Math.PI * val / 180));
                coord[1] = cy - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            else
            {
                coord[0] = cx - (int)(hlen * -Math.Sin(Math.PI * val / 180));
                coord[1] = cy - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            return coord;
        }
    }
}