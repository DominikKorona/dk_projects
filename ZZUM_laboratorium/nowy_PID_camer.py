import RPi.GPIO as GPIO
from picamera2 import Picamera2
import time
import cv2
import numpy as np

# Stałe PID
KP = 3.5
KD = 5.0
KI = 0.01  # Dodano składnik całkujący
M1_minimum_speed = 75
M2_minimum_speed = 75
M1_maximum_speed = 160
M2_maximum_speed = 160

# Piny GPIO
PWM_pin_A = 12
AO1 = 25
AO2 = 11
PWM_pin_B = 13
BO1 = 7
BO2 = 8

# Konfiguracja GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(PWM_pin_A, GPIO.OUT)
GPIO.setup(PWM_pin_B, GPIO.OUT)
GPIO.setup(AO1, GPIO.OUT)
GPIO.setup(AO2, GPIO.OUT)
GPIO.setup(BO1, GPIO.OUT)
GPIO.setup(BO2, GPIO.OUT)

# Inicjalizacja PWM
pwm_A = GPIO.PWM(PWM_pin_A, 1000)
pwm_B = GPIO.PWM(PWM_pin_B, 1000)
pwm_A.start(0)
pwm_B.start(0)

# Kamera
picam2 = Picamera2()
picam2.start()
time.sleep(2)

def set_motors(motor1speed, motor2speed):
    """Ustawienie prędkości silników z ograniczeniem."""
    motor1speed = max(M1_minimum_speed, min(M1_maximum_speed, motor1speed))
    motor2speed = max(M2_minimum_speed, min(M2_maximum_speed, motor2speed))
    pwm_A.ChangeDutyCycle(motor1speed / 255 * 100)
    pwm_B.ChangeDutyCycle(motor2speed / 255 * 100)
    GPIO.output(AO1, GPIO.HIGH)
    GPIO.output(AO2, GPIO.LOW)
    GPIO.output(BO1, GPIO.HIGH)
    GPIO.output(BO2, GPIO.LOW)

def process_frame():
    """Przetwarzanie obrazu w celu znalezienia środka ciężkości linii."""
    image = picam2.capture_array()
    height, width = image.shape[:2]
    cropped_img = image[int(height * 0.8):, :]
    gray_img = cv2.cvtColor(cropped_img, cv2.COLOR_BGR2GRAY)
    blurred_img = cv2.GaussianBlur(gray_img, (5, 5), 0)
    _, binary_img = cv2.threshold(blurred_img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    contours, _ = cv2.findContours(binary_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        largest_contour = max(contours, key=cv2.contourArea)
        M = cv2.moments(largest_contour)
        if M["m00"] > 0:
            cX = int(M["m10"] / M["m00"])
            return cX, width
    return None, width

def pid_control(cX, width, last_error, integral):
    """Obliczanie sygnału sterującego za pomocą PID."""
    error = (cX - width // 2) if cX is not None else last_error
    integral += error
    derivative = error - last_error
    motor_speed = KP * error + KD * derivative + KI * integral
    return motor_speed, error, integral

try:
    last_error = 0
    integral = 0
    while True:
        cX, width = process_frame()
        motor_speed, last_error, integral = pid_control(cX, width, last_error, integral)

        left_motor_speed = M1_minimum_speed + motor_speed
        right_motor_speed = M2_minimum_speed - motor_speed
        set_motors(left_motor_speed, right_motor_speed)

        time.sleep(0.01)
except KeyboardInterrupt:
    pwm_A.stop()
    pwm_B.stop()
    GPIO.cleanup()