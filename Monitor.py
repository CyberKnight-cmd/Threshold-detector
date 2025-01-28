# import serial
# import matplotlib.pyplot as plt
# import time
# from collections import deque

# # Serial port configuration
# SERIAL_PORT = 'COM3'  # Update with your Arduino's port
# BAUD_RATE = 9600
# REFRESH_INTERVAL = 1  # Plot update interval in seconds
# PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot

# # Initialize serial connection
# try:
#     arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
#     print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
# except serial.SerialException as e:
#     print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
#     exit()

# # Initialize a deque to store the last PLOT_DURATION seconds of data
# data_buffer = deque(maxlen=PLOT_DURATION)

# # Real-time plotting setup
# plt.ion()
# fig, ax = plt.subplots()
# line, = ax.plot([], [], label="Noise Fluctuations")
# ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
# ax.set_xlim(0, PLOT_DURATION)
# ax.set_xlabel("Time (s)")
# ax.set_ylabel("Fluctuations")
# ax.set_title("Real-Time Noise Fluctuations")
# ax.legend()
# fig.show()

# def update_plot():
#     """Update the plot with new data."""
#     line.set_xdata(range(len(data_buffer)))
#     line.set_ydata(data_buffer)
#     ax.relim()
#     ax.autoscale_view()
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# try:
#     print("Starting data collection...")
#     start_time = time.time()

#     while True:
#         # Read data from Arduino
#         if arduino.in_waiting > 0:
#             line_data = arduino.readline().decode('utf-8').strip()
#             if line_data.startswith("Fluctuations"):
#                 # Extract fluctuation count
#                 fluctuation_value = int(line_data.split(":")[1].strip())
#                 data_buffer.append(fluctuation_value)

#                 # Print to console (optional)
#                 print(f"Received Fluctuation Count: {fluctuation_value}")

#         # Update the plot at the specified interval
#         if time.time() - start_time >= REFRESH_INTERVAL:
#             update_plot()
#             start_time = time.time()

# except KeyboardInterrupt:
#     print("\nData collection stopped by user.")
# finally:
#     arduino.close()
#     print("Serial connection closed.")




# import serial
# import matplotlib.pyplot as plt
# import time
# from collections import deque
# import csv
# import os

# # Serial port configuration
# SERIAL_PORT = 'COM3'  # Update with your Arduino's port
# BAUD_RATE = 9600
# REFRESH_INTERVAL = 1  # Plot update interval in seconds
# PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot
# CSV_FILE = "noise_data.csv"  # Output CSV file name

# # Noise level thresholds
# FLUCTUATION_COUNT_LOW = 20  # Low threshold
# FLUCTUATION_COUNT_MEDIUM = 55  # Medium threshold
# FLUCTUATION_COUNT_HIGH = 75  # High threshold

# # Initialize serial connection
# try:
#     arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
#     print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
# except serial.SerialException as e:
#     print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
#     exit()

# # Initialize a deque to store the last PLOT_DURATION seconds of data
# data_buffer = deque(maxlen=PLOT_DURATION)

# # CSV file initialization
# if not os.path.exists(CSV_FILE):
#     with open(CSV_FILE, mode="w", newline="") as file:
#         writer = csv.writer(file)
#         writer.writerow(["Timestamp", "Fluctuation Count"])  # Write CSV header

# # Real-time plotting setup
# plt.ion()
# fig, ax = plt.subplots()
# line, = ax.plot([], [], label="Noise Fluctuations", color='blue')
# threshold_annotation = ax.annotate(
#     "", xy=(0.8, 0.9), xycoords="axes fraction", fontsize=10, color="red"
# )
# ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
# ax.set_xlim(0, PLOT_DURATION)
# ax.set_xlabel("Time (s)")
# ax.set_ylabel("Fluctuations")
# ax.set_title("Real-Time Noise Fluctuations")
# ax.legend()
# fig.show()

# def update_plot(current_threshold):
#     """Update the plot with new data and the threshold annotation."""
#     line.set_xdata(range(len(data_buffer)))
#     line.set_ydata(data_buffer)
#     ax.relim()
#     ax.autoscale_view()
#     threshold_annotation.set_text(f"Threshold: {current_threshold}")
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# try:
#     print("Starting data collection...")
#     start_time = time.time()

