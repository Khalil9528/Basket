#include "basket.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <memory>

/**
 * @brief Calcule la distance euclidienne entre la position actuelle et une autre position.
 * @param other L'autre position.
 * @return La distance euclidienne.
 */
float Position::distance_to(const Position& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

/**
 * @brief Trouve les coéquipiers les plus proches pour un joueur.
 * @param players Liste de tous les joueurs du jeu.
 * @param team_id L'identifiant de l'équipe du joueur.
 */
void Player::find_teammates(const std::vector<Player>& players, int team_id) {
    std::vector<std::pair<Player*, float>> distances;

    for (const Player& other : players) {
        if (other.number != this->number && other.number / 5 == team_id) {
            float distance = this->position.distance_to(other.position);
            distances.push_back({const_cast<Player*>(&other), distance});
        }
    }

    std::sort(distances.begin(), distances.end(),
              [](const std::pair<Player*, float>& a, const std::pair<Player*, float>& b) {
                  return a.second < b.second;
              });

    for (int i = 0; i < 4 && i < static_cast<int>(distances.size()); ++i) {
        Teammates[i] = distances[i].first;
    }
}

/**
 * @brief Trouve les adversaires les plus proches pour un joueur.
 * @param players Liste de tous les joueurs du jeu.
 * @param team_id L'identifiant de l'équipe du joueur.
 */
void Player::find_opponents(const std::vector<Player>& players, int team_id) {
    std::vector<std::pair<Player*, float>> distances;

    for (const Player& other : players) {
        if (other.number / 5 != team_id) {
            float distance = this->position.distance_to(other.position);
            distances.push_back({const_cast<Player*>(&other), distance});
        }
    }

    std::sort(distances.begin(), distances.end(),
              [](const std::pair<Player*, float>& a, const std::pair<Player*, float>& b) {
                  return a.second < b.second;
              });

    for (int i = 0; i < 5 && i < static_cast<int>(distances.size()); ++i) {
        Opponents[i] = distances[i].first;
    }
}

/**
 * @brief Change le possesseur du ballon pour le coéquipier le plus proche.
 * @return True si le possesseur a été changé avec succès, false sinon.
 */
bool Ballon::changer_possesseur() {
    float min_distance = std::numeric_limits<float>::max();
    Player* closest_teammate = nullptr;

    for (int i = 0; i < 4; ++i) {
        Player* teammate = this->possesseur->Teammates[i];
        if (teammate) {
            float distance = this->position.distance_to(teammate->position);
            if (distance < min_distance) {
                min_distance = distance;
                closest_teammate = teammate;
            }
        }
    }

    if (closest_teammate) {
        this->possesseur = closest_teammate;
        return true;
    }

    return false;
}

/**
 * @brief Instance singleton de la classe Gamescore.
 */
Gamescore* Gamescore::instance = nullptr;

/**
 * @brief Constructeur par défaut de Gamescore.
 */
Gamescore::Gamescore() : homeScore(0), awayScore(0) {}

/**
 * @brief Obtient l'instance unique de la classe Gamescore.
 * @return Pointeur vers l'instance singleton.
 */
Gamescore* Gamescore::GetInstance() {
    if (instance == nullptr) {
        instance = new Gamescore();
    }
    return instance;
}

/**
 * @brief Ajoute un arbitre à la liste des observateurs.
 * @param arbitre Pointeur partagé vers l'arbitre.
 */
void Gamescore::AddArbitre(std::shared_ptr<Arbitre> arbitre) {
    arbitres.push_back(arbitre);
}

/**
 * @brief Met à jour le score affiché par un arbitre.
 * @param homeScore Score de l'équipe à domicile.
 * @param awayScore Score de l'équipe adverse.
 */
void RefereeDisplay::Update(int homeScore, int awayScore) {
    std::cout << "[Arbitre] Score mis à jour : Home " << homeScore
              << " - Away " << awayScore << std::endl;
}

/**
 * @brief Retire un arbitre de la liste des observateurs.
 * @param arbitre Pointeur partagé vers l'arbitre.
 */
void Gamescore::RemoveArbitre(std::shared_ptr<Arbitre> arbitre) {
    arbitres.erase(std::remove(arbitres.begin(), arbitres.end(), arbitre), arbitres.end());
}

/**
 * @brief Notifie tous les arbitres des scores actuels.
 */
void Gamescore::NotifyArbitres() {
    for (auto& arbitre : arbitres) {
        arbitre->Update(homeScore, awayScore);
    }
}

/**
 * @brief Met à jour les scores du jeu et notifie les arbitres.
 * @param home Score de l'équipe à domicile.
 * @param away Score de l'équipe adverse.
 */
void Gamescore::UpdateScore(int home, int away) {
    homeScore = home;
    awayScore = away;
    NotifyArbitres();
}

/**
 * @brief Exécute la stratégie offensive.
 */
void OffensiveStrategy::ExecuteStrategy() {
    std::cout << "Le coach ordonne : Passer en attaque rapide !" << std::endl;
}

/**
 * @brief Exécute la stratégie défensive.
 */
void DefensiveStrategy::ExecuteStrategy() {
    std::cout << "Le coach ordonne : Renforcez la défense !" << std::endl;
}

/**
 * @brief Constructeur par défaut de Coach.
 */
Coach::Coach() : currentStrategy(nullptr) {}

/**
 * @brief Définit la stratégie actuelle pour le coach.
 * @param strategy Pointeur vers la stratégie.
 */
void Coach::SetStrategy(Strategy* strategy) {
    currentStrategy = strategy;
}

/**
 * @brief Applique la stratégie actuelle.
 */
void Coach::ApplyStrategy() {
    if (currentStrategy) {
        currentStrategy->ExecuteStrategy();
    } else {
        std::cout << "Aucune stratégie définie par le coach." << std::endl;
    }
}

/**
 * @brief Observe l'état d'un joueur.
 * @param player Le joueur à observer.
 */
void Coach::ObservePlayer(const Player& player) {
    if (player.possede_ball) {
        std::cout << "Coach observe : Le joueur " << player.number << " a le ballon." << std::endl;
    } else {
        std::cout << "Coach observe : Le joueur " << player.number << " n'a pas le ballon." << std::endl;
    }
}

/**
 * @brief Constructeur de PlayerLeaf.
 * @param p Pointeur vers le joueur représenté par cette feuille.
 */
PlayerLeaf::PlayerLeaf(Player* p) : player(p) {}

/**
 * @brief Affiche les informations du joueur.
 */
void PlayerLeaf::Display() const {
    std::cout << "Joueur " << player->number << " à la position ("
              << player->position.x << ", " << player->position.y << ")" << std::endl;
}

/**
 * @brief Ajoute un composant à une équipe.
 * @param component Pointeur vers le composant à ajouter.
 */
void TeamComposite::Add(TeamComponent* component) {
    components.push_back(component);
}

/**
 * @brief Retire un composant d'une équipe.
 * @param component Pointeur vers le composant à retirer.
 */
void TeamComposite::Remove(TeamComponent* component) {
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

/**
 * @brief Affiche les informations de l'équipe.
 */
void TeamComposite::Display() const {
    std::cout << "Équipe :\n";
    for (const auto& component : components) {
        component->Display();
    }
}
