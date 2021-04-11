#include "Arc.h"

/// constructeur
Arc::Arc(int num, std::string nom, std::string type,Sommet* ext1, Sommet* ext2, float duree, int interet)
{
    m_numero=num;
    m_nom=nom;
    m_type=type;
    m_SommetAdjacent=std::make_pair(ext1,ext2);
    m_duree=duree;
    m_interet = interet;

}

/// destructeur
Arc::~Arc()
{
}

/// getters
float Arc::getDuree()const
{
    return m_duree;
}


std::string Arc::getNom()const
{
    return m_nom;
}

int Arc::getNumero()const
{
    return m_numero;
}

std::string Arc::getType()const
{
    return m_type;
}

std::pair<Sommet*,Sommet*> Arc::getSommetAdj()const
{
    return m_SommetAdjacent;
}



int Arc::getInteret()const
{
    return m_interet;
}

bool Arc::get_actif()
{
  return m_actif;
}

/// setters
void Arc::setInteret(int interet)
{
    m_interet = interet;
}

void Arc::set_actif(bool x)
{
   m_actif = x;
}

/// methode d'affichage
void Arc::afficher()const
{
    std::cout<<m_SommetAdjacent.first->getNumero()<<"->"<<m_SommetAdjacent.second->getNumero()<<":  "<<m_duree;
}
