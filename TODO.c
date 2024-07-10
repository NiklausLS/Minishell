//======================================================
//Reste à faire :

    //*****************************
    //- signaux
    //- cas exceptionnels $
    //- norminette
    //*****************************

//======================================================

/*
- Il faut remettre la valeur de la variable globale à 0 une fois qu'elle a permis de sortir de la boucle de parsing / filling
- Il faut eventuellement mettre la variable globale à 0 / variable globale = variable globale donc inchangée pour le signal Ctrl-D
- Il faut parser les lignes et les stocker dans la structure
- Il faut remplacer les $
- Il faut effectuer les tests dans le excel --> avec valgrind
- Il faut faire les builtins
- Il faut le mettre à la norme
- Verifier Ctrl-d pendant l'execution et non pas seulement l'entrée donc peut-être un deuxième fork lisant en boucle l'entrée pour vérifier controle d et si fork détecte alors kill le child qui execute et termine le programme ou affiche une nouvelle ligne si ctrl c 
*/

    //gcc -Wall -Werror -Wextra minishell_29.c -lreadline -o minishell
    //valgrind --leak-check=full ./minishell


//=====================================================//
// "  kl | bn|az  "

//"   qs er 'b''n'         p  "

//"     kl >><bn <<> md "md'md" 'po'"

//"<<bn>>'"

//< dsgfdsg'sfgs'"kjkj" "  sqdf'hg" ""''>  sans les <> et avec ou sans l'espace au debut

/*
┌─[parrot@parrot]─[~]
└──╼ $echo $"PATH"
PATH
┌─[parrot@parrot]─[~]
└──╼ $echo "PATH"
PATH
┌─[parrot@parrot]─[~]
└──╼ $echo $"path"
path
┌─[parrot@parrot]─[~]
└──╼ $echo $path

┌─[parrot@parrot]─[~]
└──╼ $echo $PATH
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/home/parrot/.local/bin
*/







//cd Téléchargements/42/moi_minishell
//gcc -Wall -Werror -Wextra minishell_17.c -lreadline -o minishell
//valgrind --leak-check=full ./minishell


//tester lorsque entre une ligne le Ctrl-D et Ctrl-C




/*
j'ai un soucis. Quand l'utilisateur entre
"   qs er 'b''n'         p  "(sans les "") il devrait m'afficher
==============================  FINAL  ==========================
Structure's DATA :

0x4ad7480
DATA: 'qs' bdq: '0' bsq: '0'
NDSC_id : 0x4b1c6b0
NC_ID : (nil)
   ndsc_id

0x4b1c6b0
DATA: 'er' bdq: '0' bsq: '0'
NDSC_id : 0x4b1c7c0
NC_ID : (nil)
   ndsc_id

0x4b1c7c0
DATA: ''b'' bdq: '0' bsq: '2'
NDSC_id : 0x4b1c970
NC_ID : (nil)
   ndsc_id

0x4b1c970
DATA: ''n'' bdq: '0' bsq: '2'
NDSC_id : (0x4b1c971)
NC_ID : (nil)
   nc_id

0x4b1c971
DATA: 'p' bdq: '0' bsq: '2'
NDSC_id : (nil)
NC_ID : (nil)
   nc_id
END Structure DATA
*/