#     while True:
#         # Read data from Arduino
#         if arduino.in_waiting > 0:
#             line_data = arduino.readline().decode('utf-8').strip()
#             if line_data.startswith("Fluctuations"):
#                 # Extract fluctuation count
#                 fluctuation_value = int(line_data.split(":")[1].strip())
#                 data_buffer.append(fluctuation_value)

#                 # Save data to CSV
#                 with open(CSV_FILE, mode="a", newline="") as file:
#                     writer = csv.writer(file)
#                     writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), fluctuation_value])

#                 # Print to console (optional)
#                 print(f"Received Fluctuation Count: {fluctuation_value}")

#         # Update the plot at the specified interval
#         if time.time() - start_time >= REFRESH_INTERVAL:
#             # Determine the current threshold
#             if len(data_buffer) > 0:
#                 latest_value = data_buffer[-1]
#                 if latest_value >= FLUCTUATION_COUNT_HIGH:
#                     current_threshold = "HIGH"
#                 elif latest_value >= FLUCTUATION_COUNT_MEDIUM:
#                     current_threshold = "MEDIUM"
#                 elif latest_value >= FLUCTUATION_COUNT_LOW:
#                     current_threshold = "LOW"
#                 else:
#                     current_threshold = "SILENT"

#                 update_plot(current_threshold)
#             start_time = time.time()

# except KeyboardInterrupt:
#     print("\nData collection stopped by user.")
# finally:
#     arduino.close()
#     print("Serial connection closed.")

# # Post-processing: Analyze the saved data
# try:
#     print("Analyzing recorded data...")
#     total_records = 0
#     silent_records = 0

#     with open(CSV_FILE, mode="r") as file:
#         reader = csv.DictReader(file)
#         for row in reader:
#             total_records += 1
#             if int(row["Fluctuation Count"]) < FLUCTUATION_COUNT_LOW:
#                 silent_records += 1

#     if total_records > 0:
#         silence_percentage = (silent_records / total_records) * 100
#         print(f"Class Silence Percentage: {silence_percentage:.2f}%")
#     else:
#         print("No data recorded.")
# except Exception as e:
#     print(f"Error during analysis: {e}")




# import pygame
# import serial
# import time
# import csv
# import os
# import matplotlib.pyplot as plt
# from collections import deque

# # Constants
# SERIAL_PORT = 'COM3'  # Update with your Arduino's port
# BAUD_RATE = 9600
# REFRESH_INTERVAL = 1  # Plot update interval in seconds
# PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot
# CSV_FILE = "noise_data.csv"  # Output CSV file name
# FLUCTUATION_COUNT_LOW = 20  # Low threshold
# FLUCTUATION_COUNT_MEDIUM = 55  # Medium threshold
# FLUCTUATION_COUNT_HIGH = 75  # High threshold
# SCREEN_WIDTH = 800
# SCREEN_HEIGHT = 600

# # Initialize Pygame
# pygame.init()
# screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
# pygame.display.set_caption("Noise Level Monitor")
# font = pygame.font.SysFont('Arial', 24)

# # Button Class
# class Button:
#     def __init__(self, x, y, width, height, color, text, action=None):
#         self.rect = pygame.Rect(x, y, width, height)
#         self.color = color
#         self.text = text
#         self.action = action

#     def draw(self, screen):
#         pygame.draw.rect(screen, self.color, self.rect)
#         text_surf = font.render(self.text, True, (0, 255, 0))  # Green text
#         screen.blit(text_surf, (self.rect.x + (self.rect.width - text_surf.get_width()) // 2,
#                                self.rect.y + (self.rect.height - text_surf.get_height()) // 2))

#     def is_pressed(self, event):
#         if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
#             if self.action:
#                 self.action()

# # Serial port initialization
# try:
#     arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
#     print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
# except serial.SerialException as e:
#     print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
#     exit()

# # Initialize deque and CSV file
# data_buffer = deque(maxlen=PLOT_DURATION)

# if not os.path.exists(CSV_FILE):
#     with open(CSV_FILE, mode="w", newline="") as file:
#         writer = csv.writer(file)
#         writer.writerow(["Timestamp", "Fluctuation Count"])  # Write CSV header

