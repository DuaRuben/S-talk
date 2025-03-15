# S-talk - A Simple Chat Facility Using UDP and Pthreads

This project implements a simple **chat facility** called `s-talk` that allows two users to communicate over different terminals using **UNIX UDP IPC** and **pthreads** for multi-threading. The system simulates a basic client-server chat system with a focus on concurrent programming and thread synchronization.

## Features
- **UDP Communication**: Sends messages between two UNIX processes using UDP datagram sockets.
- **Multithreading**: Utilizes **pthreads** to handle multiple tasks concurrently within each process.
- **Shared Memory**: Implements shared access to a list ADT, ensuring synchronization between threads using mutexes and condition variables.
- **Terminal Interface**: Basic text-based interface for communication, where messages appear character-by-character on the sender's terminal and on the receiver's terminal once the sender presses Enter.

## Expected Process Structure

This program will be implemented using **pthreads** to handle multiple threads within the same UNIX process. The required threads for each process are:

1. **Keyboard Input Thread**: Waits for user input from the keyboard.
2. **UDP Input Thread**: Listens for incoming UDP datagrams from the remote machine.
3. **Screen Output Thread**: Displays received messages on the local terminal screen.
4. **UDP Output Thread**: Sends messages over the network to the remote client using UDP.

All four threads share access to a list ADT where messages are added and removed, with synchronization achieved using mutexes and condition variables to prevent concurrent access issues.

## Requirements

- **UNIX/Linux-based OS**
- **C Compiler** (e.g., GCC)
- **Pthreads library**
- **Basic understanding of UDP sockets and multithreading**


