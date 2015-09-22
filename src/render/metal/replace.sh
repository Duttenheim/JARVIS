for f in *.cc; do 
mv -- "$f" "${f%.cc}.mm"
done
