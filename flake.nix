{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";

  outputs = { nixpkgs, ... }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem
        ({ pkgs }:
          let
            vk-bootstrap-new = pkgs.stdenv.mkDerivation
              rec {
                pname = "vk-bootstrap";
                version = "1.3.290";
                outputs = [ "out" "dev" ];

                src = pkgs.fetchFromGitHub {
                  owner = "charles-lunarg";
                  repo = "vk-bootstrap";
                  rev = "v${version}";
                  hash = "sha256-ibu+m6NfjB7A1aFPALDmf32sH8yTA551XCmjbTSCwY8=";
                };

                nativeBuildInputs = [ pkgs.cmake ];
                buildInputs = [ pkgs.vulkan-headers pkgs.glfw pkgs.catch2_3 ];

                cmakeFlags = [
                  "-DVK_BOOTSTRAP_TEST=OFF"
                ];

                meta = {
                  description = "Vulkan Bootstrapping Library";
                  homepage = "https://github.com/charles-lunarg/vk-bootstrap";
                };
              };

            imgui-vulkan = pkgs.imgui.override {
              IMGUI_BUILD_VULKAN_BINDING = true;
            };

            common = with pkgs;[
              # C++
              clang-tools
              cmake
              codespell
              conan
              cppcheck
              doxygen
              gtest
              lcov
              vcpkg
              vcpkg-tool

              # vulkan
              vulkan-headers
              vulkan-loader
              vulkan-validation-layers
              vulkan-tools

              # Other tools
              glfw
              imgui-vulkan

              # Helpers
              vk-bootstrap-new
            ];

            scripts = with pkgs; [
              (writeScriptBin "build" ''
                cd build
                make
              '')

              (writeScriptBin "clean" ''
                rm -rf build
                mkdir build
                cd build
                cmake ..
              '')

              (writeScriptBin "start" ''
                ./build/bin/app
              '')
            ];
          in
          {
            default = pkgs.mkShell
              {
                packages = common ++ scripts;
                VULKAN_SDK = "${pkgs.vulkan-headers}";
                LD_LIBRARY_PATH = "${pkgs.vulkan-headers}/lib:${pkgs.vulkan-loader}/lib";
              };
          });
    };
}


