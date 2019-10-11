# EE3D3 Project 1 <br />

My solution consists of three main files, (web-client.cpp, web-server.cpp, httpRequest.cpp). These
set up the basis for client-server interaction with HTTP functionality. My program requires some user
interaction, however only to showcase different aspects of my implementation or in attempt to
circumvent some issues I encountered. <br />
<br />
# Server <br />
I firstly set up my server by creating a socket. The bind, listen, fork and accept commands were used
to create a socket and listen for incoming connections. Upon connecting to a client with matching
host and port number, the server will connect and wait for a HTTP request from the client.
The request is parsed, using my ‘parseRequest’ function and then the ‘searchFile’ function searches
the directory for the requested file. The server will then return one of three possible responses to
the client, using the send() function.
• 200 OK – if the file is present, sending the file
• 404 Not Found - if the file is not present
• 400 Bad Request – if there is an error with the HTTP request
All the code that processes requests is essentially put in a while loop to demonstrate behaviour of a
persistent connection. i.e. The server will stay open and listening for requests over the same
connection.<br />
<br />

# Client <br />
Upon connecting to the server successfully, the client program will allow the user to input the HTTP
version they wish to use. The purpose of this is to demonstrate the ‘400 Bad Request’ functionality
of the server. Essentially setting the HTTP version to 1.1 will result in this error.
The client.cpp file will then interact with the httpRequest.cpp file to set and build a request in the
required format. Only the ‘GET’ method is implemented in my code. If a request is valid, the client
will receive the server’s response and store it in a file called ‘receiveFile.html’ which will be reset
each time the program is run. The file is also displayed in the terminal window. At this point, the
user is then asked if they wish to make another request, specifying a new file to search for, under
the same host and port number.<br />
