import RPi.GPIO as GPIO
import time

# Stałe PID i prędkości silników
KP = 4
KD = 4
M1_minimum_speed = 100
M2_minimum_speed = 100
M1_maximum_speed = 250
M2_maximum_speed = 250
NUM_SENSORS = 5  # liczba używanych czujników
TIMEOUT = 0.0025  # 2500 us w sekundach
DEBUG = False

# Piny GPIO
EMITTER_PIN = 2  # Sterowanie diodami IR (jeśli używane)
PWM_pin_A = 12  # PWM dla pierwszego silnika
AO1 = 25        # Kierunek pierwszego silnika
AO2 = 11
PWM_pin_B = 13  # PWM dla drugiego silnika
BO1 = 7        # Kierunek drugiego silnika
BO2 = 8

# Czujniki
sensor_pins = [23, 21, 20, 16, 26]  # Piny GPIO dla czujników (QTR-8RC)

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
pwm_B = GPIO.PWM(PWM_pin_A, 1000)  # PWM o częstotliwości 1kHz
pwm_A = GPIO.PWM(PWM_pin_B, 1000)
pwm_A.start(0)
pwm_B.start(0)


def setup_pins():
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
    print("Piny GPIO zostały poprawnie skonfigurowane.")


def read_sensors():
    """Odczytuje wartości czujników."""
    durations = [0] * len(sensor_pins)

    # Ładowanie kondensatorów
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.HIGH)
    time.sleep(0.01)

    # Przełącz piny na wejścia
    start_time = time.time()
    for pin in sensor_pins:
        GPIO.setup(pin, GPIO.IN)

    while True:
        all_done = True
        current_time = time.time()
        elapsed = (current_time - start_time) * 1000  # w milisekundach
        for i, pin in enumerate(sensor_pins):
            if durations[i] == 0 and GPIO.input(pin) == GPIO.LOW:
                durations[i] = elapsed
            if durations[i] == 0:
                all_done = False
        if all_done or elapsed > TIMEOUT * 1000:  # Przerwij po czasie timeout
            break

    return durations


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
    if DEBUG:
        print("Raw values:", raw_values)
        print("Normalized values:", normalized)

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
        setup_pins()
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
