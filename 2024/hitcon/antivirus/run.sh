#!/bin/sh

docker run -v /home/ctf/clamav/:/test/ --rm -it clamav/clamav clamscan --bytecode-unsigned -d/test/print_flag.cbc /test/sample.exe