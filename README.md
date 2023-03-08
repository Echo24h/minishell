Le projet consiste en la recréation d'un shell en C, inspiré de bash, appelé Minishell. Le but est de permettre à l'utilisateur d'exécuter des commandes dans un environnement shell en utilisant des caractères / signaux spéciaux pour réaliser des tâches avancées.

## Utilisation:

Pour utiliser Minishell, il faut d'abord compiler le projet en exécutant `make` dans le répertoire principal. Ensuite, le shell peut être ouvert en exécutant `./minishell`.

## Caractères / Signaux:

Minishell utilise plusieurs caractères et signaux spéciaux pour permettre à l'utilisateur de réaliser des tâches avancées:

* `|` : Pipe
* `'` : Quote simple
* `"` : Quote double
* `$VAR` : Variables d'environnement
* `$?` : Sortie de pipeline
* `ctrl-C` : Interruption de la commande courante
* `ctrl-D` : Fin de l'entrée standard
* `ctrl-\` : Quitter Minishell

## Ré-implémentation des builtins:

Minishell ré-implemente plusieurs des builtins de bash pour fournir des fonctionnalités de base à l'utilisateur:

* `echo [-n]`: Affiche les arguments passés en paramètre, avec ou sans saut de ligne à la fin. Si l'option "-n" est présente, il n'y aura pas de saut de ligne à la fin.
* `cd`: Change le répertoire de travail courant. Si aucun argument n'est passé, il renvoie au répertoire de l'utilisateur. Si un chemin absolu ou relatif est passé en argument, le répertoire de travail est changé pour ce chemin.
* `pwd`: Affiche le chemin absolu du répertoire de travail courant.
* `export`: Définit une variable d'environnement ou modifie sa valeur. Si aucun argument n'est passé, il affiche toutes les variables d'environnement existantes. Si un argument est passé sous la forme VAR=value, la variable VAR est définie ou modifiée avec la valeur spécifiée.
* `unset`: Supprime une variable d'environnement.
* `env` : Affiche toutes les variables d'environnement existantes.
* `exit` : Termine le shell. Si un argument est présent, il est utilisé comme code de sortie.

## Autres builtins

Pour les commandes telles que ls, le programme recherche les fichiers binaires dans les sous-dossiers appropriés tels que `/bin`, etc., en utilisant la fonction `execve()`.

En résumé, Minishell est un projet éducatif visant à améliorer les compétences de programmation en C et à fournir une expérience pratique de l'implémentation d'un shell basique en utilisant les caractères et les signaux spéciaux de bash, ainsi que la ré-implémentation de certains de ses builtins.
