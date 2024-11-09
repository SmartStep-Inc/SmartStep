import serial
import pygame
import time

# Initialize Serial port (replace 'COM6' with your Arduino's port)
ser = serial.Serial('COM6', 9600)
pygame.mixer.init()

# State flags
sound_playing = False

def play_sound(file):
    """Helper function to load and play sound."""
    pygame.mixer.music.load(file)
    pygame.mixer.music.play()
    return True

def stop_sound():
    """Helper function to stop the sound."""
    pygame.mixer.music.stop()
    return False

while True:
    if ser.in_waiting > 0:  # Check for incoming data from Arduino
        line = ser.readline().decode('utf-8').rstrip()  # Read the data
        print(f"Received: {line}")  # Debug output

        if line == "BLOCKED":  # Blocked command received
            time.sleep(0.5) 
            stop_sound()  # Stop any current sound
            sound_playing = play_sound("Blocked.mp3")  # Play the blocked sound
            print("Playing Blocked.mp3 (Blocked mode activated)")

        elif line == "STOP_SOUND":  # Stop sound command
            if sound_playing:  # Only stop if something is playing
                stop_sound()  # Stop the sound
                sound_playing = False
                print("Stopped all sounds.")

        elif line == "PLAY_SOUND":  # Play sound command
            if not sound_playing:  # Only play if nothing is playing
                sound_playing = play_sound("warn.mp3")  # Play warning sound
                print("Playing warn.mp3 (Sound command received)")

    # Check if the sound has finished playing
    if not pygame.mixer.music.get_busy():  # No sound is currently playing
        sound_playing = False  # Reset sound flag

# Close the serial port when done (this line will not be reached in the infinite loop)
ser.close()
