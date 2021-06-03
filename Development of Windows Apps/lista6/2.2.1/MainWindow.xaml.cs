using System.Windows;
using System.Windows.Controls;


namespace _1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private CheckBox _Selected;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void AcceptButton_Click(object sender, RoutedEventArgs e)
        {
            if (Nazwa.Text == "" || Adres.Text == "" || Cykl.SelectedItem == null)
                return;
            if (ifDzienne.IsChecked == false && ifUzup.IsChecked == false)
                return;
            MessageBox.Show(Nazwa.Text + "\n" + Adres.Text + "\n" + Cykl.Text + "\n" + _Selected.Content, "Uczelnia");
        }

        private void DeclineButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void ifDzienne_Checked(object sender, RoutedEventArgs e)
        {
            _Selected = ifDzienne;
            ifUzup.IsChecked = false;
        }

        private void ifUzup_Checked(object sender, RoutedEventArgs e)
        {
            _Selected = ifUzup;
            ifDzienne.IsChecked = false;
        }
    }
}
