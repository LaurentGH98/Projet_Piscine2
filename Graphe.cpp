#include "Graphe.h"
#include <fstream>


//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//Ici, on récupère un handle vers ce qui représente la sortie standard sous Windows.

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
    /* std::cout<<"Nbr Sommets = "<< m_nbrSommet <<std::endl;
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


void Graphe::AffichageSommet()
{
    /**AFFICHAGE DES SOMMETS**/
    std::cout<<"Nbr Sommets = "<< m_nbrSommet <<std::endl;
    std::cout<<"\nSOMMETS :"<<std::endl;
    for (auto s : m_sommet)
    {
        std::cout << s->getNumero() << " " << s->getNom() << " " << s->getAltitude() << std::endl;
    }
}

void Graphe::AffichageArc()
{
    /**AFFICHAGE DES ARCS**/
    std::cout<<"\nNbr arcs = "<< m_nbrArc <<std::endl;
    std::cout<<"\nARCS :"<<std::endl;
    for (auto a : m_arc)
    {
        std::cout << a->getNumero() << " " << a->getNom() << " " << a->getType()<<" " ;
        a->afficher();
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
            std::cout<<"#           .-~~\\                           #"<<std::endl;
            std::cout<<"#          /     \\ _                        #"<<std::endl;
            std::cout<<"#          ~x   .-~_)_                      #"<<std::endl;
            std::cout<<"#            ~x*.-~   ~-.                   #"<<std::endl;
            std::cout<<"#        _   ( /         \\   _              #"<<std::endl;
            std::cout<<"#        ||   T  o  o     Y  ||             #"<<std::endl;
            std::cout<<"#      ==:l   l   <       !  I;==           #"<<std::endl;
            std::cout<<"#         \\\\   \\  .__/   /  //              #"<<std::endl;
            std::cout<<"#          \\\\ ,r*-,___.-'r.//               #"<<std::endl;
            std::cout<<"#           }^ \\.( )   _.'//.               #"<<std::endl;
            std::cout<<"#          /    }~Xi--~  //  \\              #"<<std::endl;
            std::cout<<"#          Y    Y I\\ \\    *    Y            #"<<std::endl;
            std::cout<<"#          |    | |o\\ \\        |            #"<<std::endl;
            std::cout<<"#          |    l_l  Y T       |  -Row      #"<<std::endl;
            std::cout<<"#          l      *o l_j       !            #"<<std::endl;
            std::cout<<"#           \\                 /             #"<<std::endl;
            std::cout<<"#    ___,.---^.     o       .^---.._____    #"<<std::endl;
            std::cout<<"#*~~~          *           ~            ~~~*#"<<std::endl;
            std::cout<<"#############################################"<<std::endl;
            infoArc();
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
            //bfs les plus courts chemins
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
            //et dijkstra (4.4)
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

            //chemin interessant (4.5)==kruskal
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
                          -->   https://www.asciiart.eu/holiday-and-events/christmas/snowmen*/




