# # Real-time plotting setup
# plt.ion()
# fig, ax = plt.subplots()
# line, = ax.plot([], [], label="Noise Fluctuations", color='green')
# threshold_annotation = ax.annotate(
#     "", xy=(0.8, 0.9), xycoords="axes fraction", fontsize=10, color="red"
# )
# ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
# ax.set_xlim(0, PLOT_DURATION)
# ax.set_xlabel("Time (s)")
# ax.set_ylabel("Fluctuations")
# ax.set_title("Real-Time Noise Fluctuations")
# ax.legend()
# fig.show()

# # Function to update the plot
# def update_plot(current_threshold):
#     """Update the plot with new data and the threshold annotation."""
#     line.set_xdata(range(len(data_buffer)))
#     line.set_ydata(data_buffer)
#     ax.relim()
#     ax.autoscale_view()
#     threshold_annotation.set_text(f"Threshold: {current_threshold}")
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# # Function to handle Start Data Collection
# def start_data_collection():
#     print("Starting data collection...")
#     start_time = time.time()

#     while True:
#         # Read data from Arduino
#         if arduino.in_waiting > 0:
#             line_data = arduino.readline().decode('utf-8').strip()
#             if line_data.startswith("Fluctuations"):
#                 fluctuation_value = int(line_data.split(":")[1].strip())
#                 data_buffer.append(fluctuation_value)

#                 # Save data to CSV
#                 with open(CSV_FILE, mode="a", newline="") as file:
#                     writer = csv.writer(file)
#                     writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), fluctuation_value])

#                 # Print to console (optional)
#                 print(f"Received Fluctuation Count: {fluctuation_value}")

#         # Update the plot at the specified interval
#         if time.time() - start_time >= REFRESH_INTERVAL:
#             if len(data_buffer) > 0:
#                 latest_value = data_buffer[-1]
#                 if latest_value >= FLUCTUATION_COUNT_HIGH:
#                     current_threshold = "HIGH"
#                 elif latest_value >= FLUCTUATION_COUNT_MEDIUM:
#                     current_threshold = "MEDIUM"
#                 elif latest_value >= FLUCTUATION_COUNT_LOW:
#                     current_threshold = "LOW"
#                 else:
#                     current_threshold = "SILENT"
#                 update_plot(current_threshold)
#             start_time = time.time()

# # Function to handle Data Analyzation
# def analyze_data():
#     print("Analyzing recorded data...")
#     total_records = 0
#     silent_records = 0

#     with open(CSV_FILE, mode="r") as file:
#         reader = csv.DictReader(file)
#         for row in reader:
#             total_records += 1
#             if int(row["Fluctuation Count"]) < FLUCTUATION_COUNT_LOW:
#                 silent_records += 1

#     if total_records > 0:
#         silence_percentage = (silent_records / total_records) * 100
#         print(f"Class Silence Percentage: {silence_percentage:.2f}%")
#     else:
#         print("No data recorded.")

# # Setup buttons
# start_button = Button(50, 500, 200, 50, (0, 255, 0), "Start Data Collection", start_data_collection)
# analyze_button = Button(550, 500, 200, 50, (0, 255, 0), "Analyze Data", analyze_data)

# # Main loop
# def main():
#     running = True
#     while running:
#         screen.fill((0, 0, 0))  # Black background

#         # Event handling
#         for event in pygame.event.get():
#             if event.type == pygame.QUIT:
#                 running = False
#             start_button.is_pressed(event)
#             analyze_button.is_pressed(event)

#         # Draw buttons
#         start_button.draw(screen)
#         analyze_button.draw(screen)

#         # Update the display
#         pygame.display.flip()

#     pygame.quit()

# if __name__ == "__main__":
#     main()

# # Close serial connection at the end
# arduino.close()





# import pygame
# import serial
# import time
# import csv
# import os
# import matplotlib.pyplot as plt
# from collections import deque

# # Constants
# SERIAL_PORT = 'COM3'  # Update with your Arduino's port
# BAUD_RATE = 9600
# REFRESH_INTERVAL = 1  # Plot update interval in seconds
# PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot
# CSV_FILE = "noise_data.csv"  # Output CSV file name
# FLUCTUATION_COUNT_LOW = 40  # Low threshold
# FLUCTUATION_COUNT_MEDIUM = 70  # Medium threshold
# FLUCTUATION_COUNT_HIGH = 90  # High threshold
# SCREEN_WIDTH = 800
# SCREEN_HEIGHT = 600

