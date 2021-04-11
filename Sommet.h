#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>
#include <vector>
#include <set>

//Sommet = point de la station

class Sommet
{
private:
    int m_numero;
    std::string m_nom;
    int m_altitude;
    bool m_marque; // lorsqu'un sommet est decouvert
    std::vector <int > m_connexe; // connexité entre les sommets
    std::set<Sommet*> m_successeurs; //chaque sommet possède des sommets successeurs, le set évite les doublons
    int m_couleur;//pour BFS : 0 pour blanc 1 pour gris 2 pour noir

public:
    /// constructeur et destructeur
    Sommet(int num, std::string nom, int altitude); //surcharge pour ces 3 attributs mais initialisation du bool m_marque à 0
                                                    //en effet pour Dijkstra, les sommets sont d'abord non marqué
    ~Sommet();

    /// getters
    int getNumero() const;
    int getAltitude() const;
    std::string getNom() const;
    int getCouleur() const;
    bool getMarque() const;
    std::set<Sommet*> getSuccesseur() const;

    /// setter
    void setMarque (bool marque);
    void setCouleur (int couleur);
    std::set<Sommet*>* setSuccesseur()
    {
        return &m_successeurs;
    }


    /// méthodes
    void afficherSommet()const; //on affiche le numéro du sommet et/ou son nom; pour Dijkstra
    void ajouterSuccesseur(Sommet* voisin); //ajoute un sommet adjacent pour BFS

    /// connexité
    //bool verif_connexe(Sommet * S2);
    std::vector<int>getConnexe();
    void addConnexe(int A);

};

#endif // SOMMET_H_INCLUDED
