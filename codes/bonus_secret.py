from PIL import Image
import numpy as np


if __name__ == '__main__':
    img = Image.open('bonus_secret_statement.png').convert('L')
    n, m = img.size
    print(n, m)

    img = np.array([[img.getpixel((x, y)) for y in range(m)] for x in range(n)])
    
    def power(img, e, mod):
        base = 1
        while e > 0:
            for _ in range(e % mod):
                img = np.array([[(
                    img[(x + base) % n, y] +
                    img[(x - base) % n, y] +
                    img[x, (y + base) % m] +
                    img[x, (y - base) % m]
                  ) % mod for y in range(m)] for x in range(n)
                ])

            e //= mod
            base *= mod

        return img

    img = np.transpose(power(img, 10**12, 7)) * 30
    Image.fromarray(img.astype(np.uint8), mode='L').show()
