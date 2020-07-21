using System;
using CoreEngine.Manager;
using OpenTK;

namespace CoreEngine
{
    class Program
    {
        private static void Main()
        {
            using (var window = new App(1200, 720, "LearnOpenTK - Camera"))
            {
                window.VSync = VSyncMode.On;
                window.Run();
            }
        }
    }
}