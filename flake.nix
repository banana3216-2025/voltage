{
  description = "Voltage Game Engine Development Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    utils,
  }:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          pkg-config
          clang
          clang-tools
        ];

        buildInputs = with pkgs; [
          libx11.dev
          libxcomposite
          libxrender
          libxext
          libxcb.dev
          xorgproto
          libxkbcommon
          vulkan-loader
          vulkan-headers
        ];

        shellHook = ''
          # 1. Sync missing header directories for Clang build tracking
          export C_INCLUDE_PATH="${pkgs.xorg.libX11.dev}/include:${pkgs.xorg.xorgproto}/include:${pkgs.xorg.libxcb.dev}/include:${pkgs.libxkbcommon}/include:${pkgs.vulkan-headers}/include:$C_INCLUDE_PATH"
          export CPLUS_INCLUDE_PATH="$C_INCLUDE_PATH:$CPLUS_INCLUDE_PATH"
          export CPATH="$C_INCLUDE_PATH:$CPATH"

          # 2. Prevent NixOS's aggressive compiler wrapper adjustments (Fixes zero-float logs)
          export HARDENING_ENABLE=""
          export NIX_CFLAGS_COMPILE="-Wno-format -Wno-format-security -U_FORTIFY_SOURCE"

          # 3. Dynamic runtime shared object path binding (.so targets)
          export LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib:${pkgs.libxkbcommon}/lib:${pkgs.xorg.libX11}/lib:${pkgs.xorg.libxcb}/lib:$LD_LIBRARY_PATH"

          echo "=== Voltage Engine Flake Dev Shell Active ==="
        '';
      };
    });
}
