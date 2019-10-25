#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/wastake.png
ICON_DST=../../src/qt/res/icons/wastake.ico
convert ${ICON_SRC} -resize 16x16 wastake-16.png
convert ${ICON_SRC} -resize 32x32 wastake-32.png
convert ${ICON_SRC} -resize 48x48 wastake-48.png
convert wastake-16.png wastake-32.png wastake-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/wastake_testnet.png
ICON_DST=../../src/qt/res/icons/wastake_testnet.ico
convert ${ICON_SRC} -resize 16x16 wastake-16.png
convert ${ICON_SRC} -resize 32x32 wastake-32.png
convert ${ICON_SRC} -resize 48x48 wastake-48.png
convert wastake-16.png wastake-32.png wastake-48.png ${ICON_DST}
rm wastake-16.png wastake-32.png wastake-48.png
