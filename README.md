# README

Patched dwm-6.2 build (for Arch Linux)

>If compiling for other distributions: There are changes made in config.h that
>are not applied by the patches, but they are still needed. The
>patch-and-install script is provided as an alternative to the Arch PKGBUILD

## DWM 6.2 with the following patches
* dwm-notitle-6.2.diff
* dwm-flextile-pertag-cfacts-vanitygaps-grid-centered-6.2.diff
* dwm-systray-6.2.diff
* dwm-attachx-6.2.diff
* dwm-movestack-6.2.diff
* dwm-scratchpad-6.2.diff
* dwm-zoomswap-6.2.diff
* dwm-center-6.2.diff

> Some of the patches are modified from their originals to they play nice with
> each other, and they must be applied in the given order.

## Configured dependencies
* alacritty
* rofi
* dmenu
* focusnextwindow from my [window-manager-extensions](https://gitlab.com/mhersson/window-manager-extensions)
