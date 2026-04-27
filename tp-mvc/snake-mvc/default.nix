{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "snake";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    pkg-config
    gtkmm4
    sfml
  ];

}


