from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

# Wczytanie obrazu
image = Image.open('bez_tytulu.png').convert('L')

# Parametry kwantyzacji
levels = 16    # liczba poziomów kwantyzacji

# Kwantyzacja obrazu
quantized_image = image.point(lambda p: p * (levels - 1) // 255 * 255 // (levels - 1))

# Wyświetlenie obrazu
plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
plt.imshow(image, cmap='gray')
plt.title('Obraz oryginalny')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(quantized_image, cmap='gray')
plt.title('Obraz po kwantyzacji')
plt.axis('off')
plt.show()