# # Initialize Pygame
# pygame.init()
# screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
# pygame.display.set_caption("Noise Level Monitor")
# font = pygame.font.SysFont('Arial', 24)

# # Button Class
# class Button:
#     def __init__(self, x, y, width, height, color, text, action=None):
#         self.rect = pygame.Rect(x, y, width, height)
#         self.color = color
#         self.text = text
#         self.action = action

#     def draw(self, screen):
#         pygame.draw.rect(screen, self.color, self.rect)
#         text_surf = font.render(self.text, True, (0, 255, 0))  # Green text
#         screen.blit(text_surf, (self.rect.x + (self.rect.width - text_surf.get_width()) // 2,
#                                self.rect.y + (self.rect.height - text_surf.get_height()) // 2))

#     def is_pressed(self, event):
#         if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
#             if self.action:
#                 self.action()

# # Serial port initialization
# try:
#     arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
#     print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
# except serial.SerialException as e:
#     print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
#     exit()

# # Initialize deque and CSV file
# data_buffer = deque(maxlen=PLOT_DURATION)

# if not os.path.exists(CSV_FILE):
#     with open(CSV_FILE, mode="w", newline="") as file:
#         writer = csv.writer(file)
#         writer.writerow(["Timestamp", "Fluctuation Count"])  # Write CSV header

# # Real-time plotting setup
# plt.ion()
# fig, ax = plt.subplots(figsize=(6, 4))  # Adjust figure size
# line, = ax.plot([], [], label="Noise Fluctuations", color='green')
# threshold_annotation = ax.annotate(
#     "", xy=(0.8, 0.9), xycoords="axes fraction", fontsize=10, color="red"
# )
# ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
# ax.set_xlim(0, PLOT_DURATION)
# ax.set_xlabel("Time (s)")
# ax.set_ylabel("Fluctuations")
# ax.set_title("Real-Time Noise Fluctuations")
# ax.legend()
# ax.grid(True)  # Enable grid
# fig.canvas.draw()
# fig.canvas.flush_events()

# # Function to update the plot
# def update_plot(current_threshold):
#     """Update the plot with new data and the threshold annotation."""
#     line.set_xdata(range(len(data_buffer)))
#     line.set_ydata(data_buffer)
#     ax.relim()
#     ax.autoscale_view()
#     threshold_annotation.set_text(f"Threshold: {current_threshold}")
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# # Function to handle Start Data Collection
# def start_data_collection():
#     print("Starting data collection...")
#     start_time = time.time()

#     while True:
#         # Read data from Arduino
#         if arduino.in_waiting > 0:
#             line_data = arduino.readline().decode('utf-8').strip()
#             if line_data.startswith("Fluctuations"):
#                 fluctuation_value = int(line_data.split(":")[1].strip())
#                 data_buffer.append(fluctuation_value)

#                 # Save data to CSV
#                 with open(CSV_FILE, mode="a", newline="") as file:
#                     writer = csv.writer(file)
#                     writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), fluctuation_value])

#                 # Print to console (optional)
#                 print(f"Received Fluctuation Count: {fluctuation_value}")

#         # Update the plot at the specified interval
#         if time.time() - start_time >= REFRESH_INTERVAL:
#             if len(data_buffer) > 0:
#                 latest_value = data_buffer[-1]
#                 if latest_value >= FLUCTUATION_COUNT_HIGH:
#                     current_threshold = "HIGH"
#                 elif latest_value >= FLUCTUATION_COUNT_MEDIUM:
#                     current_threshold = "MEDIUM"
#                 elif latest_value >= FLUCTUATION_COUNT_LOW:
#                     current_threshold = "LOW"
#                 else:
#                     current_threshold = "SILENT"
#                 update_plot(current_threshold)
#             start_time = time.time()

# # Function to handle Data Analyzation
# def analyze_data():
#     print("Analyzing recorded data...")
#     total_records = 0
#     silent_records = 0

#     with open(CSV_FILE, mode="r") as file:
#         reader = csv.DictReader(file)
#         for row in reader:
#             total_records += 1
#             if int(row["Fluctuation Count"]) < FLUCTUATION_COUNT_LOW:
#                 silent_records += 1

#     if total_records > 0:
#         silence_percentage = (silent_records / total_records) * 100
#         print(f"Class Silence Percentage: {silence_percentage:.2f}%")
#     else:
#         print("No data recorded.")

