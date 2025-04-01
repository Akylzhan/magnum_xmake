#include <Corrade/Containers/StaticArray.h>
#include <Corrade/Utility/Resource.h>
#include <Corrade/Utility/Utility.h>
#include <Magnum/GL/AbstractFramebuffer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColorGL.h>

#include <absl/numeric/int128.h>

#include <iostream>

using namespace Magnum;
using namespace Math::Literals;

class MyApplication : public Platform::Sdl2Application {

public:
  explicit MyApplication(const Arguments &arguments)
      : Platform::Sdl2Application(
            arguments, Configuration{}.setTitle("Magnum Triangle Example")) {

    _mesh.setCount(Containers::arraySize(vertices))
        .addVertexBuffer(GL::Buffer{vertices}, 0,
                         Shaders::VertexColorGL2D::Position{},
                         Shaders::VertexColorGL2D::Color3{});
  }

private:
  void drawEvent() override {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    GL::defaultFramebuffer.clearColor(Color3::blue());

    _shader.draw(_mesh);

    swapBuffers();
  }

  GL::Mesh _mesh;
  Shaders::VertexColorGL2D _shader;

  struct TriangleVertex {
    Vector2 position;
    Color3 color;
  };

  const Containers::StaticArray<3, TriangleVertex> vertices = {{
      {{-0.5f, -0.5f}, 0xff0000_rgbf}, /* Left vertex, red color */
      {{0.5f, -0.5f}, 0x00ff00_rgbf},  /* Right vertex, green color */
      {{0.0f, 0.5f}, 0x0000ff_rgbf}    /* Top vertex, blue color */
  }};
};

int main(int argc, char **argv) {
  std::cout << sizeof(absl::uint128) << "\n";

  Utility::Resource rc{"dummy-resource"};
  std::cout << std::string{rc.getString("DummyText.txt")} << "\n";

  MyApplication app({argc, argv});
  // app.setSwapInterval(1); // VSync
  app.exec();
  return 0;
}