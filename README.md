## Utilisation:
```Makefile
# Compile le projet
make
# Ouvre Minishell
./minishell
```

## Caractères / Signaux:
```C
| // Pipe
' // Single quote
" // Double quote
$VAR // Variables d'environnement
$?  // Sortie de pipeline
ctrl-C
ctrl-D
ctrl-\
```

## Ré-implémentation des builtins:
```
echo [-n]
cd
pwd
export
unset
env
exit
```
## Autres builtins
Pour une commande `ls` par exemple, le programme iras chercher dans les sous-dossiers accueillant des binaires, par examples `/bin` ect..
```Makefile
execve()
```
