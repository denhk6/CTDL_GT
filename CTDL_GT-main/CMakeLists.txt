# --- File CMakeLists.txt cho Du An ATM ---

cmake_minimum_required(VERSION 3.20)
project(ATM_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------
# BUOC 1: Dinh nghia target (file thuc thi)
# Tro den file main.cpp ben trong thu muc BankProject
# ----------------------------------------------------------------
add_executable(ATM_Project
        BankProject/main.cpp
)

# ----------------------------------------------------------------
# BUOC 2: Bao cho target biet noi de tim file HEADER (.h)
# Chung ta them thu muc goc, de cac include nhu "BankProject/Core/Card.h" hoat dong
# ----------------------------------------------------------------
target_include_directories(ATM_Project PUBLIC
        ${CMAKE_SOURCE_DIR}
)

# ----------------------------------------------------------------
# BUOC 3: Them tat ca cac file SOURCE (.cpp) khac vao target
# ----------------------------------------------------------------
target_sources(ATM_Project PRIVATE
        BankProject/Core/Account.cpp
        BankProject/Core/Card.cpp
        BankProject/Core/Transaction.cpp
        BankProject/Core/Utils.cpp
        BankProject/FileIO/FileManager.cpp
        BankProject/Admin/Admin.cpp
        BankProject/User/User.cpp
)

# ----------------------------------------------------------------
# BUOC 4: (Optional) Lien ket thu vien cho Windows
# ----------------------------------------------------------------
if(WIN32)
    target_link_libraries(ATM_Project PRIVATE kernel32)
endif()