# # Setup buttons
# start_button = Button(50, 500, 200, 50, (0, 255, 0), "Start Data Collection", start_data_collection)
# analyze_button = Button(550, 500, 200, 50, (0, 255, 0), "Analyze Data", analyze_data)

# # Main loop
# def main():
#     running = True
#     while running:
#         screen.fill((0, 0, 0))  # Black background

#         # Event handling
#         for event in pygame.event.get():
#             if event.type == pygame.QUIT:
#                 running = False
#             start_button.is_pressed(event)
#             analyze_button.is_pressed(event)

#         # Draw buttons
#         start_button.draw(screen)
#         analyze_button.draw(screen)

#         # Show the plot in Pygame window
#         plt.draw()
#         plt.pause(0.01)

#         # Update the display
#         pygame.display.flip()

#     pygame.quit()

# if __name__ == "__main__":
#     main()

# # Close serial connection at the end
# arduino.close()




# import pygame
# import serial
# import time
# import csv
# import os
# import matplotlib.pyplot as plt
# from collections import deque

# # Constants
# SERIAL_PORT = 'COM3'  # Update with your Arduino's port
# BAUD_RATE = 9600
# REFRESH_INTERVAL = 1  # Plot update interval in seconds
# PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot
# CSV_FILE = "noise_data.csv"  # Output CSV file name
# FLUCTUATION_COUNT_LOW = 40  # Low threshold
# FLUCTUATION_COUNT_MEDIUM = 70  # Medium threshold
# FLUCTUATION_COUNT_HIGH = 90  # High threshold
# SCREEN_WIDTH = 800
# SCREEN_HEIGHT = 600

# # Initialize Pygame
# pygame.init()
# screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
# pygame.display.set_caption("Noise Level Monitor")
# font = pygame.font.SysFont('Arial', 24)

# # Button Class
# class Button:
#     def __init__(self, x, y, width, height, color, text, action=None):
#         self.rect = pygame.Rect(x, y, width, height)
#         self.color = color
#         self.text = text
#         self.action = action

#     def draw(self, screen):
#         pygame.draw.rect(screen, self.color, self.rect)
#         text_surf = font.render(self.text, True, (0, 0, 0))  # Black text for visibility
#         screen.blit(text_surf, (self.rect.x + (self.rect.width - text_surf.get_width()) // 2,
#                                self.rect.y + (self.rect.height - text_surf.get_height()) // 2))

#     def is_pressed(self, event):
#         if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
#             if self.action:
#                 self.action()

# # Serial port initialization
# try:
#     arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
#     print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
# except serial.SerialException as e:
#     print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
#     exit()

# # Initialize deque and CSV file
# data_buffer = deque(maxlen=PLOT_DURATION)

# if not os.path.exists(CSV_FILE):
#     with open(CSV_FILE, mode="w", newline="") as file:
#         writer = csv.writer(file)
#         writer.writerow(["Timestamp", "Fluctuation Count"])  # Write CSV header

# # Real-time plotting setup
# plt.ion()
# fig, ax = plt.subplots(figsize=(6, 4))  # Adjust figure size
# line, = ax.plot([], [], label="Noise Fluctuations", color='green')
# threshold_annotation = ax.annotate(
#     "", xy=(0.8, 0.9), xycoords="axes fraction", fontsize=10, color="red"
# )
# ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
# ax.set_xlim(0, PLOT_DURATION)
# ax.set_xlabel("Time (s)")
# ax.set_ylabel("Fluctuations")
# ax.set_title("Real-Time Noise Fluctuations")
# ax.legend()
# ax.grid(True)  # Enable grid
# fig.canvas.draw()
# fig.canvas.flush_events()

# # Function to update the plot
# def update_plot(current_threshold):
#     """Update the plot with new data and the threshold annotation."""
#     line.set_xdata(range(len(data_buffer)))
#     line.set_ydata(data_buffer)
#     ax.relim()
#     ax.autoscale_view()
#     threshold_annotation.set_text(f"Threshold: {current_threshold}")
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# # Function to handle Start Data Collection
# def start_data_collection():
#     print("Starting data collection...")
#     start_time = time.time()

