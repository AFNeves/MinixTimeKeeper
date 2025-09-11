# MinixTimeKeeper

## 📖 Description

A MinixOS-based C application combining custom device drivers with a basic clock program, developed for the **Computer Laboratory course at FEUP**.
The project integrates drivers for the timer, keyboard, mouse, RTC, and graphics into a working system that can:

* Display the current time
* Run a countdown timer
* Operate as a chronometer

This project was built to run on a **special variant of MinixOS** used at FEUP.

## ⚙️ Features

* **Custom device drivers**:

  * Timer
  * Keyboard
  * Mouse
  * RTC (Real-Time Clock)
  * Graphics (VBE)
* **Clock modes**:

  * Real-time clock
  * Timer
  * Chronometer
* **User interface** rendered with XPM sprites

## 🚀 How to Build & Run

> ⚠️ This project is designed for the **MinixOS variant provided at FEUP**. Running it outside that environment may not be possible without adjustments.

1. Clone the repository and navigate to the `proj/src` folder:

   ```bash
   git clone <repo-url>
   cd proj/src
   ```

2. Build the project using `make`:

   ```bash
   make
   ```

3. Run the application inside the MinixOS environment using:

   ```bash
   lcom_run proj
   ```

4. To stop the application, press the **`Q` key**.

## 📘 Documentation

This project includes full technical documentation generated with **Doxygen**.

* **HTML Documentation**:
  Open [`proj/doc/html/index.html`](proj/doc/html/index.html) in your browser to explore the API and code structure.

* **PDF Documentation**:
  Open [`proj/doc/latex/refman.pdf`](proj/doc/latex/refman.pdf) for a compiled PDF reference manual.

If you want to regenerate the documentation:

```bash
cd proj/doc/Doxygen
doxygen Doxyfile
```

The HTML output will be generated in `proj/doc/html/` and LaTeX sources in `proj/doc/latex/`. You can then compile the LaTeX to PDF with:

```bash
cd proj/doc/latex
make
```

The result will be `refman.pdf`.

## 👥 Group Members

1. Afonso Neves ([up202108884@up.pt](mailto:up202108884@up.pt))
2. Tiago Oliveira ([up202009302@up.pt](mailto:up202009302@up.pt))
3. Tiago Martins ([up202206640@up.pt](mailto:up202206640@up.pt))
4. Tomás Ferreira ([up202305823@up.pt](mailto:up202305823@up.pt))

## 📎 License

This project is distributed under the terms of the [MIT License](LICENSE).
