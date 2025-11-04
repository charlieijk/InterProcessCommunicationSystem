# Inter-Process Communication System

A demonstration of inter-process communication (IPC) using named pipes (FIFO) in Unix-like systems. This project showcases data transfer between a C writer process and a Python reader process using a named pipe.

## Overview

This system consists of two components:
- **Writer (`writer.c`)**: A C program that reads sensor data from a CSV file and writes it to a named pipe
- **Reader (`reader.py`)**: A Python program that reads data from the named pipe and displays it

The programs communicate through a FIFO (First In, First Out) named pipe called `my_pipe`, demonstrating fundamental IPC concepts.

## Features

- Named pipe (FIFO) creation and management
- Cross-language IPC (C to Python)
- Sensor data streaming from CSV file
- Synchronization between writer and reader processes
- Automatic cleanup of pipe resources

## Project Structure

```
InterProcessCommunicationSystem/
├── writer.c           # C program that writes data to the pipe
├── writer             # Compiled executable
├── reader.py          # Python program that reads from the pipe
├── sensor_data.csv    # Sample sensor data (temperature, humidity, pressure)
└── README.md          # This file
```

## Requirements

### Writer (C)
- GCC compiler or compatible C compiler
- POSIX-compliant system (Linux, macOS, Unix)

### Reader (Python)
- Python 3.x
- No external dependencies required

## Compilation

Compile the C writer program:

```bash
gcc -o writer writer.c
```

## Usage

The writer and reader must be run in separate terminal windows.

### Step 1: Start the Writer
In the first terminal:
```bash
./writer
```

The writer will:
1. Create the named pipe `my_pipe`
2. Wait for the reader to connect
3. Read data from `sensor_data.csv` line by line
4. Send each line through the pipe

### Step 2: Start the Reader
In a second terminal:
```bash
python3 reader.py
```

The reader will:
1. Wait for the pipe to be created
2. Connect to the pipe
3. Read and display data as it arrives
4. Exit when the writer closes the pipe

## How It Works

1. **Pipe Creation**: The writer creates a named pipe (`my_pipe`) using `mkfifo()`
2. **Blocking Connection**: The writer blocks on `open()` until the reader connects
3. **Data Transfer**: The writer reads the CSV file line by line and writes to the pipe
4. **Reading**: The reader reads from the pipe and prints each line
5. **Cleanup**: When the writer finishes, it closes and removes the pipe

## Sample Data

The included `sensor_data.csv` contains sample environmental sensor readings:
- Timestamp
- Temperature (°C)
- Humidity (%)
- Pressure (hPa)

## Key Concepts Demonstrated

- **Named Pipes (FIFO)**: Inter-process communication mechanism
- **Blocking I/O**: Writer blocks until reader connects
- **File Descriptors**: Low-level file operations in C
- **Cross-Language IPC**: Communication between C and Python processes
- **Resource Management**: Proper cleanup of pipe resources

## Error Handling

Both programs include error handling for:
- File opening failures
- Pipe creation errors
- Connection issues
- Read/Write failures

## Notes

- The pipe is automatically removed after the writer completes
- The reader must be started after the writer creates the pipe
- Both processes must run on the same system
- The pipe name is defined as `my_pipe` in both programs

## Educational Use

This project is designed for educational purposes to demonstrate:
- Inter-process communication concepts
- Named pipes in Unix-like systems
- Synchronization between processes
- Cross-language communication

## License

This project is for educational purposes.

## Author

Charlie
