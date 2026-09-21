#!/usr/bin/env bash
set -euo pipefail

echo "[*] Step 1: Configuring Host OS Kernel for 2MB HugePages..."
# In a sandbox, we might not have root. We'll wrap sysctl in a check or just print what needs to be done.
if [ "$EUID" -ne 0 ]; then
    echo "Warning: Not running as root. Skipping sysctl and hugepage kernel settings."
    echo "Please run the following commands as root on your target hardware:"
    echo "  sudo sysctl -w vm.max_map_count=262144"
    echo "  echo always | sudo tee /sys/kernel/mm/transparent_hugepage/enabled"
    echo "  echo advise | sudo tee /sys/kernel/mm/transparent_hugepage/defrag"
else
    sudo sysctl -w vm.max_map_count=262144
    echo always | sudo tee /sys/kernel/mm/transparent_hugepage/enabled
    echo advise | sudo tee /sys/kernel/mm/transparent_hugepage/defrag
fi

echo "[*] Step 2: Preparing Isolated Python Environment..."
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install -r requirements.txt

echo "[*] Step 3: Compiling Standalone Pure C Engine..."
cd ternary_engine
make clean || true
make -j$(nproc)
cd ..

echo "[*] Step 4: Running Silicon & Register Sanity Smoke Test..."
./ternary_engine/ternary_engine --bench-tokenizer
./ternary_engine/ternary_engine --init-dummy ./test_sanity.tbin
./ternary_engine/ternary_engine ./test_sanity.tbin <<< "Base-3 sanity check"
rm -f ./test_sanity.tbin

echo "[*] Step 5: Allocating UMA Ring Buffer (/dev/shm)..."
mkdir -p /dev/shm/ternary_stream
chmod 777 /dev/shm/ternary_stream || true

echo "[*] Step 6: Launching Autonomous Orchestration Daemon..."
# For sandbox testing, we won't launch the 30 hour training loop in the background.
echo "To begin training on your hardware, run:"
echo "nohup python3 orchestrator.py \\"
echo "    --platform amd_ryzen_ai \\"
echo "    --memory-budget 58 \\"
echo "    --target-tier 1 \\"
echo "    --start-tier 3 \\"
echo "    --ctdp-watts 54 \\"
echo "    --auto-upcycle \\"
echo "    > training_agent.log 2>&1 &"

echo "[+] System Bootstrapped Successfully."
