{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "connect4";
  src = ./.;

  buildInputs = with pkgs; [
    catch2_3
    cmake
    gtkmm4
    pkg-config
  ];

}

