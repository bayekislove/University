using System;
using System.Windows;
using System.Windows.Controls;

namespace _2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            PassSeen.Content = PassHidden.Password;
        }

        private void Sliderek_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            A.IsChecked = Sliderek.Value == 0;
            B.IsChecked = Sliderek.Value == 2.5;
            C.IsChecked = Sliderek.Value == 5.0;
            D.IsChecked = Sliderek.Value == 7.5;
        }

        private void A_Checked(object sender, RoutedEventArgs e)
        {
            Sliderek.Value = 0;
            A.IsChecked = true;
        }

        private void B_Checked(object sender, RoutedEventArgs e)
        {
            Sliderek.Value = 2.5;
            B.IsChecked = true;
        }

        private void C_Checked(object sender, RoutedEventArgs e)
        {
            Sliderek.Value = 5.0;
            C.IsChecked = true;
        }

        private void D_Checked(object sender, RoutedEventArgs e)
        {
            Sliderek.Value =7.5;
            D.IsChecked = true;
        }
    }
}
