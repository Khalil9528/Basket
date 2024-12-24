/**
 * @file tests.cpp
 * @brief Fichier contenant les tests unitaires pour les différentes fonctionnalités du projet.
 */

#include "basket.cpp"
#include <iostream>
#include <cassert>

/**
 * @brief Teste la méthode de calcul de distance entre deux positions.
 */
void testPositionDistance() {
    Position pos1{0, 0};
    Position pos2{3, 4};
    // Vérifie que la distance est correcte (5 selon le théorème de Pythagore)
    assert(pos1.distance_to(pos2) == 5.0f);
    std::cout << "testPositionDistance passed.\n";
}

/**
 * @brief Teste le changement de possesseur du ballon vers un coéquipier.
 */
void testBallonChangerPossesseur() {
    Player player1{Position{10, 20}, true, 1};
    Player player2{Position{30, 40}, false, 2};
    player1.Teammates[0] = &player2;

    Ballon ballon{Position{15, 25}, &player1};
    assert(ballon.possesseur == &player1);

    ballon.changer_possesseur(); // Change le possesseur vers le coéquipier le plus proche
    assert(ballon.possesseur == &player2);

    std::cout << "testBallonChangerPossesseur passed.\n";
}

/**
 * @brief Teste que la classe `Gamescore` respecte bien le pattern Singleton.
 */
void testSingletonPattern() {
    Gamescore* instance1 = Gamescore::GetInstance();
    Gamescore* instance2 = Gamescore::GetInstance();
    // Vérifie que les deux instances sont identiques
    assert(instance1 == instance2);

    std::cout << "testSingletonPattern passed.\n";
}

/**
 * @brief Teste le fonctionnement du pattern Observer avec les arbitres.
 */
void testObserverPattern() {
    Gamescore* gameScore = Gamescore::GetInstance();
    auto referee1 = std::make_shared<RefereeDisplay>();
    auto referee2 = std::make_shared<RefereeDisplay>();

    gameScore->AddArbitre(referee1);
    gameScore->AddArbitre(referee2);

    // Met à jour le score, ce qui devrait notifier les arbitres
    gameScore->UpdateScore(15, 10);

    // Retire un arbitre et met à jour le score
    gameScore->RemoveArbitre(referee1);
    gameScore->UpdateScore(20, 15);

    std::cout << "testObserverPattern passed.\n";
}

/**
 * @brief Teste le fonctionnement du pattern Composite pour gérer les équipes.
 */
void testCompositePattern() {
    Player player1{Position{10, 20}, false, 1};
    Player player2{Position{30, 40}, false, 2};

    PlayerLeaf leaf1(&player1); // Feuille représentant le joueur 1
    PlayerLeaf leaf2(&player2); // Feuille représentant le joueur 2

    TeamComposite team;
    team.Add(&leaf1); // Ajoute le joueur 1 à l'équipe
    team.Add(&leaf2); // Ajoute le joueur 2 à l'équipe

    team.Display(); // Affiche les informations des joueurs dans l'équipe

    std::cout << "testCompositePattern passed.\n";
}

/**
 * @brief Point d'entrée principal pour exécuter tous les tests unitaires.
 * 
 * Ce fichier exécute les tests pour valider :
 * - Les calculs de distances.
 * - Le changement de possesseur du ballon.
 * - Les patterns Singleton, Observer et Composite.
 */
int main() {
    testPositionDistance();
    testBallonChangerPossesseur();
    testSingletonPattern();
    testObserverPattern();
    testCompositePattern();

    std::cout << "Tous les tests unitaires ont été exécutés avec succès.\n";
    return 0;
}
