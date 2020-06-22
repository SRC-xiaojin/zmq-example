# zmq-example
example of cppzmq

you should refer https://github.com/zeromq/cppzmq to install libzmq and cppzmq.

firstly,run sub client
./zmq -e sub -n 100000

secondly, run pub server
./zmq -e pub -n 100000
