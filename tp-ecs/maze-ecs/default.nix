
{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "maze-ecs";
  src = ./.;
  buildInputs = with pkgs; [
    cmake
    sfml
    (callPackage ./flecs.nix {})
  ];

}

