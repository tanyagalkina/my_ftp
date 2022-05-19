# MY FTP
Creating an [FTP Server](https://de.wikipedia.org/wiki/File_Transfer_Protocol) from scratch in C.
[RFC959](https://datatracker.ietf.org/doc/html/rfc959) compliant.
<br>

## Build
```sh
$> make
```

<br>

## USAGE
```sh
$> ./myftp –help
USAGE: ./myftp port path
	port is the port number on which the server socket listens
	path is the path to the home directory for the Anonymous user
```