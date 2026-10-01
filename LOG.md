## 2026-09-29
- Did: finished Step 0 (compiler, git, GitHub, project folder, first push) and Step 1 (terminal mini-Redis with SET/GET/DEL, case-insensitive commands, error handling, refactored into a Database class).
- Stuck on:
  - Blank line printed two errors. Fixed by skipping the command checks after the error (else / guard clause).
  - Ctrl+D caused an infinite loop. getline returns the stream, which is false on EOF, so break when it fails.
  - Created the istringstream before getline, so it copied an empty string. Streams copy the string when they're constructed.
  - Defined handle() as a free function. Member functions defined outside the class need Database::.
- Decisions: SET reads the rest of the line as the value, so values can have spaces. Real Redis needs quotes for this; RESP will handle it in Step 5.
- Next: Step 2, read Beej's guide ch. 1 to 5 and answer the four socket questions here.

## 2026-09-30
- What do socket(), bind(), listen(), and accept() each do?:
  - socket() → Creates a socket and returns a file descriptor (int).
  - bind() → Assigns the socket an IP address and port.
  - listen() → Marks the socket as a passive listening socket, ready to receive connection requests.
  - accept() → Waits for a client to connect and returns a new socket file descriptor for communicating with that client.
- What is a port, and why does Redis use 6379?:
  - A port is a number that identifies a specific network service running on a computer.
  - An IP address identifies which computer, while the port identifies which service/program.
  - Redis uses port 6379 by default as a convention. Redis doesn't inherently require 6379; you can configure it to use another port.
- What does accept() return, and why is it a different socket from the one you listened on?:
  - accept() returns an int file descriptor for a new socket
  - server_fd remains the listening socket.
  - client_fd is used to communicate with that specific client.
  - This allows the server to keep using server_fd to accept additional clients.
- What do send() and recv() do, and why might recv() return less data than you expected?:
  - send() sends bytes through a connected socket
  - recv() reads bytes recieved from the other side
  - might be fewer bytes than expected because TCP is a byte stream, not a message system --> One send() does not necessarily equal one recv()
  - For example, if a client sends 100 bytes, one recv() might only give you 50 bytes, and you may need to call recv() again to get the rest
- Extras: 
  - recv() can also give you more than one message. If a client sends two commands quickly, one recv() might return both glued together. So you can't treat one recv() as one command. You'll need to save bytes in a buffer and split them on \n yourself.
  - recv()'s return value tells you important things: 0 means the client disconnected, and -1 means an error. That's how your server will notice when nc closes.
  - send() can send less than you asked, too. It returns how many bytes actually went out. For small replies it'll almost always send everything, but good to know.
  - listen() takes a "backlog" number: how many pending connections can wait in line before accept() gets to them.
- Next: Step 3: socket, bind, listen, accept on port 6379 and print "someone connected"




