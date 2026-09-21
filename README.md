# Base-3 Ternary MoE LLM Lab

**Canonical Release 25.0 — The Sovereign Turnkey Directive**

This repository contains the autonomous agent execution environment for building, training, and deploying a multiplication-free Base-3 Ternary Mixture of Experts Language Model.

## Directory Structure
- `ternary_engine/`: The pure C standalone execution runtime.
  - `include/`: API Headers defining mathematical invariants and memory layouts.
  - `src/`: Implementation logic containing MAD-Norm, DABT Tokenizer, RetNet, and Hypercube routing.
  - `Makefile`: Build rules.
- `orchestrator.py`: The main Finite State Machine managing 5 execution stages.
- `distill_harness.py`: Manages up to 30 API connections for extraction.
- `train_discrete.py`: Executes BOP with leaky integer inertia for weight updates.
- `upcycle_morph.py`: Logic for Net2Net zero-shock upcycling.
- `export_tbin.py`: Model binary formatting (`.tbin`).
- `bootstrap.sh`: Automates compiling and testing.

## Execution
Review `bootstrap.sh` and run it to prepare the environment and build the C engine.
```bash
./bootstrap.sh
```

Execute training using the Orchestrator daemon once your keys are ready.
