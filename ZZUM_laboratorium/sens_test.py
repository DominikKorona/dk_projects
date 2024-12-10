import RPi.GPIO as GPIO
import time

# Konfiguracja pinów dla czujników
sensor_pins = [23, 21, 20, 16, 26]  # Dostosuj do swojej konfiguracji
# sensor_pins = [24, 23, 21, 20, 16, 26, 19, 18]  # Piny GPIO dla czujników (QTR-8RC)

# Funkcja do inicjalizacji GPIO
def setup_pins():
    GPIO.setmode(GPIO.BCM)
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
    print("Piny GPIO zostały poprawnie skonfigurowane.")

# Funkcja do pomiaru czasu reakcji czujnika
def read_sensors():
    # Naładuj kondensatory
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.HIGH)
    time.sleep(0.01)  # Krótki czas ładowania

    # Przełącz na wejście i zmierz czas
    start_time = time.time()
    durations = [0] * len(sensor_pins)

    for i, pin in enumerate(sensor_pins):
        GPIO.setup(pin, GPIO.IN)

    while True:
        all_done = True
        current_time = time.time()
        elapsed = (current_time - start_time) * 1000  # Czas w milisekundach
        for i, pin in enumerate(sensor_pins):
            if durations[i] == 0 and GPIO.input(pin) == GPIO.LOW:
                durations[i] = elapsed
            if durations[i] == 0:
                all_done = False
        if all_done or elapsed > 1000:  # Limit czasu 1s
            break

    return durations

# Funkcja do normalizacji wyników do zakresu [0, 1]
def normalize_readings(readings, min_time, max_time):
    normalized = []
    for value in readings:
        if value <= min_time:
            norm = 0
        elif value >= max_time:
            norm = 1
        else:
            norm = (value - min_time) / (max_time - min_time)
            norm = 0
        normalized.append(norm)
    return normalized


def calibrate_sensors(iterations=100):
    print("Rozpoczynam kalibrację. Umieść czujniki na białej powierzchni.")
    time.sleep(2)
    min_time = float('inf')
    max_time = 0

    for _ in range(iterations):
        readings = read_sensors()
        min_time = min(min_time, *readings)
        max_time = max(max_time, *readings)

    print("Kalibracja zakończona.")
    print(f"Minimalny czas (biały): {min_time:.4f} ms")
    print(f"Maksymalny czas (czarny): {max_time:.4f} ms")
    return min_time, max_time

# Główna pętla
def main():
    try:
        setup_pins()  # Ustawienie trybu GPIO i konfiguracji pinów
        min_time, max_time = calibrate_sensors()
        print(min_time)
        print(max_time)
        
        while True:
            readings = read_sensors()
            # max_time = 0.09
            max_time = 0.5
            normalized = normalize_readings(readings, min_time, max_time)
            print("Odczyty:", readings)
            print("Znormalizowane:", normalized)
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("Przerwanie przez użytkownika.")
    finally:
        GPIO.cleanup()


if __name__ == "__main__":
    main()