#     while True:
#         # Read data from Arduino
#         if arduino.in_waiting > 0:
#             line_data = arduino.readline().decode('utf-8').strip()
#             if line_data.startswith("Fluctuations"):
#                 fluctuation_value = int(line_data.split(":")[1].strip())
#                 data_buffer.append(fluctuation_value)

#                 # Save data to CSV
#                 with open(CSV_FILE, mode="a", newline="") as file:
#                     writer = csv.writer(file)
#                     writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), fluctuation_value])

#                 # Print to console (optional)
#                 print(f"Received Fluctuation Count: {fluctuation_value}")

#         # Update the plot at the specified interval
#         if time.time() - start_time >= REFRESH_INTERVAL:
#             if len(data_buffer) > 0:
#                 latest_value = data_buffer[-1]
#                 if latest_value >= FLUCTUATION_COUNT_HIGH:
#                     current_threshold = "HIGH"
#                 elif latest_value >= FLUCTUATION_COUNT_MEDIUM:
#                     current_threshold = "MEDIUM"
#                 elif latest_value >= FLUCTUATION_COUNT_LOW:
#                     current_threshold = "LOW"
#                 else:
#                     current_threshold = "SILENT"
#                 update_plot(current_threshold)
#             start_time = time.time()

# # Function to handle Data Analyzation
# def analyze_data():
#     print("Analyzing recorded data...")
#     total_records = 0
#     silent_records = 0

#     with open(CSV_FILE, mode="r") as file:
#         reader = csv.DictReader(file)
#         for row in reader:
#             total_records += 1
#             if int(row["Fluctuation Count"]) < FLUCTUATION_COUNT_LOW:
#                 silent_records += 1

#     if total_records > 0:
#         silence_percentage = (silent_records / total_records) * 100
#         print(f"Class Silence Percentage: {silence_percentage:.2f}%")
#     else:
#         print("No data recorded.")

# # Setup buttons
# start_button = Button(50, 500, 200, 50, (0, 255, 0), "Start Data Collection", start_data_collection)
# analyze_button = Button(550, 500, 200, 50, (0, 255, 0), "Show Data Analysis", analyze_data)  # Updated button label

# # Main loop
# def main():
#     running = True
#     while running:
#         screen.fill((0, 0, 0))  # Black background

#         # Event handling
#         for event in pygame.event.get():
#             if event.type == pygame.QUIT:
#                 running = False
#             start_button.is_pressed(event)
#             analyze_button.is_pressed(event)

#         # Draw buttons
#         start_button.draw(screen)
#         analyze_button.draw(screen)

#         # Show the plot in Pygame window
#         plt.draw()
#         plt.pause(0.01)

#         # Update the display
#         pygame.display.flip()

#     pygame.quit()

# if __name__ == "__main__":
#     main()

# # Close serial connection at the end
# arduino.close()



import pygame
import serial
import time
import csv
import os
import matplotlib.pyplot as plt
from collections import deque

# Constants
SERIAL_PORT = 'COM3'  # Update with your Arduino's port
BAUD_RATE = 9600
REFRESH_INTERVAL = 1  # Plot update interval in seconds
PLOT_DURATION = 20  # Duration (in seconds) of data to show on the plot
CSV_FILE = "noise_data.csv"  # Output CSV file name
FLUCTUATION_COUNT_LOW = 40  # Low threshold
FLUCTUATION_COUNT_MEDIUM = 70  # Medium threshold
FLUCTUATION_COUNT_HIGH = 90  # High threshold
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Noise Level Monitor")
font = pygame.font.SysFont('Arial', 24)
result_font = pygame.font.SysFont('Arial', 18)  # Smaller font for results

