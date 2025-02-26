# FORTUNE TELLER 

## Overview
The **Fortune Teller System** consists of a **server** and a **client** that work together to provide randomized responses to yes/no style questions. The server operates as a daemon, listening for client requests and providing responses, while the client allows users to input their questions and receive a formatted reply. This document combines the design and objectives of both components.

## System Components

### 1. Fortune Teller Server
The **server** is responsible for:
- Running as a daemon with no user interface.
- Listening on a TCP porT.
- Receiving yes/no questions from the client.
- Selecting a random response from a predefined set of 20 responses using `arc4random_uniform(3)`.
- Formatting and sending the response back to the client.
- Handling errors gracefully and supporting termination via `CTRL-C (SIGINT)`.
- Ensuring responses follow ASCII (plain text) formatting as per standard Internet protocols.

#### **Inputs:**
- Incoming TCP connections.
- Yes/no style ASCII questions from the client (max length: 512 bytes).

#### **Outputs:**
- Formatted responses including the original question and a randomly selected reply.
- Informative error messages in case of failures.

#### **Server Workflow:**
1. Create and bind a TCP socket to the designated port.
2. Listen for incoming client connections.
3. Accept client connections and read incoming messages.
4. Generate a random response using `arc4random_uniform(3)`.
5. Format and send the response back to the client.
6. Continue listening for new connections until terminated.

### 2. Fortune Teller Client
The **client** is responsible for:
- Accepting a hostname/IP as a command-line argument.
- Establishing a connection with the server.
- Prompting the user for a yes/no question.
- Sending the question to the server via TCP.
- Receiving and displaying the formatted response.
- Handling errors gracefully and exiting upon completion.

#### **Inputs:**
- Command-line argument specifying server hostname/IP.
- User-entered yes/no style ASCII question (max length: 512 bytes).

#### **Outputs:**
- Display of the formatted response from the server.
- Informative error messages in case of failures.

#### **Client Workflow:**
1. Validate the presence of a hostname/IP as a command-line argument.
2. Create a socket and connect to the server.
3. Prompt the user for a yes/no question.
4. Send the question to the server.
5. Receive and display the formatted response.
6. Close the connection and exit.

## Error Handling
Both components include robust error handling:
- **Server Errors:** Issues with socket creation, binding, listening, accepting connections, or sending responses.
- **Client Errors:** Invalid hostname/IP, connection failures, sending/receiving failures.
- Both ensure graceful shutdown and display informative error messages.

## Additional Implementation Details
- The server and client programs **must be developed in C** using the **BSD socket API** and must compile on the CS server using `cc (clang)`.
- **Testing without a client** can be performed using `netcat (nc)`.
- Ensure compliance with UNA CS Code Style Guide, with well-structured and efficient code.

## Conclusion
The **Fortune Teller System** demonstrates a simple yet effective client-server interaction model. The **server** handles multiple client requests efficiently, while the **client** allows seamless interaction for users. Both components are designed with robust error handling and structured workflows to ensure smooth operations.
