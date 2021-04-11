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
    int m_nbrArc; // nbr de trajet dans le graphe
    int m_nbrSommet; // nbr de sommets dans le graphe
    std::vector <Sommet*>m_sommet; //c'est le vecteur qui possede tous les sommets du graphe
    std::vector <Arc*>m_arc; //c'est le vecteur qui possede toutes les arcs du graphe

public:
    /// constructeur et destructeur ///
    Graphe (std::string nomFichier);
    ~Graphe();


    /// menu et affichage ///
    void Menu();
    void AffichageSommet();
    void AffichageArc();


    /// 4.3 ///
    void infoArc(); // m�thode permettant � l'utilisateur de savoir d'o� il part et o� il arrive (en choisissant un trajet)
    void infoSommet(); // m�thode qui renseigne sur le sommet, � savoir les arcs (trajets) entrant et sortant


    ///4.4 ///
    void dijkstra(); // r�utilisation de Dijkstra pour le 4.5


    /// 4.5 ///
    void chemin_interessant(); // m�thode chemin le plus int�ressant

};


#endif // GRAPHE_H_INCLUDED
