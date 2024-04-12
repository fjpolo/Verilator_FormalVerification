## Run verilator
PROJECT_NAME="helloworld" && VINC="/usr/share/verilator/include/" && verilator -Wall  --trace -cc ${PROJECT_NAME}.v

## Make project
make

## Deprecated by make
## && cd obj_dir/ && make -f V${PROJECT_NAME}.mk && g++ -I${VINC} -I obj_dir/ ${VINC}verilated.cpp ${VINC}/verilated_vcd_c.cpp uartsim.cpp  ${PROJECT_NAME}_tb.cpp V${PROJECT_NAME}__ALL.a -o ${PROJECT_NAME} && ./${PROJECT_NAME}
### && cd .. && 

## Run formal verification
sby -f txuart.sby ## && sby -f helloworld.sby

## Load wave
### gtkwave helloworld/engine_0/trace0.vcd