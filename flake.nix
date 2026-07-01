{
  description = "IRG";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { utils, nixpkgs, ... }:
    utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            meson
            ninja
            cmake
            pkg-config
            clang-tools
          ];

          buildInputs = with pkgs; [
            libx11
            libxrandr
            libxinerama
            libxcursor
            libxi
            libGL
          ];

        };
      }
    );
}
