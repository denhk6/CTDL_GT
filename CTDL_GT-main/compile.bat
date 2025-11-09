@echo off
echo Compiling project... Please wait.
echo This may take a moment.

REM -----------------------------------------------------------------
REM Lenh nay se bien dich tat ca cac file .cpp tu cac thu muc con
REM
REM -I.
REM Bao g++.exe tim kiem file header (nhu "BankProject/Core/List.h")
REM bat dau tu thu muc goc nay (noi chua file .bat).
REM
REM -o ATM_Project.exe
REM Tao ra file thuc thi ten la ATM_Project.exe o ngay thu muc goc nay.
REM -----------------------------------------------------------------

g++.exe -I. ^
    BankProject/main.cpp ^
    BankProject/Core/Account.cpp ^
    BankProject/Core/Card.cpp ^
    BankProject/Core/Transaction.cpp ^
    BankProject/Core/Utils.cpp ^
    BankProject/FileIO/FileManager.cpp ^
    BankProject/Admin/Admin.cpp ^
    BankProject/User/User.cpp ^
    -o ATM_Project.exe -std=c++17 -Wall

REM Kiem tra xem bien dich co thanh cong khong
if %errorlevel% == 0 (
    echo.
    echo Compile successful! Running ATM...
    echo -----------------------------------

    REM Chay file .exe tu thu muc goc nay.
    REM Dieu nay dam bao "Working Directory" la chinh xac,
    REM va code se tim thay file "BankProject/Data/Admin.txt".
    ATM_Project.exe
) else (
    echo.
    echo COMPILE FAILED! Please check the error messages above.
)

echo -----------------------------------
echo Program finished. Press any key to exit.
pause > nul