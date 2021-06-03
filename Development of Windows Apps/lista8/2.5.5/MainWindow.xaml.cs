using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace _2._5._5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private void updateDBView()
        {
            StudenciView.Items.Clear();
            using (StudenciDataContext dc = new StudenciDataContext(@"server =.\sqlexpress;database=Studenci;integrated security=true"))
            {
                foreach (Student s in dc.Students)
                {
                    string str = s.ID + " " + s.Imie + " " + s.Nazwisko + " " + s.DataUr.ToString() + " ";
                    StudenciView.Items.Add(str);
                }
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            updateDBView();
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            if (ImieBox.Text == "" || NazwBox.Text == "" || UrBox.SelectedDate == null)
                return;

            Student toAdd = new Student { Imie = ImieBox.Text, Nazwisko = NazwBox.Text, DataUr = (DateTime)UrBox.SelectedDate };
            using (StudenciDataContext dc = new StudenciDataContext(@"server =.\sqlexpress;database=Studenci;integrated security=true"))
            {
                toAdd.ID = dc.Students.Max(x => x.ID) + 1;
                toAdd.Miejscowosc = dc.Miejscowoscs.Where(x => x.Nazwa == "WRO").First();
                dc.Students.InsertOnSubmit(toAdd);
                dc.SubmitChanges();
            }
            ImieBox.Text = "";
            NazwBox.Text = "";
            UrBox.SelectedDate = null;
            updateDBView();
        }

        private void Usun_Click(object sender, RoutedEventArgs e)
        {
            if(StudenciView.SelectedItem == null)
                return;

            using (StudenciDataContext dc = new StudenciDataContext(@"server =.\sqlexpress;database=Studenci;integrated security=true"))
            {
                string findID = StudenciView.SelectedItem.ToString().Split()[0];
                Student toDel = null;
                foreach (Student s in dc.Students)
                {
                    if (s.ID.ToString() == findID)
                        toDel = s;
                }
                dc.Students.DeleteOnSubmit(toDel);
                dc.SubmitChanges();
                updateDBView();
            }
        }

        private void Uaktualnij_Click(object sender, RoutedEventArgs e)
        {
            if (StudenciView.SelectedItem == null)
                return;

            using (StudenciDataContext dc = new StudenciDataContext(@"server =.\sqlexpress;database=Studenci;integrated security=true"))
            {
                string findID = StudenciView.SelectedItem.ToString().Split()[0];
                Student toUpdate = null;
                foreach (Student s in dc.Students)
                {
                    if (s.ID.ToString() == findID)
                        toUpdate = s;
                }

                toUpdate.DataUr = UrBox.SelectedDate == null ? toUpdate.DataUr : (DateTime)UrBox.SelectedDate;
                toUpdate.Imie = ImieBox.Text == "" ? toUpdate.Imie : ImieBox.Text;
                toUpdate.Nazwisko = NazwBox.Text == "" ? toUpdate.Nazwisko : NazwBox.Text;
                dc.SubmitChanges();
                updateDBView();
            }
        }
    }
}
