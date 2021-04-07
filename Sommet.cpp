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

///méthodes pour Kruskal///

//connexité
bool Sommet::verif_connexe(Sommet * S2)
{
    bool res = true;
    for(unsigned int i=0 ; i < m_connexe.size() ; i++ )
    {
        for(unsigned int p=0 ; p < S2->getConnexe().size(); p++)
        {
            if(m_connexe[i] == S2->getConnexe()[p] )
            res = false;
        }
    }
    return res;
}

//getter connexe
std::vector<int> Sommet::getConnexe()
{
    return m_connexe;
}

//méthode ajt connexe
void Sommet::addConnexe(int A)
{
    m_connexe.push_back(A);
}
