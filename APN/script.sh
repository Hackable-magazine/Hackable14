#!/bin/bash

#exit 1

case "$ACTION" in
"init")
  echo ">>> Initialisation"
  ;;
"start")
  echo ">>> Execution des commandes"
  ;;
"download")
  echo ">>> $ARGUMENT a été téléchargé."
  convert $ARGUMENT -geometry 800 -gravity SouthEast \
    -undercolor '#000000B0' -fill white -pointsize 24 -annotate +10+10 \
    " `exif -m -t 0x9003 $ARGUMENT` " petit/$ARGUMENT
  ;;
"stop")
  echo ">>> Traitement gPhoto terminé"
  echo ">>> `ls petit/*.jpg|wc -l` fichiers traité(s) dans petit/"
  ;;
esac
