/**
 * @file basket.hpp
 * @brief Fichier en-tête définissant les classes et structures pour une simulation de jeu de basketball.
 */

#ifndef BASKET_HPP
#define BASKET_HPP

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>
#include <limits>

// Dimensions du terrain
#define basket_x 100.f ///< Largeur du terrain de basketball.
#define basket_y 50.f ///< Hauteur du terrain de basketball.

/**
 * @brief Structure représentant une position dans un espace 2D.
 */
struct Position {
    float x; ///< Coordonnée X de la position.
    float y; ///< Coordonnée Y de la position.

    /**
     * @brief Calcule la distance euclidienne vers une autre position.
     * @param other L'autre position.
     * @return La distance euclidienne vers la position donnée.
     */
    float distance_to(const Position& other) const;
};

/**
 * @brief Classe représentant un joueur dans le jeu de basketball.
 */
class Player {
public:
    Position position; ///< Position actuelle du joueur.
    bool possede_ball = false; ///< Indique si le joueur possède le ballon.
    int number; ///< Numéro attribué au joueur.
    Player* Teammates[4]; ///< Tableau de pointeurs vers les coéquipiers.
    Player* Opponents[5]; ///< Tableau de pointeurs vers les adversaires.

    /**
     * @brief Trouve les coéquipiers les plus proches.
     * @param players Liste de tous les joueurs.
     * @param team_id Identifiant de l'équipe.
     */
    void find_teammates(const std::vector<Player>& players, int team_id);

    /**
     * @brief Trouve les adversaires les plus proches.
     * @param players Liste de tous les joueurs.
     * @param team_id Identifiant de l'équipe.
     */
    void find_opponents(const std::vector<Player>& players, int team_id);
};

/**
 * @brief Classe représentant le ballon de basketball.
 */
class Ballon {
public:
    Position position; ///< Position actuelle du ballon.
    Player* possesseur = nullptr; ///< Joueur qui possède actuellement le ballon.

    /**
     * @brief Change le possesseur du ballon pour le coéquipier le plus proche.
     * @return True si le possesseur a changé avec succès, false sinon.
     */
    bool changer_possesseur();
};

/**
 * @brief Interface pour les arbitres observant le jeu (Pattern Observer).
 */
class Arbitre {
public:
    virtual ~Arbitre() = default;

    /**
     * @brief Met à jour l'arbitre avec le score actuel du jeu.
     * @param homeScore Score de l'équipe à domicile.
     * @param awayScore Score de l'équipe adverse.
     */
    virtual void Update(int homeScore, int awayScore) = 0;
};

/**
 * @brief Classe pour afficher les mises à jour des arbitres.
 */
class RefereeDisplay : public Arbitre {
public:
    /**
     * @brief Affiche le score mis à jour.
     * @param homeScore Score de l'équipe à domicile.
     * @param awayScore Score de l'équipe adverse.
     */
    void Update(int homeScore, int awayScore) override;
};

/**
 * @brief Classe gérant le score du jeu (Pattern Singleton et Observable).
 */
class Gamescore {
private:
    static Gamescore* instance; ///< Instance unique (Singleton).

    /**
     * @brief Constructeur privé pour le pattern Singleton.
     */
    Gamescore();

public:
    int homeScore; ///< Score actuel de l'équipe à domicile.
    int awayScore; ///< Score actuel de l'équipe adverse.
    std::vector<std::shared_ptr<Arbitre>> arbitres; ///< Liste des arbitres observant le jeu.

    /**
     * @brief Obtient l'instance unique de la classe Gamescore.
     * @return Pointeur vers l'instance Singleton.
     */
    static Gamescore* GetInstance();

    /**
     * @brief Ajoute un arbitre à la liste des observateurs.
     * @param arbitre Pointeur partagé vers l'arbitre.
     */
    void AddArbitre(std::shared_ptr<Arbitre> arbitre);

    /**
     * @brief Retire un arbitre de la liste des observateurs.
     * @param arbitre Pointeur partagé vers l'arbitre.
     */
    void RemoveArbitre(std::shared_ptr<Arbitre> arbitre);

    /**
     * @brief Notifie tous les arbitres des scores actuels.
     */
    void NotifyArbitres();

    /**
     * @brief Met à jour les scores du jeu et notifie les arbitres.
     * @param home Score de l'équipe à domicile.
     * @param away Score de l'équipe adverse.
     */
    void UpdateScore(int home, int away);
};

/**
 * @brief Classe abstraite représentant une stratégie pour le coach.
 */
class Strategy {
public:
    virtual ~Strategy() = default;

    /**
     * @brief Exécute la stratégie.
     */
    virtual void ExecuteStrategy() = 0;
};

/**
 * @brief Classe représentant une stratégie offensive.
 */
class OffensiveStrategy : public Strategy {
public:
    /**
     * @brief Exécute la stratégie offensive.
     */
    void ExecuteStrategy() override;
};

/**
 * @brief Classe représentant une stratégie défensive.
 */
class DefensiveStrategy : public Strategy {
public:
    /**
     * @brief Exécute la stratégie défensive.
     */
    void ExecuteStrategy() override;
};

/**
 * @brief Classe représentant le coach, qui applique des stratégies et observe les joueurs.
 */
class Coach {
private:
    Strategy* currentStrategy; ///< Stratégie actuelle appliquée par le coach.

public:
    Coach(); ///< Constructeur par défaut.

    /**
     * @brief Définit la stratégie actuelle.
     * @param strategy Pointeur vers la stratégie.
     */
    void SetStrategy(Strategy* strategy);

    /**
     * @brief Applique la stratégie actuelle.
     */
    void ApplyStrategy();

    /**
     * @brief Observe l'état d'un joueur.
     * @param player Joueur à observer.
     */
    void ObservePlayer(const Player& player);
};

/**
 * @brief Classe abstraite pour les composants dans le Pattern Composite.
 */
class TeamComponent {
public:
    virtual ~TeamComponent() = default;

    /**
     * @brief Affiche les informations sur le composant.
     */
    virtual void Display() const = 0;
};

/**
 * @brief Classe représentant un joueur individuel dans une équipe.
 */
class PlayerLeaf : public TeamComponent {
private:
    Player* player; ///< Pointeur vers le joueur.

public:
    explicit PlayerLeaf(Player* p); ///< Constructeur.

    /**
     * @brief Affiche les informations du joueur.
     */
    void Display() const override;
};

/**
 * @brief Classe représentant une équipe composée de joueurs ou de sous-équipes.
 */
class TeamComposite : public TeamComponent {
private:
    std::vector<TeamComponent*> components; ///< Liste des composants (joueurs ou sous-équipes).

public:
    /**
     * @brief Ajoute un composant à l'équipe.
     * @param component Pointeur vers le composant.
     */
    void Add(TeamComponent* component);

    /**
     * @brief Retire un composant de l'équipe.
     * @param component Pointeur vers le composant.
     */
    void Remove(TeamComponent* component);

    /**
     * @brief Affiche les informations de l'équipe.
     */
    void Display() const override;
};

#endif // BASKET_HPP
