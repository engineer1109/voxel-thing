#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <shader.hpp>
#include <utils.hpp>
#include <data.hpp>

const float SCREEN_WIDTH=800.0f;
const float SCREEN_HEIGHT=600.0f;

float lastTime;
float deltaTime;

float cameraSpeed = 5.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

double lastMouseX = SCREEN_WIDTH/2;
double lastMouseY = SCREEN_HEIGHT/2;

float pitch = 0;
float yaw = 0;

bool firstMouse = false;

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * deltaTime * cameraFront;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * deltaTime * cameraFront;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
  }
}

void mouseCallback(GLFWwindow *window, double x, double y) {
  if (firstMouse) {
    lastMouseX = x;
    lastMouseY = y;

    firstMouse = false;
  }

  double xOffset = lastMouseX - x;
  double yOffset = lastMouseY - y;

  double sensitivity = 0.5;

  yaw  -= xOffset * sensitivity;
  pitch += yOffset * sensitivity;

  pitch = clamp(pitch, -45.0f, 90.0f);

  glm::vec3 front;

  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  cameraFront = glm::normalize(front);

  lastMouseX = x;
  lastMouseY = y;
}

int main(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();

    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialise GLAD" << std::endl;

    return -1;
  }

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);

  Shader def("shaders/default.vs", "shaders/default.fs");
  def.use();

  stbi_set_flip_vertically_on_load(true);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nChannels;
  unsigned char* data = stbi_load("img/dirt.jpg", &width, &height, &nChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load image" << std::endl;

    return -1;
  }

  stbi_image_free(data);

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glm::vec3 cubes[] = {
      glm::vec3(0.0f, -2.0f, -3.0f),
      glm::vec3(1.0f, -2.0f, -3.0f),
      glm::vec3(-1.0f, -2.0f, -3.0f),
      glm::vec3(0.0f, -2.0f, -4.0f),
      glm::vec3(1.0f, -2.0f, -4.0f),
      glm::vec3(-1.0f, -2.0f, -4.0f),
      glm::vec3(0.0f, -2.0f, -5.0f),
      glm::vec3(1.0f, -2.0f, -5.0f),
      glm::vec3(-1.0f, -2.0f, -5.0f),
      glm::vec3(0.0f, -2.0f, -6.0f),
      glm::vec3(1.0f, -2.0f, -6.0f),
      glm::vec3(-1.0f, -2.0f, -6.0f),
      glm::vec3(0.0f, -2.0f, -7.0f),
      glm::vec3(1.0f, -2.0f, -7.0f),
      glm::vec3(-1.0f, -1.0f, -7.0f)
  };

  while (!glfwWindowShouldClose(window)) {
    deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    processInput(window);

    glClearColor(rgbToGl(49), rgbToGl(198), rgbToGl(247), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

    def.setMatrix("view", glm::value_ptr(view));
    def.setMatrix("projection", glm::value_ptr(projection));

    for(unsigned int i = 0; i < 15; i++) {
        glm::mat4 model;
        model = glm::translate(model, cubes[i]);

        def.setMatrix("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();

  return 0;
}
