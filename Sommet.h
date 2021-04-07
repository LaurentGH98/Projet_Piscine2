#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>
#include <vector>

//Sommet = point de la station

class Sommet
{
private:
    int m_numero;
    std::string m_nom;
    int m_altitude;
    bool m_marque; //pour Dijkstra
    std::vector <int > m_connexe; // connexit� entre les sommets (Kruskal)

public:
    ///constructeur et destructeur
    Sommet(int num, std::string nom, int altitude); //surcharge pour ces 3 attributs mais initialisation du bool m_marque � 0
                                                    //en effet pour Dijkstra, les sommets sont d'abord non marqu�
    ~Sommet();

    ///getters
    int getNumero() const;
    int getAltitude() const;
    std::string getNom() const;
    bool getMarque() const;

    ///setters
    void setMarque (bool marque);

    ///m�thodes
    void afficherSommet()const; //on affiche le num�ro du sommet et/ou son nom; pour Dijkstra

    /// Kruskal
    bool verif_connexe(Sommet * S2);
    std::vector<int>getConnexe();
    void addConnexe(int A);

};

#endif // SOMMET_H_INCLUDED
