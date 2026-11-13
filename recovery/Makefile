PYTHON ?= python3
.PHONY: all firmware c-model verify export-c
all: firmware c-model
firmware:
	$(MAKE) -C full_assembly all
c-model:
	$(MAKE) -C full_c all
verify: all
	$(PYTHON) verification/check_workflow.py
	$(MAKE) -C full_assembly verify
	$(PYTHON) tools/check_artifacts.py
	$(PYTHON) verification/check_serial.py
	$(PYTHON) tools/verify_semantics.py
	$(PYTHON) verification/check_update_crc.py
	$(PYTHON) verification/check_application_main.py
	$(PYTHON) verification/check_business.py
	$(MAKE) -C full_c verify
	$(PYTHON) full_c/review_boundaries.py
	$(PYTHON) tools/audit_recovery.py
export-c: firmware
	$(PYTHON) ghidra/export_all.py
