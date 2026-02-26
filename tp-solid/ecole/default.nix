{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "ecole";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
  ];

}


