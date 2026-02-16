{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "mul2";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    pkg-config
    gtkmm4
  ];

}


