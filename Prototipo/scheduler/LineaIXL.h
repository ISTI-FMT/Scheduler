#pragma once

const int cdbStatoIgnoto = -1;
const int cdbOccupato = 0;
const int cdbImpegnato = 1;
const int cdbLibero = 2;
const int cdbFuoriControllo = 3;

const int deviatoioStatoIgnoto = -1;
const int deviatoioNonPresente = 0;
const int deviatoioNormale = 1;
const int deviatoioRovescio = 2;

ref class LineaIXL
{
	int id;
	int statoCDB;
	int statoDeviatoio;
public:
	LineaIXL(void);
	LineaIXL(int idCdb);
	LineaIXL(int idCdb, int statoCdb, int statoDeviatoio);
	void setCDBOccupato(){statoCDB = cdbOccupato;};
	void setCDBImpegnato(){statoCDB = cdbImpegnato;};
	void setCDBLibero(){statoCDB = cdbLibero;};
	void setCDBFuoriControllo(){statoCDB = cdbFuoriControllo;};
	void setDeviatoioNonPresente(){statoDeviatoio = deviatoioNonPresente;};
	void setDeviatoioNormale(){statoDeviatoio = deviatoioNormale;};
	void setDeviatoioRovescio(){statoDeviatoio = deviatoioRovescio;};
	int getStatoCdb(){return statoCDB;};
	void setStatoCdb(int stato){statoCDB = stato;};
	int getStatoDeviatoio(){return statoDeviatoio;};
	void setStatoDeviatoio(int stato){statoDeviatoio = stato;};
};