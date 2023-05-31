#!/usr/bin/env bash

cp ./config.def.h ./dwm-6.4/config.h || exit 1

(
  cd dwm-6.4 || exit 1

  make && sudo make install
)
