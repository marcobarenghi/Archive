#!/bin/bash

gm convert -depth 8 -size 50x50 gray:input.bin input.png
gm convert -depth 8 -size 50x50 gray:afterDilation.bin afterDilation.png
gm convert -depth 8 -size 50x50 gray:afterErosion.bin afterErosion.png
gm convert -depth 8 -size 50x50 gray:afterCloseGap.bin afterCloseGap.png
