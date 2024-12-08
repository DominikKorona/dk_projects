import RPi.GPIO as GPIO
import time

# Stałe
KP = 4
KD = 5
M1_MINIMUM_SPEED = 150
M2_MINIMUM_SPEED = 150
M1_MAXIMUM_SPEED = 250
M2_MAXIMUM_SPEED = 250
NUM_SENSORS = 5

# Piny GPIO
PWM_PIN_A = 12  # GPIO __ (PWM0)
PWM_PIN_B = 13  # GPIO __ (PWM1)
AO1 = 24
AO2 = 23
BO1 = 28
BO2 = 26

# Inicjalizacja GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup([PWM_PIN_A, PWM_PIN_B, AO1, AO2, BO1, BO2], GPIO.OUT)

# PWM
pwm_a = GPIO.PWM(PWM_PIN_A, 100)  # 100 Hz
pwm_b = GPIO.PWM(PWM_PIN_B, 100)
pwm_a.start(0)
pwm_b.start(0)

# Funkcja ustawiająca prędkość silników
def set_motors(motor1_speed, motor2_speed):
    motor1_speed = max(0, min(M1_MAXIMUM_SPEED, motor1_speed))
    motor2_speed = max(0, min(M2_MAXIMUM_SPEED, motor2_speed))
    
    pwm_a.ChangeDutyCycle(motor1_speed / 2.55)  # Przeliczenie na % duty cycle
    pwm_b.ChangeDutyCycle(motor2_speed / 2.55)
    
    GPIO.output(AO1, GPIO.LOW)
    GPIO.output(AO2, GPIO.HIGH)
    GPIO.output(BO1, GPIO.LOW)
    GPIO.output(BO2, GPIO.HIGH)

# Kalibracja (symulacja, brak rzeczywistej funkcji kalibracji)
def manual_calibration():
    print("Kalibracja zakończona (symulacja)")

# Główna pętla
def main():
    last_error = 0
    manual_calibration()
    
    while True:
        # Symulacja odczytu pozycji (zastąp rzeczywistym odczytem z czujników)
        position = 2000  # Przykładowa wartość środka linii
        error = position - 2000
        
        motor_speed = KP * error + KD * (error - last_error)
        last_error = error
        
        left_motor_speed = M1_MINIMUM_SPEED + motor_speed
        right_motor_speed = M2_MINIMUM_SPEED - motor_speed
        
        set_motors(left_motor_speed, right_motor_speed)
        time.sleep(0.01)  # Małe opóźnienie w pętli

# Start programu
try:
    main()
except KeyboardInterrupt:
    print("Zatrzymanie programu.")
finally:
    pwm_a.stop()
    pwm_b.stop()
    GPIO.cleanup()