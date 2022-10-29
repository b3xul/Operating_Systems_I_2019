#!/bin/bash
echo "\$HOME=$HOME"
echo "\$PATH=$PATH"
robe="Casa mia"

./robe.bash

export robe

./robe.bash

echo "$(printenv | grep Casa)"
echo "$robe"
set -v
robe="Casa tua"
echo "$robe"
set +v
echo "$robe"
echo "*********"
set -x
robe="Casa loro"
echo "$robe"
echo "$(date)"
set +x
echo "$(date)"
echo $(date)
