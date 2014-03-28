using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal class AreaCriticaLineare : AreaCritica
    {
        private int treniSinistra;
        private int treniDestra;

        public AreaCriticaLineare(int[] lcdb)
        {
            
        }

        public AreaCriticaLineare()
        {
            
        }

        public bool entrataPermessa(int idTreno, int cdb, int tipoEntrata)
        {
            bool res = true;
            if (tipoEntrata > 0)
            {
                if (tipoEntrata == 3) //Entrata da sinistra (se il cdb è il primo della lista e non ero già entrato da destra)
                {
                    if (treniDestra > 0)
                    {
                        res = false;
                    }
                }
                else if (tipoEntrata == 2) //Entrata da sinistra (se il cdb è l'ultimo della lista e non ero già entrato da destra)
                {
                    if (treniSinistra > 0)
                    {
                        res = false;
                    }
                }
            }
            return res;
        }

        public void entrata(int idTreno, int cdb, int tipoEntrata)
        {
            if (tipoEntrata > 0)
            {
                if (tipoEntrata == 3) //entrata da sinistra
                {
                    treniSinistra++;
                }
                else if (tipoEntrata == 2) //entrata da destra
                {
                    treniDestra++;
                }
            }
            else //sto entrando in un cdb che non è di questa area. Rimuovo il treno
            {
                if (tipoEntrata == -3)
                {
                    treniSinistra--;
                }
                else if (tipoEntrata == -2)
                {
                    treniDestra--;
                }
            }
        }

        public object Clone()
        {
            AreaCriticaLineare areaClone = new AreaCriticaLineare();
            areaClone.treniSinistra = treniSinistra;
            areaClone.treniDestra = treniDestra;
            return areaClone;
        }
    }
}
