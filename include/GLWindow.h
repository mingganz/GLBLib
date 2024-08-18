#pragma once

#include "GLCommon.h"

namespace glb {

    class GLB_API Window
    {
    public:
        static Window& GetInstance(int width, int height, std::string name) {
            static Window instance(width, height, name);
            return instance;
        }

        Window(Window const&) = delete;            // Disallow copy
        void operator=(Window const&) = delete;      // Disallow asign
        ~Window() { ShutDown(), glfwTerminate(); }

        inline int IsExist() const { return m_isExist; }
        inline int IsOpen() const { return glfwWindowShouldClose(m_window) == GL_FALSE; }
        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }

        inline void SetSwapInterval(int interval) const { glfwSwapInterval(1); }
        inline void SetTitle(std::string title) const { glfwSetWindowTitle(m_window, title.c_str()); }
        inline void PollEvents() const { glfwPollEvents(); }
        inline void SwapBuffers() const { glfwSwapBuffers(m_window); }

        inline GLFWwindow* GetWindow() { return m_window; }

        void ShutDown()
        {
            m_isExist = false;
            glfwSetWindowShouldClose(m_window, GL_TRUE);
        }

    private:
        Window(int width, int height, std::string title);
        static void GLLogMessageCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const void* userParam);

    private:
        GLFWwindow* m_window;
        int m_width, m_height;
        float m_aspectRatio;
        std::string m_title;
        bool m_isExist;
    };

}