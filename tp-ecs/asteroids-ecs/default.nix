
{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "asteroids-ecs";
  src = ./.;
  buildInputs = with pkgs; [
    cmake
    sfml
    (callPackage ./flecs.nix {})
  ];

}

