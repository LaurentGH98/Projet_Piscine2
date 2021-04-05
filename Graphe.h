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


    ///méthode permettant à l'utilisateur de savoir d'où il part et où il arrive (en choisissant un trajet)
    void infoArc();

    ///méthode qui renseigne sur le sommet, à savoir les arcs (trajets) entrant et sortant
    void infoSommet();

    ///méthode algorithme Dijkstra
    void Dijkstra(); //Peut se décomposer en plusieurs méthodes, on verra plus tard

};


#endif // GRAPHE_H_INCLUDED
