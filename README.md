# webserver
HTTP server writed in C using POSIX sockets

# How to use it?

Just put your shitty frontend page into static and use make && make run to start server 

# EXAMPLE
```bash
git clone https:/github.com/makar10l/webserver
cd webserver
rm -rf static # if you wanna not start server with my static
cp -r ~/static webserver/
make
make run
```

# TODO: 
1. Normal static files parser
2. JSON settings
3. Multithearding(maybe)

# Special thanks
Robotron(just cool guy)