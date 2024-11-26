#ifndef BASKET_HPP
#define BASKET_HPP

#include <string>
#include <vector>
#include <map>
#include <cmath>

struct Position {
    float x;
    float y;

    float distance_to(const Position& other);
};

class Terrain {
public:
    Ballon ballon;
    Agent Players[10];
    float largeur;
    float longueur;

    /// @brief verify the position
    /// @param pos the positon to verify
    /// @return true if the position is valid and false if it's not
    bool verifier_position(const Position& pos);
};

class Agent;

class Ballon {
public:
    Position position;
    float vitesse;
    Agent* possesseur;
    Terrain Terrain;
    
    /// @brief this method attribut a possesseur to the ball after calculating the distance between the ball and all the players 
    /// @param possesseur the player that own the ball
    void possesseur_actuel(Agent* possesseur);

    /// @brief 
    /// @param destination 
    void deplacer(const Position& destination);

    /// @brief 
    /// @param nouveau_possesseur 
    void changer_possesseur(Agent* nouveau_possesseur);
};

class Agent {
public:
    Position position;
    float vitesse;
    float endurance;
    bool possede_balle;

    virtual void se_deplacer(const Position& destination);
    virtual void analyser_environnement();
    virtual void prendre_decision();
};

class JoueurRouge : public Agent {
public:
    std::string role;
    float precision_tir;

    Position analyser_position_tir(const Position& panier);
    JoueurRouge* chercher_passe(const std::vector<JoueurRouge*>& coequipiers);
    void action(const std::vector<JoueurRouge*>& coequipiers, const std::vector<Agent*>& adversaires);
};

class JoueurBleu : public Agent {
public:
    std::string role;
    float capacite_defense;
    std::map<std::string, float> apprentissage;

    JoueurRouge* analyser_attaque(const std::vector<JoueurRouge*>& attaquants);
    void optimiser_defense(const JoueurRouge* attaquant);
    void action(const std::vector<JoueurBleu*>& coequipiers, const std::vector<JoueurRouge*>& adversaires);
};

class Equipe {
public:
    std::string nom;
    std::string couleur;
    int score;
    std::vector<Agent*> joueurs;

    void calculer_score();
    void ajuster_strategie();
    void gerer_formation();
};

class Environnement {
public:
    int largeur;
    int hauteur;
    Ballon ballon;
    std::vector<Terrain> Terrains;
    std::vector<Equipe> equipes;

    void verifier_collisions();
    void mettre_a_jour();
    void gerer_score();
};

#endif // BASKET_HPP
