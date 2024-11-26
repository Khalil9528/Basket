import numpy as np
import matplotlib.pyplot as plt

def R_matrice(L, p):
    r = np.random.rand(L, L)
    R = np.zeros((L, L))
    for i in range(L):
        for j in range(L):
            if r[i, j] <= p:
                R[i, j] = 1
    return R

def Above_left(i, j, R):
    """
    Vérifie les voisins "au-dessus" et "à gauche" d'une cellule (i, j).
    Retourne leurs valeurs si elles existent, sinon 0.
    """
    above = R[i - 1, j] if i > 0 else 0
    left = R[i, j - 1] if j > 0 else 0
    return above, left

def Find(label, i, j, i1, j1, L):
    """
    Trouve le label correct dans le cas où deux amas sont connectés.
    Implémente un algorithme de compression de chemins pour fusionner les labels.
    """
    # On parcourt les labels jusqu'à trouver la racine
    while label[i, j] != label[int(i), int(j)]:
        i, j = int(i1), int(j1)
    return label

def Label(L, p):
    """
    Crée la matrice des amas en identifiant les regroupements de 1.
    """
    R = R_matrice(L, p)
    label = np.zeros((L, L), dtype=int)
    iD = 1  # Premier identifiant pour les amas

    for i in range(L):
        for j in range(L):
            if R[i, j]:  # Si la cellule fait partie d'un amas
                above, left = Above_left(i, j, label)

                if left == 0 and above == 0:
                    # Nouveau label pour un nouvel amas
                    label[i, j] = iD
                    iD += 1
                elif left != 0 and above == 0:
                    # Hérite du label à gauche
                    label[i, j] = left
                elif left == 0 and above != 0:
                    # Hérite du label au-dessus
                    label[i, j] = above
                else:
                    # Fusionne les amas
                    Lab_prim = Find(label, i, j - 1, i - 1, j, L)
                    label[i, j] = Lab_prim
                    label[i, j] = above

    return label

def plot_matrix(matrix, title):
    """
    Affiche une matrice sous forme de graphique.
    """
    plt.imshow(matrix, cmap='viridis', origin='upper')
    plt.colorbar()
    plt.title(title)
    plt.show()

# Exemple d'utilisation
if __name__ == "__main__":
    L = 5  # Taille de la matrice
    p = 0.3  # Probabilité de 1

    matrice_R = R_matrice(L, p)
    plot_matrix(matrice_R, "Matrice R (uns et zéros)")

    matrice_label = Label(L, p)
    plot_matrix(matrice_label, "Matrice des amas")
