using System.Drawing;

namespace PowderToyCSharp
{
    public class Element
    {
        public string Name { get; set; } = "";
        public Color Color { get; set; }
        public float Density { get; set; }
        public float Flammability { get; set; }
        public int State { get; set; } // 0: Solid, 1: Liquid, 2: Gas
    }
}