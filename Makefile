.PHONY: clean All

All:
	@echo "----------Building project:[ PowerGrid - Debug ]----------"
	@cd "PowerGrid" && "$(MAKE)" -f  "PowerGrid.mk"
clean:
	@echo "----------Cleaning project:[ PowerGrid - Debug ]----------"
	@cd "PowerGrid" && "$(MAKE)" -f  "PowerGrid.mk" clean
