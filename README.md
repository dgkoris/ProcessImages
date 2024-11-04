# Shared Memory Image Processing

This project demonstrates how to use shared memory for communication between a C# and a C++ program to process images.

## GitHub Repositories

You can find the code for each project here:

- **C# Application:** [SharedMemoryManager](https://github.com/dgkoris/SharedMemoryManager)
- **C++ Application:** [ProcessImages](https://github.com/dgkoris/ProcessImages)

This project is also organised within a GitHub project board:

- **[Shared Memory Image Transfer and Analysis](https://github.com/users/dgkoris/projects/2/views/1)**

## How to Use

1. **Run the C# program first:**
   - Start the `SharedMemoryManager` C# app. This application loads BMP images from the `TestImages` folder and writes this data to shared memory named `Local\SharedMemoryImages`.

2. **Then, run the C++ program:**
   - Next, run the `ProcessImages` C++ app. This program reads the image data from shared memory, analyses each image to find the most common colour in each row.

## Additional Information

These applications were created with Visual Studio 2022 and currently work with BMP images only.
