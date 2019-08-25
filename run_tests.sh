RED='\033[0;31m |-'
BLUE='\033[0;34m |-'
YELLOW='\033[1;33m |-'
NC='\033[0m'
FILES=$(ls -l tests/ | grep  'case' | grep -v 'out' | grep -v 'valgrind' | awk '{print $9}')

PROGRAM_NAME="./$1"

if [ -z "$1" ]
then
    PROGRAM_NAME="./interval.out"
fi

#interval.out
reset && make && {
    echo "Running Tests";
    if hash valgrind >/dev/null;
    then
        for i in $FILES; do
            valgrind --leak-check=full --error-exitcode=121 --log-file="tests/memory_leak_$i" $PROGRAM_NAME < tests/$i > tests/out_$i
            if [ $? -eq 0 ]
            then
                printf "${BLUE}Memory Test $i [x] ${NC}\n";
                rm tests/memory_leak_$i;
            else
                 printf "${YELLOW}Memory Test $i [] (check the logs in /tests/ folder)${NC}\n";
            fi;
        done;
        rm -rf *core* tests/valgrind* tests/core*
    else
        print "${RED} Need to install Valgrind${NC}\n";
    fi

    echo "Program Tests";
    for i in $FILES; do
        #$PROGRAM_NAME < tests/$i > tests/out_$i;
        cmp tests/result$(echo "${i#case}") tests/out_$i && printf "${BLUE}Test $i [x] ${NC}\n" && rm tests/out_$i || printf "${RED}Test $i []${NC}\n";
    done;

} || printf "${RED} Erro na compilação${NC}\n"
