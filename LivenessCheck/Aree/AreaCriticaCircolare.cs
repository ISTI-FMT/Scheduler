using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal class AreaCriticaCircolare : AreaCritica
    {
        private int treni = 0;
        private int limite;

        public AreaCriticaCircolare(int limite)
        {
            this.limite = limite;
        }

        public AreaCriticaCircolare(int[] cdbs, int limite)
        {
            this.limite = limite;
        }

        public bool entrataPermessa(int idTreno, int cdb, int tipoEntrata)
        {
            bool res = true;
            //l'ingresso è negato se:
            //- il cdb è uno di quelli dell'area
            //- il treno non è già dentro l'area
            //- l'area ha già il numero massimo di treni
            if (tipoEntrata == 1)
            {
                if (treni >= limite)
                {
                    res = false;
                }
            }
            return res;
        }

        public void entrata(int idTreno, int cdb, int tipoEntrata)
        {
            if (tipoEntrata == 1)
            {
                treni++;
            }
            else if (tipoEntrata == -1)
            {
                treni--;
            }
        }

        public object Clone()
        {
            AreaCriticaCircolare areaClone = new AreaCriticaCircolare(limite);
            areaClone.treni = treni;
            return areaClone;
        }

    }
}
