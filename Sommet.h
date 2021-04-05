#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>

class Sommet
{
private:
    int m_numeroSommet;
    std::string m_nomSommet;
    int m_altitude;

public:
    ///constructeur et destructeur
    Sommet(int num, std::string nom, int altitude);
    ~Sommet();

    ///getters
    int getNumeroSommet() const;
    int getAltitude() const;
    std::string getNomSommet() const;

};

#endif // SOMMET_H_INCLUDED
