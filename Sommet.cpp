#include "Sommet.h"

///constructeur
Sommet::Sommet(int num, std::string nom, int altitude):m_numeroSommet(num),m_nomSommet(nom),m_altitude(altitude)
{
}

///destructeur
Sommet::~Sommet()
{
}

///getters
int Sommet::getNumeroSommet()const
{
    return m_numeroSommet;
}

int Sommet::getAltitude()const
{
    return m_altitude;
}

std::string Sommet::getNomSommet()const
{
    return m_nomSommet;
}
