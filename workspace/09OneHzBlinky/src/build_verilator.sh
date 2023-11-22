PROJECT_NAME="onehzblinky"
VINC="/usr/share/verilator/include/"

verilator -Wall  --trace -GWIDTH=12 -cc ${PROJECT_NAME}.v && cd obj_dir/ && make -f V${PROJECT_NAME}.mk
g++ -I${VINC} -I obj_dir/ ${VINC}verilated.cpp ${VINC}/verilated_vcd_c.cpp ${PROJECT_NAME}.cpp V${PROJECT_NAME}__ALL.a -o ${PROJECT_NAME}
./${PROJECT_NAME}
gtkwave onehzblinky.vcd
cd ..
