add_executable(viewer image-viewer.cc)
target_link_libraries(viewer PRIVATE glfw OpenGL::GL glad imgui project_options project_warnings)# Eigen3::Eigen)
