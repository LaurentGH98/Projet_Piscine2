#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "Sommet.h"
#include <iostream>

class Arc
{
private:
    std::pair<Sommet*,Sommet*> m_SommetAdjacent; // plus facile d'utilisation + associer les 2 extrémités d'un arc en un seul attribut pour un arc
    float m_dureeArc;
    std::string m_nomArc;
    int m_numeroArc;
    std::string m_typeArc;

public:
    ///constructeur et destructeur
    Arc(int num, std::string nom, std::string type, Sommet* ext1,Sommet* ext2, float duree);
    ~Arc();

    ///getters
    float getDureeArc()const;
    std::string getNomArc()const;
    int getNumeroArc()const;
    std::string getTypeArc()const;
    std::pair<Sommet*,Sommet*> getSommetAdj()const;

    void afficherArc()const;
};

#endif // ARC_H_INCLUDED
