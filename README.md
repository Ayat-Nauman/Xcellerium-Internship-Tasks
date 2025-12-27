# Simple BMP Blur Processor

This project demonstrates a **minimal C++ implementation** for:

* Reading a **24-bit BMP** image directly (no external libraries)
* Converting the image to **grayscale**
* Applying a **3×3 blur convolution**
* Converting the blurred image back to **RGB**
* Writing the processed result as a new BMP file

---

## 📥 Input Image

The program expects an input file named:

```
input.bmp
```

Example input image:


[input.bmp](https://github.com/user-attachments/files/24251921/input.bmp)

---

## ⚙️ Processing Steps

1. Load BMP headers and pixel data
2. Convert RGB → Grayscale
3. Apply a 3×3 averaging blur filter
4. Convert Grayscale → RGB
5. Save the result as `output.bmp`

---

## 📤 Output Image (Blurred)

After processing, the output is saved as:

```
output.bmp
```

Blurred output image:

[output_blur.bmp](https://github.com/user-attachments/files/24251923/output_blur.bmp)


---

## Comparison of input and output image

<img width="1500" height="761" alt="comparison" src="https://github.com/user-attachments/assets/c2785553-17f8-46c8-b257-bb3eb4943aed" />

## ▶️ How to Compile and Run

```bash
g++ bmp_blur.cpp -o bmp_blur
./bmp_blur
```

Make sure `input.bmp` is in the same directory as the executable.

---

## ℹ️ Notes

* Only **24-bit uncompressed BMP** files are supported
* Image padding (4-byte row alignment) is handled correctly
* Designed for **learning, experimentation, and hardware-friendly pipelines**

---

✔️ Output message on success:

```
Done. Output saved as output.bmp
```
