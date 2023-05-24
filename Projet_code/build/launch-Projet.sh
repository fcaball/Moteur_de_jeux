#!/bin/sh
bindir=$(pwd)
cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/Projet/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/Projet 
	else
		"/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/Projet"  
	fi
else
	"/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/Projet"  
fi
