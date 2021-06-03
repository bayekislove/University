
using System;
using System.Windows.Forms;

namespace _2._1._1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Adres = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.Name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.U = new System.Windows.Forms.CheckBox();
            this.D = new System.Windows.Forms.CheckBox();
            this.EducationComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.CancelButton = new System.Windows.Forms.Button();
            this.AcceptButton = new System.Windows.Forms.Button();
            this.helpProvider1 = new System.Windows.Forms.HelpProvider();
            this.Pomoc = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Beige;
            this.groupBox1.Controls.Add(this.Adres);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.Name);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(776, 139);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Uczelnia";
            // 
            // Adres
            // 
            this.Adres.Location = new System.Drawing.Point(165, 91);
            this.Adres.Name = "Adres";
            this.Adres.Size = new System.Drawing.Size(605, 27);
            this.Adres.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Adres:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // Name
            // 
            this.Name.Location = new System.Drawing.Point(165, 34);
            this.Name.Name = "Name";
            this.Name.Size = new System.Drawing.Size(605, 27);
            this.Name.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Nazwa:";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Bisque;
            this.groupBox2.Controls.Add(this.U);
            this.groupBox2.Controls.Add(this.D);
            this.groupBox2.Controls.Add(this.EducationComboBox);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(12, 170);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(776, 201);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Rodzaj studiów";
            // 
            // U
            // 
            this.U.AutoSize = true;
            this.U.Location = new System.Drawing.Point(553, 124);
            this.U.Name = "U";
            this.U.Size = new System.Drawing.Size(122, 24);
            this.U.TabIndex = 4;
            this.U.Text = "uzupełniające";
            this.U.UseVisualStyleBackColor = true;
            this.U.Click += new System.EventHandler(this.U_CheckedChanged);
            // 
            // D
            // 
            this.D.AutoSize = true;
            this.D.Location = new System.Drawing.Point(85, 124);
            this.D.Name = "D";
            this.D.Size = new System.Drawing.Size(83, 24);
            this.D.TabIndex = 3;
            this.D.Text = "dzienne";
            this.D.UseVisualStyleBackColor = true;
            this.D.Click += new System.EventHandler(this.D_CheckedChanged);
            // 
            // EducationComboBox
            // 
            this.EducationComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.EducationComboBox.FormattingEnabled = true;
            this.EducationComboBox.Items.AddRange(new object[] {
            "3 letnie",
            "3,5 letnie",
            "5 letnie"});
            this.EducationComboBox.Location = new System.Drawing.Point(165, 52);
            this.EducationComboBox.Name = "EducationComboBox";
            this.EducationComboBox.Size = new System.Drawing.Size(605, 28);
            this.EducationComboBox.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label3.Location = new System.Drawing.Point(13, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 31);
            this.label3.TabIndex = 0;
            this.label3.Text = "Cykl nauki:";
            // 
            // CancelButton
            // 
            this.CancelButton.Location = new System.Drawing.Point(574, 377);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(214, 61);
            this.CancelButton.TabIndex = 2;
            this.CancelButton.Text = "Anuluj";
            this.CancelButton.UseVisualStyleBackColor = true;
            this.CancelButton.Click += new System.EventHandler(this.CancelClick);
            // 
            // AcceptButton
            // 
            this.AcceptButton.Location = new System.Drawing.Point(12, 377);
            this.AcceptButton.Name = "AcceptButton";
            this.AcceptButton.Size = new System.Drawing.Size(186, 61);
            this.AcceptButton.TabIndex = 3;
            this.AcceptButton.Text = "Akceptuj";
            this.AcceptButton.UseVisualStyleBackColor = true;
            this.AcceptButton.Click += new System.EventHandler(this.AcceptClick);
            // 
            // helpProvider1
            // 
            this.helpProvider1.HelpNamespace = "C:\\Users\\Kacper\\Desktop\\University\\Development of Windows Apps\\lista5\\2.1.chm";
            // 
            // Pomoc
            // 
            this.Pomoc.Location = new System.Drawing.Point(373, 402);
            this.Pomoc.Name = "Pomoc";
            this.Pomoc.Size = new System.Drawing.Size(94, 29);
            this.Pomoc.TabIndex = 4;
            this.Pomoc.Text = "Pomoc";
            this.Pomoc.UseVisualStyleBackColor = true;
            this.Pomoc.Click += new System.EventHandler(this.Pomoc_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.BurlyWood;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Pomoc);
            this.Controls.Add(this.AcceptButton);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.HelpButton = true;
            this.helpProvider1.SetShowHelp(this, true);
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button CancelButton;
        private System.Windows.Forms.Button AcceptButton;
        private System.Windows.Forms.TextBox Adres;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox Name;
        private System.Windows.Forms.CheckBox U;
        private System.Windows.Forms.CheckBox D;
        private System.Windows.Forms.ComboBox EducationComboBox;
        private System.Windows.Forms.Label label3;
        private HelpProvider helpProvider1;
        private Button Pomoc;
    }
}

