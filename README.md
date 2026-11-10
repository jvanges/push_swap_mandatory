*This project has been created as part of the 42 curriculum by jvan-ges, anaubare.*

## Description

`push_swap` trie une liste d'entiers distincts avec deux piles et un vocabulaire
limité d'instructions. Le programme reçoit la pile **a** en argument, le premier
entier étant son sommet, puis écrit sur la sortie standard une suite
d'opérations qui la trie par ordre croissant. La pile **b** est initialement vide.

Le programme embarque les quatre stratégies exigées :

- **Simple**, en `O(n²)` : extraction successive du minimum ;
- **Medium**, en `O(n√n)` : découpage en blocs de rangs ;
- **Complex**, en `O(n log n)` : radix LSD binaire ;
- **Adaptive**, le comportement par défaut : choix d'une stratégie selon le
  désordre mesuré avant toute opération.

Les entiers sont convertis en rangs de `0` à `n - 1`. Cette normalisation
préserve leur ordre, simplifie les algorithmes et gère les valeurs négatives
sans modifier la sémantique du tri.

## Contributions

Le travail a été réparti de manière égale entre les deux membres du binôme.
Chacun a contribué à hauteur de 50 % au projet et doit pouvoir expliquer
l'intégralité du code pendant la soutenance.

| Membre | Contribution |
|---|---|
| `jvan-ges` | Contribution égale au projet : 50 % |
| `anaubare` | Contribution égale au projet : 50 % |

## Instructions

### Compilation

```sh
make
```

Le Makefile utilise `cc -Wall -Wextra -Werror` et fournit les règles `all`,
`clean`, `fclean` et `re`. Aucune bibliothèque externe n'est nécessaire.

```sh
make clean    # supprime les fichiers objets
make fclean   # supprime aussi le binaire
make re       # recompile entièrement
```

### Exécution

