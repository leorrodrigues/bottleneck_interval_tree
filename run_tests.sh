RED='\033[0;31m |-'
BLUE='\033[0;34m |-'
NC='\033[0m'

FILES=$(ls -l tests/ | grep  'case' | grep -v 'out' | awk '{print $9}')

reset && make && {
    for i in $FILES; do
    ./interval.out < tests/$i > tests/out_$i;
    cmp tests/result$(echo "${i#case}") tests/out_$i && printf "${BLUE}Teste $i Passou ${NC}\n" && rm tests/out_$i || printf "${RED}Teste $i Falhou${NC}\n";
done;} || printf "${RED} Erro na compilação${NC}\n"
