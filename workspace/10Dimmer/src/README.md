% verilator -Wall -cc thruwire.v
% cd obj_dir/
% make -f Vthruwire.mk
%cd ..

// Build CPP
% g++ -I /usr/share/verilator/include -I obj_dir/ /usr/share/verilator/include/verilated.cpp thruwire.cpp Vthruwire__ALL.a -o thruwire