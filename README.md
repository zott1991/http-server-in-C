# C HTTP Server

A lightweight HTTP server written from scratch in C using POSIX TCP sockets.

The project demonstrates how a basic web server can accept TCP connections, receive and parse HTTP requests, and return an HTTP response containing an HTML document without relying on a web framework or external HTTP library.

## Features

- Creates a TCP socket using the POSIX socket API
- Binds the server to port `8080`
- Enables address reuse with `SO_REUSEADDR`
- Listens for incoming TCP connections
- Accepts client connections
- Receives and inspects HTTP requests
- Handles HTTP `GET` requests
- Returns an `HTTP/1.1 200 OK` response
- Serves an `index.html` file to connected clients
- Handles unsupported request methods by closing the connection

## Concepts Demonstrated

This project provides hands-on experience with low-level network programming and operating system APIs, including:

- TCP/IP networking
- Client/server architecture
- POSIX sockets
- Socket creation and configuration
- `bind()`
- `listen()`
- `accept()`
- `recv()`
- `send()`
- `setsockopt()`
- `getaddrinfo()`
- Network address structures
- File I/O
- HTTP request/response structure
- C strings and memory management
- Process-level resource management with `close()`

## How It Works

The server follows a basic client/server workflow:

```text
Client
   |
   | TCP connection
   v
Socket
   |
   v
bind()
   |
   v
listen()
   |
   v
accept()
   |
   v
recv() HTTP request
   |
   +---- GET request ----> HTTP 200 response
   |                         |
   |                         v
   |                    index.html
   |
   +---- Other request --> Connection closed
