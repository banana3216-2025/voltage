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

      mingwPkgs = pkgs.pkgsCross.mingwW64;
    in {
      devShells = {
        default = pkgs.mkShell {
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
            echo "=== Voltage Engine Native Linux Dev Shell Active ==="
          '';
        };

        # WINDOWS SHELL: Cross-compilation & Wine Testing
        windows = pkgs.mkShell {
          nativeBuildInputs = [
            mingwPkgs.buildPackages.gcc
            mingwPkgs.buildPackages.cmake
            pkgs.gnumake
            pkgs.wineWow64Packages.stable
          ];

          buildInputs = [
            mingwPkgs.windows.pthreads
          ];

          shellHook = ''
            export VULKAN_SDK="$PWD/vulkan_windows_sdk"

            export WINEARCH="win64"
            export WINEPREFIX="$HOME/.wine_wow64_voltage"

            # Simple alias helpers to streamline your iteration
            alias build-win="cd ~/Projects/voltage/build-windows && rm -rf * && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake .. && cmake --build ."
            alias run-win="wine ~/Projects/voltage/bin/testbed.exe"

            echo "=== Voltage Engine Windows Cross-Compile Shell Active ==="
            echo "Available Shortcuts:"
            echo "  build-win : Flush, re-configure, and compile the Windows targets"
            echo "  run-win   : Instantly launch your testbed.exe executable using Wine"
          '';
        };
      };
    });
}
