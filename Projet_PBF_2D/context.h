#ifndef CONTEXT_H
#define CONTEXT_H
#include <unordered_map>
#include <memory>
#include "collider.h"

class Context //Classe pour la représentation du contexte de la simulation.
{

public:

    // Particules simulées

    std::vector<Particle> particles;

    // Colliders simulées

    std::vector<std::unique_ptr<Collider>> colliders;

    // Contraintes statiques résolues

    std::vector<StaticConstraint> staticConstraints;

    // Table de hachage.
    // La struture de données choisie est similaire à un dictionnaire Python.
    // Clé : index de la case (int)
    // Valeur : liste des indices des particules dans la case

    std::unordered_map<int, std::vector<int>> spatialGrid;

    // Intensité de la gravité piloté par un QSlider

    float gravity;

    // Amplitude de déplacement du mur gauche et du mur droit pour
    // la mise en mouvement du fluide. Valeur pilotée par un QSlider

    float amplitude;

    // PARAMETRES DES PARTICULES

    float rayon = 5.0f;
    float masse = 1.0f;

    // PARAMETRES DE SIMULATION

    float cellSize = 3*rayon;       // Pas de maillage de la grille pour la recherche des voisins
    float dt = 0.008f;              // Pas de temps
    float rho_0 = 0.001;            // Densité cible
    float epsilon = 100.0f;         // Paramètre de relaxation pour éviter la division par zéro dans computeLambda()
    int   itr = 0;                  // Compteur d'itération dans la méthode updatePhysicalSystem de la classe Context utilisé
                                    // dans l'argument des fonctions de déplacement du mur gauche et du mur droit.

    // PARAMETRES D'AFFICHAGE

    float height; // Hauteur de la zone d'affichage. Automatiquement gérée par la méthode resizeEvent
    // de la classe DrawArea
    float width;  // Largeur de la zone d'affichage. Automatiquement gérée par la méthode resizeEvent
    // de la classe drawArea

    // PARAMETRES POUR LA PRESSION ARTIFICIELLE

    float k_scorr;     // Piloté par un QSlider. Les auteurs utilisent la valeur 0.1.
    float n_scorr = 4.0f;
    float dq_dist_scorr = 0.2*cellSize;

    // PARAMETRES DE VORTICITE ET DE VISCOSITE

    float c_vorti;    //Valeurs recommandées : 0.01 < c_vorti < 0.1. Ajustable par un QSlider
    float c_visco;    //Valeur recommandée : 0.01 Ajustable par un QSlider

    // CONSTRUCTEUR ET DESTRUCTEUR DE CLASSE

    Context();
    ~Context()=default;

    // LISTE DES METHODES

    void updatePhysicalSystem(float dt);    // Méthode contenant la boucle de simulation
    void resetColliders();                  // Génération des colliders
    void addParticle(float x, float y);     // Ajout d'une particule dans std::vector<Particle> particles
    void addRandomParticles(int count);     // Ajout d'un nombre de particules selon une distribution uniforme dans le plan.

    void setGravity(const float g){gravity = g;};
    void setAmplitude(const float newAmplitude){amplitude = newAmplitude;}
    void setCoeff_Vorti(const float newCoeffVorti){c_vorti = newCoeffVorti;}
    void setCoeff_Visco(const float newCoeffVisco){c_visco = newCoeffVisco;}
    void setK_scorr(const float newK_scorr){k_scorr = newK_scorr;}

    // METHODES POUR LE CALCUL DES NOYAUX

    float computePoly6(float r, float h); // Estimation de la densité
    Vec2 gradW(Vec2 r, float h);          // Calcul du gradient

    //METHODE POUR LA TABLE DE HACHAGE

    void updateGrid();              // Fonction de hachage spatial
    int getHash(int ix, int iy);    // Calcul de la table de hachage

    // METHODES DE LA BOUCLE DE SIMULATION

    // 1. Prédiction
    void applyExternalForce(int i);
    void updateVelocity(float dt, int i);
    void updateExpectedPosition(float dt, int i);

    // 2. MAJ des voisins
    void findNeighbors();

    // 3. Résolution des contraintes
    void addStaticContactConstraints();
    void enforceStaticGroundConstraint(const StaticConstraint& constraint, Particle& p);
    void computeLambdas();
    void computeDeltaPositions();
    void updatePbfPosition(float dt, int i);

    // 4. Intégration finale
    void updateVelocity2(float dt, int i);
    void applyVorticityAndViscosity(float dt);
    void updateFinalPosition(float dt, int i);

};

#endif // CONTEXT_H
