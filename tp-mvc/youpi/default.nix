{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "youpi";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    pkg-config
    gtkmm4
    python3
    (libhv.overrideDerivation (attrs: { cmakeFlags = []; }))
  ];

}

