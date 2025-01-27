import RPi.GPIO as GPIO
# from picamera2 import Picamera2
import time
from picamera2 import Picamera2
import cv2
import numpy as np

# Inicjalizacja kamery z wyższą rozdzielczością
# camera = Picamera2()
# camera.resolution = (1920, 1080)  # Full HD
# camera.framerate = 30
# camera.brightness = 60
# camera.contrast = 50
# time.sleep(2)
# camera = cv2.VideoCapture(0)
# camera.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
# camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)


# Stałe PID i prędkości silników
KP = 4
KD = 4
M1_minimum_speed = 105
M2_minimum_speed = 105
M1_maximum_speed = 150
M2_maximum_speed = 150
# Piny GPIO
EMITTER_PIN = 2  # Sterowanie diodami IR (jeśli używane)
PWM_pin_A = 12  # PWM dla pierwszego silnika
AO1 = 25        # Kierunek pierwszego silnika
AO2 = 11
PWM_pin_B = 13  # PWM dla drugiego silnika
BO1 = 7        # Kierunek drugiego silnika
BO2 = 8

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

# Inicjalizacja PWM
pwm_B = GPIO.PWM(PWM_pin_A, 1000)  # PWM o częstotliwości 1kHz
pwm_A = GPIO.PWM(PWM_pin_B, 1000)
pwm_A.start(0)
pwm_B.start(0)


# Inicjalizacja kamery
picam2 = Picamera2()
picam2.start()
cX=0
# Poczekaj na ustawienie kamery
time.sleep(2)

image = picam2.capture_array()
cv2.imwrite('/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/lf_original_image.jpg', image)

# Silniki

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

# Kamera
def write_images(img1=None, img2=None, centroid=False, cX=0, cY=0):
    if centroid==False:
        cv2.imwrite('/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/lf_cropped.jpg', img1)
        cv2.imwrite('/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/lf_dilates.jpg', img2)
    else:
        output_img = image.copy()  # Tworzymy kopię, aby nie modyfikować oryginału
        cv2.circle(output_img, (cX, cY), 10, (0, 255, 0), -1)  # Zielony punkt
        # Nadpisanie obrazu z oznaczonym środkiem ciężkości
        filename = "/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/cropped_image_with_centroid.jpg"
        cv2.imwrite(filename, output_img)

def search_for_contures():
    image = picam2.capture_array()
    

    # Sprawdź wymiary obrazu
    height, width = image.shape[:2]

    # Przycinasz obraz (np. 60% do 80% wysokości)
    start_height = int(height * 0.8)
    end_height = int(height * 1)
    cropped_img = image[start_height:end_height, :]  # Wycinamy od 60% do 80% wysokości

    # Konwersja do skali szarości
    gray_img = cv2.cvtColor(cropped_img, cv2.COLOR_BGR2GRAY)

    # Filtracja przed binaryzacją (rozmycie Gaussa)
    blurred_img = cv2.GaussianBlur(gray_img, (9, 9), 0)

    # Obliczanie średniej jasności obrazu
    mean_intensity = np.mean(gray_img)
    # Ustalanie progów w zależności od średniej jasności
    lower_thresh = int(max(0, 0.86 * mean_intensity))
    upper_thresh = int(min(255, 1.03 * mean_intensity))

    # Detekcja krawędzi (Canny) z dynamicznymi progami
    edges = cv2.Canny(blurred_img, threshold1=lower_thresh, threshold2=upper_thresh)

    # Dilatacja krawędzi, aby wzmocnić kontury
    kernel = np.ones((5, 5), np.uint8)
    dilated_edges = cv2.dilate(edges, kernel, iterations=4)

    # Znalezienie konturów
    contours, _ = cv2.findContours(dilated_edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    return contours, cropped_img, dilated_edges, start_height, end_height

def search_for_centroid(image):
     # Przechwycenie bieżącej klatki
    global cX
    # Sprawdź wymiary obrazu
    height, width = image.shape[:2]

    # Przycinasz obraz (np. 60% do 80% wysokości)
    start_height = int(height * 0.8)
    end_height = int(height * 1)
    cropped_img = image[start_height:end_height, :]  # Wycinamy od 60% do 80% wysokości

    # Konwersja do skali szarości
    gray_img = cv2.cvtColor(cropped_img, cv2.COLOR_BGR2GRAY)

    # Filtracja przed binaryzacją (rozmycie Gaussa)
    blurred_img = cv2.GaussianBlur(gray_img, (9, 9), 0)


    hist = cv2.calcHist([gray_img], [0], None, [256], [0, 256])
    # cv2.imwrite('/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/lf_hist.jpg', hist)

    # Obliczanie średniej jasności obrazu
    mean_intensity = np.mean(gray_img)
    # Ustalanie progów w zależności od średniej jasności
    lower_thresh = int(max(0, 0.33 * mean_intensity))
    upper_thresh = int(min(255, 0.73 * mean_intensity))

    # Detekcja krawędzi (Canny) z dynamicznymi progami
    edges = cv2.Canny(blurred_img, threshold1=lower_thresh, threshold2=upper_thresh)

    # Dilatacja krawędzi, aby wzmocnić kontury
    kernel = np.ones((5, 5), np.uint8)
    dilated_edges = cv2.dilate(edges, kernel, iterations=2)

    # Znalezienie konturów
    contours, _ = cv2.findContours(dilated_edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # contours, cropped_img, dilated_edges, start_height, _ = search_for_contures()
    # Obliczenie łącznego momentu dla wszystkich konturów
    M_total = {'m00': 0, 'm10': 0, 'm01': 0}

    # write_images(cropped_img, dilated_edges)
    for contour in contours:
        M = cv2.moments(contour)
        if M["m00"] > 0:
            M_total['m00'] += M['m00']
            M_total['m10'] += M['m10']
            M_total['m01'] += M['m01']

    # Obliczenie środka ciężkości
    if M_total["m00"] > 0:
        cX = int(M_total["m10"] / M_total["m00"])
        cY = int(M_total["m01"] / M_total["m00"])

        #print(f"Środek: ({int(cX/6.4-50)})")
        # write_images(centroid=True, cX=cX, cY=cY + start_height)
    else:
        #print("Brak wykrytych konturów z niezerowym momentem.")
        #print(f"Poprzedni srodek: ({int(cX/6.4-50)})")
        pass
    return int(cX/6.4)


try:
    previous_pos = 0
    last_error = 0
    while True:
        cX = search_for_centroid(image=image)
        print(f"Środek: ({cX})")    
        # if cX<30 and previous_pos>90:
        #     cX=98
        image = picam2.capture_array()
        # # TODO:Sterowanie silnikami
        # error = cX
        error = cX -12

        motor_speed = KP * error + KD * (error - last_error)
        last_error = error

        left_motor_speed = (M1_minimum_speed + motor_speed)
        right_motor_speed = (M2_minimum_speed - motor_speed)
        time.sleep(0.001)
        print("L:",left_motor_speed,"R:",right_motor_speed)

        set_motors(left_motor_speed, right_motor_speed)
        # time.sleep(0.01)  # 10ms pętla

        # Interwał czasowy (np. 1 sekunda)
        print("pos:",cX,"prev:",previous_pos,"error:",error,"motorspeed:", motor_speed)
        previous_pos = cX
        time.sleep(0.001)

except KeyboardInterrupt:
    print("Przerwano działanie programu.")
    pwm_A.stop()
    pwm_B.stop()
    GPIO.cleanup()
    print("\nProgram zatrzymany.")

finally:
    # Zwolnienie zasobów kamery po zakończeniu
    picam2.stop()
