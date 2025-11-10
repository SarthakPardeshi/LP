
import tkinter as tk
from tkinter import messagebox

# Function for button click event
def submit_action():
    name = name_entry.get()
    email = email_entry.get()
    if name == "" or email == "":
        messagebox.showwarning("Warning", "Please fill all fields!")
    else:
        messagebox.showinfo("Success", f"Hello {name}! Your email {email} is registered.")

# Create main window
root = tk.Tk()
root.title("User Registration Form")
root.geometry("400x300")
root.config(bg="#e6f2ff")  # Light blue background

# Heading Label
tk.Label(root, text="User Registration", font=("Arial", 16, "bold"), bg="#e6f2ff", fg="blue").pack(pady=10)

# Name Label and Entry
tk.Label(root, text="Name:", font=("Arial", 12), bg="#e6f2ff").pack(pady=5)
name_entry = tk.Entry(root, width=30)
name_entry.pack()

# Email Label and Entry
tk.Label(root, text="Email:", font=("Arial", 12), bg="#e6f2ff").pack(pady=5)
email_entry = tk.Entry(root, width=30)
email_entry.pack()

# Submit Button
tk.Button(root, text="Submit", font=("Arial", 12), bg="green", fg="white", command=submit_action).pack(pady=20)

# Exit Button
tk.Button(root, text="Exit", font=("Arial", 12), bg="red", fg="white", command=root.destroy).pack()

# Run the application
root.mainloop()
    
