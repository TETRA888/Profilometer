# Open Road Profiler (ORP)

The **Open Road Profiler (ORP)** is an advanced, open-source system engineered to map the degradation of theoretical road designs developed by Caltrans. This precision gantry platform leverages a robust integration of **computer vision**, **LiDAR sensing**, and **optical measurement** technologies, including a Garmin LiDAR-Lite v3HP, a 64MP high-resolution camera, and a Class II precision laser, to capture sub-millimeter road surface details crucial for high-fidelity data.

## About

Purpose-built to support the **Heavy Vehicle Simulator (HVS)**, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated **V&V (Verification & Validation)** cycles via external encoder sensors, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California. 

## Table of Contents
1. [System Design Overview](#High-Level-Multi-System-Integration-Overview)
2. [Key Features/Specifications](#Tech-Stack-and-Specs)
3. [Project Code](#Code-with-active-offsetting-for-submilimeter-accuracy-debugging-and-testing)
4. [Project Leadership](#Key-Contributors)
5. [Collaborating Institutions](#collaborating-institutions)

# High-Level Multi System Integration Overview

System diagram designs for Electrical, Software and Embedded are found here. 

![Systems Diagram](https://github.com/user-attachments/assets/a596d962-1c3d-4df4-bdc4-865af248637e)

# Mechanical Frame Design And Parts Overview
![image](https://github.com/user-attachments/assets/1d78618b-e48f-44f0-9139-ca29d3cbe0ff)

# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

# Tech Stack and Specs:
- ![Static Badge](https://img.shields.io/badge/Language-C-blue)
- ![Static Badge](https://img.shields.io/badge/Language-Python-red)
- ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
- ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
- ![Static Badge](https://img.shields.io/badge/Tech-%20Class%20II%20Precision%20Laser-purple)
- ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Parts list Wiki](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)
2. [Google Sheets containing exact quantities and parts needed for single axial system](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

# Blender Renders:

![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
## <div align = "Center" > Figure 1. (Side view of the 3D model)
</div>

 Low Level Electrical System Design Overview
### Iteration #1 Initial schematic for stepper motor control:

![370549337-e03756ac-cc0a-44d8-81d0-12ec9ca38810](https://github.com/user-attachments/assets/c86bd222-eb04-4c2a-aee0-ba2ea33dbb47)
## <div align = "Center" > Figure 2. (Basic Schematic of the controller)
</div>

# Code with active offsetting for submilimeter accuracy debugging and testing

Full code used for the project found in [here](https://github.com/TETRA888/Profilometer/blob/main/Code/XAxisRailControl/XAxisRailControl.ino).

# Project Leadership

Led by **Asad Melibaev**, the project emphasizes a modular, scalable design, ensuring smooth integration with existing systems and adaptability to future sensing technologies. With support from a dedicated team of R&D engineers, PhD researchers, and machinists, the ORP’s goal is to enable precise, actionable data analysis to inform road composition improvements and advance Caltrans' pavement research efforts.

# Key Contributors

### Core Team
- **Asad Melibaev**  
  *(Systems Lead)*  
  [GitHub Profile](https://github.com/TETRA888)

### Help, Advice and Guidance from
- **Andrew Cobb**  
  *(Sr. Machinst)*  

- **Kin Yen**  
  *(Sr. Development Engineer)*  

- **Stephanus Louw**  
  *(Lead Geotechnical Engineer)*
  
- **Rauf Zokhrabov**  
  *(Documentation Assistant)*
  *(University of Illinois Urbana-Champaign)*

### Acknowledgments
I would like to express my sincere gratitude to my Electrical Engineering professors and faculty members at UC Davis for their invaluable support in designing the system and deepening my understanding of circuit design. Their expertise and guidance have been instrumental in the development of this project.
  
## Collaborating Institutions
![PIC_Logo_Version3-1](https://github.com/user-attachments/assets/17cbd89d-2607-47e3-9363-86e45fdb013c)
![cee_logo_125px](https://github.com/user-attachments/assets/006992ca-56f5-472b-9f67-138f40989d7f)
![ece_logo_125px](https://github.com/user-attachments/assets/dc39ba0e-d0da-407a-b563-ca034a3d2a44)
