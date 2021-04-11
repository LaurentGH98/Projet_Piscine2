#include "Graphe.h"
#include <fstream>
#include <queue>

//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//Ici, on récupère un handle vers ce qui représente la sortie standard sous Windows.

/// constructeur
Graphe::Graphe(std::string nomFichier)
{
    int interet = 0; // variable contenant les interets d'une piste (montée/descente)

    // lecture d'un fichier
    std::ifstream ifs{nomFichier};

    // blindage
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    // lecture des sommets
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

    // lecture des arcs
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
        m_arc.push_back(new Arc(numArc,nomArc,typeArc,m_sommet[ext1-1],m_sommet[ext2-1],tpsTrajet, interet));
    }

    // lecture des arcs
    for(int i=0; i<12; i++)
    {
        ifs>>interet;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture des interets");

        // initialisation des interets en fonction des types
        if(i==0) //interet = 10 (descente) (V)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "V")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==1) // interet = 5 (descente) (B)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "B")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==2) // interet = 3 (descente) (R)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "R")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==3) // interet = 1 (descente) (N)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "N")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==4) // interet = 2 (descente) (KL)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "KL")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==5) // interet = 1 (descente) (SURF)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "SURF")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==6) // interet = 50 (montée) (TPH)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "TPH")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==7) // interet = 55 (montée) (TC)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "TC")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==8) // interet = 60 (montée) (TSD)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "TSD")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==9) // interet = 65 (montée) (TS)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "TS")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==10) // interet = 70 (montée) (TK)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "TK")
                {
                    vec->setInteret(interet);
                }
            }
        }
        else if(i==11) // interet = 75 (montée) (BUS)
        {
            for(auto vec : m_arc)
            {
                if(vec->getType() == "BUS")
                {
                    vec->setInteret(interet);
                }
            }
        }
    }

    for(unsigned int i=0 ; i<m_arc.size(); i++)
    {
        m_sommet[m_arc[i]->getSommetAdj().first->getNumero()-1]->addConnexe(i);
    }
}


///destructeur
Graphe::~Graphe()
{
}


/// méthode d'affichage des sommets
void Graphe::AffichageSommet()
{
    std::cout<<"Nbr Sommets = "<< m_nbrSommet <<std::endl;
    std::cout<<"\nSOMMETS :"<<std::endl;
    for (auto s : m_sommet)
    {
        std::cout << s->getNumero() << " " << s->getNom() << " " << s->getAltitude() << std::endl;
    }
}


