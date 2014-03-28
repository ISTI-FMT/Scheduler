using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal class StatoTreni
    {
        public StatoTreni()
        {
            Missioni = new List<MissioneLiveness>();
        }
        public List<MissioneLiveness> Missioni { get; set; }

        public StatoTreni Clone()
        {
            StatoTreni clone = new StatoTreni();
            foreach (MissioneLiveness missione in Missioni)
            {
                clone.Missioni.Add(missione.Clone());
            }

            return clone;
        }

        public override bool Equals(object obj)
        {
            StatoTreni stato2 = (StatoTreni)obj;
            return GetHashCode() == stato2.GetHashCode();           
        }

        public override string ToString()
        {
            int[] steps = Missioni.Select(missione => missione.CurrentStep).ToArray();
            return string.Join(",", steps);
        }

        public override int GetHashCode()
        {
            return GetHashCode(Missioni);
        }

        static int GetHashCode(List<MissioneLiveness> values)
        {
            int result = 0;
            int shift = 0;
            for (int i = 0; i < values.Count; i++)
            {
                shift = (shift + 11) % 21;
                result ^= (values[i].CurrentStep + 1024) << shift;
            }
            return result;
        }
    }
}
