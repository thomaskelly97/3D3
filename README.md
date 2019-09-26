# 3D3
Networking &amp; Socket Programming Projects

**Client - Server with HTTP Abstraction** <br />
This project involved creation of Client and Server applications, with incorporated HTTP Abstraction. <br />
All applications were created in C++ with no additional specialised libraries. Additional features were added as follows: <br />
- Transfer of traffic between client and server 
- Server ability to handle multiple concurrent client connections 
- HTTP Responses 404, 200, 400  

**Router Communications involving the Distance Vector Algorithm** <br />
This was a group project, involving the creation of a functional router network. The network would be generated based on <br />
router names, connections and path costs listed in a txt file which was read and processed accordingly. <br />
The routers would then generate and begin to transfer Distance Vector Tables (routing tables) which enabled them to 'converge' and discover the optimal paths of least cost to all other routers in the network. <br /> 
Upon converging, the user could then inject a message to the network which would the be forwarded appropriately along the path <br />
of least cost to the specified destination. <br />
- The project can be run by running the './start-router' command, which runs a shell script building the network. 
- Indivdual routers can be run by using './my-router' 
- Note: This project is geared towards use on a linux machine with x-term installed. 
