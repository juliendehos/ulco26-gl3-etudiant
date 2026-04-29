
{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "test-ecs";
  src = ./.;
  buildInputs = with pkgs; [
    cmake
    (callPackage ./flecs.nix {})
  ];
}

