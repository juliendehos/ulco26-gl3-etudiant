
{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "flecs";
  src = pkgs.fetchFromGitHub {
    owner = "SanderMertens";
    repo = "flecs";
    rev = "v4.1.5";
    sha256 = "sha256-FqYIXpbYYRFEUL9enK+BWhuHIgvzO3dc2cd5CTYveag=";
  };
  nativeBuildInputs = with pkgs; [
    cmake
  ];
}

