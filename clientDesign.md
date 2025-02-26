
# Fortune Teller Client

## Program Requirements for Client: 

The Client for the Fortune teller must: 
- `Accept one command line argument` which specifies the hostname or IP address of the server.
- `Establish a connection` to the specified port number using TCP (**port number is : 11000 + last three digits of id**).
- `Ask the user a yes/no style question` (the question is ASCII- plain text).
- `Send the question entered by the user to the server`.
-  `Recieve the formatted response from the server`(that includes the sent question and randomly selected response) and display it onto the screen and then terminate.
- `Handle errors gracefully`, which means program should recover from different errors and continue running if possible, otherwise the client should display an informative message on the screen stating the error and clean up the resources and then lead to termination.
## Program Inputs: 
- One command line argument that is the hostname or IP address of the server. 
- `Example - ./client localhost `
- Yes/No style questions from the user that are plain text (ASCII) format;
    - **Allowed characters:** A-Z, a-z, 0-9, punctuation & symbols, and whitespace.
    - **Allowed length:** 512 bytes

## Program Outuputs: 
- To work gracefully the client must print **informative error messages** on the screen if encountered any error.
- The client will also display the formatted response from the server as follows: 
Example Client Run Output Screen Format : 
Enter yout (yes/no) question : `<question>` - entered by user
Q: `"<question>"`                           - formatted question and response sent by server
R: `"<random possible response>"`



## Test Plan: 


| #  |   Test Case             | Description                                | Input                                     | Expected Output                           |
|----|-------------------------|--------------------------------------------|------------------------------------------ |-------------------------------------------| 
| 1  | **Server Unavailable**  | Start client without running the server    |./client localhost                         | `Connection error message displayed`      |
| 2  | **Wrong Port Number**   | Testing client on invalid port number "    |./client 1                                 |`Error message displayed`                  |
| 3  | **Valid Question**      | Testing normal working                     | `Will I get full grade on the assignment?`| `Q: "Will I get full grade on the assignment?"    R: "<random possible response>"`|

## Design Overview:
1. `Check if a command line argument has been passed` which is the hostname or IP adrress of the server, if not then print appropriate error message on the screen. 
2. `Create a socket` using socket() function, display an error message if socket creation fails and then exit.
3.  Using the specific port number `connect to the server` using connect() function, display an error message if connect() function fails, close the socket and exit.
4. `Ask the user a yes/no style question` and read the input from the user.
5. `Send the user response to the server` using send() function, if the send() fails display an error message on the screen, close the socket and exit.
6.  After sending `read the response ` sent by the server using recv() function (the message sent by the server includes the question sent by the client and randomly selcted response by the server)  display an error message if recv()    fails, close the socket and exit.
7. `Print the recieved message from the server` on the screen, close the socket using close() function and exit the program.