/// méthode d'affichage des arcs
void Graphe::AffichageArc()
{
    std::cout<<"\nNbr arcs = "<< m_nbrArc <<std::endl;
    std::cout<<"\nARCS :"<<std::endl;
    for (auto a : m_arc)
    {
        std::cout << a->getNumero() << " " << a->getNom() << " " << a->getType()<<" " ;
        a->afficher();
        std::cout << " (" << a->getInteret() <<  ")" << std::endl;
    }
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

    // premiere boucle pour trouver les sommets sortants
    for(auto elem : m_arc) // on parcourt la liste des arcs du graphe
    {
        if(elem->getSommetAdj().first->getNumero() == numSomChoisi) // si le numéro du sommet choisi correspond à la première extrémité
            // alors le trajet est forcément sortant
        {
            std::cout<<"Ce trajet se dirigeant vers : "<<elem->getSommetAdj().second->getNom()<<" s'appelle : "<<elem->getNom();

            // conditions pour donné le nom du type de trajet
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

    // deuxieme boucle pour trouver les somments entrant
    for(auto elem : m_arc) // même démarche
    {
        if(elem->getSommetAdj().second->getNumero() == numSomChoisi)
        {
            std::cout<<"Ce trajet arrive de : "<<elem->getSommetAdj().first->getNom()<<" s'appelle : "<<elem->getNom();

            // conditions pour donné le nom du type de trajet
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
    int niveau = 0;

    std::cout << "1-Debutant\n2-Intermediaire\n3-Professionel" <<std::endl;
    std::cout << "Veuillez saisir votre niveau : ";
    std::cin>>niveau;

    // blindage
    while(niveau<1 || niveau>3)
    {
        int niveau2 = 0;
        std::cout << "Saisi non valide, veuillez saisir a nouveau : ";
        std::cin>>niveau2;
        niveau = niveau2;
    }

    std::string choix_utilisateur = "Q"; // initialisation par defaut

    if(niveau == 1) // debutant
    {
        std::cout << "Vous ne pouvez pas emprunter de pistes noires ni de pistes rouges.\n" <<std::endl;
        std::cout << "Z-FIN.\nV-Piste Verte\nB-Piste bleue\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter d'autre ? \n(Veuillez saisir 'Z' pour terminer votre saisi)\n" << std::endl;

        // blindage
        while(choix_utilisateur != "Z")
        {

            std::cin >> choix_utilisateur;
            // blindage saisie
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
            // saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!\n" <<std::endl;
                for(unsigned int i=0 ; i< m_arc.size() ; i++ )
                {
                    if( m_arc[i]->getType() == "R" || m_arc[i]->getType() == "N") // on lui retire les pistes noires et rouges
                        m_arc[i]->set_actif(false);
                }

            }
            // bonne saisie
            else
            {
                std::cout << "ok!" << std::endl;
                for(unsigned int i=0 ; i< m_arc.size() ; i++ )
                {
                    if( m_arc[i]->getType() == "R" || m_arc[i]->getType() == "N" || m_arc[i]->getType() == choix_utilisateur) // on lui retire les pistes noires et rouges
                        m_arc[i]->set_actif(false);
                }
            }
        }
    }

    else if(niveau == 2) // intermediaire
    {
        std::cout << "Vous ne pouvez pas emprunter de pistes noires.\n" <<std::endl;
        std::cout << "Z-Rien\nV-Piste Verte\nB-Piste bleue\nR-Piste Rouge\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter d'autre ?\n(Veuillez saisir Z pour terminer votre saisi)\n" <<std::endl;

        // blindage
        while(choix_utilisateur != "Z")
        {
            std::cin >> choix_utilisateur;
            // blindage saisie
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
            // saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!" <<std::endl;
                for(unsigned int i=0 ; i< m_arc.size() ; i++ )
                {
                    if(m_arc[i]->getType() == "N") // on lui retire les pistes noires et rouges
                        m_arc[i]->set_actif(false);
                }
            }
            // bonne saisie
            else
            {
                std::cout << "ok!" << std::endl;
                for(unsigned int i=0 ; i< m_arc.size() ; i++ )
                {
                    if(m_arc[i]->getType() == "N" || m_arc[i]->getType() == choix_utilisateur) // on lui retire les pistes noires et vertes
                        m_arc[i]->set_actif(false);
                }
            }
        }
    }

    else if(niveau == 3) // professionnel
    {
        std::cout << "Z-Rien\nV-Piste Verte\nB-Piste bleue\nR-Piste Rouge\nN-Piste Noire\nKL-Piste de Kilometre Lance\nSURF-Snowpark" << std::endl;
        std::cout << "TPH-Telepherique\nTC-Telecabine\nTSD-Telesiege debrayable\nTS-Telesiege\nTK-Teleski\nBUS-Navette" << std::endl;
        std::cout << "\nQue voulez-vous eviter ? \n(Veuillez saisir Z pour terminer votre saisi)\n" <<std::endl;

        // blindage
        while(choix_utilisateur != "Z")
        {
            std::cin >> choix_utilisateur;
            // blindage saisie
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
            // saisie pour sortir de la boucle
            else if(choix_utilisateur=="Z")
            {
                std::cout << "Saisie valide!" <<std::endl;
            }
            // bonne saisie
            else
            {
                std::cout << "ok!" << std::endl;
                for(unsigned int i=0 ; i< m_arc.size() ; i++ )
                {
                    if( m_arc[i]->getType() == choix_utilisateur) // on lui retire les pistes noires et vertes
                        m_arc[i]->set_actif(false);
                }

            }
        }
    }

    dijkstra(); // on appelle l'algorithme de Dijkstra

    // on remet comme avant une fois Dijkstra fini
    for(unsigned int i=0 ; i< m_arc.size() ; i++ )
    {
        m_arc[i]->set_actif(true);
    }

}

// utilisation pour la priority queue
typedef std::pair <int, int> pi;

/// algorithme de Dijkstra
void Graphe::dijkstra()
{

    int V= m_sommet.size();

    Sommet * borne;

    // initialisation
    bool *visited = new bool[V];
    for(int i = 0 ; i < V ; i++)
        visited[i] = false;


    // initialisation
    int *distance = new int [V];
    for(int i = 0; i < V; i++)
        distance[i] = 10000000;


    // initialisation
    Sommet **antecedent = new Sommet*[V];
    for(int i = 0; i < V; i++)
        antecedent[i] = NULL;

    // initialisation
    Arc **trajet = new Arc*[V];
    for(int i = 0; i < V; i++)
        trajet[i] = NULL;


    std::cout << "/////PARCOURS LE PLUS RAPIDE ENTRE DEUX BORNES/////" << std::endl << std::endl;

    std::cout << "Borne de depart: ";
    int depart;
    std::cin >> depart;
    std::cout << "Borne d'arrive: ";
    int arrive;
    std::cin >> arrive;

    system("cls");

    // initialisation
    borne = m_sommet[depart-1];
    int a = borne->getNumero()-1;
    distance[a] = 0 ;
    int out = 0;

    std::priority_queue <pi, std::vector<pi>, std::greater <pi> > pile;
    // std::greater permet de classer en fonction du premier attribut de la pair


    // blindage
    while(out == 0)
    {
        // initialisation
        borne = m_sommet[a]; // sommet de depart
        visited[a] = true; // marqué


        for(unsigned int i = 0 ; i<borne->getConnexe().size() ; i++)
        {
            Arc * arrete = m_arc[borne->getConnexe()[i]];

            int b = arrete->getSommetAdj().second->getNumero()-1; // initialisation de l'extrémité second d'un arc
            int duree = distance[a] + arrete->getDuree(); // initialisation d'une durée

            // si c'est la plus petite durée
            if(duree < distance[b] && arrete->get_actif() == true )
            {
                antecedent[b] = borne;
                trajet[b]  = arrete;
                distance[b] = duree;
                std::pair<int, int> Pair; // contient la durée et l'extremité second d'un arc
                Pair.first = duree;
                Pair.second = b;
                pile.push(Pair);

            }
        }


        out=1; // on sort de la boucle while
        // parcours de tous les sommets
        for(int i=0 ; i< V; i++)
        {
            if(visited[i] == false) // si pas marqué
                out=0;
        }

        // si la pile n'est pas vide
        if(pile.size() != 0)
        {
            a = pile.top().second;
            pile.pop();// on supprime

        }

        // si aucun chemin n'existe
        else if(out == 0)
        {
            if(visited[arrive-1] == false) // si le sommet d'arrivé n'est pas marqué
            {
                std::cout << "Desole mais il n'existe aucun chemin repondant a votre demande\n\n";
                system("PAUSE");
            }
            out = 1; // on sort de la boucle while

        }

    }

    // affichage du chemin le plus rapide
    if(visited[arrive-1] == true)
    {
        std::cout << "Chemin le plus rapide entre la borne " << m_sommet[depart-1]->getNom() <<" et la borne " << m_sommet[arrive-1]->getNom() << std::endl << std::endl;
        int ant = arrive-1;
        int nmb=0;
        while( ant != (depart-1) )
        {
            std::cout <<std::endl <<"==>"<< m_sommet[ant]->getNom() ;
            std::cout<<std::endl << "[" << trajet[ant]->getNom() << "] " << trajet[ant]->getType() << "  " << trajet[ant]->getDuree() <<" minutes" ;
            ant=antecedent[ant]->getNumero()-1;
            nmb++;
        }

        std::cout<< std::endl <<std::endl << "==>" << m_sommet[ant]->getNom();

        std::cout << std::endl <<std::endl<< "Temps de l'itineraire: environ "<< distance[arrive-1] << " minutes"  ;
        std::cout << std::endl << std::endl;

    }

}


/// menu principal de la borne
void Graphe::Menu()
{
    int choix(0);//pour menu
    bool valide(false);//pour blindage
    bool boucle(false);

    std::cout<<std::endl;
    std::cout<<"********************************************************************************"<<std::endl;
    std::cout<<"**************************************BONJOUR!**********************************"<<std::endl;
    std::cout<<"********************************************************************************"<<std::endl;
    std::cout<<std::endl;


    while(boucle == false )
    {
        std::cout<<std::endl;
        std::cout<<"**************************************MENU**************************************"<<std::endl;
        std::cout<<"/1/  Information sur un trajet"<<std::endl;
        std::cout<<"/2/  Information sur un de nos points de stations"<<std::endl;
        std::cout<<"/3/  Information sur les plus courts chemin depuis votre position"<<std::endl;
        std::cout<<"/4/  Information sur le chemin le plus rapide entre 2 points"<<std::endl;
        std::cout<<"/5/  Information sur le chemin le plus interressant pour vous"<<std::endl;
        std::cout<<"/6/  Information sur nos points de stations et nos trajets"<<std::endl;
        std::cout<<"/7/  Information flots"<<std::endl;
        std::cout<<"/8/  Quitter la borne"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Quelle information souhaitez-vous connaitre par rapport a notre magnifique station ?(Entrez un numero)  "<<std::endl;


        while (valide==false)   //blindage de la saisie des sommets pour les entiers
        {
            std::cin>> choix;

            if( choix>=1 && choix<=8)
                valide=true;
            else
            {
                std::cout<<"Choix impossible, veuillez recommencer : ";
            }
        }

        switch(choix)
        {
        case 1:
            system("cls");
            std::cout<<"#############################################"<<std::endl;
            std::cout<<"#           .-~~\\                          #"<<std::endl;
            std::cout<<"#          /     \\ _                       #"<<std::endl;
            std::cout<<"#          ~x   .-~_)_                      #"<<std::endl;
            std::cout<<"#            ~x*.-~   ~-.                   #"<<std::endl;
            std::cout<<"#        _   ( /         \\   _             #"<<std::endl;
            std::cout<<"#        ||   T  o  o     Y  ||             #"<<std::endl;
            std::cout<<"#      ==:l   l   <       !  I;==           #"<<std::endl;
            std::cout<<"#         \\\\   \\  .__/   /  //           #"<<std::endl;
            std::cout<<"#          \\\\ ,r*-,___.-'r.//             #"<<std::endl;
            std::cout<<"#           }^ \\.( )   _.'//.              #"<<std::endl;
            std::cout<<"#          /    }~Xi--~  //  \\             #"<<std::endl;
            std::cout<<"#          Y    Y I\\ \\    *    Y          #"<<std::endl;
            std::cout<<"#          |    | |o\\ \\        |          #"<<std::endl;
            std::cout<<"#          |    l_l  Y T       |  -Row      #"<<std::endl;
            std::cout<<"#          l      *o l_j       !            #"<<std::endl;
            std::cout<<"#           \\                 /            #"<<std::endl;
            std::cout<<"#    ___,.---^.     o       .^---.._____    #"<<std::endl;
            std::cout<<"#*~~~          *           ~            ~~~*#"<<std::endl;
            std::cout<<"#############################################"<<std::endl;
            infoArc();
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 2:
            system("cls");
            std::cout<<"#############################################################"<<std::endl;
            std::cout<<"#        _    .  ,   .           .                          #"<<std::endl;
            std::cout<<"#    *  / \\_ *  / \\_      _  *        *   /\\'__        *    #"<<std::endl;
            std::cout<<"#      /    \\  /    \\,   ((        .    _/  /  \\  *'.       #"<<std::endl;
            std::cout<<"#   . /\\/\\  /\\/ :' __ \\_  `          _^/  ^/    `--.        #"<<std::endl;
            std::cout<<"#    /    \\/  \\  _/  \\-'\\      *    /.' ^_   \\_   .'\\  *    #"<<std::endl;
            std::cout<<"#  /\\  .-   `. \\/     \\ /==~=-=~=-=-;.  _/ \\ -. `_/   \\     #"<<std::endl;
            std::cout<<"# /  `-.__ ^   / .-'.--\\ =-=~_=-=~=^/  _ `--./ .-'  `-      #"<<std::endl;
            std::cout<<"#/        `.  / /       `.~-^=-=~=^=.-'      '-._ `._       #"<<std::endl;
            std::cout<<"#############################################################"<<std::endl;
            infoSommet();
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 3:
            system("cls");
            std::cout<<"#############################################################################"<<std::endl;
            std::cout<<"#          /\\                                                               #"<<std::endl;
            std::cout<<"#         /**\\                                                              #"<<std::endl;
            std::cout<<"#        /****\\   /\\                                                        #"<<std::endl;
            std::cout<<"#       /      \\ /**\\                                                       #"<<std::endl;
            std::cout<<"#      /  /\\    /    \\        /\\    /\\  /\\      /\\            /\\/\\/\\  /\\    #"<<std::endl;
            std::cout<<"#     /  /  \\  /      \\      /  \\/\\/  \\/  \\  /\\/  \\/\\  /\\  /\\/ / /  \\/  \\   #"<<std::endl;
            std::cout<<"#    /  /    \\/ /\\     \\    /    \\ \\  /    \\/ /   /  \\/  \\/  \\  /    \\   \\  #"<<std::endl;
            std::cout<<"#   /  /      \\/  \\/\\   \\  /      \\    /   /    \\                           #"<<std::endl;
            std::cout<<"#__/__/_______/___/__\\___\\__________________________________________________#"<<std::endl;
            std::cout<<"#############################################################################"<<std::endl;
            // bfs les plus courts chemins (4.4)
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 4:
            system("cls");
            std::cout<<"###############################"<<std::endl;
            std::cout<<"#            o\\               #"<<std::endl;
            std::cout<<"#  _________/__\\__________    #"<<std::endl;
            std::cout<<"#  |                  - (  |  #"<<std::endl;
            std::cout<<"# ,'-.                 . `-|  #"<<std::endl;
            std::cout<<"#(____ .       ,-.    '   ||  #"<<std::endl;
            std::cout<<"#  |          /\\,-\\   ,-.     #"<<std::endl;
            std::cout<<"#  |      ,-./     \\ /'.-\\ |  #"<<std::endl;
            std::cout<<"#  |     /-.,\\      /     \\|  #"<<std::endl;
            std::cout<<"#  |    /     \\    ,-.     \\  #"<<std::endl;
            std::cout<<"#  |___/_______\\__/___\\_____\\ #"<<std::endl;
            std::cout<<"###############################"<<std::endl;
            // dijkstra l'itineraire le plus court (4.4)
            dijkstra ();
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 5:
            system("cls");
            std::cout<<"######################################"<<std::endl;
            std::cout<<"#            *                       #"<<std::endl;
            std::cout<<"#            XX                      #"<<std::endl;
            std::cout<<"#           MMMMM                    #"<<std::endl;
            std::cout<<"#           //(00                    #"<<std::endl;
            std::cout<<"#        .:.....                     #"<<std::endl;
            std::cout<<"#        .:::::::::                  #"<<std::endl;
            std::cout<<"#       :: %%%%%% ::.                #"<<std::endl;
            std::cout<<"#      ::  ::::::  :::::::I)         #"<<std::endl;
            std::cout<<"#      (%  ::::::         |          #"<<std::endl;
            std::cout<<"#      /   |   /_____     |          #"<<std::endl;
            std::cout<<"#     /    |         ))   |          #"<<std::endl;
            std::cout<<"#    /      ------/ //    |          #"<<std::endl;
            std::cout<<"#   /            / //     |          #"<<std::endl;
            std::cout<<"#  /            / //      |          #"<<std::endl;
            std::cout<<"# *            ZZZZ       *          #"<<std::endl;
            std::cout<<"#    _________ZZZZZZ_________//_//   #"<<std::endl;
            std::cout<<"#------------------------------------#"<<std::endl;
            std::cout<<"######################################"<<std::endl;
            // dijkstra l'itinéraire le plus interessant (4.5)
            chemin_interessant();
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;

            break;
        case 6:
            system("cls");
            std::cout<<"##################################################"<<std::endl;
            std::cout<<"#                /----|       .         .        #"<<std::endl;
            std::cout<<"#  .            /     [   .        .         .   #"<<std::endl;
            std::cout<<"#         ______|---- _|__     .        .        #"<<std::endl;
            std::cout<<"#.     _--    --\\_<\\_//   \\-----           .     #"<<std::endl;
            std::cout<<"#     _  _--___   \\__/     ___  -----_ **     *  #"<<std::endl;
            std::cout<<"#*  _- _-      --_         /  [ ----__  --_  *   #"<<std::endl;
            std::cout<<"#*/__-      .    [           _[  *** --_  [*     #"<<std::endl;
            std::cout<<"#  [*/ .          __[/-----__/   [**     [*/     #"<<std::endl;
            std::cout<<"#        .     /--  /            /               #"<<std::endl;
            std::cout<<"#     .        /   /   /[----___/        .       #"<<std::endl;
            std::cout<<"#             /   /*[  !   /==/              .   #"<<std::endl;
            std::cout<<"# .          /   /==[   |/==/      .             #"<<std::endl;
            std::cout<<"#          _/   /=/ | _ |=/   .               .  #"<<std::endl;
            std::cout<<"#         /_   //  / _ _//              .        #"<<std::endl;
            std::cout<<"#.        [ '//    |__//    .    .            .  #"<<std::endl;
            std::cout<<"#        /==/  .  /==/                .          #"<<std::endl;
            std::cout<<"#      /==/     /==/                       .     #"<<std::endl;
            std::cout<<"#     /==/     /==/       .       .    .         #"<<std::endl;
            std::cout<<"#  _/==/    _/==/            .                   #"<<std::endl;
            std::cout<<"# [|*      [|*                   White Powder!!  #"<<std::endl;
            std::cout<<"##################################################"<<std::endl;
            //info listes sommets et arcs
            AffichageSommet();
            AffichageArc();
            std::cout << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 7:
            system("cls");
            std::cout<<"#####################################################################"<<std::endl;
            std::cout<<"# -   -       -   -     -  -  -    -     -       -   -   -  -    -  #"<<std::endl;
            std::cout<<"#- -   (  -      -    -  -   -   -    -   -    -   -   -    -     - #"<<std::endl;
            std::cout<<"#-  (     )   (   |\\  -  -       -     -      -    -  --    -  - -  #"<<std::endl;
            std::cout<<"# -   ) -  -   )  ) \\  -       _  .---.  -    -    -    -      -   -#"<<std::endl;
            std::cout<<"#-  -   -    -  (/   \\   -  - (_)-.   _\\ - -    -     -  -      -  -#"<<std::endl;
            std::cout<<"# -     .--.  -  \\   | -     -     \\ /u( -   -   -      -      -   -#"<<std::endl;
            std::cout<<"#   .-./ ___\\    /\\  )    -   -  - _\\_-/   -     -   -   -  -    -  #"<<std::endl;
            std::cout<<"# - `-'\\|. .| - // \\/   -  -   -  /    \\     -     --       -    - -#"<<std::endl;
            std::cout<<"#  -   __\\-/__ (_)    -  -   - - /  \\ \\ \\___    -       -    -   -  #"<<std::endl;
            std::cout<<"# -   (  \\:/  // | -  --  -  -  /   /\\ \\___/)     -  -  -    -   -.-#"<<std::endl;
            std::cout<<"#   -  \\ \\:  //V /  -  -     - /`._/ -\\___(_) \\        -   -   .-'  #"<<std::endl;
            std::cout<<"#_-  - (\\ \\_//`-' - -  -  -    |\\  \\  -      \\ \\  -  -    -   /     #"<<std::endl;
            std::cout<<"# `. - (_\\(_)) -    -   -  - - | \\  \\   -  -  \\ \\___ .-. _   |      #"<<std::endl;
            std::cout<<"#   \\  \\  // /  -  -   -   -  /  /)  )-     -  \\/__ (  _( ) /       #"<<std::endl;
            std::cout<<"#    \\ |  |  | -  -    -  -  /  //  /   - -   -|   `-.(   )'        #"<<std::endl;
            std::cout<<"#     `--------------------------------------------------'          #"<<std::endl;
            std::cout<<"#####################################################################"<<std::endl;
            //flots(4.6)
            std::cout << "\nNous sommes desoles, cette option n'est pas encore disponible.\n" << std::endl;
            system("PAUSE");
            system("cls");
            valide=false;
            break;
        case 8:
            //Quitter
            std::cout<<"#####################################################################"<<std::endl;
            std::cout<<"#                     ,---.           ,---.                         #"<<std::endl;
            std::cout<<"#                    / /*`.\\.--***--./,'*\\ \\                        #"<<std::endl;
            std::cout<<"#                    \\ \\    _       _    / /                        #"<<std::endl;
            std::cout<<"#                     `./  / __   __ \\  \\,'                         #"<<std::endl;
            std::cout<<"#                      /    /_O)_(_O\\    \\                          #"<<std::endl;
            std::cout<<"#                      |  .-'  ___  `-.  |                          #"<<std::endl;
            std::cout<<"#                   .--|       \\_/       |--.                       #"<<std::endl;
            std::cout<<"#                 ,'    \\   \\   |   /   /    `.                     #"<<std::endl;
            std::cout<<"#                /       `.  `--^--'  ,'       \\                    #"<<std::endl;
            std::cout<<"#             .-*****-.    `--.___.--'     .-*****-.                #"<<std::endl;
            std::cout<<"#.-----------/         \\------------------/         \\--------------.#"<<std::endl;
            std::cout<<"#| .---------\\         /----------------- \\         /------------. |#"<<std::endl;
            std::cout<<"#| |          `-`--`--'                    `--'--'-'             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                PROFITEZ BIEN DE VOTRE SEJOUR !!             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                        A TRES BIENTOT !!                    | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |                                                             | |#"<<std::endl;
            std::cout<<"#| |_____________________________________________________________| |#"<<std::endl;
            std::cout<<"#|_________________________________________________________________|#"<<std::endl;
            std::cout<<"#                   )__________|__|__________(                      #"<<std::endl;
            std::cout<<"#                  |            ||            |                     #"<<std::endl;
            std::cout<<"#                  |____________||____________|                     #"<<std::endl;
            std::cout<<"#                    ),-----.(      ),-----.(                       #"<<std::endl;
            std::cout<<"#                  ,'   ==.   \\    /  .==    `.                     #"<<std::endl;
            std::cout<<"#                 /            )  (            \\                    #"<<std::endl;
            std::cout<<"#                 `==========='    `==========='                    #"<<std::endl;
            std::cout<<"#####################################################################"<<std::endl;

            boucle=true;
            break;

        }

    }


//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//Ici, on récupère un handle vers ce qui représente la sortie standard sous Windows.
//SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);
//Ici, on change les attributs. Tu as droit aux 3 couleurs primaire informatique (rouge, vert et bleu)
//que tu peux mélanger entre elle pour faire plus de couleurs (par exemple vert + bleu = jaune)...Tu peux coupler ces mélanges de couleur avec une intensité de couleur
// plus élevé avec INTENSITY...Pour l'exemple du jaune, ca passerait d'un jaune sale à un jaune lumineux. Ici, ça met du blanc flashy sur fond rouge flashy.

    /*std::cout << "La boutique se compose donc de : " << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Cartes CREATURES";
        SetConsoleTextAttribute(hConsole, 2);
        std::cout<<"                                Cartes ENERGIE";
        SetConsoleTextAttribute(hConsole, 6);
        std::cout<<"                             Cartes Speciales" << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, 7);*/
}






/*SOURCES: Art by Joan Stark--> https://www.asciiart.eu/nature/mountains
                            --> https://www.asciiart.eu/sports-and-outdoors/skiing
                            --> https://www.asciiart.eu/nature/snows
                            --> https://www.asciiart.eu/holiday-and-events/christmas/snowmen*/
