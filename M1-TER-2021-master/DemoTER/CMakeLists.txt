#CMakeLists DemoTER
project(DemoTER)
cmake_minimum_required(VERSION 3.8.2)

set(RESOURCES_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/")
# set(RESOURCES_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/resources/")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include/")

#Configure config.hpp.in
configure_file(
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp @ONLY
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include BEFORE)

set(SRC
	${SRC_DIR}/CheckError.cpp

	${SRC_DIR}/glwrapper/Display.cpp
	${SRC_DIR}/glwrapper/Shader.cpp
	${SRC_DIR}/glwrapper/VBO.cpp
	${SRC_DIR}/glwrapper/VAO.cpp
	${SRC_DIR}/glwrapper/TexBuffer.cpp
	${SRC_DIR}/glwrapper/Texture.cpp
	${SRC_DIR}/glwrapper/CubeMapTexture.cpp
	${SRC_DIR}/glwrapper/FrameBuffer.cpp
	${SRC_DIR}/glwrapper/DepthTexture.cpp
	${SRC_DIR}/glwrapper/MSTexture.cpp
	${SRC_DIR}/glwrapper/MSDepthTexture.cpp

	${SRC_DIR}/utils/Camera.cpp
	${SRC_DIR}/utils/OrbitCamera.cpp
	${SRC_DIR}/utils/Mouse.cpp
	${SRC_DIR}/utils/Transform.cpp
	${SRC_DIR}/utils/Parser.cpp

	${SRC_DIR}/Mesh.cpp
	${SRC_DIR}/PBRShader.cpp
	${SRC_DIR}/SkyboxShader.cpp
	${SRC_DIR}/Environment.cpp
	${SRC_DIR}/GuiParams.cpp
	${SRC_DIR}/Materials.cpp
	${SRC_DIR}/FlatShader.cpp
	${SRC_DIR}/LightsSet.cpp
	${SRC_DIR}/BloomFilter.cpp
	${SRC_DIR}/MergeShader.cpp
	${SRC_DIR}/GuiDrawFunctions.cpp
	${SRC_DIR}/main.cpp
)


set(HEADER
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/CheckError.hpp

	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/Display.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/Shader.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/VBO.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/VAO.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/TexBuffer.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/Texture.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/CubeMapTexture.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/FrameBuffer.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/DepthTexture.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/MSTexture.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwrapper/MSDepthTexture.hpp

	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/Camera.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/OrbitCamera.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/Mouse.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/Transform.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/Parser.hpp
	

	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Mesh.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/PBRShader.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/SkyboxShader.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Environment.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/GuiParams.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Materials.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/FlatShader.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/LightsSet.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BloomFilter.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/MergeShader.hpp
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/GuiDrawFunctions.hpp
)

set(RESOURCE_FILES	
	${PROJECT_SOURCE_DIR}/resources/shaders/pbr.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/pbr.vert

	${PROJECT_SOURCE_DIR}/resources/shaders/flat.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/flat.vert

	${PROJECT_SOURCE_DIR}/resources/shaders/skybox.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/skybox.vert

	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom5.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom5.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom9.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom9.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom11.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/bloom11.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/transfer.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/bloom/transfer.vert


	${PROJECT_SOURCE_DIR}/resources/shaders/merge.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/merge.vert

	${PROJECT_SOURCE_DIR}/resources/shaders/env/rectToCube.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/env/rectToCube.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/env/irradiance.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/env/irradiance.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/env/prefilter.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/env/prefilter.vert
	${PROJECT_SOURCE_DIR}/resources/shaders/env/brdf.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/env/brdf.vert
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/resources" PREFIX "Resources Files" FILES ${RESOURCE_FILES})

add_executable(${PROJECT_NAME} ${SRC} ${HEADER} ${RESOURCE_FILES})
include_directories(${INC_DIR} AFTER)

#SET(VS_STARTUP_PROJECT ${EXECUTABLE_NAME})
# set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

#Copy resources
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
	# RUNTIME DESTINATION "bin/${PROJECT_NAME}"
)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/resources
	# DESTINATION "bin/${PROJECT_NAME}"
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Detect and add SFML (don't forghet to defined SFML_ROOT in cmake)
# find_package(SFML 2.5 COMPONENTS main system window graphics audio REQUIRED)
# include_directories(${SFML_INCLUDE_DIR})

# Linking
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} stbimage glad glfw glm imgui)

add_subdirectory(doc)
