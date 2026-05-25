{
  description = "Voltage Development Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        vulkan-headers
        vulkan-loader
        vulkan-tools
        vulkan-validation-layers

        xorg.libX11
        libxkbcommon

        clang
        clang-tools
      ];

      shellHook = ''
        export VK_LAYER_PATH="${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d"
        
        # Define the exact libraries we need to expose
        NIX_LIBS="${pkgs.lib.makeLibraryPath [
          pkgs.vulkan-loader
          pkgs.xorg.libX11
          pkgs.xorg.libxcb
          pkgs.libxkbcommon
        ]}"

        # Fixes runtime discovery (running your compiled app)
        export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$NIX_LIBS"

        # Fixes compile-time linking (resolves the 'cannot find -lxcb' error)
        export LIBRARY_PATH="$LIBRARY_PATH:$NIX_LIBS"
      '';
    };
  };
}
