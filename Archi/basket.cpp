#include "basket.hpp"


float Position::distance_to(const Position &other)
{
    return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2));

}

bool Terrain::verifier_position(const Position &pos)
{
    if(abs(pos.x) < this->largeur  &&   abs(pos.y) < this->longueur){
        return true ;
    }
    return false;
}

void Ballon::possesseur_actuel(Agent *possesseur)
{
    int min = this->position.distance_to(this->Terrain.Players[0]);
    possesseur = this->Terrain.Players[0];
    for(int i = 1; i < 10 ; i++){
        if(this->position.distance_to(this->Terrain.Players[i]) < min){
            possesseur = this->Terrain.Players[i];
        }
    }
}

void Ballon::deplacer(const Position &destination)
{
    
}

void Ballon::changer_possesseur(Agent *nouveau_possesseur)
{
}

void Agent::se_deplacer(const Position &destination)
{
}

void Agent::analyser_environnement()
{
}

void Agent::prendre_decision()
{
}

Position JoueurRouge::analyser_position_tir(const Position &panier)
{
    return Position();
}

JoueurRouge *JoueurRouge::chercher_passe(const std::vector<JoueurRouge *> &coequipiers)
{
    return nullptr;
}

void JoueurRouge::action(const std::vector<JoueurRouge *> &coequipiers, const std::vector<Agent *> &adversaires)
{
}

JoueurRouge *JoueurBleu::analyser_attaque(const std::vector<JoueurRouge *> &attaquants)
{
    return nullptr;
}

void JoueurBleu::optimiser_defense(const JoueurRouge *attaquant)
{
}

void JoueurBleu::action(const std::vector<JoueurBleu *> &coequipiers, const std::vector<JoueurRouge *> &adversaires)
{
}

void Equipe::calculer_score()
{
}

void Equipe::ajuster_strategie()
{
}

void Equipe::gerer_formation()
{
}

void Environnement::verifier_collisions()
{
}

void Environnement::mettre_a_jour()
{
}

void Environnement::gerer_score()
{
}
