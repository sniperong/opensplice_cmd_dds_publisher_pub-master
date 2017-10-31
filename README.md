# boilerplates
This package contains the default template for running a generic Pub/Sub program code

# The following Prismtech folders are required to be present before generating the codes
1. examples folder
2. include folder
3. lib folder

# Adding new IDL file:

1. Add your own idl file in the idl folder, the generated code files would be stored in a created directory with the idl name follow by an underscore 'Build'.
2. Generate the codes by call the vortexddsgen.sh
    
This script will auto:
- Generate the DDS codes for the idl files you have created. 
- Generate Pub/Sub codes using boilerplates specific to the message type so you can start running the program.
- Generate the makesfiles to compile the codes to executable.

#Samples folder
It contains the working examples of the idl file tested for verification purpose.
