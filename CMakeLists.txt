set(LIB_NAME QtKeychainAdapter)

set(LIB_SOURCES
    src/qtkeychain/keychain.cpp
    src/qtkeychain/keychain.h
    src/qtkeychainadapter/keychainservice.cpp
    src/qtkeychainadapter/keychainservice.h
)

if(APPLE)
    list(APPEND LIB_SOURCES src/qtkeychain/keychain_apple.mm)
    list(APPEND LIB_LIBRARIES "-framework Foundation" "-framework Security")
endif()

qt_add_library(${LIB_NAME} STATIC
    ${LIB_SOURCES}
)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Core
    ${LIB_LIBRARIES}
)

target_compile_definitions(${LIB_NAME} PRIVATE
    QTKEYCHAIN_NO_EXPORT
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qtkeychain
    ${CMAKE_CURRENT_BINARY_DIR}/src/qtkeychain
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
