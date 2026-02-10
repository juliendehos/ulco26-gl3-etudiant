{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "hello-sfml";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    sfml
  ];

}


