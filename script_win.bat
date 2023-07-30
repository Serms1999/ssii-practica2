set outputFolder="Ficheros Salida"

if exist %outputFolder% (
    rmdir %outputFold% /s /q
)
mkdir %outputFolder%

pause