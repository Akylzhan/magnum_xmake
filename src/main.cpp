#include "Magnum/GL/AbstractFramebuffer.h"
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <absl/numeric/int128.h>
#include <iostream>

using namespace Magnum;

class MyApplication : public Platform::Sdl2Application {
public:
  explicit MyApplication(const Arguments &arguments)
      : Platform::Sdl2Application(arguments) {}
  void drawEvent() override {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    GL::defaultFramebuffer.clearColor(Color3::blue());
    swapBuffers();
  }
};

int main(int argc, char **argv) {
  std::cout << sizeof(absl::uint128) << "\n";
  MyApplication app({argc, argv});
  // app.setSwapInterval(1); // VSync
  app.exec();
  return 0;
}