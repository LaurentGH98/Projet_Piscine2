#include "Graphe.h"
#include <fstream>

///constructeur
Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> m_nbrSommet;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int numSom, altitude;
    std::string nomSom;
    for (int i=0; i<m_nbrSommet; ++i)
    {
        ifs>>numSom>>nomSom>>altitude;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture des sommets");
        m_sommet.push_back(new Sommet(numSom,nomSom,altitude));
    }


    /**AFFICHAGE DES SOMMETS**/
    std::cout<<"Nbr Sommets = "<< m_nbrSommet <<std::endl;
    std::cout<<"\nSOMMETS :"<<std::endl;
    for (auto s : m_sommet)
    {
        std::cout << s->getNumero() << " " << s->getNom() << " " << s->getAltitude() << std::endl;
    }


    ifs >> m_nbrArc;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int numArc, ext1,ext2;
    std::string nomArc, typeArc;
    float tpsTrajet;
    for (int i=0; i<m_nbrArc; ++i)
    {
        ifs>>numArc>>nomArc>>typeArc>>ext1>>ext2>>tpsTrajet;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture des arcs");
        m_arc.push_back(new Arc(numArc,nomArc,typeArc,m_sommet[ext1-1],m_sommet[ext2-1],tpsTrajet));
    }

    /**AFFICHAGE DES ARCS**/
    std::cout<<"\nNbr arcs = "<< m_nbrArc <<std::endl;
    std::cout<<"\nARCS :"<<std::endl;
    for (auto a : m_arc)
    {
        std::cout << a->getNumero() << " " << a->getNom() << " " << a->getType()<<" " ;
        a->afficher();
    }

}

///destructeur
Graphe::~Graphe()
{
}

///méthode permettant à l'utilisateur de savoir d'où il part et où il arrive
void Graphe::infoArc()
{
    int Num_Arc = 0; // variable contenant le numéro de l'arc saisie
    int Num_Arc2 = 0; // variable tempon pour blindage
    bool Num_Trouve = false;

    std::cout << "\n\nVeuillez saisir le numero d'un arc : " << std::endl;
    std::cin >> Num_Arc;


    while(Num_Trouve == false) // tant que l'arete n'a pas été trouvé
    {
        for(auto a : m_arc) //a pour arc; on parcourt le vector d'arc
        {
            if(Num_Arc == a->getNumero()) // si le numéro existe dans le vector
            {
                std::cout << "\nVous avez choisi le trajet suivant :" << std::endl;
                std::cout << "Numero: " << a->getNumero() << "\nNom: " << a->getNom() << "\nType: " << a->getType()<< std::endl;
                std::cout << "Point de depart: " << a->getSommetAdj().first->getNom() << " (" << a->getSommetAdj().first->getNumero()<< ")" << std::endl;
                std::cout << "Point d'arrivee: " << a->getSommetAdj().second->getNom() << " (" << a->getSommetAdj().second->getNumero() << ")" << std::endl;
                std::cout << "Duree entre ces deux points: " << a->getDuree()  << " minute(s)" <<std::endl;

                Num_Trouve = true; // alors on a trouvé l'arete
                break;
            }

            else if( (a->getNumero()>=95) && (Num_Arc != a->getNumero()) ) // sinon
            {
                std::cout << "\nCe trajet n'existe pas.\nVeuillez saisir a nouveau: ";
                std::cin >> Num_Arc2;
                Num_Arc = Num_Arc2;
                Num_Trouve = false; // on n'a toujours pas trouvé l'arete
            }
        }
    }
}

