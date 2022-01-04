#! /bin/ bash
sudo apt-get update

sudo gcc -Wall ETD.c -o ETD -lm

chmod +x ETD.c

./ETD
