#include <stdio.h>
#include <libserialport.h>

struct sp_port *port;
struct sp_port **ports;

void open_port(char *port_to_use, int baudrate);
void open_port_to_write(char *port_to_use, int baudrate);
void parse_serial_data(char *byte_buffer, int byte_number); 
void write_serial(void);
void read_serial(void);
void print_list_ports(void);

int main(void) {
	sp_list_ports(&ports);
	print_list_ports();

	int selected_port, baudrate, readwrite;
	printf("Select port to use: ");
	scanf("%d", &selected_port);
	printf("Enter baudrate to use: ");
	scanf("%d", &baudrate);
	printf("Would you like to read[0] or write[1] serial data?: ");
	scanf("%d", &readwrite);

	if (readwrite == 0) {
		open_port(sp_get_port_name(ports[selected_port]), baudrate);
		read_serial();
	}

	if (readwrite == 1) {
		open_port_to_write(sp_get_port_name(ports[selected_port]), baudrate);
		write_serial();
	}
    sp_close(port);

	return 0;
}

void write_serial(void) {
	while(1) {
		char buffer[] = "";
		scanf("%s", buffer);
		sp_nonblocking_write(port, buffer, 100);
	}
}

void read_serial(void) {
    while(1) {
        int bytes_waiting = sp_input_waiting(port);
        if (bytes_waiting > 0) {
            char byte_buffer[512];
            int byte_number = sp_nonblocking_read(port, byte_buffer, 500);
            parse_serial_data(byte_buffer, byte_number);
        }
        fflush(stdout);
    }
}

void open_port_to_write(char *port_to_use, int baudrate) {
	enum sp_return error = sp_get_port_by_name(port_to_use, &port);
	if (error == SP_OK) {
		error = sp_open(port, SP_MODE_WRITE);
		if (error == SP_OK) {
			sp_set_baudrate(port, baudrate);
		}
	}
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
