#ifndef VR_CONTEXT_H
#define VR_CONTEXT_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <openvr.h>

#include <E/context.hpp>
#include <E/render_manager.hpp>
#include <E/view.hpp>

const int numEyes = 2;
const float nearClip = 0.1f;
const float farClip = 40.0f;

namespace E {
  class VRContext : public Context {
    public:
      void init();
      void preFrame();
      void render(RenderManager *renderer);
      void postFrame();

      unsigned int framebufferWidth;
      unsigned int framebufferHeight;
    private:
      vr::Hmd_Eye eyes[2] = { vr::Eye_Left, vr::Eye_Right };

      unsigned int framebuffers[2];
      unsigned int colorTargets[2];
      unsigned int depthTargets[2];

      vr::IVRSystem *hmd;
      vr::TrackedDevicePose_t trackedDevicePoses[vr::k_unMaxTrackedDeviceCount];

      View viewFor(vr::Hmd_Eye eye);
      void setupEye(int eye);
      std::string getHMDString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = nullptr);
      vr::IVRSystem* VRContext::initOpenVR(unsigned int &hmdWidth, unsigned int &hmdHeight);
  };
};

#endif
