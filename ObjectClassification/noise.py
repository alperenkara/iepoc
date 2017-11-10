import numpy as np 
from scipy import ndimage


DEFAULT_SCALE = (0.0, 1.0)


class Noise:
    def __init__(self, scale=DEFAULT_SCALE):
        self.scale = scale

    def _apply(self, image):
        raise NotImplementedError

    def apply(self, image):
        noisy = self._apply(image)

        noisy[noisy < self.scale[0]] = self.scale[0]
        noisy[noisy > self.scale[1]] = self.scale[1]

        return noisy

    def set_scale(self, scale):
        self.scale = scale


class GaussianNoise(Noise):
    def __init__(self, std=0.05, mean=0.0, scale=DEFAULT_SCALE):
        Noise.__init__(self, scale)

        self.std = std
        self.mean = mean

    def _apply(self, image):
        return image + np.random.normal(self.mean, self.std, image.shape) * self.scale[1]


class SaltAndPepperNoise(Noise):
    def __init__(self, p=0.05, scale=DEFAULT_SCALE):
        Noise.__init__(self, scale)

        self.p = p

    def _apply(self, image):
        noisy = np.copy(image)

        p = np.random.random(image.shape)

        noisy[p < self.p / 2.] = self.scale[0]
        noisy[p > (1 - self.p / 2.)] = self.scale[1]

        return noisy


class QuantizationNoise(Noise):
    def __init__(self, q=0.01, scale=DEFAULT_SCALE):
        Noise.__init__(self, scale)

        self.q = q

    def _apply(self, image):
        return image + self.q * np.random.random(image.shape) * self.scale[1]
