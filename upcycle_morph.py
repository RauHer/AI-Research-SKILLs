#!/usr/bin/env python3
import numpy as np

def upcycle_tier(weights_parent):
    # W_child = Triplicate(W_parent)
    # W_e -> W_3e+0, W_3e+1, W_3e+2

    parent_experts = weights_parent.shape[0]
    dim = weights_parent.shape[1]

    weights_child = np.zeros((parent_experts * 3, dim), dtype=np.int8)

    for e in range(parent_experts):
        weights_child[3*e + 0] = weights_parent[e]
        weights_child[3*e + 1] = weights_parent[e]
        weights_child[3*e + 2] = weights_parent[e]

    return weights_child

def main():
    print("[*] Performing Net2Net Upcycle Morphing")

    # Tier 3 (27 experts) -> Tier 2 (729 experts)
    # Just a small test with 27 to 81
    w_parent = np.random.choice([-1, 0, 1], size=(27, 243))
    w_child = upcycle_tier(w_parent)

    assert w_child.shape[0] == 81
    print("[+] Zero-Shock upcycle complete.")

if __name__ == "__main__":
    main()
