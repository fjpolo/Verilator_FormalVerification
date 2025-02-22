#!/bin/zsh

# Step 0: Source the OSS CAD Suite environment
echo "Sourcing OSS CAD Suite environment..."
source ~/oss-cad-suite/environment
if [ $? -ne 0 ]; then
    echo "Failed to source OSS CAD Suite environment. Exiting script."
    exit 1
fi

# Input files
MASTER_FILE="apb_master.v"
MASTER_FORMAL_FILE="apb_master_properties.v"
MASTER_TB_FILE="apb_master_tb.v"
MUTATIONS_DIR="mutations"  # Directory to store mutations
SIMULATOR="iverilog"       # Change to your preferred simulator (e.g., vcs, xrun)
VVP=vvp
OUTPUT_VVP="apb_master_tb.vvp"
VCD_FILE="apb_master_sim.vcd"
COVERAGE_DIR="coverage_report"

# Generate a timestamp for the temporary file
MASTER_TEMP_ORIGINAL_FILE="apb_master_formal.v"
echo -n > $MASTER_TEMP_ORIGINAL_FILE

# Check if required files exist
echo "Checking if required files exist..."
for FILE in "$MASTER_FILE" "$MASTER_FORMAL_FILE" "$MASTER_TB_FILE"; do
    if [ ! -f "$FILE" ]; then
        echo "Error: File $FILE not found. Exiting script."
        exit 1
    fi
done

# Insert formal properties into the original master.v before `endmodule`
gsed "/endmodule/e cat $MASTER_FORMAL_FILE" "$MASTER_FILE" > "$MASTER_TEMP_ORIGINAL_FILE"

#
# Verilator Linting
#

# Run Verilator on the original master.v
echo "Running Verilator on original master.v..."
verilator -Wall -cc --lint-only $MASTER_FILE
if [ $? -ne 0 ]; then
    echo "Verilator failed for original master.v. Exiting script."
    rm $MASTER_TEMP_ORIGINAL_FILE
    exit 1
fi

#
# Icarus Verilog
#

# Clean up previous builds
echo "Cleaning up previous builds..."
rm -rf $OUTPUT_VVP $VCD_FILE $COVERAGE_DIR

# Run simulation of master_tb.v with the original master.v
echo "Running simulation for original master.v..."
$SIMULATOR -g2012 -DCOVERAGE -o $OUTPUT_VVP $MASTER_TB_FILE $MASTER_FILE
if [ $? -ne 0 ]; then
    echo "Simulation compilation failed for original master.v. Exiting script."
    rm -f sim_output
    rm $MASTER_TEMP_ORIGINAL_FILE
    exit 1
fi

# Execute the simulation and check the exit status
$VVP -n $OUTPUT_VVP -lxt2
SIM_EXIT_STATUS=$?
if [ $SIM_EXIT_STATUS -ne 0 ]; then
    echo "Simulation failed for original master.v with exit status $SIM_EXIT_STATUS. Exiting script."
    rm -f sim_output
    rm $MASTER_TEMP_ORIGINAL_FILE
    exit 1
fi

# # Generate coverage report
# echo "Generating coverage report..."
# gcov $MASTER_FILE
# if [ $? -ne 0 ]; then
#     echo "Coverage report generation failed!"
#     exit 1
# fi

# # Clean up the simulation executable
# rm -f sim_output

#
# Verilator
#

# # Configuration
# VERILATOR=verilator
# VERILATOR_TB_FILE="apb_master_tb.cpp"
# VERILATOR_OUTPUT_DIR="obj_dir"
# VERILATOR_VCD_FILE="apb_master_sim.vcd"
# export CXX=clang++

# # Clean up previous builds
# # echo "Cleaning up previous builds..."
# # rm -rf $VERILATOR_OUTPUT_DIR $VERILATOR_VCD_FILE

# # Compile the design and testbench with Verilator
# echo "Running Verilator..."
# $VERILATOR --binary -j -Wall -CFLAGS "-std=c++14" $MASTER_FILE $VERILATOR_TB_FILE
# # Check if compilation succeeded
# if [ $? -ne 0 ]; then
#     echo "Verilator compilation failed!"
#     exit 1
# fi
# # Run the simulation
# echo "Running simulation..."
# ./$VERILATOR_OUTPUT_DIR/Vapb_master

# # Check if simulation succeeded
# if [ $? -ne 0 ]; then
#     echo "Simulation failed!"
#     exit 1
# fi

# echo "Simulation completed successfully!"
# echo "Waveform file: $VERILATOR_VCD_FILE"

# # Verilator coverage
# echo "Verilator coverage"
# $VERILATOR -Wall -cc --coverage $MASTER_FILE
# verilator_coverage

#
# cocoTB
#

#
python3 apb_master_runner.py


# Check if simulation succeeded
if [ $? -ne 0 ]; then
    echo "Simulation failed!"
    exit 1
fi

# Generate coverage report
echo "Generating coverage report..."
mkdir -p $COVERAGE_DIR
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory $COVERAGE_DIR

# Check if lcov succeeded
if [ $? -ne 0 ]; then
    echo "HTML coverage report generation failed!"
    exit 1
fi

echo "Simulation and coverage report generation completed successfully!"
echo "Coverage report: $COVERAGE_DIR/index.html"xdg-open coverage_report/index.html



#
# SBY
#

# # Verify the original master.v with formal properties
# # Run SymbiYosys (sby) on the temporary file
# echo "Verifying original master.v with formal properties..."
# sby -f apb_master.sby

# # Check if sby succeeded
# if [ $? -ne 0 ]; then
#     echo "sby failed for original master.v. Exiting script."
#     rm $MASTER_TEMP_ORIGINAL_FILE
#     exit 1
# fi

# # Clean up the temporary file for the original master.v
# rm $MASTER_TEMP_ORIGINAL_FILE

# # Generate mutations using mcy
# echo "Generating mutations using mcy..."
# mcy purge; mcy init; mcy run -j8
# # ; mcy purge

