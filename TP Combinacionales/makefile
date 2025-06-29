CIRCUIT = combinacionales.circ 
TARGET  = out.txt
EXPECTED = salida_catedra.txt

.PHONY: all test clean

all: test

test: $(CIRCUIT)
	@echo "Ejecutando Logisim-Evolution..."
	logisim-evolution --toplevel-circuit "verificador" -tty table $(CIRCUIT) > $(TARGET)
	@echo "Comparando la salida con el archivo esperado..."
	@if diff -y --suppress-common-lines $(TARGET) $(EXPECTED); then \
		echo "Prueba completada: la salida coincide con la esperada."; \
	else \
		echo "Prueba fallida: la salida no coincide con la esperada."; \
	fi

clean:
	@echo "Limpiando archivos generados..."
	rm -f $(TARGET)
