cmake_minimum_required(VERSION 3.2.0)

project(LaminarOS C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(INCLUDE_PATHS   ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Interface/Inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Core/Inc

                    # Include the config header folder
                    ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Interface/Common/${FOLDER_NAME}/Inc

                    ## Any new driver folders Inc dirs must be added here ##
                    ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Driver/RC_Receiver/Inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Driver/Motor_Channel/Inc

                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/${FAMILY_NAME}_HAL_Driver/Inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Core/Inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/CMSIS/Device/ST/${FAMILY_NAME}/Include
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/CMSIS/Include
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Middlewares/Third_Party/FreeRTOS/Source
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_${PORTABLE_NAME}
                    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Middlewares/Third_Party/FreeRTOS/Source/include
)
set(LOS_INCLUDES ${INCLUDE_PATHS} PARENT_SCOPE)
include_directories(
    ${INCLUDE_PATHS}
)

set(HAL_DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers)
set(HAL_DRIVERS_C_SOURCES "${HAL_DRIVERS_DIR}/${FAMILY_NAME}_HAL_Driver/Src/*.c")

set(FREE_RTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Middlewares/Third_Party/FreeRTOS/Source)
set(FREE_RTOS_C_SOURCES "${FREE_RTOS_DIR}/*.c"
                        "${FREE_RTOS_DIR}/CMSIS_RTOS_V2/*.c"
                        "${FREE_RTOS_DIR}/portable/GCC/ARM_${PORTABLE_NAME}/*.c"
                        "${FREE_RTOS_DIR}/portable/MemMang/*.c")

set(HAL_CORE ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Core)
set(HAL_CORE_C_SOURCES "${HAL_CORE}/Src/*.c")
set(HAL_CORE_CXX_SOURCES "${HAL_CORE}/Src/*.cpp")

set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Interface)
set(INTERFACE_C_SOURCES "${INTERFACE_DIR}/Src/*.c" "${INTERFACE_DIR}/Common/${FOLDER_NAME}/Src/*.c")
set(INTERFACE_CXX_SOURCES "${INTERFACE_DIR}/Src/*.cpp" "${INTERFACE_DIR}/Common/${FOLDER_NAME}/Src/*.cpp")

set(DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Driver)
set(DRIVERS_C_SOURCES "${DRIVERS_DIR}/*/Src/*.c")
set(DRIVERS_CXX_SOURCES "${DRIVERS_DIR}/*/Src/*.cpp")

set(CORE_Dir ${CMAKE_CURRENT_SOURCE_DIR}/LOS_Core)
set(CORE_C_SOURCES "${CORE_Dir}/Src/*.c")
set(CORE_CXX_SOURCES "${CORE_Dir}/Src/*.cpp")

file(GLOB_RECURSE C_SOURCES ${HAL_DRIVERS_C_SOURCES}
                            ${HAL_CORE_C_SOURCES}
                            ${INTERFACE_CXX_SOURCES}
                            ${DRIVERS_CXX_SOURCES}
                            ${CORE_C_SOURCES}
                            ${FREE_RTOS_C_SOURCES})                            
message("MESSAGE: ${C_SOURCES}")                         
file(GLOB_RECURSE CXX_SOURCES ${HAL_CORE_CXX_SOURCES} 
                              ${INTERFACE_CXX_SOURCES}
                              ${DRIVERS_CXX_SOURCES}
                              ${CORE_CXX_SOURCES})

add_library(${PROJECT_NAME} ${C_SOURCES} ${CXX_SOURCES})
