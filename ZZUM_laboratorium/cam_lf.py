import time
from picamera2 import Picamera2
import cv2
import numpy as np

# Inicjalizacja kamery
picam2 = Picamera2()
picam2.start()
cX=0
# Poczekaj na ustawienie kamery
time.sleep(2)

image = picam2.capture_array()
cv2.imwrite('/home/roosterpi/Documents/Github/dk_projects/ZZUM_laboratorium/cam_/lf_original_image.jpg', image)

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
    lower_thresh = int(max(0, 0.66 * mean_intensity))
    upper_thresh = int(min(255, 1.03 * mean_intensity))

    # Detekcja krawędzi (Canny) z dynamicznymi progami
    edges = cv2.Canny(blurred_img, threshold1=lower_thresh, threshold2=upper_thresh)

    # Dilatacja krawędzi, aby wzmocnić kontury
    kernel = np.ones((5, 5), np.uint8)
    dilated_edges = cv2.dilate(edges, kernel, iterations=2)

    # Znalezienie konturów
    contours, _ = cv2.findContours(dilated_edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    return contours, cropped_img, dilated_edges, start_height, end_height

# def search_for_centroid():

try:
    while True:
        # Przechwycenie bieżącej klatki
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
        lower_thresh = int(max(0, 0.66 * mean_intensity))
        upper_thresh = int(min(255, 1.03 * mean_intensity))

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

        write_images(cropped_img, dilated_edges)
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

            print(f"Środek: ({int(cX/6.4-50)})")
            write_images(centroid=True, cX=cX, cY=cY + start_height)
        else:
            print("Brak wykrytych konturów z niezerowym momentem.")
            print(f"Poprzedni srodek: ({int(cX/6.4-50)})")

        # TODO: Sterowanie silnikami

        # Interwał czasowy (np. 1 sekunda)
        time.sleep(1)

except KeyboardInterrupt:
    print("Przerwano działanie programu.")

finally:
    # Zwolnienie zasobów kamery po zakończeniu
    picam2.stop()
