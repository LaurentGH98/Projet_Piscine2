#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "Sommet.h"
#include <iostream>
#include <vector>

class Arc
{
private:
    std::pair<Sommet*,Sommet*> m_SommetAdjacent; // plus facile d'utilisation + associer les 2 extrémités d'un arc en un seul attribut pour un arc
    float m_duree; //temps du trajet correspondant à la pondération (pour Dijkstra)
    std::string m_nom;
    int m_numero;
    std::string m_type; // type d'une piste (R, V, TS, TK, etc.)
    int m_interet; // interet d'une piste (montée/descente)
    bool m_actif = true; // utilisation lors du 4.5 pour les chemins par lesquels on passe (true) ou non (false)

public:
    ///constructeur et destructeur
    Arc(int num, std::string nom, std::string type, Sommet* ext1,Sommet* ext2, float duree, int interet);
    ~Arc();

    ///getters
    float getDuree()const;
    std::string getNom()const;
    int getNumero()const;
    std::string getType()const;
    std::pair<Sommet*,Sommet*> getSommetAdj()const; // utilisation d'une seule variable pour stocker les extrémités d'un arc
    int getInteret()const;
    bool get_actif();

    ///setter
    void setInteret(int interet);
    void set_actif(bool x);

    ///methode affiche les attributs d'un arc
    void afficher()const;

};

#endif // ARC_H_INCLUDED

