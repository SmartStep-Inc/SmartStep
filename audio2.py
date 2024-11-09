import customtkinter as ctk
import serial
import pygame
import threading
import time

class SerialApp:
    def __init__(self, master):
        self.master = master
        self.master.title("SmartStep")

        self.title = ctk.CTkLabel(self.master, text="SmartStep", font=("Arial", 16, "bold"))
        self.title.pack(pady=10)
        
        # Create a non-editable text box
        self.text_box = ctk.CTkTextbox(self.master, width=400, height=300, state='disabled')
        self.text_box.pack(pady=10)

        # Initialize Pygame mixer
        pygame.mixer.init()

        # Initialize Serial port (replace 'COM6' with your Arduino's port)
        self.ser = serial.Serial('COM6', 9600)
        
        # State flag
        self.sound_playing = False

        # Start the serial thread
        self.serial_thread = threading.Thread(target=self.read_serial, daemon=True)
        self.serial_thread.start()

    def read_serial(self):
        while True:
            if self.ser.in_waiting > 0:  # Check for incoming data from Arduino
                line = self.ser.readline().decode('utf-8').rstrip()  # Read the data
                print(f"Received: {line}")  # Debug output
                self.update_text_box(line)  # Update GUI text box
                self.process_command(line)

    def process_command(self, line):
        if line == "BLOCKED":  # Blocked command received
            time.sleep(0.5)
            self.stop_sound()  # Stop any current sound
            self.play_sound("Blocked.mp3")  # Play the blocked sound
            print("Playing Blocked.mp3 (Blocked mode activated)")

        elif line == "STOP_SOUND":  # Stop sound command
            if self.sound_playing:  # Only stop if something is playing
                self.stop_sound()  # Stop the sound
                print("Stopped all sounds.")

        elif line == "PLAY_SOUND":  # Play sound command
            if not self.sound_playing:  # Only play if nothing is playing
                self.sound_playing = self.play_sound("warn.mp3")  # Play warning sound
                print("Playing warn.mp3 (Sound command received)")

    def play_sound(self, file):
        """Helper function to load and play sound."""
        pygame.mixer.music.load(file)
        pygame.mixer.music.play()
        self.sound_playing = True
        return True

    def stop_sound(self):
        """Helper function to stop the sound."""
        pygame.mixer.music.stop()
        self.sound_playing = False

    def update_text_box(self, text):
        """Update the text box with new data."""
        self.text_box.configure(state='normal')
        self.text_box.insert('end', text + '\n')
        self.text_box.configure(state='disabled')
        self.text_box.see('end')  # Scroll to the bottom

if __name__ == "__main__":
    ctk.set_appearance_mode("dark")  # Set the appearance mode
    ctk.set_default_color_theme("blue")  # Set the default color theme
    
    root = ctk.CTk()
    app = SerialApp(root)
    
    root.mainloop()
