cmake_minimum_required(VERSION 3.10)
project(Evidencia2)

# Configuración de C++ estándar
set(CMAKE_CXX_STANDARD 17)

# Configuración para SonarQube (si aplica)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Google Test: Descarga y compila automáticamente si no está instalado
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Asegurarse de que las rutas de Google Test se incluyen correctamente
include_directories(${googletest_SOURCE_DIR}/googletest/include)
include_directories(${googletest_SOURCE_DIR}/googlemock/include)

# Configuración del runtime para evitar el error LNK2038 (para MSVC)
if(MSVC)
  # Usar la biblioteca estática de tiempo de ejecución para todos los proyectos
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Habilitar las pruebas
enable_testing()

# Definir archivos fuente comunes para el proyecto
set(SRC_FILES 
    src/main.cpp
    src/Kruskal.h
    src/MaxFlowSolver.h
    src/linear_search.h
    src/traveling_salesman.h
)

# Ejecutable principal
add_executable(main ${SRC_FILES})

# Definir archivos de prueba
set(TEST_FILES 
    tests/test_linear_search.cpp
    tests/kruskal.cpp
    tests/MaxFlowSolver.cpp
    tests/tsp.cpp
)

# Ejecutable para las pruebas unitarias
add_executable(tests ${TEST_FILES} ${SRC_FILES})  # Asegúrate de incluir los archivos fuente

# Compilar Google Test (si no se compiló previamente)
add_dependencies(tests gtest gtest_main)

# Enlace correcto de las librerías de Google Test
target_link_libraries(tests gtest gtest_main)
