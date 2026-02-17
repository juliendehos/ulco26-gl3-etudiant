{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "paint";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    pkg-config
    gtkmm4
  ];

}


