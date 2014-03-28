using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    public class MissioneLiveness
    {
        public MissioneLiveness(int trn)
        {
            Trn = trn;
        }

        public int Trn { get; set; }
        public int[] Cdbs { get; set; }
        public List<int[]> AzioniCdb { get; set; }
        internal int CurrentStep { get; private set; }

        internal void MoveNext()
        {
            CurrentStep++;
        }

        internal bool Terminata
        {
            get
            {
                return CurrentStep == Cdbs.Length - 1;
            }
        }

        internal MissioneLiveness Clone()
        {
            MissioneLiveness clone = new MissioneLiveness(Trn);
            clone.Cdbs = Cdbs;
            clone.AzioniCdb = AzioniCdb;
            clone.CurrentStep = CurrentStep;

            return clone;
        }
    }
}
