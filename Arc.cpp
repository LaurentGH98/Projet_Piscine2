#include "Arc.h"

///constructeur
Arc::Arc(int num, std::string nom, std::string type,Sommet* ext1, Sommet* ext2, float duree)
{
    m_numeroArc=num;
    m_nomArc=nom;
    m_typeArc=type;
    m_SommetAdjacent=std::make_pair(ext1,ext2);
    m_dureeArc=duree;

}

///destructeur
Arc::~Arc()
{
}

///getters
float Arc::getDureeArc()const
{
    return m_dureeArc;
}


std::string Arc::getNomArc()const
{
    return m_nomArc;
}

int Arc::getNumeroArc()const
{
    return m_numeroArc;
}

std::string Arc::getTypeArc()const
{
    return m_typeArc;
}

std::pair<Sommet*,Sommet*> Arc::getSommetAdj()const
{
    return m_SommetAdjacent;
}

void Arc::afficherArc()const
{
    std::cout<<m_SommetAdjacent.first->getNumeroSommet()<<"-"<<m_SommetAdjacent.second->getNumeroSommet()<<":  "<<m_dureeArc<<std::endl;
}
