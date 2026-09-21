#!/usr/bin/env python3
import numpy as np

def mad_norm(x):
    sum_abs = np.sum(np.abs(x))
    # mad = (sum(|x_i|) * 17261U) >> 22
    return (int(sum_abs) * 17261) >> 22

class BOPLayer:
    def __init__(self, dim, num_experts):
        self.dim = dim
        self.num_experts = num_experts
        # Master weights are strictly ternary
        self.W = np.random.choice([-1, 0, 1], size=(num_experts, dim)).astype(np.int8)
        # Leaky integer momentum buffer [-127, 127]
        self.m = np.zeros((num_experts, dim), dtype=np.int8)

    def step(self, G, tau):
        # G is the gradient sign: sum_{b} (delta * x)

        # Leaky decay: beta = 8/9 -> x - (x >> 3)
        decay = np.right_shift(self.m, 3)

        # Center pull weight decay: Delta m = -W
        self.m = self.m - decay - np.sign(G) - self.W

        # Clip to int8 bounds
        self.m = np.clip(self.m, -127, 127)

        # Threshold update
        update_mask = np.abs(self.m) >= tau
        if np.any(update_mask):
            self.W[update_mask] = np.sign(self.m[update_mask])
            self.m[update_mask] = 0

def main():
    print("[*] Starting BOP Discrete Training Engine")
    layer = BOPLayer(243, 27)

    # Simulate a few steps
    tau = 3
    for step in range(10):
        # Dummy batch gradient sign
        G = np.random.choice([-1, 0, 1], size=(27, 243))
        layer.step(G, tau)

    print("[+] BOP Training completed successfully.")

if __name__ == "__main__":
    main()
