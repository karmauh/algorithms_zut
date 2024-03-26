import numpy as np
import matplotlib.pyplot as plt

# Parametry sygnału
amp = 1         # amplituda sygnału
freq = 10       # częstotliwość sygnału (Hz)
duration = 1    # czas trwania sygnału (s)
fs = 50         # częstotliwość próbkowania (Hz)

# Generowanie sygnału
t = np.arange(0, duration, 1/fs)
signal = amp * np.sin(2 * np.pi * freq * t)

# Wykres sygnału
plt.figure(figsize=(10, 4))
plt.plot(t, signal, label='Sygnał oryginalny')
plt.title('Dyskretyzacja sygnału')
plt.xlabel('Czas [s]')
plt.ylabel('Amplituda')
plt.grid(True)
plt.legend()
plt.show()
