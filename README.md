# Web Server
HTTP server writed in C using POSIX sockets

# How to use it?

Just put your shitty frontend page into static and use make && make run to start server
P.S in your frontend every fucking references(to css or js) must to be writed relatively http request like domen is http:/localhost:8000/hello_page in fronted must be writed 
```HTML
WRITE THIS BULLSHIT
```

# EXAMPLE
```bash
git clone https:/github.com/makar10l/webserver
cd webserver
cp -r ~/static webserver/user_static #DONT TOUCH(pls) static FOLDER THERE ARE SYSTEM FILES
make
make run
```

# TODO: 
1. Normal static files parser
2. JSON settings
3. Multithearding(maybe)

# Special thanks
Robotron(just cool guy)
