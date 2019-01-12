#include <stdio.h>
#include <libserialport.h>
#include <stdbool.h>

//declare global variables

char *port_to_use = "";
struct sp_port *port;
struct sp_port **ports;

//function prototypes

struct sp_port** list_ports(void);
void open_port(char *port_to_use, struct sp_port *port, int baudrate); 
void parse_serial_data(char *byte_buffer, int byte_number); 

//main function

int main(void) {
	int baudrate, selected_port;
	//get list of ports
	ports = list_ports();
	//select port
	printf("Select port with num key: ");
	scanf("%d", &selected_port);
	//assign selected_port variable with string of port
	printf("You have chosen to use port %s\n", sp_get_port_name(ports[selected_port]));
	port_to_use = sp_get_port_name(ports[selected_port]);
	//enter baud rate to communicate
	printf("Enter baud rate: ");
	scanf("%d", &baudrate);
	//open port
	open_port(port_to_use, port, baudrate);
	return 0;
}

void parse_serial_data(char *byte_buffer, int byte_number) {
	//parses serial data by reading ascii values from the buffer and printing to stdio as char
	for (int i = 0; i < byte_number; i++){
		printf("%c", byte_buffer[i]);
	}
}

struct sp_port** list_ports(void) {
	//returns an array of pointers of ports available on system. Otherwise returns error 0 
	int i;
	//local decleration of structure to hold array
	struct sp_port **ports;
	//library function call to populate local array of structures
	enum sp_return error = sp_list_ports(&ports);
	//error checking to ensure nothing has gone wrong with the above function call
	if (error == SP_OK) {
		for (i = 0; ports[i]; i++) {
			//print all found ports on local system
			printf("Found port [%d]: '%s'\n", i, sp_get_port_name(ports[i]));
		}
		//return array of pointers to ports found and free the ports
		return ports;
		sp_free_port_list(ports);
	} else {
		//if no ports found or there is an error let user know
		printf("No serial devices detected\n");
	}
	return 0;
}

void open_port(char * port_to_use, struct sp_port *port, int baudrate) {
	//open port and return error if there is an issue
	enum sp_return error = sp_get_port_by_name(port_to_use, &port);
	//check return of opening port
	if (error == SP_OK) {
		error = sp_open(port, SP_MODE_READ);
		//if port opens ok set desired baud rate
		if (error == SP_OK) {
			sp_set_baudrate(port, baudrate);
			//inform to stdio that port is open and available for use
			printf("Device %s open for comms at %d baud rate.\n", port_to_use, baudrate); 	
	//permanent loop to read serial data	
	while(true) {
		//library function to see if data is incoming	
        int bytes_waiting = sp_input_waiting(port);
		//if data is incoming set buffer, read buffer on port and pass to parse function
        if (bytes_waiting > 0) {
			char byte_buffer[512];
			int byte_number = sp_nonblocking_read(port, byte_buffer, 512);
			parse_serial_data(byte_buffer, byte_number);
        }
		//flush the output buffer of the stream on the port
        fflush(stdout);
	}
	//if loop exits close the port (this should never happen!)
	sp_close(port);
		} else {
			//if unable to open serial device
			printf("Error opening serial device\n");
		}
	} else {
		//if unable to find the serial device
		printf("Error finding serial device\n");
	}
}
