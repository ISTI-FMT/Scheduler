using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    public static class LivenessCheck
    {
        /// <summary>
        /// Se esiste, Ritorna una sequenza di movimenti che porta tutte le missioni a destinazione
        /// Altrimenti, ritorna NULL
        /// </summary>
        /// <param name="limitiAree">lista dei limiti delle aree. Zero per aree lineari, maggiore di zero per aree circolari</param>
        /// <param name="missioniLiveness">Lista delle missioni dei treni</param>
        public static Stack<KeyValuePair<int, int>> CheckLiveness(int[] limitiAree, List<MissioneLiveness> missioniLiveness)
        {
            StatoAree statoAree = new StatoAree();
            AreaCritica area;
            foreach (int limiteArea in limitiAree)
            {
                if (limiteArea == 0)
                {
                    area = new AreaCriticaLineare();
                }
                else
                {
                    area = new AreaCriticaCircolare(limiteArea);
                }
                statoAree.Aree.Add(area);
            }

            StatoTreni statoTreni = new StatoTreni();
            foreach (MissioneLiveness missione in missioniLiveness)
            {
                statoTreni.Missioni.Add(missione);
            }

            return CheckLiveness(statoTreni, statoAree);
        }

        internal static bool CheckLiveness(StatoTreni statoTreni, StatoAree statoAree, Stack<KeyValuePair<int, int>> sequenza, HashSet<StatoTreni> visitati)
        {
            if (visitati.Contains(statoTreni))
            {
                return false;
            }

            bool res = false;
            bool cannotAdvance = true;
            for (int i = 0; i < statoTreni.Missioni.Count; i++)
            {
                MissioneLiveness missione = statoTreni.Missioni[i];
                if (missione.Terminata)
                {
                    KeyValuePair<int, int> movement = new KeyValuePair<int, int>(missione.Trn, missione.Cdbs[missione.CurrentStep]);
                    if (!sequenza.Contains(movement))
                    {
                        sequenza.Push(movement);
                    }
                }
                else
                {
                    int cdbCorrente = missione.Cdbs[missione.CurrentStep];
                    int cdbNext = missione.Cdbs[missione.CurrentStep + 1];

                    bool evolving = true;
                    for (int j = 0; j < statoTreni.Missioni.Count; j++)
                    {
                        if (j != i)
                        {
                            MissioneLiveness missione2 = statoTreni.Missioni[j];
                            int cdbCorrente2 = missione2.Cdbs[missione2.CurrentStep];
                            if (cdbNext == cdbCorrente2)
                            {
                                //il prossimo cdb è occupato, non posso avanzare
                                evolving = false;
                                break;
                            }
                        }
                    }

                    if (evolving)
                    {
                        //controllo vincoli aree critich
                        if (!statoAree.EntrataPermessa(missione, missione.CurrentStep + 1, cdbNext))
                        {
                            evolving = false;
                        }
                    }

                    if (evolving)
                    {
                        cannotAdvance = false;

                        StatoTreni stato2 = statoTreni.Clone();
                        stato2.Missioni[i].MoveNext();
                        StatoAree aree2 = statoAree.Clone();
                        aree2.Entrata(stato2.Missioni[i], stato2.Missioni[i].CurrentStep, cdbNext);

                        //se esiste un path che porta alla fine non vado oltre
                        if (CheckLiveness(stato2, aree2, sequenza, visitati))
                        {
                            sequenza.Push(new KeyValuePair<int, int>(missione.Trn, missione.Cdbs[missione.CurrentStep]));
                            res = true;
                            break;
                        }
                        else
                        {
                            sequenza.Clear();
                        }
                    }
                }
            }

            //Non posso più andare oltre (tutti i treni hanno evolving a false)
            //Controllo se il motivo è un deadlock o se tutte le missioni sono terminate
            if (cannotAdvance)
            {
                bool final = statoTreni.Missioni.All(missione => missione.Terminata);
                if (final)
                {
                    res = true;
                }
            }
            if (!res)
            {
                visitati.Add(statoTreni);
            }
            return res;
        }

        /// <summary>
        /// Ritorna una sequenza di coppie (Trn,Cdb), se esiste, che porta ad uno stato finale senza deadlock
        /// Se la sequenza non esiste ritorna NULL
        /// </summary>
        /// <param name="stato">lo stato dei treni</param>
        /// <param name="sequenza">sequenza dei movimenti effettuati dai treni (contiene i TRN dei treni mossi)</param>
        internal static Stack<KeyValuePair<int, int>> CheckLiveness(StatoTreni statoTreni, StatoAree statoAree)
        {
            Stack<KeyValuePair<int, int>> sequenza = new Stack<KeyValuePair<int, int>>();
            HashSet<StatoTreni> visitati = new HashSet<StatoTreni>();

            if (CheckLiveness(statoTreni, statoAree, sequenza, visitati))
            {
                return sequenza;
            }
            else
            {
                return null;
            }
        }


    }
}
