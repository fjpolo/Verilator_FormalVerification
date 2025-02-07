#!/bin/bash

# Verify master module
echo "Verifying master module..."
cd master/; ./verify.sh
if [ $? -ne 0 ]; then
    echo "Master verification failed. Exiting script."
    rm $MASTER_TEMP_ORIGINAL_FILE
    exit 1
fi
echo "Master verification succeeded :)"
cd ..

# Verify slave module
# Verify slave_wait module
# Verify top module
