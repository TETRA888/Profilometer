#  <div align = "center">` Open Road Profiler `(ORP) </div>

 ![Static Badge](https://img.shields.io/badge/Contributors-9-blueviolet)
 ![Static Badge](https://img.shields.io/badge/License-GPL%203.0-brightgreen)
 ![Static Badge](https://img.shields.io/badge/Language-C-blue)
 ![Static Badge](https://img.shields.io/badge/Language-Python-red)
 ![Static Badge](https://img.shields.io/badge/Tech-RaspberryPi-hotpink)
 ![Static Badge](https://img.shields.io/badge/Tech-Arduino-darkblue)
 ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-Class%203B%20Precision%20Laser-purple)
 ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
 
An open-source system engineered to accurately map the deterioration of theoretical road designs proposed by Caltrans. Levergaing Class 3B precision laser, High load and Precision Stepper Motor Drivers, Encoders, Proximity sensors, and adjustable lighting to capture sub-millimeter road surface deformations under simulated traffic loads.

<div align="center">
  <img src="https://github.com/user-attachments/assets/0f8856cc-a083-4535-b870-cc8844e09d20" alt="title image" width="550">
</div>
<div align = "Center"> Figure 1.0 (Frame with Electronics) </div>

## Table of Contents
- [Purpose](#purpose)
- [How to Get Started](#how-to-get-started)
   - Parts List
- [Software System Design](#software-design)
- [Electrical System Design](#electrical-system-design)
  - Mounted Electronics
- [Mechanical Design](#mechanical-frame)
  - Assembled Frame
  - CAD model
- [Core Team](#core-team)
- [Documentation](#documentation-and-implementation)
- [Future Work](#future-work)
## Purpose

Purpose-built to work with the **Heavy Vehicle Simulator (HVS) system**, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated verification via external encoder sensors and validation via a 24/7 HVS Crew, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California. The end goal of this project is to enable all road research labs in the world with the ability to accurately assess how their road design degrades and performs overtime.

<p align="center">
  <img src="https://github.com/user-attachments/assets/a2f987fe-74d6-4f24-bebb-29c878471050" alt="1-s2 0-S1996681417300354-gr6" width="500">
</p>
<div align="center"> Figure 2.0 (Heavy Vehicle Simulator @ UCPRC Davis, CA 2025) </div>

<div style="text-align" align = "center">
  <img src="https://github.com/user-attachments/assets/ac2b38b4-f7ed-4a44-ba55-4ce7c39c568a" width="500" />
  <div>Figure 2.1</div>

  <img src="https://github.com/user-attachments/assets/55ddd6bd-506d-4cd9-876a-5803f1acf2ee" width="500" />
  <div>Figure 2.2</div>
</div>

<div style="text-align" align = "center"">
  Paving new Caltrans Proposed Road Designs @ UCPRC Davis, CA 2024
</div>


## How to Get Started
1. Clone the repository
```bash
$ git clone https://github.com/TETRA888/Profilometer.git
$ cd Profilometer
```
2. Set up the hardware as described in the [Electrical System Design](#electrical-system-design) and [Mechanical Frame](#mechanical-frame) sections.
* [Parts list](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

## Software Design
The software is written in Python and C/C++ and provides tools for:
* Real-time data acquisition.
* Calibrating tools 
* Exporting data to formats like CSV and STL.


<p align="center">
 <img src = "https://github.com/user-attachments/assets/fe528e88-6bc0-46dd-bb4b-45c65ca7cced" alt="software design overview" width="40%">
 <img src = "https://github.com/user-attachments/assets/32ccac83-22e0-466b-923a-43ae7843b1e9" alt="simple gui" width="40%">
</p>
<div align ="center"> Software Design Overview/Simple Gui 1.1</div>




## Electrical System Design

The profilometer consists of the following major electronic components:
* Sensors: Class 3B Precision laser, High Resolution Taiss Rotary Encoder, Inductive Proximity Sensor.
* Motors and Power: Nema 23 Stepper Motor, 600W Universal power supply.
*	Controllers: Arduino Mega microntroller with Raspberry Pi.

<p align="center">
  <img src="https://github.com/user-attachments/assets/d2793204-312c-4bae-87c7-b930093b7640" alt="System Design" width="40%">
  <img src="https://github.com/user-attachments/assets/e47172af-e0ef-41ed-a5eb-c84660c2853c" alt="Electrical Schematic" width="40%">
</p>
<div align="center"> Figure 3.1 High-Level Electrical System Design/Schematic  </div>

<p align="center">
  <img src="https://github.com/user-attachments/assets/57f5ed04-3421-409e-b34d-de18fb0aa7bf" alt="System Design" width="40%">
</p>
<div align="center"> Figure 3.2 (Assembled electronics) </div>

## Mechanical Frame

The mechanical frame of the profilometer serves as the structure that supports all the components, ensuring stability and precision during measurements. Below are the key aspects of the frame:

Material:
*	Constructed from high-strength aluminum alloy for durability and minimal thermal expansion.
*	Lightweight yet rigid enough to maintain precision during operation.

Design:
*	Modular design to allow for easy assembly and future upgrades.
*	Includes adjustable components to accommodate different sensor configurations and sample sizes.
  
Accessibility and Maintenance:
*	Open design for easy access to internal components, making maintenance and calibration straightforward.
*	Cable management system to keep wiring organized and prevent interference.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e" alt="System Design" width="70%">
</p>
<div align = "Center" > Figure 4.1 (3D Blender Render) </div>

<p align="center">
  <img src="https://github.com/user-attachments/assets/19168a9b-73d9-4032-93db-c142c46b60a5" alt="System Design" width="70%">
</p>
<div align = "Center" > Figure 4.2 (2nd Design Iteration Of Frame) </div>

# Core Team
- [<img src="https://github.com/TETRA888.png" width="60px;"/><br /><sub><a href="https://github.com/TETRA888">Asad Melibaev</a></sub>](https://github.com/TETRA888/Profilometer)

- [<img src="https://github.com/adamhwu.png" width="60px;"/><br /><sub><a href="https://github.com/adamhwu">Adam Wu</a></sub>](https://github.com/TETRA888/Profilometer)

# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

## Future Work
To integrate ORP’s point cloud data into OpenUSD, the UsdGeomPoints schema will be used to represent sub-millimeter road surface deformations. Each point will include attributes like position (X,Y,ZX,Y,Z), normals, color, and custom degradation metrics. The data pipeline starts with preprocessing raw outputs from ORP (e.g., .txt, .ply), which are then converted into USD files using Python’s USD libraries. Surface reconstruction algorithms, such as Poisson reconstruction, can transform point clouds into detailed meshes stored as UsdGeomMesh. Time-series visualization of road degradation over simulated traffic cycles will leverage USD’s animation capabilities, enabling dynamic analysis. Once generated, USD files can be validated with tools like USDView or NVIDIA Omniverse for real-time visualization and shared for collaborative research. This pipeline enables scalable, accurate modeling of road performance, paving the way for global adoption in road research. Furthermore, OpenUSD could perhaps be even used to generate synthetic data. A similar usecase for generating synthetic data for license plate detection using OpenUSD is showcased here:https://developer.nvidia.com/blog/developing-smart-city-traffic-management-systems-with-openusd-and-synthetic-data/

![image](https://github.com/user-attachments/assets/0236c53d-0974-4850-a30e-3736df479050)

## Acknowledgements

We would like to thank the following for their contributions to this project:
* Open-Source Libraries: This project uses several open-source libraries (check the dependencies section for a full list).
* Contributors: Thank you to everyone who has contributed to the development of this profilometer. See the contributors page for a list of all contributors.
* Issues: Feel free to open an issue in this GitHub repository for bug reports or feature requests.
