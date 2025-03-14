using System.Collections.Generic;
using System.Drawing;

namespace PowderToyCSharp
{
    public class Simulation
    {
        public int Width { get; set; }
        public int Height { get; set; }
        public List<Particle> Particles { get; set; }
        public Element[] Elements { get; set; }

        public Simulation(int width, int height)
        {
            Width = width;
            Height = height;
            Particles = new List<Particle>();
            Elements = new Element[3]; // Initialize with 3 elements

            // Define elements
            Elements[0] = new Element { Name = "Water", Color = Color.Blue, Density = 1.0f, Flammability = 0.0f, State = 1 };
            Elements[1] = new Element { Name = "Fire", Color = Color.Red, Density = 0.5f, Flammability = 1.0f, State = 2 };
            Elements[2] = new Element { Name = "Stone", Color = Color.Gray, Density = 2.0f, Flammability = 0.0f, State = 0 };
        }

        private System.Random random = new System.Random();

        public void Step()
        {
            // Move each particle randomly
            foreach (var particle in Particles)
            {
                particle.X += (float)(random.NextDouble() - 0.5);
                particle.Y += (float)(random.NextDouble() - 0.5);

                // Keep particles within bounds
                particle.X = System.Math.Max(0, System.Math.Min(Width, particle.X));
                particle.Y = System.Math.Max(0, System.Math.Min(Height, particle.Y));
            }
        }

        public Bitmap Render()
        {
            // Implement rendering logic here
            return new Bitmap(Width, Height);
        }
    }
}