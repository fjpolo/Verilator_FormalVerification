#!/bin/bash

# Step 0: Source the OSS CAD Suite environment
echo "Sourcing OSS CAD Suite environment..."
source ~/oss-cad-suite/environment
if [ $? -ne 0 ]; then
    echo "Failed to source OSS CAD Suite environment. Exiting script."
    exit 1
fi

# Input files
SLAVE_FILE="apb_slave.v"
SLAVE_FORMAL_FILE="apb_slave_properties.v"
SLAVE_TB_FILE="apb_slave_tb.v"
MUTATIONS_DIR="mutations"  # Directory to store mutations
SIMULATOR="iverilog"       # Change to your preferred simulator (e.g., vcs, xrun)

# Generate a timestamp for the temporary file
SLAVE_TEMP_ORIGINAL_FILE="apb_slave_formal.v"
echo -n > $SLAVE_TEMP_ORIGINAL_FILE

# Check if required files exist
echo "Checking if required files exist..."
for FILE in "$SLAVE_FILE" "$SLAVE_FORMAL_FILE" "$SLAVE_TB_FILE"; do
    if [ ! -f "$FILE" ]; then
        echo "Error: File $FILE not found. Exiting script."
        exit 1
    fi
done

# Insert formal properties into the original slave.v before `endmodule`
sed "/endmodule/e cat $SLAVE_FORMAL_FILE" $SLAVE_FILE > $SLAVE_TEMP_ORIGINAL_FILE

# Run Verilator on the original slave.v
echo "Running Verilator on original slave.v..."
verilator -Wall -cc $SLAVE_FILE
if [ $? -ne 0 ]; then
    echo "Verilator failed for original slave.v. Exiting script."
    rm $SLAVE_TEMP_ORIGINAL_FILE
    exit 1
fi

# Run simulation of slave_tb.v with the original slave.v
echo "Running simulation for original slave.v..."
$SIMULATOR -o sim_output $SLAVE_TB_FILE $SLAVE_FILE
if [ $? -ne 0 ]; then
    echo "Simulation compilation failed for original slave.v. Exiting script."
    rm -f sim_output
    rm $SLAVE_TEMP_ORIGINAL_FILE
    exit 1
fi

# Execute the simulation and check the exit status
./sim_output
SIM_EXIT_STATUS=$?
if [ $SIM_EXIT_STATUS -ne 0 ]; then
    echo "Simulation failed for original slave.v with exit status $SIM_EXIT_STATUS. Exiting script."
    rm -f sim_output
    rm $SLAVE_TEMP_ORIGINAL_FILE
    exit 1
fi

# Clean up the simulation executable
rm -f sim_output

# Verify the original slave.v with formal properties
# Run SymbiYosys (sby) on the temporary file
echo "Verifying original slave.v with formal properties..."
sby -f apb_slave.sby

# Check if sby succeeded
if [ $? -ne 0 ]; then
    echo "sby failed for original slave.v. Exiting script."
    rm $SLAVE_TEMP_ORIGINAL_FILE
    exit 1
fi

# Clean up the temporary file for the original slave.v
rm $SLAVE_TEMP_ORIGINAL_FILE

# Generate mutations using mcy
echo "Generating mutations using mcy..."
mcy purge; mcy init; mcy run -j8
# ; mcy purge

