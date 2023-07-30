EXECUTABLE_FILE=Practica2
OUTPUT_FOLDER=Ficheros\ Salida
declare -a SITUATIONS=("I" "F")

if [ -f $EXECUTABLE_FILE ]; then
    if [ -d $OUTPUT_FOLDER ]; then
        rm -rf $OUTPUT_FOLDER
    fi
    mkdir $OUTPUT_FOLDER

    for s in ${SITUATIONS[@]}; do
        for n in {1..4}; do
            ./$EXECUTABLE_FILE ./Situaciones/BC-$s.txt ./Situaciones/BH-$s$n.txt ./Situaciones/Config-$s.txt
            mv Salida*.txt $OUTPUT_FOLDER
        done
    done
else
    echo "Ejecutable \"$EXECUTABLE_FILE\" no encontrado"
fi
