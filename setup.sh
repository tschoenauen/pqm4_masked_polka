#! /bin/bash

### CAUTION: expected to be execution into the cloned pqm4_masked repository


PYTHON_VE=ve

# Setup Python environment
if [[ -d $PYTHON_VE ]]
then
    echo "$PYTHON_VE already exists"
    source $PYTHON_VE/bin/activate
else
    python3 -m venv $PYTHON_VE
    source $PYTHON_VE/bin/activate
    pip install pyserial pandas matplotlib
fi

# Build libopencm3 
(cd libopencm3 && make && cd ..)


