using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace HelloWPF
{
    /// <summary>
    /// Interaction logic for Greetings.xaml
    /// </summary>
    public partial class Greetings : Window
    {
        public Greetings()
        {
            InitializeComponent();
        }

        private void Display_Click(object sender, RoutedEventArgs e)
        {
            if (helloButton.IsChecked == true)
            {
                MessageBox.Show("Hello.");
            }
            else if (byeButton.IsChecked == true)
            {
                MessageBox.Show("Bye.");
            }
        }
    }
}
