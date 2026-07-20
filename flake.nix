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
          cmake

          gnumake
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
          libXdmcp
          libxkbcommon
          vulkan-loader
          vulkan-headers
        ];
        hardeningDisable = ["fortify"];

        shellHook = ''
          export VULKAN_SDK="${pkgs.vulkan-headers}"
          export LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib:${pkgs.libxkbcommon}/lib:${pkgs.libx11}/lib:${pkgs.libxcb}/lib:$LD_LIBRARY_PATH"

          echo "=== Voltage Engine Flake Dev Shell Active ==="
        '';
      };
    });
}
