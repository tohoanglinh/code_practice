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
using System.Diagnostics;

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
            if (Constants.DEBUG)
            {
                greetings_welcome();
            }
        }

        static class Constants
        {
            public const bool DEBUG = true;
            public const int MAX = 100;
            public const int MIN = 1;
        }

        private void greetings_welcome()
        {
            Console.WriteLine("-------------------");
            Console.WriteLine("*****Greetings*****");
            Console.WriteLine("-------------------");
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

        System.Data.SqlClient.SqlConnection conn;

        private void submitButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                conn = new System.Data.SqlClient.SqlConnection();
                conn.ConnectionString = @"Data Source = (LocalDB)\MSSQLLocalDB; AttachDbFilename = D:\gitworks\code_practice\csharp\HelloWPF\HelloWPF\SampleDatabase.mdf; Integrated Security = True";
                conn.Open();
                MessageBox.Show("connection opened successfully");
                conn.Close();
                //int a;
                //a = 1;
                //bool test;
                //test = true;
                if (conn.State == System.Data.ConnectionState.Closed)
                {
                    //Console.WriteLine("test = {0}, a = {1}", test, a);
                    MessageBox.Show(nameTextBox.Text);
                    MessageBox.Show("connection closed successfully");
                }
                else if (conn.State == System.Data.ConnectionState.Executing || conn.State == System.Data.ConnectionState.Fetching)
                {
                    MessageBox.Show("this connection is too busy to close. pls try again later");
                }
                else if (conn.State == System.Data.ConnectionState.Broken)
                {
                    MessageBox.Show("this connection is broken");
                }
            } catch (Exception)
            {
                MessageBox.Show("failed to access database or not exist!!!");
            }
        }

        private void buttonSum_Click(object sender, RoutedEventArgs e)
        {
            textBoxSum.Text = (Convert.ToInt16(textBoxNum1.Text) + Convert.ToInt16(textBoxNum2.Text)).ToString();
        }
    }
}
