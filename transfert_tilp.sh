#!/bin/bash
set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

tilpcmd=tilp2

if ! command -v tilp2 2>&1 >/dev/null
then
    if command -v tilp 2>&1 >/dev/null
    then
        tilpcmd=tilp
    else
        echo "error: tilp2 not found. See https://tipla.net/tilpinst"
        exit 1
    fi
fi

tilpcmd="${tilpcmd} --cable=DirectLink -ns"

pushd $SCRIPT_DIR

for i in $(seq -w 00 43); do
    echo "Transferring AppIns${i}.8xv..."
    $tilpcmd "app/AppIns${i}.8xv" &>/dev/null
done

echo "Transferring arTIfiCE and the app installer..."
$tilpcmd arTIfiCE.8xv &>/dev/null
$tilpcmd INST.8xp &>/dev/null

if [ -f CabriJr_5.0.0.0089.8ek ]; then
    echo "Transferring CabriJr..."
    $tilpcmd CabriJr_5.0.0.0089.8ek &>/dev/null
else
    echo "'CabriJr_5.0.0.0089.8ek' not found, please download it and transfer it!"
fi

popd
