from PIL import Image

# Wczytanie obrazu
image = Image.open('obraz.jpg').convert('L')

# Parametry binaryzacji
threshold = 128

# Binaryzacja obrazu
binary_image = image.point(lambda p: p > threshold and 255)

# Wyświetlenie obrazu
binary_image.show()
