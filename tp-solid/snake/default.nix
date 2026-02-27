{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "snake";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    sfml
  ];

}


