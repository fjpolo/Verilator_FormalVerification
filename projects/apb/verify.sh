#!/bin/bash

# Step 0: Source the OSS CAD Suite environment
echo "Sourcing OSS CAD Suite environment..."
source ~/oss-cad-suite/environment
if [ $? -ne 0 ]; then
    echo "Failed to source OSS CAD Suite environment. Exiting script."
    exit 1
fi

# Input files
MASTER_FILE="apb_master.v"
FORMAL_FILE="apb_master_properties.v"
TB_FILE="apb_master_tb.v"
MUTATIONS_DIR="mutations"  # Directory to store mutations
SIMULATOR="iverilog"       # Change to your preferred simulator (e.g., vcs, xrun)

# Generate a timestamp for the temporary file
TEMP_ORIGINAL_FILE="apb_master_formal.v"
echo -n > $TEMP_ORIGINAL_FILE

# Check if required files exist
echo "Checking if required files exist..."
for FILE in "$MASTER_FILE" "$FORMAL_FILE" "$TB_FILE"; do
    if [ ! -f "$FILE" ]; then
        echo "Error: File $FILE not found. Exiting script."
        exit 1
    fi
done

# Insert formal properties into the original master.v before `endmodule`
sed "/endmodule/e cat $FORMAL_FILE" $MASTER_FILE > $TEMP_ORIGINAL_FILE

# Run Verilator on the original master.v
echo "Running Verilator on original master.v..."
verilator -Wall -cc $MASTER_FILE
if [ $? -ne 0 ]; then
    echo "Verilator failed for original master.v. Exiting script."
    rm $TEMP_ORIGINAL_FILE
    exit 1
fi

# Run simulation of master_tb.v with the original master.v
echo "Running simulation for original master.v..."
$SIMULATOR -o sim_output $TB_FILE $MASTER_FILE
if [ $? -ne 0 ]; then
    echo "Simulation compilation failed for original master.v. Exiting script."
    rm -f sim_output
    rm $TEMP_ORIGINAL_FILE
    exit 1
fi

# Execute the simulation and check the exit status
./sim_output
SIM_EXIT_STATUS=$?
if [ $SIM_EXIT_STATUS -ne 0 ]; then
    echo "Simulation failed for original master.v with exit status $SIM_EXIT_STATUS. Exiting script."
    rm -f sim_output
    rm $TEMP_ORIGINAL_FILE
    exit 1
fi

# Clean up the simulation executable
rm -f sim_output

# Verify the original master.v with formal properties
# Run SymbiYosys (sby) on the temporary file
echo "Verifying original master.v with formal properties..."
sby -f apb_master.sby

# Check if sby succeeded
if [ $? -ne 0 ]; then
    echo "sby failed for original master.v. Exiting script."
    rm $TEMP_ORIGINAL_FILE
    exit 1
fi

# Clean up the temporary file for the original master.v
rm $TEMP_ORIGINAL_FILE

# Generate mutations using mcy
echo "Generating mutations using mcy..."
mcy purge; mcy init; mcy run -j8
# ; mcy purge

