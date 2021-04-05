#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "Sommet.h"
#include <iostream>

class Arc
{
private:
    std::pair<Sommet*,Sommet*> m_SommetAdjacent; // plus facile d'utilisation + associer les 2 extrémités d'un arc en un seul attribut pour un arc
    float m_duree; //temps du trajet correspondant à la pondération (pour Dijkstra)
    std::string m_nom;
    int m_numero;
    std::string m_type;

public:
    ///constructeur et destructeur
    Arc(int num, std::string nom, std::string type, Sommet* ext1,Sommet* ext2, float duree);
    ~Arc();

    ///getters
    float getDuree()const;
    std::string getNom()const;
    int getNumero()const;
    std::string getType()const;
    std::pair<Sommet*,Sommet*> getSommetAdj()const;

    void afficher()const; //affiche les attributs d'un arc
};

#endif // ARC_H_INCLUDED
