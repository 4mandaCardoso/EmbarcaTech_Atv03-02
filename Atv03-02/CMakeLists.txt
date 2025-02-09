# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Atividade-03_02 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Adicione os arquivos fonte do seu projeto, incluindo a implementação da biblioteca SSD1306
add_executable(Atividade-03_02
    Atividade-03_02.c
    inc/ssd1306.c    # Adicione este arquivo se existir, que contém as implementações dos métodos do SSD1306.
    inc/font.h      
)

pico_set_program_name(Atividade-03_02 "Atividade-03_02")
pico_set_program_version(Atividade-03_02 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Atividade-03_02 1)
pico_enable_stdio_usb(Atividade-03_02 1)

# Add the standard library to the build
target_link_libraries(Atividade-03_02
        pico_stdlib
        hardware_gpio
        hardware_i2c
        hardware_pio
        pico_bootrom
    )

# Add the standard include files to the build
target_include_directories(Atividade-03_02 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Gera o cabeçalho PIO a partir do arquivo matriz_de_leds.pio localizado em inc/
pico_generate_pio_header(Atividade-03_02 ${CMAKE_CURRENT_LIST_DIR}/matriz_de_leds.pio)

# Add any user requested libraries
target_link_libraries(Atividade-03_02 

)

pico_add_extra_outputs(Atividade-03_02)
