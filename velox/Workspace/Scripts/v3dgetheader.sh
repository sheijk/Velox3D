name=`echo $1 | tr [a-z] [A-Z]`
echo ${name}_`date +%Y_%m_%d`
