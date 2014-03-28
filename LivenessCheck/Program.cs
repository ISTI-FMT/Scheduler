using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LivenessCheck
{
    internal class Program
    {




        static void Main(string[] args)
        {
            StatoAree statoAree = new StatoAree();

            AreaCriticaLineare lineare;
            AreaCriticaCircolare circolare;

            lineare = new AreaCriticaLineare(new[] { 1, 3 });
            statoAree.Aree.Add(lineare);
            lineare = new AreaCriticaLineare(new[] { 2, 3 });
            statoAree.Aree.Add(lineare);
            circolare = new AreaCriticaCircolare(new[] { 6, 7, 9, 8 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 3, 4, 5, 6 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 1, 3, 4, 5, 6 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 2, 3, 4, 5, 6 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 13, 15, 20, 25, 22, 17, 18, 11 }, 7);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 13, 15, 20, 26, 22, 17, 18, 11 }, 7);
            statoAree.Aree.Add(circolare);
            lineare = new AreaCriticaLineare(new[] { 31, 30 });
            statoAree.Aree.Add(lineare);
            lineare = new AreaCriticaLineare(new[] { 32, 30 });
            statoAree.Aree.Add(lineare);
            circolare = new AreaCriticaCircolare(new[] { 30, 28, 27, 29 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 31, 30, 28, 27, 29 }, 3);
            statoAree.Aree.Add(circolare);
            circolare = new AreaCriticaCircolare(new[] { 32, 30, 28, 27, 29 }, 3);
            statoAree.Aree.Add(circolare);


























            StatoTreni statoTreni = new StatoTreni();
            MissioneLiveness missione;
            List<int[]> azioni;


            missione = new MissioneLiveness(0);
            missione.Cdbs = (new[] { 1, 3, 4, 6, 7, 9, 10, 13, 15, 20, 23 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { -3, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;

            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(1);
            missione.Cdbs = (new[] { 2, 3, 4, 6, 7, 9, 10, 13, 15, 20, 24 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, -3, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(7);
            missione.Cdbs = (new[] { 26, 22, 17, 18, 12, 27, 29, 30, 32 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, -1, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(2);
            missione.Cdbs = (new[] { 31, 30, 28, 27, 11, 13, 16, 20, 25 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 1, 0, 1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(3);
            missione.Cdbs = (new[] { 32, 30, 28, 27, 11, 13, 16, 20, 26 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 1, 1, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(4);
            missione.Cdbs = (new[] { 23, 22, 17, 18, 11, 9, 8, 6, 5, 3, 1 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, -1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 2, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(5);
            missione.Cdbs = (new[] { 24, 22, 17, 18, 11, 9, 8, 6, 5, 3, 2 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, -1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 2, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);

            missione = new MissioneLiveness(6);
            missione.Cdbs = (new[] { 25, 22, 17, 18, 12, 27, 29, 30, 31 });
            azioni = new List<int[]>();
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, -1, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            azioni.Add(new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
            missione.AzioniCdb = azioni;
            statoTreni.Missioni.Add(missione);







            //Missione missione = new Missione(0);
            //missione.Cdbs.AddRange(new[] { 0, 1, 2,3,5 });
            //statoIniziale.Missioni.Add(missione);

            //missione = new Missione(1);
            //missione.Cdbs.AddRange(new[] {6,1,2,3,7 });
            //statoIniziale.Missioni.Add(missione);

            //missione = new Missione(2);
            //missione.Cdbs.AddRange(new[] { 5,3,4,1,0 });
            //statoIniziale.Missioni.Add(missione);

            //missione = new Missione(3);
            //missione.Cdbs.AddRange(new[] { 7,3,4,1,6 });
            //statoIniziale.Missioni.Add(missione);


            DateTime start = DateTime.Now;
            Stack<KeyValuePair<int, int>> sequenza = LivenessCheck.CheckLiveness(statoTreni, statoAree);
            DateTime end = DateTime.Now;

            bool liveness = sequenza != null;

            TimeSpan elapsed = end.Subtract(start);

            Console.WriteLine();
            Console.WriteLine("Liveness: {0}", liveness);

            if (liveness)
            {
                Console.Write("Movements (Trn,Cdb): ");
                StringBuilder sb = new StringBuilder();
                while (sequenza.Count > 0)
                {
                    KeyValuePair<int, int> top = sequenza.Pop();
                    sb.Append(top.Key + "=>" + top.Value);
                    sb.Append(", ");
                }
                Console.WriteLine(sb.ToString().Trim(new[] { ',', ' ' }));
            }

            Console.WriteLine("Elapsed time: {0} seconds", elapsed.TotalSeconds);

        }
    }
}
