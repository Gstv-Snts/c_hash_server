@make:
	@if [ ! -d build/ ]; then \
		echo "Creating build/"; \
		mkdir -p build/ && cd build/ && cmake .. && mv compile_commands.json ..; \
		echo "buid/ created"; \
	fi 

run:
	@make --no-print-directory
	@cd build/ && make
	@echo "############" 
	@echo ""
	@./build/main
	@echo ""
	@echo ""
	@echo "############" 

test:
	@make --no-print-directory
	@cd build/ && make
	@echo "############" 
	@echo ""
	@cd build/ && ctest --output-on-failure
	@echo ""
	@echo ""
	@echo "############" 

bench:
	@make --no-print-directory
	@cd build/ && make
	@echo "############" 
	@echo ""
	@./build/bench --confidence=5
	@echo ""
	@echo ""
	@echo "############" 

cov:
	@make --no-print-directory
	@make test
	@cd build/ && lcov --capture --directory . --output-file coverage.info
	@cd build/ && lcov --remove coverage.info '*/libs/*' '*/tests/*' --output-file coverage.info
	@cd build/ && genhtml coverage.info --output-directory out
	@cd build/ && cd out/ && google-chrome index.html

debug_test:
	@make --no-print-directory
	@cd build/ && make
	@echo "############" 
	@echo ""
	@gdb ./build/tests
	@echo ""
	@echo ""
	@echo "############" 

debug_run:
	@make --no-print-directory
	@cd build/ && make
	@echo "############" 
	@echo ""
	@gdb ./build/main
	@echo ""
	@echo ""
	@echo "############" 

clean:
	@sudo rm -r build/ 
	@sudo rm -r compile_commands.json
	@sudo rm -r libs/
	@sudo rm -r .cache/

.PHONY: all clean
