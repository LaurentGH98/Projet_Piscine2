#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "Sommet.h"
#include <iostream>
#include <vector>

class Arc
{
private:
    std::pair<Sommet*,Sommet*> m_SommetAdjacent; // plus facile d'utilisation + associer les 2 extr?mit?s d'un arc en un seul attribut pour un arc
    int m_duree; //temps du trajet en secondes correspondant ? la pond?ration (pour Dijkstra)
    std::string m_nom;
    int m_numero;
    std::string m_type; // type d'une piste (R, V, TS, TK, etc.)
    int m_interet; // interet d'une piste (mont?e/descente)
    bool m_actif = true; // utilisation lors du 4.5 pour les chemins par lesquels on passe (true) ou non (false)
    float m_denivele; //m?tres de denivel? pour un trajet
    int m_orientation;//0 si arc sortant du sommet et 1 si arc entrant du sommet

public:
    ///constructeur et destructeur
    Arc(int num, std::string nom, std::string type, Sommet* ext1,Sommet* ext2, int interet);
    ~Arc();

    ///getters
    int getDuree()const;
    std::string getNom()const;
    int getNumero()const;
    std::string getType()const;
    std::pair<Sommet*,Sommet*> getSommetAdj()const; // utilisation d'une seule variable pour stocker les extr?mit?s d'un arc
    int getInteret()const;
    bool get_actif();
    int getOrientation() const;
    float getDenivele() const;


    ///setters
    void setInteret(int interet);
    void set_actif(bool x);
    void setOrientation(int orientation);


    ///methode affiche les attributs d'un arc
    void afficher()const;

};

#endif // ARC_H_INCLUDED

