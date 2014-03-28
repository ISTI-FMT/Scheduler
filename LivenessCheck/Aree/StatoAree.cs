using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal class StatoAree
    {
        public List<AreaCritica> Aree { get; private set; }

        public StatoAree()
        {
            Aree = new List<AreaCritica>();
        }

        public bool EntrataPermessa(MissioneLiveness missione, int idx, int cdb)
        {
            bool entrataValida = true;

            int[] azioni = missione.AzioniCdb[idx];

            for (int i = 0; i < Aree.Count; i++)
            {
                int azione = azioni[i];

                if (azione != 0)
                {
                    AreaCritica area = Aree[i];
                    if (!area.entrataPermessa(missione.Trn, cdb, azione))
                    {
                        entrataValida = false;
                        break;
                    }
                }
            }

            return entrataValida;
        }

        public bool Entrata(MissioneLiveness missione, int idx, int cdb)
        {
            bool entrataValida = true;
            int[] azioni = missione.AzioniCdb[idx];

            for (int i = 0; i < Aree.Count; i++)
            {
                int azione = azioni[i];
                if (azione != 0)
                {
                    AreaCritica area = Aree[i];
                    area.entrata(missione.Trn, cdb, azione);
                }
            }
            return entrataValida;
        }

        public StatoAree Clone()
        {
            StatoAree areeClone = new StatoAree();
            foreach (AreaCritica area in Aree)
            {
                AreaCritica areaClone = (AreaCritica)area.Clone();
                areeClone.Aree.Add(areaClone);
            }
            return areeClone;
        }


    }
}
