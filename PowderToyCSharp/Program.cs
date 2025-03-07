using System;

namespace PowderToyCSharp
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Powder Toy C#");

            int width = 640;
            int height = 480;
            Simulation simulation = new Simulation(width, height);

            // Initialize elements here

            // Run simulation loop here

            Console.WriteLine("Simulation finished.");
        }
    }
}