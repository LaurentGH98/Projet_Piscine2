#include <iostream>
#include "Sommet.h"

///constructeur
Sommet::Sommet(int num, std::string nom, int altitude):m_numero(num),m_nom(nom),m_altitude(altitude)
{
    m_marque=0;
}

///destructeur
Sommet::~Sommet()
{
}

///getters
int Sommet::getNumero()const
{
    return m_numero;
}

int Sommet::getAltitude()const
{
    return m_altitude;
}

std::string Sommet::getNom()const
{
    return m_nom;
}

bool Sommet::getMarque()const
{
    return m_marque;
}


///setter(s)
void Sommet::setMarque(bool marque)
{
    m_marque=marque;
}


///méthode(s)
void Sommet::afficherSommet() const
{
    std::cout<<" "<< m_numero << " :  " << m_nom;
}
