g++ ../src/principal.cpp ../src/DFS.cpp -o ../bin/main -Wall

../bin/main < ../data/input/1.in > ../data/output/execution_1.out
diff ../data/output/1.out ../data/output/execution_1.out

../bin/main < ../data/input/2.in > ../data/output/execution_2.out
diff ../data/output/2.out ../data/output/execution_2.out

../bin/main < ../data/input/3.in > ../data/output/execution_3.out
diff ../data/output/3.out ../data/output/execution_3.out

../bin/main < ../data/input/4.in > ../data/output/execution_4.out
diff ../data/output/4.out ../data/output/execution_4.out

../bin/main < ../data/input/5.in > ../data/output/execution_5.out
diff ../data/output/5.out ../data/output/execution_5.out
