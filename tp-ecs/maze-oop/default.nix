
{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "maze-oop";

  src = ./.;

  nativeBuildInputs = with pkgs; [
    cmake
    sfml
  ];
}

