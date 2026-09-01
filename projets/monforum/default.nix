{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "monforum";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    (libhv.overrideDerivation (attrs: { cmakeFlags = []; }))
  ];

}


