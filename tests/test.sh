RED='\033[0;31m'
NC='\033[0m'
numtest=$(ls test/test* | wc -l)
i=$((0))

numtest=$((numtest - 2))

cc get_next_line.c main.c

while [ $i -le $numtest ];
do
	cp test/test$i curtest
	./a.out > copy
	echo "${RED}"
	diff curtest copy
	echo "${NC}"
	i=$((i + 1))
	rm curtest
	rm copy
done
