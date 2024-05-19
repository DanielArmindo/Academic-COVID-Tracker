# Disclaimer

This project was carried out as part of the Programming I course in Computer Engineering at the Polytechnic Institute of Leiria.

# About This Project

The aim of this project is to develop a program (**in C language**) to manage COVID-19 diagnostic tests and lockdowns for members of an academic community of up to 200 people.

Another objective of this project is to demonstrate the application of C language concepts, as well as to ensure good code structuring, promoting efficient and organized programming practices.

<span style="font-size: larger;font-weight:bold;">Features</span>

- Registration of Academic Community Members:
	- Only registered members can schedule tests.
- Test scheduling:
	- Identification of the type of test (PCR or antigen) when scheduling.
- Recording Test Results:
	- Inconclusive or positive antigen test results require a new PCR test.
- Isolation and Quarantine:
	- Members with positive results are placed in prophylactic isolation.
	- Members with inconclusive results are quarantined.
	- Registration of members in isolation due to close contact with infected persons.

<span style="font-size: larger;font-weight:bold;">Proceedings</span>

- Scheduling
	- Exclusive to registered members, specifying the type of test.
- Results:
	- Positive (Antigen) → PCR scheduling and isolation.
	- Inconclusive → Schedule PCR and quarantine.
	- Positive (PCR) → Prophylactic isolation.
- Isolation by Contact
	- Registered manually by the user.

This program aims to ensure efficient management of tests and lockdowns, contributing to the safety of the academic community.

# Softwares Requeriments

This project used the following softwares:

- **C compiler** - Software that translates source code written in the C programming language into machine code that can be executed directly by the computer's hardware.
	- Installation guidelines for Windows - https://www.scaler.com/topics/c/c-compiler-for-windows/
	- Linux environment **natively supports**
- **GNU Make** - Tool which controls the generation of executables and other non-source files of a program from the program's source files.
	- In a linux environment it's **normally installed**
	- For Windows Environment - https://gnuwin32.sourceforge.net/packages/make.htm
- **GNU Gengetopt** - tool that automatically generates C code for processing command line arguments
	- For Windows Environment - https://gnuwin32.sourceforge.net/packages/gengetopt.htm
	- In a linux environment it's **necessary to install**

# How to run Project

```bash
# Inside the root folder (when changes to files are detected or first time)
make
cd debug
store.exe
```

# Reminders

Depending on the operating system that will run the program and based on the C compiler used, **if it's different from gcc** it is necessary to **change the "CC" makefile variable to the respective compiler**.

This project was developed on linu# Disclaimer

This project was carried out as part of the Programming I course in Computer Engineering at the Polytechnic Institute of Leiria.

# About This Project

The aim of this project is to develop a program (**in C language**) to manage COVID-19 diagnostic tests and lockdowns for members of an academic community of up to 200 people.

Another objective of this project is to demonstrate the application of C language concepts, as well as to ensure good code structuring, promoting efficient and organized programming practices.

**Features**

- Registration of Academic Community Members:
	- Only registered members can schedule tests.
- Test scheduling:
	- Identification of the type of test (PCR or antigen) when scheduling.
- Recording Test Results:
	- Inconclusive or positive antigen test results require a new PCR test.
- Isolation and Quarantine:
	- Members with positive results are placed in prophylactic isolation.
	- Members with inconclusive results are quarantined.
	- Registration of members in isolation due to close contact with infected persons.

**Proceedings**

- Scheduling
	- Exclusive to registered members, specifying the type of test.
- Results:
	- Positive (Antigen) → PCR scheduling and isolation.
	- Inconclusive → Schedule PCR and quarantine.
	- Positive (PCR) → Prophylactic isolation.
- Isolation by Contact
	- Registered manually by the user.

This program aims to ensure efficient management of tests and lockdowns, contributing to the safety of the academic community.

# Softwares Requeriments

This project used the following softwares:

- **C compiler** - Software that translates source code written in the C programming language into machine code that can be executed directly by the computer's hardware.
	- Installation guidelines for Windows - https://www.scaler.com/topics/c/c-compiler-for-windows/
	- Linux environment **natively supports**
- **GNU Make** - Tool which controls the generation of executables and other non-source files of a program from the program's source files.
	- In a linux environment it's **normally installed**
	- For Windows Environment - https://gnuwin32.sourceforge.net/packages/make.htm
- **GNU Gengetopt** - tool that automatically generates C code for processing command line arguments
	- For Windows Environment - https://gnuwin32.sourceforge.net/packages/gengetopt.htm
	- In a linux environment it's **necessary to install**

# How to run Project

```bash
# Inside the root folder (when changes to files are detected or first time)
make
cd debug
store.exe
```

# Reminders

Depending on the operating system that will run the program and based on the C compiler used, **if it's different from gcc** it is necessary to **change the "CC" makefile variable to the respective compiler**.

This project was developed on linux and tested on Windows, **recommend running it in a linux environment** and tested on Windows, **recommend running it in a linux environment**
