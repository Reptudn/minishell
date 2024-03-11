import pyautogui
import keyboard
import time
import math

# width, height = pyautogui.size()
# centerX = width / 2
# centerY = height / 2
# pyautogui.moveTo(centerX, centerY)

# y, x = pyautogui.position()

# radius = 10
# angle = 0

while True:
	if (keyboard.is_pressed('q')):
		break
	# newX = x + math.cos(angle) * radius
	# newY = y + math.sin(angle) * radius
	# pyautogui.moveTo(newX, newY)
	# angle += 0.1
	# if angle >= 2 * math.pi:
	# 	angle = 0
	time.sleep(0.5)