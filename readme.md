# MySerial 

This is a simple c program that runs a command line usb serial bus monitor

## Getting Started

You will need the libserialport library and of course some serial devices connected to your machine

### Prerequisites

This project relies on the external libserialport library

* [libserialport](https://sigrok.org/wiki/Libserialport)

### Installing

First of all download the libserialport library an compile for your machine

once installed you can run the make file of myserial to create a commandline executable called myserial

you can then run myserial using the complete path or ./myserial

## Running myserial 

On running myserial you will be shown a list of valid serial bus ports

Select the relevant number for the port you wish to read

You will then be asked to set the baud rate of the port, any board rate can be entered here as long as it is the same as the serial bus transmitter

## Deployment

This has been tested on mac os x only. It should work on other machines however no tests have yet been performed

## Built With

* [GCC](http://gcc.gnu.org) - The compiler used

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

Only one version exists so far!

## Authors

* **John Hopkins** - *Initial work* - [johnhopkins.co.uk](https://www.johnhopkins.co.uk)

See also the list of [contributors](https://github.com/johnhopkins/myserial/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to sigrok for the excellent library, without which none of this would have been possible 
* Thanks too to the Arduino project, that got me interested in this kind of thing 
