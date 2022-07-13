# diretorio dos arquivos fonte (.java)
SRC_DIR := graph

# diretorio do pacote (pacote graph)
PCKG_DIR := .

# diretorio onde serao colocados os arquivos .class gerados
# precisa existir, então podem criar uma pasta out ou classes
# ou deixar no root ('.')
OUT_DIR := .

# expressão regular para compilar todos os .java de uma vez
SRCS := $(wildcard $(SRC_DIR)/*.java)

# expressão regular para selecionar todos os .class baseado nos .javas
CLS := $(SRCS:$(SRC_DIR)/%.java=$(OUT_DIR)/%.class)

# compilador (usualmente o javac)
JC := javac
# flags de compilação, -d define o diretório de saída
# -cp onde achar os arquivos de classes (classpath)
# https://docs.oracle.com/javase/7/docs/technotes/tools/windows/javac.html
JCFLAGS := -d $(OUT_DIR)/ -cp $(PCKG_DIR)/

# main class, precisa ser definida para executar
MAIN := GraphController

# make padrao
# gera as classes no diretorio de saida 
# a partir de todos os .java no diretorio de entrada
# usa o compilador com as flags especificadas
all: $(CLS)

$(CLS): $(OUT_DIR)/%.class: $(SRC_DIR)/%.java
	$(JC) $(JCFLAGS) $<

# limpa os arquivos .class
clean:
	rm $(OUT_DIR)/*.class

# roda o programa, precisa definir o diretorio das classes com -cp e a main
run:
	@java -cp $(OUT_DIR) graph.$(MAIN)
	