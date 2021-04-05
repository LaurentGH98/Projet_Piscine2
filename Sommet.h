#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>

//Sommet = point de la station

class Sommet
{
private:
    int m_numero;
    std::string m_nom;
    int m_altitude;
    bool m_marque; //pour Dijkstra

public:
    ///constructeur et destructeur
    Sommet(int num, std::string nom, int altitude); //surcharge pour ces 3 attributs mais initialisation du bool m_marque à 0
                                                    //en effet pour Dijkstra, les sommets sont d'abord non marqué
    ~Sommet();

    ///getters
    int getNumero() const;
    int getAltitude() const;
    std::string getNom() const;
    bool getMarque() const;

    ///setters
    void setMarque (bool marque);

    ///méthodes
    void afficherSommet()const; //on affiche le numéro du sommet et/ou son nom; pour Dijkstra

};

#endif // SOMMET_H_INCLUDED
