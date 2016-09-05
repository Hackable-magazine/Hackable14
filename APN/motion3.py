#!/usr/bin/python
# -*- coding: utf-8 -*-

# modules
from subprocess import check_output
import os, signal, time, sys
import RPi.GPIO as GPIO

# Fonction pour quitter avec CTRL+C
def quitter(sig, frame):
    print "On quitte !"
    # Arrêt de gPhoto
    os.kill(gphotopid, signal.SIGTERM)
    # On quitte
    sys.exit()

# Déclenchement gPhoto
def detection(channel):
    # Obtention de l'heure système
    localtime = time.strftime('%x %X')
    # Affichage du message de capture
    print localtime,"- Mouvement Détecté ! Envoi SIGUSR1 à", gphotopid
    # Envoi du signal à gPhoto
    os.kill(gphotopid, signal.SIGUSR1)

# Configuration de la broche
GPIO.setmode(GPIO.BOARD)
GPIO.setup(40, GPIO.IN)

# Recherche du processus gPhoto en mémoire
try:
    gphotopid = int(check_output(["pidof","gphoto2"]))
except Exception:
    print "Pas de PID gPhoto trouvé"
    sys.exit()

# Prêt à travailler
print "gPhoto présent. PID = ", gphotopid

# Installation du gestionnaire pour CTRL+C
signal.signal(signal.SIGINT, quitter)

# Installation de la gestion de changement d'état
GPIO.add_event_detect(40, GPIO.RISING, callback=detection)

# Message
print "En attente de détection..."

# Boucle sans fin
while True:
    time.sleep(10)
