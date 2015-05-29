kill $(ps aux | grep 'slurmd' | awk '{print $2}')
