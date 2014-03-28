using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal interface AreaCritica : ICloneable
    {
        bool entrataPermessa(int idTreno, int cdb, int tipoEntrata);
        void entrata(int idTreno, int cdb, int tipoEntrata);
    }
}
