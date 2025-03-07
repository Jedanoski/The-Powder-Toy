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

            Random random = new Random();

            // Initialize elements here
            for (int i = 0; i < 100; i++)
            {
                Particle particle = new Particle
                {
                    Type = 0, // Water
                    X = (float)(random.NextDouble() * width),
                    Y = (float)(random.NextDouble() * height),
                    VX = 0,
                    VY = 0,
                    Temperature = 20
                };
                simulation.Particles.Add(particle);
            }

            // Run simulation loop here
            for (int i = 0; i < 100; i++)
            {
                simulation.Step();
                Console.WriteLine($"Step {i + 1}");
            }

            Console.WriteLine("Simulation finished.");
        }
    }
}