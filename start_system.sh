#!/bin/bash

# Informations pour les logs
APPLI_PATH="/home/pi/appli/"

# Ajout de la variable d'export.
LD_LIBRARY_PATH=/usr/local/lib && export LD_LIBRARY_PATH

# On lance l'initialisation du systeme
cd $APPLI_PATH
cd avionic_blackbox
./blackbox_debug

exit 0
