import RPi.GPIO as GPIO
import time

# Stałe PID i prędkości silników
KP = 3
KD = 4
M1_minimum_speed = 150
M2_minimum_speed = 150
M1_maximum_speed = 250
M2_maximum_speed = 250
NUM_SENSORS = 5  # liczba używanych czujników
TIMEOUT = 0.0025  # 2500 us w sekundach
DEBUG = False

# Piny GPIO (ustaw według podłączenia na Raspberry Pi 4B)
EMITTER_PIN = 2  # Sterowanie diodami IR (jeśli używane)
PWM_pin_A = 18  # PWM dla pierwszego silnika
AO1 = 23        # Kierunek pierwszego silnika
AO2 = 24
PWM_pin_B = 13  # PWM dla drugiego silnika
BO1 = 27        # Kierunek drugiego silnika
BO2 = 22

sensor_pins = [17, 4, 3, 2, 14]  # Piny GPIO dla czujników (QTR-8RC)

# Konfiguracja GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Konfiguracja pinów silników
GPIO.setup(PWM_pin_A, GPIO.OUT)
GPIO.setup(PWM_pin_B, GPIO.OUT)
GPIO.setup(AO1, GPIO.OUT)
GPIO.setup(AO2, GPIO.OUT)
GPIO.setup(BO1, GPIO.OUT)
GPIO.setup(BO2, GPIO.OUT)

# Konfiguracja czujników
for pin in sensor_pins:
    GPIO.setup(pin, GPIO.OUT)

# Inicjalizacja PWM
pwm_A = GPIO.PWM(PWM_pin_A, 1000)  # PWM o częstotliwości 1kHz
pwm_B = GPIO.PWM(PWM_pin_B, 1000)
pwm_A.start(0)
pwm_B.start(0)


def read_sensors():
    """Odczytuje wartości czujników QTR-8RC."""
    values = []
    # Ustaw wszystkie piny jako wyjście i ustaw na HIGH, aby naładować kondensatory
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.HIGH)
    time.sleep(0.00001)  # 10 µs na naładowanie

    # Ustaw wszystkie piny jako wejście i mierz czas rozładowania
    start_time = time.time()
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.IN)

    # Sprawdź, ile czasu potrzeba na rozładowanie
    while time.time() - start_time < TIMEOUT:
        elapsed_time = time.time() - start_time
        for i, pin in enumerate(sensor_pins):
            if GPIO.input(pin) == GPIO.LOW and len(values) <= i:
                values.append(elapsed_time)

    # Uzupełnij brakujące wartości, jeśli piny nie zdążyły przejść na LOW
    while len(values) < NUM_SENSORS:
        values.append(TIMEOUT)

    return values


def calibrate_sensors():
    """Kalibracja czujników."""
    min_values = [float('inf')] * NUM_SENSORS
    max_values = [0] * NUM_SENSORS

    print("Kalibracja... Przesuń czujnik nad linią!")
    for _ in range(250):
        values = read_sensors()
        for i in range(NUM_SENSORS):
            min_values[i] = min(min_values[i], values[i])
            max_values[i] = max(max_values[i], values[i])
        time.sleep(0.02)

    if DEBUG:
        print("Min values:", min_values)
        print("Max values:", max_values)

    return min_values, max_values


def read_line(min_values, max_values):
    """Odczyt wartości z czujników i obliczenie pozycji linii."""
    raw_values = read_sensors()
    normalized = [
        max(0, min(1000, 1000 * (raw_values[i] - min_values[i]) // (max_values[i] - min_values[i] + 1)))
        for i in range(NUM_SENSORS)
    ]
    weighted_sum = sum(i * 1000 * val for i, val in enumerate(normalized))
    total = sum(normalized)
    position = weighted_sum // total if total > 0 else 0
    return position, normalized


def set_motors(motor1speed, motor2speed):
    """Ustawienie prędkości silników."""
    motor1speed = max(0, min(M1_maximum_speed, motor1speed))
    motor2speed = max(0, min(M2_maximum_speed, motor2speed))

    pwm_A.ChangeDutyCycle(motor1speed / 255 * 100)
    pwm_B.ChangeDutyCycle(motor2speed / 255 * 100)

    GPIO.output(AO1, GPIO.HIGH)
    GPIO.output(AO2, GPIO.LOW)
    GPIO.output(BO1, GPIO.HIGH)
    GPIO.output(BO2, GPIO.LOW)


def main():
    try:
        min_values, max_values = calibrate_sensors()
        last_error = 0

        while True:
            position, sensor_values = read_line(min_values, max_values)
            error = position - 2000

            motor_speed = KP * error + KD * (error - last_error)
            last_error = error

            left_motor_speed = M1_minimum_speed + motor_speed
            right_motor_speed = M2_minimum_speed - motor_speed

            set_motors(left_motor_speed, right_motor_speed)
            time.sleep(0.01)  # 10ms pętla
    except KeyboardInterrupt:
        pwm_A.stop()
        pwm_B.stop()
        GPIO.cleanup()
        print("\nProgram zatrzymany.")


if __name__ == "__main__":
    main()
