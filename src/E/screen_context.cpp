#include <E/screen_context.hpp>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

E::ScreenContext::ScreenContext(E::Camera *cam, GLFWwindow *window) : camera(cam) {
  ImGui_ImplGlfwGL3_Init(window, false);
  ImGuiIO& io = ImGui::GetIO();

  io.MouseDrawCursor = true;
}

void E::ScreenContext::preFrame() {
  ImGui_ImplGlfwGL3_NewFrame();
}

void E::ScreenContext::render(RenderManager *renderer) {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer->preRender();
  renderer->render(view());

  ImGui::Render();
}

E::View E::ScreenContext::view() {
  return View(camera->projectionMatrix() * camera->viewMatrix());
}
