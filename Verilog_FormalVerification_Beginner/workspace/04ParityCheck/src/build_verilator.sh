PROJECT_NAME="paritycheck"

verilator -Wall -cc ${PROJECT_NAME}.v && cd obj_dir/ && make -f V${PROJECT_NAME}.mk
g++ -I /usr/share/verilator/include -I obj_dir/ /usr/share/verilator/include/verilated.cpp ${PROJECT_NAME}.cpp V${PROJECT_NAME}__ALL.a -o ${PROJECT_NAME}
./${PROJECT_NAME}
cd ..