using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _2._1._1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void AcceptClick(object sender, EventArgs e)
        {
            if (Name.Text == "" || Adres.Text == "" || EducationComboBox.Text == "")
                return;
            string txt = D.Checked ? D.Text : U.Text;
            MessageBox.Show($"{Name.Text}\n{Adres.Text}\n{EducationComboBox.Text}\n{txt}", "Uczelnia");
        }

        private void CancelClick(object sender, EventArgs e)
        {
            Name.Text = "";
            Adres.Text = "";
            EducationComboBox.Text = "";
            D.Checked = false;
            U.Checked = false;
        }

        private void D_CheckedChanged(Object sender, EventArgs e)
        {
            U.Checked = false;
        }

        private void U_CheckedChanged(Object sender, EventArgs e)
        {
            D.Checked = false;
        }

        private void Pomoc_Click(object sender, EventArgs e)
        {
            Help.ShowHelp(this, helpProvider1.HelpNamespace);
        }
    }
}
