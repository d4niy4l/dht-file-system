### DISTRIBUTED HASH TABLE (IPFS)

# INTRODUCTION
The task was to simulate the working of a distributed hash table in an IPFS, where there are multiple machines and the request to store and access files can come at any machine, on the system. The system further uses robust data structures like B-Trees and Routing Tables, to provide for fast lookup, and storage. The data is spread across different machines based on their ids in the identifier space, and the machines leave gracefully.

# PROCEDURE:
The first approach towards building the system was identifying the flow of data and coming up with a list of necessary data structures, which were: 
-	Circular Linked List – for making a circular linked list of machines
-	Doubly Linked List – for making routing tables
-	B-Tree – for storing filepaths
-	Bigint – for storing hashes

Several other data structures were also required in order to simplify common operations:
-	Vector class is used for efficient management of dynamic memory
-	LinkedList for storing duplicates
-	Key_Pair 
-	File

Firstly, all the data structures were coded up, ready to be integrated. It was integral to ensure that all data structures worked properly so no errors came afterwards.

# Implementation:
During the implementation of the code, we used softwares like Git and GitHub to stay updated to the latest state of the project. We used Graphiz to visualize complex data structures like B-Trees. Setting up the Routing tables and the routing mechanism between the nodes was a challenging part, but we came up with a decent solution and tested it several times. The menu was added as a neat interface for the user, to provide options for different operations provided by the system and to observe things as they happen on the go. The system was tested to store different filetypes on different machines and on variable identifier space too. 

# Contribution
The contribution amongst the team members was extraordinary. With time we were all able to understand each other’s code better and came up with better practices for naming conventions, etc.
Conclusion:
The system made offered a decentralized system for storing files and provided faster search results.  


## Getting Started

# 1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/your-project.git
   ```
# 2. Open the project in Visual Studio:

Open Visual Studio.
```
File -> Open -> Project/Solution.
```
Navigate to the cloned repository and open the solution file (.sln).

# 3. Build the project:

Build the solution by clicking on the Build menu and selecting Build Solution.

# 4. Run the project:

Set the startup project if needed.
Press F5 or click on the Run button to execute the program.

