@echo off

set executableFile=Practica2.exe
set outputFolder="Ficheros Salida"
set situations=I F

if exist %executableFile% (
    if exist %outputFolder% (
        rmdir %outputFolder% /s /q
    )
    mkdir %outputFolder%

    for %%s in (%situations%) do (
        for /l %%n in (1, 1, 4) do (
             call %executableFile% Situaciones\BC-%%s.txt Situaciones\BH-%%s%%n.txt Situaciones\Config-%%s.txt
             move Salida*.txt %outputFolder%
        )
    )
) else (
    echo Ejecutable %executableFile% no encontrado
)

pause