```sh
./push_swap 2 1 3 6 5 8
./push_swap "4 67 3 87 23"
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

Les espaces, tabulations et retours à la ligne peuvent séparer plusieurs entiers
dans un même argument. Un argument vide, un entier invalide, un dépassement de
la plage `int`, un doublon, un drapeau inconnu ou plusieurs sélecteurs de
stratégie provoquent `Error\n` sur la sortie d'erreur.

Sans argument, ou avec un seul entier déjà trié, aucune opération n'est écrite.
Les instructions sont toujours séparées par un unique `\n`, sans texte
supplémentaire sur la sortie standard.

### Mode benchmark

`--bench` peut être combiné avec n'importe quel sélecteur :

```sh
./push_swap --bench --adaptive 2 1 3 6 5 8 >/dev/null
./push_swap --bench --complex 2 1 3 6 5 8 2>bench.txt >/dev/null
```

Les métriques sont envoyées uniquement sur **stderr** : désordre en pourcentage
avec deux décimales, stratégie interne et classe de complexité, total et nombre
d'occurrences de chacune des onze opérations.

Exemple de début de sortie :

```text
[bench] disorder: 13.33%
[bench] strategy: Complex (O(n*log(n)))
[bench] total operations: 29
[bench] sa: 0
```

## Algorithmes et complexité

Toutes les complexités ci-dessous mesurent le **nombre d'instructions
Push_swap générées**, comme demandé par le sujet. Les rotations sont comptées
individuellement, même lorsque leur coût C sur le tableau est linéaire.

### Métrique de désordre

Le désordre est le nombre d'inversions divisé par le nombre de paires :

```text
disorder = |{(i, j) : i < j et a[i] > a[j]}| / (n(n - 1) / 2)
```

Pour moins de deux éléments, il vaut zéro. Il est calculé sur les valeurs
originales, avant la normalisation et avant la première instruction.

### Simple — `O(n²)`

Pour chaque rang cible croissant, l'algorithme recherche sa position dans **a**,
l'amène au sommet par le plus court des deux sens de rotation, puis exécute `pb`.
Lorsque tous les rangs sont dans **b**, `n` instructions `pa` reconstruisent **a**
par ordre croissant.

À l'étape de taille `m`, il y a au plus `m / 2` rotations et un `pb`. La somme
pour `m = 1…n`, suivie de `n` instructions `pa`, est majorée par `O(n²)`. Une
entrée déjà triée est détectée et ne produit aucune opération.

### Medium — `O(n√n)`

Les rangs sont divisés en blocs de taille `k = floor(5 * sqrt(n) / 2)`, donc
`k = Θ(√n)`. Pour chaque bloc croissant :

1. parcourir une fois toutes les valeurs non encore triées ; `pb` isole une
   valeur du bloc et `ra` conserve une autre valeur dans **a** ;
2. restaurer, par le sens le plus court, les valeurs restantes au-dessus des
   blocs déjà terminés ;
3. extraire les maxima du bloc depuis **b** avec au plus `k / 2` rotations par
   maximum, puis les remettre dans **a** avec `pa` ;
4. effectuer `k` rotations `ra` pour concaténer le bloc trié aux précédents.

Les phases 1 et 2 coûtent au total `O(n²/k)` sur tous les blocs. La phase 3
coûte `O(k²)` par bloc, soit `O(nk)` au total, et la phase 4 coûte `O(n)`. Avec
`k = Θ(√n)`, la borne est donc `O(n√n)`. Le facteur constant `5/2` ne change pas
la classe ; il réduit le nombre de rotations observé expérimentalement.

### Complex — `O(n log n)`

Le radix LSD binaire effectue un passage stable par bit des rangs. Pendant un
passage, chacun des `n` éléments donne un `pb` si son bit vaut zéro, sinon un
`ra`. Tous les éléments de **b** reviennent ensuite dans **a** avec `pa`.

Il y a `ceil(log2(n))` passages pour les rangs `0…n - 1` (zéro passage pour une
pile de taille un). Chaque passage produit au plus `2n` opérations, ce qui donne
une borne `O(n log n)`. La stabilité des passages garantit le tri lexicographique
des bits, donc l'ordre final des rangs.

### Adaptive — choix par le désordre

Les seuils sont ceux imposés par le sujet, et non des seuils appris sur un jeu
de tests :

| Désordre | Méthode interne | Borne en opérations |
|---|---|---|
| `< 0.2` | Simple | `O(n²)` |
| `>= 0.2` et `< 0.5` | Medium | `O(n√n)` |
| `>= 0.5` | Complex | `O(n log n)` |

Une faible densité d'inversions rend l'extraction des minima économique. Dans le
régime intermédiaire, les blocs bornent le coût des recherches. Pour un désordre
élevé, le radix évite le comportement quadratique. Le calcul du désordre ne
génère aucune opération et ne modifie donc pas la borne dans le modèle retenu.

### Espace

Les deux tableaux de piles contiennent au plus `n` entiers chacun. Le parsing et
la normalisation utilisent également `O(n)` espace ; les tableaux temporaires
sont libérés. Les quatre stratégies et le mode adaptatif occupent donc `O(n)`
espace, sans variable globale. Toutes les allocations encore possédées sont
libérées avant chaque sortie du programme.

## Performance

Objectifs du sujet pour le comportement par défaut :

| Taille | Minimum | Good | Excellent |
|---|---:|---:|---:|
| 100 valeurs | `< 2000` | `< 1500` | `< 700` |
| 500 valeurs | `< 12000` | `< 8000` | `< 5500` |

Le choix dépend du désordre ; le nombre d'opérations d'une entrée particulière
peut donc différer de la moyenne d'entrées uniformément aléatoires.

## Resources

- Sujet `Push_swap`, version 1.2 : règles, opérations, métrique de désordre,
  sélecteurs, benchmark et objectifs de performance.
- Donald E. Knuth, *The Art of Computer Programming*, volume 3, *Sorting and
  Searching* : tris par sélection, distribution et radix.
- Thomas H. Cormen et al., *Introduction to Algorithms* : inversions, bornes de
  complexité, stabilité et tri radix.
- Documentation C du langage et des fonctions `malloc`, `free` et `write` pour
  la gestion mémoire et les descripteurs de fichiers.

### Utilisation de l'IA

L'intelligence artificielle a été utilisée pour écrire le code conforme à la Norme 42, ainsi que pour rédiger ce README.
