#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "Sommet.h"
#include <iostream>

class Arc
{
private:
    std::pair<Sommet*,Sommet*> m_SommetAdjacent; // plus facile d'utilisation + associer les 2 extr�mit�s d'un arc en un seul attribut pour un arc
    int m_duree; //temps du trajet en secondes correspondant � la pond�ration (pour Dijkstra)
    std::string m_nom;
    int m_numero;
    std::string m_type;
    float m_denivele; //m�tres de denivel� pour un trajet

public:
    ///constructeur et destructeur
    Arc(int num, std::string nom, std::string type, Sommet* ext1,Sommet* ext2);
    ~Arc();

    ///getters
    int getDuree()const;
    std::string getNom()const;
    int getNumero()const;
    std::string getType()const;
    std::pair<Sommet*,Sommet*> getSommetAdj()const;

    float getDenivele() const;

    ///methode affiche les attributs d'un arc
    void afficher()const;

};

#endif // ARC_H_INCLUDED

