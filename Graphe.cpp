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
    /*std::cout<<"Nbr Sommets = "<< m_nbrSommet <<std::endl;
    std::cout<<"\nSOMMETS :"<<std::endl;
    for (auto s : m_sommet)
    {
        std::cout << s->getNumero() << " " << s->getNom() << " " << s->getAltitude() << std::endl;
    }*/


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
    /*std::cout<<"\nNbr arcs = "<< m_nbrArc <<std::endl;
    std::cout<<"\nARCS :"<<std::endl;
    for (auto a : m_arc)
    {
        std::cout << a->getNumero() << " " << a->getNom() << " " << a->getType()<<" " ;
        a->afficher();
    }*/

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


    while(Num_Trouve == false) // tant que l'arc n'a pas été trouvé
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

                Num_Trouve = true; // alors on a trouvé l'arc
                break;
            }

            else if( (a->getNumero()>=95) && (Num_Arc != a->getNumero()) ) // sinon
            {
                std::cout << "\nCe trajet n'existe pas.\nVeuillez saisir a nouveau: ";
                std::cin >> Num_Arc2;
                Num_Arc = Num_Arc2;
                Num_Trouve = false; // on n'a toujours pas trouvé l'arc
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

/// méthode qui permet d'obtenir le chemin le plus interessant (montées/descentes)
void Graphe::chemin_interessant()
{
    int niveau = 3;
    std::string choix_utilisateur = "Q"; // initialisation par defaut
    std::vector<std::string> choix_tot; // vector pour stocker tous les choix de l'utilisateur
    std::vector<Arc*>arcs_tries; // vector contenant tous les arcs sauf ceux que veux eviter l'utilisateur


    //int interet[12]; // 0-Rien // 1-Piste Verte // 2-Piste bleue // 3-Piste Rouge // n4-Piste Noire // 5-Piste de Kilometre Lance // 6-Snowpark
    // 7-Telepherique // 8-Telecabine // 9-Telesiege debrayable // 10-Telesiege // 11-Teleski // 12-Navette

    /*
    for(int i = 1; i <= 6; i++) // positif si descente
    {
        interet[i] = +10*i;
    }
    for(int i = 7; i<=12; i++) // negatif si remontée
    {
        interet[i] = -10*i;
    }*/

    if(niveau == 1) // debutant
    {
        std::cout << "Vous ne pouvez pas emprunter de pistes noires ni de pistes rouges.\n" <<std::endl;
        std::cout << "Z-FIN.\nV-Piste Verte\nB-Piste bleue\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter d'autre ? \n(Veuillez saisir 'Z' pour terminer votre saisi)\n" << std::endl;

        while(choix_utilisateur != "Z")
        {

            std::cin >> choix_utilisateur;
            //blindage saisie
            if((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
            {
                while((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
                {
                    char choix_utilisateur2;
                    std::cout << "Saisie invalide. Veuillez saisir a nouveau :" << std::endl;
                    std::cin >> choix_utilisateur2;
                    choix_utilisateur = choix_utilisateur2;
                }
            }
            //saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!\n" <<std::endl;
            }

            choix_tot.push_back(choix_utilisateur); // on stock tous les choix de l'utilisateur dans un vector
        }


        // parcours de tous les choix de l'utilisateur
        for(unsigned int k=0; k<choix_tot.size(); k++)
        {
            // parcours de tous les arcs
            for(unsigned int i=0; i<m_arc.size(); i++)
            {
                // si c le premier choix (k=0) et si on ne prend pas en compte les pistes Noires et les choix de l'utilisateur
                if( (k==0) && (choix_tot[k] != m_arc[i]->getType()) && (m_arc[i]->getType()!="N") && (m_arc[i]->getType()!="R"))
                {
                    // alors on rempli un vecteur avec toutes ces conditions
                    arcs_tries.push_back(m_arc[i]);
                }
                // si c + que le premier choix (k>0)
                else if(k>0)
                {
                    // parcours du vecteur déjà rempli auparavant pour k=0
                    for(unsigned int j=0; j<arcs_tries.size(); j++)
                    {
                        // si le choix de l'utilisateur est parmi le vecteur rempli auparavant
                        if(choix_tot[k] == arcs_tries[j]->getType())
                        {
                            // alors on supprime aussi ces conditions
                            arcs_tries.erase(arcs_tries.begin()+j);
                        }
                    }
                }
            }
        }

        //affichage
        for(auto tri : arcs_tries)
        {
            std::cout << "APRES : " << tri->getType() << std::endl;
        }
    }

    else if(niveau == 2) // intermediaire
    {
        std::cout << "Vous ne pouvez pas emprunter de pistes noires.\n" <<std::endl;
        std::cout << "Z-Rien\nV-Piste Verte\nB-Piste bleue\nR-Piste Rouge\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter d'autre ?\n(Veuillez saisir 0 pour terminer votre saisi)\n" <<std::endl;

        while(choix_utilisateur != "Z")
        {
            std::cin >> choix_utilisateur;
            //blindage saisie
            if((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "R") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
            {
                while((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "R") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
                {
                    char choix_utilisateur2;
                    std::cout << "Saisie invalide. Veuillez saisir a nouveau :" << std::endl;
                    std::cin >> choix_utilisateur2;
                    choix_utilisateur = choix_utilisateur2;
                }
            }
            //saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!" <<std::endl;
            }
            choix_tot.push_back(choix_utilisateur); // on stock tous les choix de l'utilisateur dans un vector
        }

        // parcours de tous les choix de l'utilisateur
        for(unsigned int k=0; k<choix_tot.size(); k++)
        {
            // parcours de tous les arcs
            for(unsigned int i=0; i<m_arc.size(); i++)
            {
                // si c le premier choix (k=0) et si on ne prend pas en compte les pistes Noires et Rouges et les choix de l'utilisateur
                if( (k==0) && (choix_tot[k] != m_arc[i]->getType()) && (m_arc[i]->getType()!="N"))
                {
                    // alors on rempli un vecteur avec toutes ces conditions
                    arcs_tries.push_back(m_arc[i]);
                }
                // si c + que le premier choix (k>0)
                else if(k>0)
                {
                    // parcours du vecteur déjà rempli auparavant pour k=0
                    for(unsigned int j=0; j<arcs_tries.size(); j++)
                    {
                        // si le choix de l'utilisateur est parmi le vecteur rempli auparavant
                        if(choix_tot[k] == arcs_tries[j]->getType())
                        {
                            // alors on supprime aussi ces conditions
                            arcs_tries.erase(arcs_tries.begin()+j);
                        }
                    }
                }
            }
        }

        //affichage
        for(auto tri : arcs_tries)
        {
            std::cout << "APRES : " << tri->getType() << std::endl;
        }
    }

    else if(niveau == 3) // professionnel
    {
        std::cout << "Z-Rien\nV-Piste Verte\nB-Piste bleue\nR-Piste Rouge\nN-Piste Noire\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter ? \n(Veuillez saisir 0 pour terminer votre saisi)\n" <<std::endl;

        while(choix_utilisateur != "Z")
        {
            std::cin >> choix_utilisateur;
            //blindage saisie
            if((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "R") && (choix_utilisateur!= "N") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
            {
                while((choix_utilisateur!= "V") && (choix_utilisateur!= "B") && (choix_utilisateur!= "R") && (choix_utilisateur!= "N") && (choix_utilisateur!= "KL") && (choix_utilisateur!= "SURF") && (choix_utilisateur!= "TPH") && (choix_utilisateur!= "TC") && (choix_utilisateur!= "TSD") && (choix_utilisateur!= "TS") && (choix_utilisateur!= "TK") && (choix_utilisateur!= "BUS") && choix_utilisateur!= "Z" )
                {
                    char choix_utilisateur2;
                    std::cout << "Saisie invalide. Veuillez saisir a nouveau :" << std::endl;
                    std::cin >> choix_utilisateur2;
                    choix_utilisateur = choix_utilisateur2;
                }
            }
            //saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!" <<std::endl;
            }
            choix_tot.push_back(choix_utilisateur); // on stock tous les choix de l'utilisateur dans un vector
        }

        // parcours de tous les choix de l'utilisateur
        for(unsigned int k=0; k<choix_tot.size(); k++)
        {
            // parcours de tous les arcs
            for(unsigned int i=0; i<m_arc.size(); i++)
            {
                // si c le premier choix (k=0) et si on ne prend pas en compte les choix de l'utilisateur
                if( (k==0) && (choix_tot[k] != m_arc[i]->getType()) )
                {
                    // alors on rempli un vecteur avec toutes ces conditions
                    arcs_tries.push_back(m_arc[i]);
                }
                // si c + que le premier choix (k>0)
                else if(k>0)
                {
                    // parcours du vecteur déjà rempli auparavant pour k=0
                    for(unsigned int j=0; j<arcs_tries.size(); j++)
                    {
                        // si le choix de l'utilisateur est parmi le vecteur rempli auparavant
                        if(choix_tot[k] == arcs_tries[j]->getType())
                        {
                            // alors on supprime aussi ces conditions
                            arcs_tries.erase(arcs_tries.begin()+j);
                        }
                    }
                }
            }
        }

        //affichage
        for(auto tri : arcs_tries)
        {
            std::cout << "APRES : " << tri->getType() << std::endl;
        }
    }

    //demande du sommet de depart/arrivee
    saisi_depart_arrivee(arcs_tries);
}

/// saisi les sommets de depart et d'arrive et ensuite appel l'algo de Kruskal
void Graphe::saisi_depart_arrivee(std::vector<Arc*>arcs_tries)
{
    int x1,x2;
    std::cout<<"\nSommet de depart: ";
    std::cin>>x1;
    std::cout<<"Sommet d'arrive : ";
    std::cin>>x2;
    Kruskal(x1, x2, arcs_tries);
}

/// algo de Kruskal
void Graphe::Kruskal(int x1, int x2, std::vector<Arc*>arcs_tries)
{
    std::vector <Arc*> arc_final; // vector qui stock tous les arcs qui vont être affichés
    bool fin = false; // booléen devient true lorsque on a atteint x2

    while((arc_final.size() <(unsigned int)m_nbrSommet -1) && (fin==false))
    {

        int MIN=9999; // initialisation par défaut
        int act; // variable pour stocker l'arc

        // recherche de la plus petite arc
        for(unsigned int i =0 ; i<arcs_tries.size(); i++)
        {
            if(arcs_tries[i]->getSommetAdj().first->getNumero() == x1) // on détecte le sommet de départ dans le vector d'arc
            {
                if(arcs_tries[i]->getDuree() < MIN) // on prend l'arc qui a la plus petite pondération
                {
                    act=i; // on stock cet arc
                    MIN = arcs_tries[i]->getDuree();
                }
            }
        }



        // vérifie si l'arc ne fait pas de boucle
        if(arcs_tries[act]->getSommetAdj().first->verif_connexe(arcs_tries[act]->getSommetAdj().second) == true)
        {
            arc_final.push_back(arcs_tries[act]); // on met cet arc dans un vector

            // ajout des nouvelles composantes connexes
            arcs_tries[act]->getSommetAdj().first->addConnexe( arcs_tries[act]->getSommetAdj().second->getNumero());
            arcs_tries[act]->getSommetAdj().second->addConnexe( arcs_tries[act]->getSommetAdj().first->getNumero());


            for(unsigned int i=0 ; i<arcs_tries[act]->getSommetAdj().first->getConnexe().size() ; i++)
            {
                // ajout connexité sommet2 avec sommet1
                arcs_tries[act]->getSommetAdj().second->addConnexe(arcs_tries[act]->getSommetAdj().first->getConnexe()[i]);
            }

            for(unsigned int i=0 ; i<arcs_tries[act]->getSommetAdj().second->getConnexe().size() ; i++)
            {
                // ajout connexité sommet1 avec sommet2
                arcs_tries[act]->getSommetAdj().first->addConnexe(arcs_tries[act]->getSommetAdj().second->getConnexe()[i]);
            }

            if(arcs_tries[act]->getSommetAdj().second->getNumero() == x2) // si l'extrémité 2 est le sommet x2 saisi par l'utilisateur
            {
                fin = true; // alors on sort de la boucle while
            }

        }
        //supprimer l'arc séléctionnée du vector de base
        arcs_tries.erase(arcs_tries.begin()+ act);
    }

    // affichage des arcs conservées (final)
    std::cout <<std::endl << "\nARCS CONSERVEES : "<<std::endl;
    int poids=0;
    for(unsigned int i =0 ; i<arc_final.size(); i++)
    {
        poids=poids+arc_final[i]->getDuree(); // on récupère le poids final (pondération de tous les arcs séléctionnées)
        std::cout << arc_final[i]->getSommetAdj().first->getNumero() << " --> " <<  arc_final[i]->getSommetAdj().second->getNumero() << "   Poids: " << arc_final[i]->getDuree();
        std::cout << "   Type : " << arc_final[i]->getType() << std::endl;
    }

    std::cout <<std::endl <<"poids de l'arbre: "<<poids<<std::endl;

}
