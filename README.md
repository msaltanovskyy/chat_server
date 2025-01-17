# Chat Application

This project is a simple chat application with a server implemented in C++ and a client-side interface built with HTML, CSS, and JavaScript.

## Project Structure

### Files

- `.vscode/`: Contains Visual Studio Code configuration files.
  - `launch.json`: Configuration for debugging.
  - `settings.json`: Editor settings.
  - `tasks.json`: Task definitions for building the project.
- `client/`: Directory for client-side code (currently empty).
- `server/`: Directory for server-side code.
  - `head/server.h`: Header file for the `Server` class.
  - `index.html`: HTML file for the chat application interface.
  - `server_main.cpp`: Main entry point for the server application.
  - `server.cpp`: Implementation of the `Server` class.

## Building and Running the Project

### Prerequisites

- g++ (GNU Compiler Collection)
- Visual Studio Code

### Build

To build the project, use the build task defined in `.vscode/tasks.json`. You can run the build task in Visual Studio Code by pressing `Ctrl+Shift+B` and selecting `C/C++: g++ build active file`.

### Run

1. Build the project as described above.
2. Run the server by executing the compiled `server_main` binary in the `server` directory.

```sh
./server/server_main


Feel free to modify the `README.md` as needed to better fit your project.
