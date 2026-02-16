{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "hello-gtkmm";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    pkg-config
    gtkmm4
  ];

}


