PYTHON ?= python3
.PHONY: all host native test verify recovery verify-recovery clean
all:
	$(MAKE) -C firmware all
host:
	$(MAKE) -C firmware host
native:
	$(MAKE) -C firmware native
test:
	$(MAKE) -C firmware test
	$(PYTHON) tests/check_architecture.py
	$(PYTHON) tests/protocol_differential.py
	$(PYTHON) tests/check_domain_services.py
verify: all test
	$(PYTHON) tests/check_native.py
recovery:
	$(MAKE) -C recovery all
verify-recovery:
	$(MAKE) -C recovery verify
clean:
	$(MAKE) -C firmware clean
