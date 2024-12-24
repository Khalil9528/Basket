/**
 * @file main.cpp
 * @brief Point d'entrée principal pour tester les fonctionnalités du projet de simulation de basketball.
 */

#include "basket.cpp"
#include <iostream>

/**
 * @brief Fonction principale pour exécuter les tests des fonctionnalités principales.
 * 
 * Cette fonction :
 * - Initialise les joueurs, leurs positions et leurs relations (coéquipiers, adversaires).
 * - Teste le changement de possesseur de ballon.
 * - Vérifie le fonctionnement des patterns Singleton, Observer, Strategy et Composite.
 * 
 * @return Retourne 0 si l'exécution est réussie.
 */
int main() {
    // Création de joueurs
    Player player1{Position{10, 20}, true, 1}; ///< Joueur 1 possédant initialement le ballon.
    Player player2{Position{30, 40}, false, 2}; ///< Joueur 2 sans ballon.
    Player player3{Position{50, 60}, false, 3}; ///< Joueur 3 sans ballon.
    Player player4{Position{70, 80}, false, 4}; ///< Joueur 4 sans ballon.

    // Initialisation des coéquipiers et adversaires
    std::vector<Player> players = {player1, player2, player3, player4};
    player1.find_teammates(players, 0);
    player1.find_opponents(players, 1);

    // Test du changement de possesseur du ballon
    Ballon ballon{Position{15, 25}, &player1};
    std::cout << "Initialement, le ballon est avec le joueur " << ballon.possesseur->number << ".\n";
    ballon.changer_possesseur();
    std::cout << "Après le changement, le ballon est avec le joueur " << ballon.possesseur->number << ".\n";

    // Test du Singleton et de l'Observer Pattern
    Gamescore* gameScore = Gamescore::GetInstance();
    auto referee1 = std::make_shared<RefereeDisplay>();
    auto referee2 = std::make_shared<RefereeDisplay>();

    gameScore->AddArbitre(referee1);
    gameScore->AddArbitre(referee2);

    std::cout << "\nMise à jour du score :\n";
    gameScore->UpdateScore(10, 5);

    gameScore->RemoveArbitre(referee1);
    std::cout << "\nMise à jour du score après suppression d'un arbitre :\n";
    gameScore->UpdateScore(20, 15);

    // Test du Strategy Pattern
    Coach coach;
    OffensiveStrategy offensive;
    DefensiveStrategy defensive;

    coach.SetStrategy(&offensive);
    coach.ApplyStrategy();

    coach.SetStrategy(&defensive);
    coach.ApplyStrategy();

    // Observation des joueurs
    coach.ObservePlayer(player1);
    coach.ObservePlayer(player2);

    // Test du Composite Pattern
    PlayerLeaf playerLeaf1(&player1);
    PlayerLeaf playerLeaf2(&player2);
    PlayerLeaf playerLeaf3(&player3);

    TeamComposite team;
    team.Add(&playerLeaf1);
    team.Add(&playerLeaf2);
    team.Add(&playerLeaf3);

    std::cout << "\nAffichage de l'équipe :\n";
    team.Display();

    TeamComposite subTeam;
    subTeam.Add(&playerLeaf1);
    subTeam.Add(&playerLeaf2);

    std::cout << "\nAffichage de la sous-équipe :\n";
    subTeam.Display();

    return 0;
}
