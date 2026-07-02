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
        pkgsMusl = import nixpkgs {
          localSystem = system;
          crossSystem = pkgs.lib.systems.examples.musl64;
        };
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

        devShells.musl = pkgsMusl.mkShell {
          nativeBuildInputs = with pkgsMusl; [
            meson
            ninja
            cmake
            pkg-config
          ];

          buildInputs = with pkgsMusl; [
            libx11
            libxrandr
            libxinerama
            libxcursor
            libxi
            libGL
            mesa
          ];

          LIBGL_DRIVERS_PATH = "${pkgsMusl.mesa}/lib/dri";
          LD_LIBRARY_PATH = "${pkgsMusl.mesa}/lib";
        };
      }
    );
}
