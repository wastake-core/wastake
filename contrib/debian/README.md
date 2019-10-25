
Debian
====================
This directory contains files used to package wastaked/wastake-qt
for Debian-based Linux systems. If you compile wastaked/wastake-qt yourself, there are some useful files here.

## wastake: URI support ##


wastake-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install wastake-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your wastakeqt binary to `/usr/bin`
and the `../../share/pixmaps/wastake128.png` to `/usr/share/pixmaps`

wastake-qt.protocol (KDE)
