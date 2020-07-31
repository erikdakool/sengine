using System;
using CoreEngine.Manager;
using Noesis;

namespace CoreEngine.XamlController
{
    public class MyGrid : Grid
    {
        public MyGrid()
        {
            Console.WriteLine("Init");
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this,"Resources/XAML/test.xaml");
        }
        
        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "Click" && handlerName == "OnButton1Click")
            {
                ((Button)source).Click += this.OnButton1Click;
                return true;
            }

            if (eventName == "Click" && handlerName == "OnButton2Click")
            {
                ((Button)source).Click += this.OnButton2Click;
                return true;
            }

            return false;
        }
        
        private void OnButton1Click(object sender, RoutedEventArgs args)
        {
            Button b = (Button)sender;
            b.Content = "Clicked";
            System.Console.WriteLine("Button1 was clicked");
        }

        private void OnButton2Click(object sender, RoutedEventArgs args)
        {
            System.Console.WriteLine("Button2 was clicked");
        }
    }
}