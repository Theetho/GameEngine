project(GLAD C)

################################################################################
# Source groups
################################################################################
set(include__KHR
    "include/KHR/khrplatform.h"
)
source_group("include\\KHR" FILES ${include__KHR})

set(include__glad
    "include/glad/glad.h"
)
source_group("include\\glad" FILES ${include__glad})

set(src
    "src/glad.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include__KHR}
    ${include__glad}
    ${src}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GLAD)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "GLAD"
    TARGET_NAME_DISTRIBUTION "GLAD"
    TARGET_NAME_RELEASE      "GLAD"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug-windows-x64/GLAD/"
    OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/bin/Distribution-windows-x64/GLAD/"
    OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release-windows-x64/GLAD/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
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
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:WINDOWS
    )
endif()



























project(GLAD C)

################################################################################
# Source groups
################################################################################
set(include__KHR
    "include/KHR/khrplatform.h"
)
source_group("include\\KHR" FILES ${include__KHR})

set(include__glad
    "include/glad/glad.h"
)
source_group("include\\glad" FILES ${include__glad})

set(src
    "src/glad.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include__KHR}
    ${include__glad}
    ${src}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GLAD)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "GLAD"
    TARGET_NAME_DISTRIBUTION "GLAD"
    TARGET_NAME_RELEASE      "GLAD"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug-windows-x64/GLAD/"
    OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/bin/Distribution-windows-x64/GLAD/"
    OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release-windows-x64/GLAD/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
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
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:WINDOWS
    )
endif()



























project(GLAD C)

################################################################################
# Source groups
################################################################################
set(include__KHR
    "include/KHR/khrplatform.h"
)
source_group("include\\KHR" FILES ${include__KHR})

set(include__glad
    "include/glad/glad.h"
)
source_group("include\\glad" FILES ${include__glad})

set(src
    "src/glad.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include__KHR}
    ${include__glad}
    ${src}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GLAD)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "GLAD"
    TARGET_NAME_RELEASE "GLAD"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug-windows-x64/GLAD/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release-windows-x64/GLAD/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
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
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:WINDOWS
    )
endif()



























project(GLAD C)

################################################################################
# Source groups
################################################################################
set(include__KHR
    "include/KHR/khrplatform.h"
)
source_group("include\\KHR" FILES ${include__KHR})

set(include__glad
    "include/glad/glad.h"
)
source_group("include\\glad" FILES ${include__glad})

set(src
    "src/glad.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include__KHR}
    ${include__glad}
    ${src}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GLAD)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "GLAD"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release-windows-x64/GLAD/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
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
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF
    )
endif()



























project(GLAD C)

################################################################################
# Source groups
################################################################################
set(include__KHR
    "include/KHR/khrplatform.h"
)
source_group("include\\KHR" FILES ${include__KHR})

set(include__glad
    "include/glad/glad.h"
)
source_group("include\\glad" FILES ${include__glad})

set(src
    "src/glad.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include__KHR}
    ${include__glad}
    ${src}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GLAD)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "GLAD"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release-windows-x64/GLAD/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
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
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF
    )
endif()

