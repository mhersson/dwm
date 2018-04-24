# $Id$
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.1
pkgrel=3
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'rxvt-unicode' 'dmenu' 'rofi')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h
	dwm.desktop
    startdwm)
md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'SKIP'
         '3a0ce822cb8a841465d629728523bc04'
         '177e2843712827d0fc47845ff1e8121e')

prepare() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  echo -e "\nApplying systray patch"
  patch -i $startdir/patches/dwm-systray-6.1.diff
  echo -e "\nApplying gaplessgrid patch"
  patch -i $startdir/patches/dwm-gaplessgrid-6.1.diff
  echo -e "\nApplying pertag patch"
  patch -i $startdir/patches/dwm-pertag-6.1.diff
  echo -e "\nApplying movestack patch"
  patch -i $startdir/patches/dwm-movestack-6.1.diff
  echo -e "\nApplying rmaster patch"
  patch -i $startdir/patches/dwm-rmaster-6.1.diff
  echo -e "\nApplying columns patch"
  patch -i $startdir/patches/dwm-columns-6.1.diff
  echo -e "\nApplying scratchpad patch"
  patch -i $startdir/patches/dwm-scratchpad-6.1.diff
  echo -e "\nApplying attachabove patch"
  patch -i $startdir/patches/dwm-attachabove-6.1.diff
}

build() {
  cd $srcdir/$pkgname-$pkgver
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
  install -m755 -D $startdir/startdwm $pkgdir/usr/bin/startdwm
}
