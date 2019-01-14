#include <stdio.h>
#include <libserialport.h>

struct sp_port *port;
struct sp_port **ports;

void open_port(char *port_to_use, int baudrate);
void parse_serial_data(char *byte_buffer, int byte_number); 
void print_list_ports(void);

int main(void) {
	sp_list_ports(&ports);
	print_list_ports();

	int selected_port, baudrate;
	printf("Select port to use: ");
	scanf("%d", &selected_port);
	printf("Enter baudrate to use: ");
	scanf("%d", &baudrate);

	open_port(sp_get_port_name(ports[selected_port]), baudrate);

    while(1) {
        int bytes_waiting = sp_input_waiting(port);
        if (bytes_waiting > 0) {
            char byte_buffer[512];
            int byte_number = sp_nonblocking_read(port, byte_buffer, 512);
            parse_serial_data(byte_buffer, byte_number);
        }
        fflush(stdout);
    }
    sp_close(port);
	
	return 0;
}

void open_port(char *port_to_use, int baudrate) {
	enum sp_return error = sp_get_port_by_name(port_to_use, &port);
	if (error == SP_OK) {
		error = sp_open(port, SP_MODE_READ);
		if (error == SP_OK) {
			sp_set_baudrate(port, baudrate);
		}
	}
}

void print_list_ports(void) {
	for (int i = 0; ports[i]; i++) {
		printf("Found port [%d]: '%s'\n", i, sp_get_port_name(ports[i]));
	}
}

void parse_serial_data(char *byte_buffer, int byte_number) {
    for (int i = 0; i < byte_number; i++){
        printf("%c", byte_buffer[i]);
    }
}
