# prevus
Répositoire qui contient le code du microcontrôleur Atmel.

## Logiciel

Pour utiliser/modifier/tester le code, il faut installer le logiciel Atmel Studio 7: http://www.microchip.com/mplab/avr-support/atmel-studio-7

Des tutoriels sont disponibles ici: https://eewiki.net/display/Wireless/ATmega256RFR2+Xplained+Pro

## Branches

Pour essayer de garder le tout fluide, on va essayer de se fixer ces guidelines:

	- La branche _master_ contient du code toujours fonctionnel. On doit valider le code avant de l'intégrer à cette branche (voir Airtable).
	- On crée une autre branche avec un nom adéquat pour travailler sur un nouveau feature. On essaye de créer UNE branche PAR feature pour être cohérent.

# Guide de compilation

Pour compiler et programmer un microcontrôleur, il faut suivre les étapes suivantes:

 * Brancher le microcontrôleur à l'aide du câble USB
 * Démarrer Atmel Studio 7
 * Fichier->Ouvrir->Projet/Solution
 * Sélectionner le fichier C:\Users\louis\Desktop\prevus\prevus\URUBUS\URUBUS\URUBUS\astudio\URUBUS.atsln
 * Debug->URUBUS Properties, puis Tool
 * Choisir EDBG - ATMLxxxxxxx en fonction du microcontrôleur qu'on souhaite programmer.
 * Build URUBUS ou Solution (F7)
 * Run without debugging (CTRL-ALT-F5)
 
Voilà!