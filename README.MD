## 🖼️ kview — PPM Framebuffer Image Viewer

kview is a minimal image viewer written in C that displays **PPM (P6)** images directly on the **Linux framebuffer**, without using any graphic library (SDL, MLX, X11, Wayland, etc.).

The goal of this project is **not** to build a modern graphical application, but to explore **low-level image rendering** by interacting directly with the Linux display subsystem.

---

## ✨ Features

- Direct rendering to `/dev/fb0` (fbdev)
- Support for **PPM P6** (binary) images
- Manual parsing of image headers (width, height, max color value)
- Pixel-by-pixel rendering
- No graphical or windowing library
- Linux-only, system-level project

---

## 🧠 Why framebuffer?

Modern Linux desktops rely on **DRM/KMS** and GPU-accelerated pipelines.  
This project intentionally uses **fbdev**, an older but simpler interface, for **educational purposes**.

The framebuffer allows:
- direct memory-mapped access to the screen
- understanding pixel formats and memory layout
- learning how images are actually displayed at a low level

This project focuses on **understanding the fundamentals**, not on performance or portability.

---

## 🖼️ Supported Image Format

- **PPM (Portable Pixmap)**
- Type: **P6**
- Binary RGB data
- Max color value typically `255` (8-bit per channel)

PPM was chosen because it is:
- simple
- uncompressed
- easy to parse manually
- well-suited for low-level experimentation

---

## 🔧 Requirements

- Linux system with framebuffer support (`/dev/fb0`)
- User must belong to the `video` group **or** run as root
- Works best from a **TTY** (not under Wayland/X11)

> ⚠️ This program is not intended to run inside a graphical desktop environment.

---

## 🛠️ Compilation

```bash
make
```
This will generate the `kview` executable.

---

## ▶️ Usage

```bash
./kview path/to/image.ppm
```

you can also put the image on stdin

```bash
cat path/to/image.ppm | ./kview
```

> Note: if an image path is provided as an argument, stdin is ignored.

During execution, the program prints image information such as:

- width
- height
- maximum color value

---

# 📚 What I learned

- How Linux displays graphics at a low level
- How the framebuffer maps screen memory
- Pixel formats and color representation
- Binary file parsing
- Memory-mapped I/O (`mmap`)
- System constraints of display devices

---

# ⚠️ Limitations

- Linux only
- fb only (no DRM/KMS)
- No windowing system
- No scaling or aspect ratio handling
- Hardware-dependent behavior

These limitations are intentional and part of the learning process.

---

# 📌 Notes

This project is meant as a learning and exploration tool, not a production-ready image viewer.
It serves as a foundation for understanding modern display stacks such as DRM/KMS and Wayland.