///Pour connaître les arcs/trajets entrants et sortants à un sommet choisi
void Graphe::infoSommet()
{

    int numSomChoisi;
    bool boucle(false);

    std::cout<<"\nSur quel point de station souhaitez vous vous renseigner ?(Entrez un numero) ";

    while (boucle==false)   //blindage de la saisie des sommets pour les entiers
    {
        std::cout<<std::endl;
        std::cin>> numSomChoisi;

        if( numSomChoisi>=1 && numSomChoisi<=37)
            boucle=true;
        else
        {
            std::cout<<"Ce point de station n'existe pas, reessayez : ";
        }

    }



    std::cout<<std::endl;
    std::cout<<"Voici toutes les pistes ou remontees sortant du point de station "<<numSomChoisi<<" :"<<std::endl;
    std::cout<<std::endl;

    /*Premiere boucle pour trouver les sommets sortants*/
    for(auto elem : m_arc) //on parcourt la liste des arcs du graphe
    {
        if(elem->getSommetAdj().first->getNumero() == numSomChoisi) //si le numéro du sommet choisi correspond à la première extrémité
                                                                    //alors le trajet est forcément sortant
        {
            std::cout<<"Ce trajet se dirigeant vers : "<<elem->getSommetAdj().second->getNom()<<" s'appelle : "<<elem->getNom();

            /*Conditions pour donné le nom du type de trajet */
            if((elem->getType()) == "V")
                std::cout<<" et c'est une piste verte.";

            if((elem->getType()) == "B")
                std::cout<<" et c'est une piste bleue.";

            if((elem->getType()) == "R")
                std::cout<<" et c'est une piste rouge.";

            if((elem->getType()) == "N")
                std::cout<<" et c'est une piste noire.";

            if((elem->getType()) == "KL")
                std::cout<<" et c'est une piste de kilometre lance.";

            if((elem->getType()) == "SURF")
                std::cout<<" et c'est un snowpark.";

            if((elem->getType()) == "TPH")
                std::cout<<" et c'est un telepherique.";

            if((elem->getType()) == "TC")
                std::cout<<" et c'est des telecabines.";

            if((elem->getType()) == "TSD")
                std::cout<<" et c'est un telesiege debrayable.";

            if((elem->getType()) == "TS")
                std::cout<<" et c'est un telesiege.";

            if((elem->getType()) == "TK")
                std::cout<<" et c'est un teleski.";

            if((elem->getType()) == "BUS")
                std::cout<<" et c'est une navette.";

            std::cout<<std::endl;

        }
    }

    std::cout<<std::endl;
    std::cout<<"Voici toutes les pistes ou remontes permattant d'aller au point de station "<<numSomChoisi<<" :"<<std::endl;
    std::cout<<std::endl;

    /*Deuxieme boucle pour trouver les somments entrant*/
    for(auto elem : m_arc) //même démarche
    {
        if(elem->getSommetAdj().second->getNumero() == numSomChoisi)
        {
            std::cout<<"Ce trajet arrive de : "<<elem->getSommetAdj().first->getNom()<<" s'appelle : "<<elem->getNom();

            /*Conditions pour donné le nom du type de trajet */
            if((elem->getType()) == "V")
                std::cout<<" et c'est une piste verte.";

            if((elem->getType()) == "B")
                std::cout<<" et c'est une piste bleue.";

            if((elem->getType()) == "R")
                std::cout<<" et c'est une piste rouge.";

            if((elem->getType()) == "N")
                std::cout<<" et c'est une piste noire.";

            if((elem->getType()) == "KL")
                std::cout<<" et c'est une piste de kilometre lance.";

            if((elem->getType()) == "SURF")
                std::cout<<" et c'est un snowpark.";

            if((elem->getType()) == "TPH")
                std::cout<<" et c'est un telepherique.";

            if((elem->getType()) == "TC")
                std::cout<<" et c'est des telecabines.";

            if((elem->getType()) == "TSD")
                std::cout<<" et c'est un telesiege debrayable.";

            if((elem->getType()) == "TS")
                std::cout<<" et c'est un telesiege.";

            if((elem->getType()) == "TK")
                std::cout<<" et c'est un teleski.";

            if((elem->getType()) == "BUS")
                std::cout<<" et c'est une navette.";

            std::cout<<std::endl;

        }
    }
}
