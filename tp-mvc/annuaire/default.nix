{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "annuaire";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
    (libhv.overrideDerivation (attrs: { cmakeFlags = []; }))
  ];

}


