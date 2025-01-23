import tkinter as tk
from tkinter import filedialog
import subprocess

def select_file():
    file_path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
    entry_file.delete(0, tk.END)  
    entry_file.insert(0, file_path)  

def run_cpp_program(): 
    file_path = entry_file.get() 
    if file_path:
        try:
            # Execute the C++ program with the selected file path as argument
            result = subprocess.run(["/Users/macuser/Documents/tsp/tsp/main"], capture_output=True, text=True, input=file_path)  # Change to 'main.exe' on Windows
            # Show the output in the Text widget
            text_output.delete(1.0, tk.END)  # Clear the current text
            text_output.insert(tk.END, result.stdout)  # Insert the output
        except Exception as e:
            text_output.delete(1.0, tk.END)
            text_output.insert(tk.END, f"Error: {e}")

# Set up the main window
root = tk.Tk()
root.title("C++ Program GUI")

# Set up the file selection components
frame_file = tk.Frame(root)
frame_file.pack(pady=10)

label_file = tk.Label(frame_file, text="Select a text file:")
label_file.pack(side=tk.LEFT)

entry_file = tk.Entry(frame_file, width=40)
entry_file.pack(side=tk.LEFT)

button_browse = tk.Button(frame_file, text="Browse", command=select_file)
button_browse.pack(side=tk.LEFT)

# Set up the Run button
button_run = tk.Button(root, text="Run Program", command=run_cpp_program)
button_run.pack(pady=10)

# Set up the output display
text_output = tk.Text(root, height=15, width=50)
text_output.pack(pady=10)

root.mainloop()