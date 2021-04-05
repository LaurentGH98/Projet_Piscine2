#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <string>
#include <iostream>
#include "Sommet.h"
#include "Arc.h"

class Graphe
{
private:
    int m_nbrArc;//nbr de trajet dans le graphe
    int m_nbrSommet;// nbr de sommets dans le graphe
    std::vector <Sommet*>m_sommet;//c est le vecteur qui possede tous les sommets du graphe
    std::vector <Arc*>m_arc;//c est le vecteur qui possede toutes les arcs du graphe
public:
    ///constructeur et destructeur
    Graphe (std::string nomFichier);
    ~Graphe();


    ///m�thode permettant � l'utilisateur de savoir d'o� il part et o� il arrive (en choisissant un trajet)
    void infoArc();

    ///m�thode qui renseigne sur le sommet, � savoir les arcs (trajets) entrant et sortant
    void infoSommet();

    ///m�thode algorithme Dijkstra
    void Dijkstra(); //Peut se d�composer en plusieurs m�thodes, on verra plus tard

};


#endif // GRAPHE_H_INCLUDED
