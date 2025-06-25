# SignatureClusterTool

A desktop-based clustering and visualization tool that processes datasets, calculates correlation matrices, and uses discretization and permutation techniques to visually identify clusters. Built using Object-Oriented Programming principles and C++ with the FireMonkey (FMX) framework.



- [Project Report](https://github.com/shabihidk/2nd-Semester-Final-Project/blob/main/Report.docx) : Contains breakdown of project's thought process.
- [Project Code](https://github.com/shabihidk/2nd-Semester-Final-Project/blob/main/Code%20Project.zip): Code and Files Required
- [Restriction Notice](https://github.com/shabihidk/2nd-Semester-Final-Project/blob/main/README.txt): Code Limitations


## 🚀 Features

- 📊 **Correlation Analysis**: Computes Pearson correlation coefficients between data rows.
- ⚙️ **Discretization**: Transforms correlation matrices into binary matrices based on mean thresholding.
- 🖼️ **Visualization**: Displays matrices as zoomable bitmap images for pattern analysis.
- 🔀 **Permutation & Signature Clustering**: Shuffles data and recovers cluster structure using a signature-based technique.
- 🧠 **Image-Based Insights**: Shows color-coded cluster visuals pre- and post-signature transformation.

---

## 🧱 Project Structure

| Task | Description |
|------|-------------|
| Task 1 | Correlation matrix generation, discretization, bitmap visualization |
| Task 2 | Data permutation, cluster recovery using signature technique, re-visualization |

---

## 📂 Libraries Used

- `fmx.h`, `FMX.Graphics.hpp` – GUI rendering (FireMonkey)
- `iostream`, `fstream`, `string` – Data I/O
- `cmath`, `ctime`, `random` – Math and randomness utilities

---

## 🧑‍💻 Team Contribution

- **Muhammad Shabih Ul Hassan Raja**
  - GUI implementation
  - Front-End visualization
  - Correlation mechanics

- **Syed Ghazi Abbas**
  - Base logic and clustering backend
  - Data processing

---

## 🛠️ How to Run

> 🛑 Prerequisite: Embarcadero C++ Builder (with FMX support)

1. Clone the repository.
2. Open the `.cbproj` file in C++ Builder.
3. Run the project.
4. Load a dataset (formatted rows of numerical data).
5. Choose between Task 1 (basic clustering) or Task 2 (signature-based permutation clustering).

---

## 📸 Sample Outputs


[Original](![image](https://github.com/user-attachments/assets/0d3dd560-6a53-4b26-8330-186872ec818e))

[Permuted](![image](https://github.com/user-attachments/assets/5df74217-fc1d-4a59-8a6c-9f501f444511))

[Clustered](![image](https://github.com/user-attachments/assets/a9e9a3a6-f105-4405-a3a7-96876dd3e718))


## 📌 Notes

- All memory is cleaned using dynamic deallocation.
- Signature clustering improves visual grouping of hidden clusters.
- Future plans: add CSV input, dynamic thresholding, and improved image scaling.

---

## 📜 License

MIT License — feel free to use and extend the project with credits.

