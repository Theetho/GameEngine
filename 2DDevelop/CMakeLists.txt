project(2DDevelop CXX)

################################################################################
# Source groups
################################################################################
set(Noise
    "Noise/FastNoise.cpp"
    "Noise/FastNoise.h"
    "Noise/HeightMap.cpp"
    "Noise/HeightMap.h"
    "Noise/Main.cpp"
    "Noise/NormalMap.cpp"
    "Noise/NormalMap.h"
    "Noise/stb_image.h"
    "Noise/stb_image_write.h"
    "Noise/stbi.cpp"
)
source_group("Noise" FILES ${Noise})

set(UILib
    "UILib/Button.h"
    "UILib/Input.h"
    "UILib/Slider.h"
    "UILib/Table.h"
    "UILib/UIElement.cpp"
    "UILib/UIElement.h"
    "UILib/UILib.h"
    "UILib/Window.cpp"
    "UILib/Window.h"
)
source_group("UILib" FILES ${UILib})

set(ALL_FILES
    ${Noise}
    ${UILib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE 2DDevelop)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "2DDevelop"
    TARGET_NAME_DISTRIBUTION "2DDevelop"
    TARGET_NAME_RELEASE      "2DDevelop"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
    OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
    OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "ENGINE_DEBUG"
    ">"
    "$<$<CONFIG:Distribution>:"
        "ENGINE_DISTRIBUTION"
    ">"
    "$<$<CONFIG:Release>:"
        "ENGINE_RELEASE"
    ">"
    "ENGINE_WINDOWS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Distribution>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /MT;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /MT;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Distribution>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "sfml-main;"
    "sfml-audio;"
    "sfml-window;"
    "sfml-graphics;"
    "sfml-network;"
    "sfml-system"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/x64"
)



























project(2DDevelop CXX)

################################################################################
# Source groups
################################################################################
set(Noise
    "Noise/FastNoise.cpp"
    "Noise/FastNoise.h"
    "Noise/HeightMap.cpp"
    "Noise/HeightMap.h"
    "Noise/Main.cpp"
    "Noise/NormalMap.cpp"
    "Noise/NormalMap.h"
    "Noise/stb_image.h"
    "Noise/stb_image_write.h"
    "Noise/stbi.cpp"
)
source_group("Noise" FILES ${Noise})

set(UILib
    "UILib/Button.h"
    "UILib/Input.h"
    "UILib/Slider.h"
    "UILib/Table.h"
    "UILib/UIElement.cpp"
    "UILib/UIElement.h"
    "UILib/UILib.h"
    "UILib/Window.cpp"
    "UILib/Window.h"
)
source_group("UILib" FILES ${UILib})

set(ALL_FILES
    ${Noise}
    ${UILib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE 2DDevelop)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "2DDevelop"
    TARGET_NAME_DISTRIBUTION "2DDevelop"
    TARGET_NAME_RELEASE      "2DDevelop"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
    OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
    OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "ENGINE_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "ENGINE_RELEASE"
    ">"
    "ENGINE_WINDOWS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Distribution>:
            /Od;
            /MT;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /MT;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Distribution>:
            /DEBUG:FULL;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "sfml-main;"
    "sfml-audio;"
    "sfml-window;"
    "sfml-graphics;"
    "sfml-network;"
    "sfml-system"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/x64"
)



























project(2DDevelop CXX)

################################################################################
# Source groups
################################################################################
set(Noise
    "Noise/FastNoise.cpp"
    "Noise/FastNoise.h"
    "Noise/HeightMap.cpp"
    "Noise/HeightMap.h"
    "Noise/Main.cpp"
    "Noise/NormalMap.cpp"
    "Noise/NormalMap.h"
    "Noise/stb_image.h"
    "Noise/stb_image_write.h"
    "Noise/stbi.cpp"
)
source_group("Noise" FILES ${Noise})

set(UILib
    "UILib/Button.h"
    "UILib/Input.h"
    "UILib/Slider.h"
    "UILib/Table.h"
    "UILib/UIElement.cpp"
    "UILib/UIElement.h"
    "UILib/UILib.h"
    "UILib/Window.cpp"
    "UILib/Window.h"
)
source_group("UILib" FILES ${UILib})

set(ALL_FILES
    ${Noise}
    ${UILib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE 2DDevelop)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "2DDevelop"
    TARGET_NAME_RELEASE "2DDevelop"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "ENGINE_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "ENGINE_RELEASE"
    ">"
    "ENGINE_WINDOWS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /MTd;
            /ZI
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /MT;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "sfml-main;"
    "sfml-audio;"
    "sfml-window;"
    "sfml-graphics;"
    "sfml-network;"
    "sfml-system"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/x64"
)



























project(2DDevelop CXX)

################################################################################
# Source groups
################################################################################
set(Noise
    "Noise/FastNoise.cpp"
    "Noise/FastNoise.h"
    "Noise/HeightMap.cpp"
    "Noise/HeightMap.h"
    "Noise/Main.cpp"
    "Noise/NormalMap.cpp"
    "Noise/NormalMap.h"
    "Noise/stb_image.h"
    "Noise/stb_image_write.h"
    "Noise/stbi.cpp"
)
source_group("Noise" FILES ${Noise})

set(UILib
    "UILib/Button.h"
    "UILib/Input.h"
    "UILib/Slider.h"
    "UILib/Table.h"
    "UILib/UIElement.cpp"
    "UILib/UIElement.h"
    "UILib/UILib.h"
    "UILib/Window.cpp"
    "UILib/Window.h"
)
source_group("UILib" FILES ${UILib})

set(ALL_FILES
    ${Noise}
    ${UILib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE 2DDevelop)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "2DDevelop"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "ENGINE_WINDOWS;"
    "ENGINE_RELEASE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /std:c++17;
        /Gm-;
        /Ox;
        /Oi;
        /GF;
        /MT;
        /Gy;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /DEBUG:FULL;
        /SUBSYSTEM:CONSOLE;
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "sfml-main;"
    "sfml-audio;"
    "sfml-window;"
    "sfml-graphics;"
    "sfml-network;"
    "sfml-system"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/x64"
)



























project(2DDevelop CXX)

################################################################################
# Source groups
################################################################################
set(Noise
    "Noise/FastNoise.cpp"
    "Noise/FastNoise.h"
    "Noise/HeightMap.cpp"
    "Noise/HeightMap.h"
    "Noise/Main.cpp"
    "Noise/NormalMap.cpp"
    "Noise/NormalMap.h"
    "Noise/stb_image.h"
    "Noise/stb_image_write.h"
    "Noise/stbi.cpp"
)
source_group("Noise" FILES ${Noise})

set(UILib
    "UILib/Button.h"
    "UILib/Input.h"
    "UILib/Slider.h"
    "UILib/Table.h"
    "UILib/UIElement.cpp"
    "UILib/UIElement.h"
    "UILib/UILib.h"
    "UILib/Window.cpp"
    "UILib/Window.h"
)
source_group("UILib" FILES ${UILib})

set(ALL_FILES
    ${Noise}
    ${UILib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE 2DDevelop)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "2DDevelop"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}//2DDevelop/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "ENGINE_WINDOWS;"
    "ENGINE_RELEASE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /std:c++17;
        /Gm-;
        /Ox;
        /Oi;
        /GF;
        /MT;
        /Gy;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /DEBUG:FULL;
        /SUBSYSTEM:CONSOLE;
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "sfml-main;"
    "sfml-audio;"
    "sfml-window;"
    "sfml-graphics;"
    "sfml-network;"
    "sfml-system"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/x64"
)