# Button Class
class Button:
    def __init__(self, x, y, width, height, color, text, action=None):
        self.rect = pygame.Rect(x, y, width, height)
        self.color = color
        self.text = text
        self.action = action

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)
        text_surf = font.render(self.text, True, (0, 0, 0))  # Black text for visibility
        screen.blit(text_surf, (self.rect.x + (self.rect.width - text_surf.get_width()) // 2,
                               self.rect.y + (self.rect.height - text_surf.get_height()) // 2))

    def is_pressed(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
            if self.action:
                self.action()

# Serial port initialization
try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"Error: Could not connect to {SERIAL_PORT}. {e}")
    exit()

# Initialize deque and CSV file
data_buffer = deque(maxlen=PLOT_DURATION)

if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Timestamp", "Fluctuation Count"])  # Write CSV header

# Real-time plotting setup
plt.ion()
fig, ax = plt.subplots(figsize=(6, 4))  # Adjust figure size
line, = ax.plot([], [], label="Noise Fluctuations", color='green')
threshold_annotation = ax.annotate(
    "", xy=(0.8, 0.9), xycoords="axes fraction", fontsize=10, color="red"
)
ax.set_ylim(0, 120)  # Adjust based on the maximum fluctuation count
ax.set_xlim(0, PLOT_DURATION)
ax.set_xlabel("Time (s)")
ax.set_ylabel("Fluctuations")
ax.set_title("Real-Time Noise Fluctuations")
ax.legend()
ax.grid(True)  # Enable grid
fig.canvas.draw()
fig.canvas.flush_events()

# Function to update the plot
def update_plot(current_threshold):
    """Update the plot with new data and the threshold annotation."""
    line.set_xdata(range(len(data_buffer)))
    line.set_ydata(data_buffer)
    ax.relim()
    ax.autoscale_view()
    threshold_annotation.set_text(f"Threshold: {current_threshold}")
    fig.canvas.draw()
    fig.canvas.flush_events()

# Function to handle Start Data Collection
def start_data_collection():
    print("Starting data collection...")
    start_time = time.time()

    while True:
        # Read data from Arduino
        if arduino.in_waiting > 0:
            line_data = arduino.readline().decode('utf-8').strip()
            if line_data.startswith("Fluctuations"):
                fluctuation_value = int(line_data.split(":")[1].strip())
                data_buffer.append(fluctuation_value)

                # Save data to CSV
                with open(CSV_FILE, mode="a", newline="") as file:
                    writer = csv.writer(file)
                    writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), fluctuation_value])

                # Print to console (optional)
                print(f"Received Fluctuation Count: {fluctuation_value}")

        # Update the plot at the specified interval
        if time.time() - start_time >= REFRESH_INTERVAL:
            if len(data_buffer) > 0:
                latest_value = data_buffer[-1]
                if latest_value >= FLUCTUATION_COUNT_HIGH:
                    current_threshold = "HIGH"
                elif latest_value >= FLUCTUATION_COUNT_MEDIUM:
                    current_threshold = "MEDIUM"
                elif latest_value >= FLUCTUATION_COUNT_LOW:
                    current_threshold = "LOW"
                else:
                    current_threshold = "SILENT"
                update_plot(current_threshold)
            start_time = time.time()

# Function to handle Data Analyzation
def analyze_data():
    print("Analyzing recorded data...")
    total_records = 0
    silent_records = 0
    silence_percentage = 0

    with open(CSV_FILE, mode="r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            total_records += 1
            if int(row["Fluctuation Count"]) < FLUCTUATION_COUNT_LOW:
                silent_records += 1

    if total_records > 0:
        silence_percentage = (silent_records / total_records) * 100
        result_text = f"Class Silence Percentage: {silence_percentage:.2f}%"
    else:
        result_text = "No data recorded."

    return result_text

# Setup buttons
start_button = Button(50, 500, 200, 50, (0, 255, 0), "Start Data Collection", start_data_collection)
analyze_button = Button(550, 500, 200, 50, (0, 255, 0), "Show Data Analysis", None)  # No action needed for display

# Main loop
def main():
    running = True
    result_text = ""  # To hold the result message
    
    try:
        while running:
            screen.fill((0, 0, 0))  # Black background

            # Event handling
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                start_button.is_pressed(event)
                analyze_button.is_pressed(event)

            # If "Analyze Data" is pressed, show the results
            if pygame.mouse.get_pressed()[0] and analyze_button.rect.collidepoint(pygame.mouse.get_pos()):
                result_text = analyze_data()

            # Draw buttons
            start_button.draw(screen)
            analyze_button.draw(screen)

            # Display the analysis result on the screen
            result_surface = result_font.render(result_text, True, (255, 255, 255))  # White text for results
            screen.blit(result_surface, (50, 450))  # Positioning the result

            # Show the plot in Pygame window
            plt.draw()
            plt.pause(0.01)

            # Update the display
            pygame.display.flip()
            

    except KeyboardInterrupt:
        print(analyze_data())

    pygame.quit()
if __name__ == "__main__":
    main()

# Close serial connection at the end
arduino.close()
