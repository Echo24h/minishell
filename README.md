Utilisation:
```
make
./minishell
```

Les fonctionnalitées:
```
pipe: |
single quote: '
double quote: "
variables d'environnement: $..
statut de sortie pipeline: $?
ctrl-C
ctrl-D
ctrl-\
```

Ré-implémentation des builtins suivants:
```
echo [-n]
cd
pwd
export
unset
env
exit
```
Les autres builtins sont gérés par
```
execve()
```
