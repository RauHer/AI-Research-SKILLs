import unittest
import numpy as np
from train_discrete import mad_norm, BOPLayer

class TestBOP(unittest.TestCase):
    def test_mad_norm(self):
        # sum(|x|) = 243, answer should be exactly 1
        x = np.ones(243)
        self.assertEqual(mad_norm(x), 1)

    def test_bop_layer(self):
        layer = BOPLayer(243, 27)
        self.assertEqual(layer.W.shape, (27, 243))
        self.assertEqual(layer.m.shape, (27, 243))

        G = np.zeros((27, 243))
        layer.step(G, 3)

if __name__ == '__main__':
    unittest.main()
