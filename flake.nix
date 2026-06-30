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
          libxkbcommon
          vulkan-loader
          vulkan-headers
        ];
        hardeningDisable = ["fortify"];

        shellHook = ''
          # 2. Expose the Vulkan SDK path for CMake's internal modules
          export VULKAN_SDK="${pkgs.vulkan-headers}"

          # 3. Inform the dynamic linker where the runtime Vulkan loader resides
          export LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib:${pkgs.libxkbcommon}/lib:${pkgs.xorg.libX11}/lib:${pkgs.xorg.libxcb}/lib:$LD_LIBRARY_PATH"

          echo "=== Voltage Engine Flake Dev Shell Active ==="
        '';
      };
    });
}
