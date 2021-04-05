#include "Arc.h"

///constructeur
Arc::Arc(int num, std::string nom, std::string type,Sommet* ext1, Sommet* ext2, float duree)
{
    m_numero=num;
    m_nom=nom;
    m_type=type;
    m_SommetAdjacent=std::make_pair(ext1,ext2);
    m_duree=duree;

}

///destructeur
Arc::~Arc()
{
}

///getters
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

void Arc::afficher()const
{
    std::cout<<m_SommetAdjacent.first->getNumero()<<"-"<<m_SommetAdjacent.second->getNumero()<<":  "<<m_duree<<std::endl;
}
