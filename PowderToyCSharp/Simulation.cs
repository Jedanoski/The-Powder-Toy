using System.Collections.Generic;
using System.Drawing;

namespace PowderToyCSharp
{
    public class Simulation
    {
        public int Width { get; set; }
        public int Height { get; set; }
        public List&lt;Particle&gt; Particles { get; set; }
        public Element[] Elements { get; set; }

        public Simulation(int width, int height)
        {
            Width = width;
            Height = height;
            Particles = new List&lt;Particle&gt;();
            Elements = new Element[0]; // Initialize with an empty array, populate later
        }

        public void Step()
        {
            // Implement simulation logic here
        }

        public Bitmap Render()
        {
            // Implement rendering logic here
            return new Bitmap(Width, Height);
        }
    }
}