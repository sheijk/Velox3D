filename=$1
old=$2
new=$3

sed -e ":start" -e "s#${old}#${new}#" -e "t start" ${filename} > ${filename}.temp
mv ${filename}.temp ${filename}
