# $Id$
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'dmenu' 'rofi' 'alacritty')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h
	dwm.desktop
    startdwm)
sha256sums=('97902e2e007aaeaa3c6e3bed1f81785b817b7413947f1db1d3b62b8da4cd110e'
            'SKIP'
            '90dd949befe46ec76c1d989a5bf99f896ac096810e4f720afea81e914b10f9b3'
            'd3ecee9ee2494349e8fdf614bb758eb1f096f188b16edecd075213fb54059eb9' )

prepare() {
  cd "$srcdir/$pkgname-$pkgver"
  cp "$srcdir/config.h" config.h

  echo -e "\nApplying notitle patch"
  patch -i $startdir/patches/dwm-notitle-6.2.diff
  echo -e "\nApplying flexitile patch"
  patch -i $startdir/patches/dwm-flextile-pertag-cfacts-vanitygaps-grid-centered-6.2.diff
  echo -e "\nApplying systray patch"
  patch -i $startdir/patches/dwm-systray-6.2.diff
  echo -e "\nApplying attachx patch"
  patch -i $startdir/patches/dwm-attachx-6.2.diff
  echo -e "\nApplying movestack patch"
  patch -i $startdir/patches/dwm-movestack-6.2.diff
  echo -e "\nApplying scratchpad patch"
  patch -i $startdir/patches/dwm-scratchpad-6.2.diff
  echo -e "\nApplying zoomswap patch"
  patch -i $startdir/patches/dwm-zoomswap-6.2.diff
  echo -e "\nApplying center patch"
  patch -i $startdir/patches/dwm-center-6.2.diff
}

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
  install -m644 -D "$srcdir/dwm.desktop" "$pkgdir/usr/share/xsessions/dwm.desktop"
  install -m755 -D $startdir/startdwm $pkgdir/usr/bin/startdwm
}
