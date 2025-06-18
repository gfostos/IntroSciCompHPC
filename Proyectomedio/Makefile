# Compilador y flags
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
LDFLAGS = -lCatch2Main -lCatch2
DEBUG_FLAGS = -g
PROFILE_FLAGS = -pg
SANITIZE_FLAGS = -fsanitize=undefined,leak,address

# Archivos fuente
SRCS = main.cpp percolation.cpp
OBJS = $(SRCS:.cpp=.o)

# Ejecutables
BIN = percolate
TEST_BIN = test_percolation

# Target por defecto
all: $(BIN)
	parallel './$(BIN) {1} {2} 10' ::: 32 64 128 256 512 ::: $(shell seq 0.0 0.054 0.54) $(shell seq 0.55 0.01 0.65) $(shell seq 0.66 0.034 1.0) | sort -t'|' -k1,1n -k2,2n > resultados.txt

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

simul: $(BIN)
	./$(BIN) 4 0.6 10

#
test: percolation.o test_percolation.o
	spack load catch2 && \
	$(CXX) $(CXXFLAGS) $(SANITIZE_FLAGS) -o $(TEST_BIN) test_percolation.o percolation.o $(LDFLAGS)
	./$(TEST_BIN)

report:
	@echo "--- Generando reporte en PDF desde Informe/report.tex ---"
	pdflatex -output-directory=Informe Informe/report.tex
	pdflatex -output-directory=Informe Informe/report.tex
	@echo "Reporte generado: Informe/report.pdf"
	rm -f Informe/*.aux Informe/*.log

profile:
	@echo "--- Generando reporte de profiling (gprof) con L=8, p=0.5 ---"
	$(CXX) $(CXXFLAGS) $(SANITIZE_FLAGS) $(PROFILE_FLAGS) -o $(BIN)_profile $(SRCS)
	./$(BIN)_profile 8 0.5 50000
	@echo "--- Perfil para L=8, p=0.5 ---"
	gprof $(BIN)_profile gmon.out > profile.txt

#Para el profiling-report.txt
#g++ -O2 -Wall -std=c++17 -pg -g main.cpp percolation.cpp
#./a.out 128 0.59271 2000
#gprof a.out gmon.out > Reporte/profiling-report.txt

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -ggdb -o $(BIN)_debug $(SRCS) 
	gdb ./$(BIN)_debug
	
valgrind:
	$(CXX) $(DEBUG_FLAGS) -o $(BIN)_valgrind $(SRCS)
	valgrind ./$(BIN)_valgrind 6 0.6 10

clean:
	rm -f *.o $(BIN) $(TEST_BIN) *.txt *.out percolate_profile percolate_debug percolate_valgrind
