import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import math
from dataclasses import dataclass


# ====== DATA MODEL ======
@dataclass
class Point:
    id: int
    y: float
    x: float
    z: float
    typ: str   # 👈 NOVÉ


points = []


# ====== VÝPOČTY ======
def smernik_delka(dy, dx):
    if dy == 0 and dx == 0:
        s = 0
    elif dx == 0:
        s = 100 if dy > 0 else 300
    elif dy == 0:
        s = 0 if dx > 0 else 200
    else:
        s = math.atan(dy / dx) * 200 / math.pi
        if dx > 0 and dy < 0:
            s += 400
        elif dx < 0:
            s += 200

    d = math.sqrt(dx**2 + dy**2)
    return s, d


# ====== SOUBORY ======
def load_points():
    global points
    file = filedialog.askopenfilename()
    if not file:
        return

    points = []

    try:
        with open(file, "r", encoding="cp1250") as f:
            for line in f:
                parts = line.strip().split()

                if len(parts) >= 4:
                    try:
                        pid = int(parts[0])
                        y = float(parts[1].replace(",", "."))
                        x = float(parts[2].replace(",", "."))
                        z = float(parts[3].replace(",", "."))

                        # 👇 typ bodu (pokud existuje)
                        typ = parts[4] if len(parts) > 4 else ""

                        points.append(Point(pid, y, x, z, typ))
                    except:
                        continue

        refresh_table()

    except Exception as e:
        messagebox.showerror("Chyba", str(e))


def save_points():
    file = filedialog.asksaveasfilename(defaultextension=".txt")
    if not file:
        return

    try:
        with open(file, "w", encoding="utf-8") as f:
            for p in points:
                f.write(f"{p.id} {p.y:.3f} {p.x:.3f} {p.z:.3f} {p.typ}\n")
    except Exception as e:
        messagebox.showerror("Chyba", str(e))


# ====== TABULKA ======
def refresh_table():
    for row in tree.get_children():
        tree.delete(row)

    for p in points:
        tree.insert("", "end", values=(p.id, p.y, p.x, p.z, p.typ))


# ====== VÝPOČET SMĚRNÍKU ======
def compute_direction():
    try:
        id1 = int(entry_id1.get())
        id2 = int(entry_id2.get())

        p1 = next(p for p in points if p.id == id1)
        p2 = next(p for p in points if p.id == id2)

        dy = p2.y - p1.y
        dx = p2.x - p1.x

        s, d = smernik_delka(dy, dx)

        result_var.set(f"Směrník: {s:.4f}   Délka: {d:.4f}")

    except StopIteration:
        messagebox.showerror("Chyba", "Bod nenalezen")
    except Exception as e:
        messagebox.showerror("Chyba", str(e))


# ====== GUI ======
root = tk.Tk()
root.title("GEO5 Python")
root.geometry("700x500")

# --- MENU ---
frame_top = tk.Frame(root)
frame_top.pack(pady=10)

tk.Button(frame_top, text="Načíst body", command=load_points).grid(row=0, column=0, padx=5)
tk.Button(frame_top, text="Uložit body", command=save_points).grid(row=0, column=1, padx=5)

# --- TABULKA ---
tree = ttk.Treeview(root, columns=("ID", "Y", "X", "Z", "TYP"), show="headings")

tree.heading("ID", text="ID")
tree.heading("Y", text="Y")
tree.heading("X", text="X")
tree.heading("Z", text="Z")
tree.heading("TYP", text="Typ")

# --- SMĚRNÍK ---
frame_calc = tk.Frame(root)
frame_calc.pack(pady=10)

tk.Label(frame_calc, text="Bod 1:").grid(row=0, column=0)
entry_id1 = tk.Entry(frame_calc, width=5)
entry_id1.grid(row=0, column=1)

tk.Label(frame_calc, text="Bod 2:").grid(row=0, column=2)
entry_id2 = tk.Entry(frame_calc, width=5)
entry_id2.grid(row=0, column=3)

tk.Button(frame_calc, text="Spočítat", command=compute_direction).grid(row=0, column=4, padx=10)

result_var = tk.StringVar()
tk.Label(root, textvariable=result_var, font=("Arial", 12)).pack(pady=10)


# ====== START ======
root.mainloop()