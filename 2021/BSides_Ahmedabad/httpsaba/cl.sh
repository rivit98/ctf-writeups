kill -9 $(ps -x | grep httpsaba | head -n 1 | awk '{print $1}')

